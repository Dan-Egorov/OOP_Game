#pragma once
#include "../status.hpp"

class Burning: public Status {
private:
    int turnsLeft;
    int damage;
public:
    Burning(int turns = 1, int dam = 1);

    StatusType getType() const override;

    std::string getName() const override;

    void apply(Robot& bot) override;
    void remove(Robot& bot) override;
    void merge(const Status& other) override;
    void tick(Robot& bot) override;
    bool isExpired() const override;
};