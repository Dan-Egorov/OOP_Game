#pragma once
#include <string>

class Robot;

enum StatusType {
    Slow_st,
    Overload_st,
    Burning_st,
    Shield_st
};

class Status {
public:
    virtual ~Status() = default;

    virtual StatusType getType() const = 0;

    virtual std::string getName() const = 0;

    virtual void apply(Robot& bot) = 0;
    virtual void remove(Robot& bot) = 0;
    virtual void merge(const Status& other) = 0;
    virtual void tick(Robot& bot) = 0;
    virtual bool isExpired() const = 0;
};