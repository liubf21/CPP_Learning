#include "plugin_interface.hpp"
#include <memory>

class MyPlugin1 : public PluginInterface
{
public:
    std::string getName() const override
    {
        return "查找缺省成绩";
    }

    void execute(ScoreSheet<int> *scoreSheet) override
    {
        // plugin function: find absent students
        auto absentStudents = scoreSheet->getAbsentStudents();
        for (auto &[subject, names] : absentStudents)
        {

            if (names.empty())
            {
                continue;
            }
            std::cout << "缺省" << subject << "成绩的有 " << std::endl;
            for (auto &name : names)
            {
                std::cout << name << " ";
            }
            std::cout << std::endl;
        }
    }
};

extern "C" PluginInterface *createPlugin()
{
    return new MyPlugin1();
}

extern "C" void destroyPlugin(PluginInterface *plugin)
{
    delete plugin;
}
