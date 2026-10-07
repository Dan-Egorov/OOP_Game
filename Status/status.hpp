#pragma once

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

    virtual void apply(Robot& bot) = 0;             // наложили
    virtual void remove(Robot& bot) = 0;            // снимаем
    virtual void merge(const Status& other) = 0;    // слияние
    virtual void tick(Robot& bot) = 0;              // каждый ход
    virtual bool isExpired() const = 0;             // пора удалить?
};