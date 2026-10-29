#pragma once
#include "../status.hpp"

class AttackBuff : public Status {
private:
    int turnsLeft;
    int savedPower;
public:
    AttackBuff(int turns);

    StatusType getType() const override;
    std::string getName() const override;
    void apply(Robot& bot) override;
    void remove(Robot& bot) override;
    void merge(const Status& other) override;
    void tick(Robot&) override;
    bool isExpired() const override;
};