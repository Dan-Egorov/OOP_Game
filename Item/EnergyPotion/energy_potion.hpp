#pragma once
#include "../item.hpp"

class EnergyPotion : public Item {
public:
    std::string getName() const override;
    void use(Robot& bot) override;
};