//
// Created by hegkr3 on 2026. 04. 30..
//

#ifndef CLIONGRAPHICSKIT_BUTTON_HPP
#define CLIONGRAPHICSKIT_BUTTON_HPP
#include <functional>

#include "Application.hpp"
#include "graphics.hpp"
#include "widget.hpp"


class Button : public widget {
    protected:
    std::function<void()> onClick;
    std::function<void()> onHover;
    std::function<void()> onLeave;
    std::string label;
    bool hovered = false;

    public:
    Button(Application* parent, int x, int y, int w, int h,
             std::string label,
           std::function<void()> click = nullptr,
           std::function<void()> hover = nullptr,
           std::function<void()> leave = nullptr
          );

    void draw() override;
    void handle(genv::event ev) override;
    std::string getValue() const override { return ""; }
};

#endif //CLIONGRAPHICSKIT_BUTTON_HPP