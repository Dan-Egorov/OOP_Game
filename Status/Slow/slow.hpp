#pragma once
#include "../status.hpp"

class Slow : public Status {
private:
    int turnsLeft;
    int savedSpeed = 0;
public:
    Slow(int turns = 1) : turnsLeft(turns) {}

    StatusType getType() const override { return Slow_st; }

    void apply(Robot& bot) override;
    void remove(Robot& bot) override;
    void merge(const Status& other) override;
    void tick(Robot& bot) override;
    bool isExpired() const override { return turnsLeft < 0; }
};