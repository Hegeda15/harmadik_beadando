#ifndef CLIONGRAPHICSKIT_LISTBOX_WIDGET_HPP
#define CLIONGRAPHICSKIT_LISTBOX_WIDGET_HPP

#include "widget.hpp"
#include <vector>
#include <string>

class listBox_widget : public widget {
protected:
    std::vector<std::string> items;
    int selectedItemIndex;
    int scrollOffset;
    bool dragging;

public:
    listBox_widget(Application*parent,int x,int y,int w,int h,const std::vector<std::string>& items);

    virtual void draw() override;
    virtual void handle(genv::event ev) override;
    virtual std::string getValue() const override;

    virtual void csere();

    virtual void add(const std::string& value);
};

#endif