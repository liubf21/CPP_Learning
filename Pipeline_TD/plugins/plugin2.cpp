#include "plugin_interface.hpp"
#include <memory>
#include <chrono>
#include <thread>
#include <functional>

class MyPlugin2 : public PluginInterface
{
public:
    MyPlugin2() : m_interval(0), m_isRunning(false) {}

    std::string getName() const override
    {
        return "定期执行功能";
    }

    void execute(ScoreSheet<int> *scoreSheet) override
    {
        // check if the function is running
        if (m_isRunning)
        {
            std::cout << "功能正在执行中...是否停止执行(y/n)" << std::endl;
            std::string choice;
            std::cin >> choice;
            if (choice == "y")
            {
                m_isRunning = false;
                std::cout << "功能已停止执行" << std::endl;
            }

            return;
        }

        // plugin function: execute a function periodically
        int interval;
        std::cout << "请输入定期执行的时间间隔(秒): ";
        std::cin >> interval;
        setInterval(interval);

        std::cout << "请输入定期执行的功能编号: " << std::endl;
        std::cout << "a. 查询科目最高/最低分" << std::endl;
        std::cout << "b. 以各科成绩对同学姓名排序" << std::endl;
        std::cout << "c. 查询各科目平均分" << std::endl;

        std::string choice;
        std::cin >> choice;

        std::function<void()> callback;

        if (choice == "a")
        {
            std::cout << "请输入科目名称：";
            std::string subject;
            std::cin >> subject;
            callback = [scoreSheet, subject]()
            { scoreSheet->checkScore_1(subject); };
        }
        else if (choice == "b")
        {
            callback = [scoreSheet]()
            { scoreSheet->checkScore_2(); };
        }
        else if (choice == "c")
        {
            callback = [scoreSheet]()
            { scoreSheet->checkScore_3(); };
        }
        else
        {
            std::cout << "输入错误！" << std::endl;
            return;
        }

        start(callback); // start the periodic execution, there can be no input in callback

        std::cout << "定期执行功能已启动(再次调用则停止执行)" << std::endl;
    }

private:
    int m_interval;
    bool m_isRunning;

    void setInterval(int interval)
    {
        m_interval = interval;
    }

    void start(std::function<void()> callback)
    {
        m_isRunning = true;
        std::thread([this, callback]()
                    {
            while (m_isRunning) {
                callback();
                std::this_thread::sleep_for(std::chrono::seconds(m_interval));
            } })
            .detach();
    }

    void stop()
    {
        m_isRunning = false;
    }
};

extern "C" PluginInterface *createPlugin()
{
    return new MyPlugin2();
}

extern "C" void destroyPlugin(PluginInterface *plugin)
{
    delete plugin;
}