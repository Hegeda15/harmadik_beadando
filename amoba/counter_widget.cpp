//
// Created by heged on 4/14/2026.
//

#include "counter_widget.hpp"
using namespace genv;


counter_widget::counter_widget(Application*parent,int x, int y, int w, int h, int min, int max)
    : widget(parent,x,y,w,h), min(min), max(max)
{
    value = min;
}
void counter_widget::draw() {
    genv::canvas can(w, h);
    int btn_w = 20;
    int btn_h = h / 2;


    can << move_to(0, 0) << color(220, 220, 220) << box(w, h);


    can << move_to(5, h / 2 + 7) << color(0, 0, 0) << text(std::to_string(value));


    can <<move_to(w - btn_w, 0) << color(200, 200, 200) << box(btn_w, btn_h);


    can << move_to(w - btn_w + 3, btn_h - 5) <<color(0, 0, 0) << text("/\\");


    can << move_to(w - btn_w, btn_h) << color(180, 180, 180) << box(btn_w, btn_h);


    can << move_to(w - btn_w + 3, h - 5) << color(0, 0, 0) << text("\\/");


    can << move_to(w - btn_w, 0) << color(0,0,0) << line(0, h);
    can << move_to(w - btn_w, btn_h) << line(btn_w, 0);


    gout << stamp(can, x, y);
}


void counter_widget::handle(event ev)
{
    if (ev.type == ev_mouse && ev.button == btn_left)
    {
        if (ev.pos_x >= x && ev.pos_x <= y + w &&
            ev.pos_y >= y && ev.pos_y <= y + h)
        {
            //gombok
            if (ev.pos_x > x + w - 20 &&
                ev.pos_y < y + h/2)
            {
                value++;
            }

            else if (ev.pos_x > x + w - 20 &&
                     ev.pos_y >= y + h/2)
            {
                value--;
            }

            if (value < min) value = min;
            if (value > max) value = max;
        }
    }
    if (ev.type == ev_key) {
        if (ev.keycode == key_up) value++;
        if (ev.keycode == key_down) value--;
        if (ev.keycode == key_pgup) value += 10;
        if (ev.keycode == key_pgdn) value -= 10;


        if (value < min) value = min;
        if (value > max) value = max;
    }
}
int counter_widget::getIntValue() const {
    return value;
}
std::string counter_widget::getValue() const
{
    return std::to_string(value);
}

