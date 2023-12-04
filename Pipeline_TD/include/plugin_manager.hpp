#pragma once
#include "plugin_interface.hpp"
#include <iostream>
#include <string>
#include <map>
#include <memory>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif


// plugin manager interface
class PluginManager
{
public:
    virtual bool loadPlugin(const std::string &pluginPath) = 0;
    virtual bool unloadPlugin(const std::string &pluginPath) = 0;
};

// plugin manager implementation
class PluginManagerImpl : public PluginManager
{
public:
    PluginManagerImpl() = default;
    PluginManagerImpl(const PluginManagerImpl &other) = delete;
    PluginManagerImpl(PluginManagerImpl &&other) = delete;
    PluginManagerImpl &operator=(const PluginManagerImpl &other) = delete;
    PluginManagerImpl &operator=(PluginManagerImpl &&other) = delete;
    ~PluginManagerImpl() = default;

    bool loadPlugin(const std::string &pluginPath) override;
    bool unloadPlugin(const std::string &pluginPath) override;
    void unloadAllPlugins();
    PluginInterface *getPlugin(const std::string &pluginName) const;
    std::map<std::string, PluginInterface *> getPlugins() const;
    void run();

private:
    std::map<std::string, std::string> m_pluginNames; // plugin path -> plugin name
    std::map<std::string, void *> m_pluginHandles; // plugin path -> plugin handle
    std::map<std::string, PluginInterface *> m_plugins; // plugin name -> plugin instance
};

bool PluginManagerImpl::loadPlugin(const std::string &pluginPath)
{
    // load plugin
    if (m_pluginHandles.find(pluginPath) != m_pluginHandles.end())
    {
        std::cerr << "Plugin already loaded: " << pluginPath << std::endl;
        return false;
    }

    #ifdef _WIN32
    HINSTANCE pluginHandle = LoadLibrary(pluginPath.c_str());
    if (!pluginHandle)
    {
        std::cerr << "Error loading plugin: " << GetLastError() << std::endl;
        return false;
    }

    // get plugin factory function
    auto getPluginFunc = reinterpret_cast<PluginInterface *(*)()>(GetProcAddress(pluginHandle, "createPlugin"));
    if (!getPluginFunc)
    {
        std::cerr << "Error loading symbol: " << GetLastError() << std::endl;
        return false;
    }

    #else // Unix
    void *pluginHandle = dlopen(pluginPath.c_str(), RTLD_LAZY);
    if (!pluginHandle)
    {
        std::cerr << "Error loading plugin: " << dlerror() << std::endl;
        return false;
    }

    auto getPluginFunc = reinterpret_cast<PluginInterface *(*)()>(dlsym(pluginHandle, "createPlugin"));
    if (!getPluginFunc)
    {
        std::cerr << "Error loading symbol: " << dlerror() << std::endl;
        return false;
    }
    #endif

    // create plugin instance
    std::unique_ptr<PluginInterface> plugin(getPluginFunc());
    if (!plugin)
    {
        std::cerr << "Error creating plugin" << std::endl;
        return false;
    }

    std::cout << "Loaded plugin: " << pluginPath << std::endl;
    std::cout << "Plugin name: " << plugin->getName() << std::endl;

    // save plugin instance
    m_pluginNames[pluginPath] = plugin->getName();

    m_pluginHandles[pluginPath] = pluginHandle;

    m_plugins[m_pluginNames[pluginPath]] = plugin.release(); // release ownership of plugin instance

    return true;
}

bool PluginManagerImpl::unloadPlugin(const std::string &pluginPath)
{
    // unload plugin
    if (m_pluginHandles.find(pluginPath) == m_pluginHandles.end())
    {
        std::cerr << "Plugin not loaded: " << pluginPath << std::endl;
        return false;
    }

    // get plugin handle and instance
    auto pluginHandle = m_pluginHandles[pluginPath];
    auto plugin = m_plugins[m_pluginNames[pluginPath]];

    #ifdef _WIN32
    // get plugin destroy function
    HMODULE moduleHandle = static_cast<HMODULE>(pluginHandle); // 在Windows平台下，HMODULE和void*是等价的，可以直接将pluginHandle强制转换为HMODULE类型
    auto destroyPluginFunc = reinterpret_cast<void (*)(PluginInterface *)>(GetProcAddress(moduleHandle, "destroyPlugin"));
    // auto destroyPluginFunc = reinterpret_cast<void (*)(PluginInterface *)>(GetProcAddress(pluginHandle, "destroyPlugin"));
    if (!destroyPluginFunc)
    {
        std::cerr << "Error loading symbol: " << GetLastError() << std::endl;
        return false;
    }

    // unload plugin
    destroyPluginFunc(plugin);
    FreeLibrary(moduleHandle);

    #else
    auto destroyPluginFunc = reinterpret_cast<void (*)(PluginInterface *)>(dlsym(pluginHandle, "destroyPlugin"));
    if (!destroyPluginFunc)
    {
        std::cerr << "Error loading symbol: " << dlerror() << std::endl;
        return false;
    }

    destroyPluginFunc(plugin);
    dlclose(pluginHandle);
    #endif

    // remove plugin instance ( order is opposite to creation )
    m_plugins.erase(m_pluginNames[pluginPath]);
    m_pluginHandles.erase(pluginPath);
    m_pluginNames.erase(pluginPath);

    std::cout << "Unloaded plugin: " << pluginPath << std::endl;
    return true;
}

void PluginManagerImpl::unloadAllPlugins()
{
    // unload all plugins
    std::vector<std::string> pathToRemove; // use vector to avoid iterator invalidation
    for (const auto &plugin : m_pluginNames)
    {
        pathToRemove.push_back(plugin.first);
    }

    for (const auto &path : pathToRemove)
    {
        unloadPlugin(path);
    }

    std::cout << "Unloaded all plugins" << std::endl;
}

PluginInterface *PluginManagerImpl::getPlugin(const std::string &pluginName) const
{
    // get plugin instance
    if (m_plugins.find(pluginName) == m_plugins.end())
    {
        std::cerr << "Plugin not loaded: " << pluginName << std::endl;
        return nullptr;
    }

    return m_plugins.at(pluginName);
}

std::map<std::string, PluginInterface *> PluginManagerImpl::getPlugins() const
{
    // get all plugin instances
    return m_plugins;
}
