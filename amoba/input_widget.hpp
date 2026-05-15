#ifndef INPUT_WIDGET_HPP
#define INPUT_WIDGET_HPP

#include "widget.hpp"
#include "graphics.hpp"
#include <string>

class input_widget : public widget {
protected:
    std::string text;
    bool focused;
    int cursorPos;

public:
    input_widget(Application* parent,
                 int x,
                 int y,
                 int w,
                 int h);

    virtual void draw() override;

    virtual void handle(genv::event ev) override;

    virtual std::string getValue() const override;

    virtual void setValue(const std::string& value);
};

#endif