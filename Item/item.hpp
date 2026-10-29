#pragma once
#include <string>

class Robot;

class Item {
public:
    virtual ~Item() = default;

    virtual std::string getName() const = 0;
    virtual void use(Robot& bot) = 0;
};