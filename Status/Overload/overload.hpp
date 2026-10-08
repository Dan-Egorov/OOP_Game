#pragma once
#include "../status.hpp"

class Overload: public Status {
private:
    bool needExit = false;
public:
    StatusType getType() const override;

    std::string getName() const override;


    void apply(Robot& bot) override;
    void remove(Robot& bot) override;
    void merge(const Status& other) override;
    void tick(Robot& bot) override;
    bool isExpired() const override;
};
