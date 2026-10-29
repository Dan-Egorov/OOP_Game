#pragma once
#include "../status.hpp"

class ItemPickup : public Status {
public:
    StatusType getType() const override { return ItemPickup_st; }
    std::string getName() const override { return "Item Pickup"; }
    void apply(Robot& bot) override;
    void remove(Robot&) override {}
    void merge(const Status&) override {}
    void tick(Robot&) override {}
    bool isExpired() const override;
};