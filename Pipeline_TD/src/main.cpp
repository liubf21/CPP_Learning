#include "scoresheet.hpp"
#include "plugin_manager.hpp"
#include <iostream>
#include <memory>
#include <string>

int main()
{
    // create score sheet
    auto scoreSheet = std::make_unique<ScoreSheet<int>>();

    // create plugin manager
    auto pluginManager = std::make_unique<PluginManagerImpl>();

    // load plugins
    #ifdef _WIN32
    pluginManager->loadPlugin("./plugins/myplugin1.dll");
    pluginManager->loadPlugin("./plugins/myplugin2.dll");
    #else
    pluginManager->loadPlugin("./plugins/libmyplugin1.dylib");
    pluginManager->loadPlugin("./plugins/libmyplugin2.dylib");
    #endif

    // get plugin names
    auto plugins = pluginManager->getPlugins();
    std::vector<std::string> pluginNames;
    for (auto& plugin : plugins)
    {
        pluginNames.push_back(plugin.second->getName());
    }

    while(scoreSheet->run()) // run score sheet, return false if user wants to exit, return true if user wants to use plugin
    {
        // show plugin menu
        std::cout << "拓展功能：" << std::endl;
        std::cout << "0. 退出" << std::endl;
        for (int i = 0; i < pluginNames.size(); ++i)
        {
            std::cout << i + 1 << ". " << pluginNames[i] << std::endl;
        }
        std::cout << "请输入功能编号：";
        int choice;
        std::cin >> choice;
        if (choice == 0)
        {
            break;
        }
        else if (choice > 0 && choice <= plugins.size())
        {
            plugins[pluginNames[choice - 1]]->execute(scoreSheet.get());
        }
        else
        {
            std::cout << "输入错误！" << std::endl;
        }
    }

    // unload plugins
    pluginManager->unloadAllPlugins();

    return 0;
}