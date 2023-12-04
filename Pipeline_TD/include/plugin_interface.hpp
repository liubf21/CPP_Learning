#pragma once
#include "scoresheet.hpp"
#include <string>

class PluginInterface {
public:
    virtual ~PluginInterface() = default;
    virtual std::string getName() const = 0;
    virtual void execute(ScoreSheet<int> *scoreSheet) = 0;
};