#pragma once
#include "../item.hpp"

class HealthPotion : public Item {
public:
    std::string getName() const override;
    void use(Robot& bot) override;
};