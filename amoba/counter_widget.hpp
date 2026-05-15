//
// Created by heged on 4/14/2026.
//

#ifndef CLIONGRAPHICSKIT_COUNTER_WIDGET_HPP
#define CLIONGRAPHICSKIT_COUNTER_WIDGET_HPP
#include "widget.hpp"
#pragma once


class counter_widget:public widget {
protected:
    int value;
    int max,min;

public:
    counter_widget(Application*parent,int x,int y,int h,int w,int min,int max);
    virtual void draw() override;
    virtual void handle(genv::event ev) override;

    int getIntValue() const;
    virtual std::string getValue() const override;

};


#endif //CLIONGRAPHICSKIT_COUNTER_WIDGET_HPP