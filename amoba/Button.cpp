//
// Created by hegkr3 on 2026. 04. 30..
//

#include "Button.hpp"
using namespace genv;
Button::Button(Application* parent, int x, int y, int w, int h,
               std::function<void()> click,
               std::function<void()> hover,
               std::function<void()> leave)
    : widget(parent,x,y,w,h), onClick(click), onHover(hover), onLeave(leave) {}

void Button::draw() {
   gout<<move_to(x,y)<<genv::color(230,230,230)<<box(w,h);
   gout << move_to(x, y) << color(0,0,0) << line(w, 0);


   gout << move_to(x, y) << line(0, h);


   gout << move_to(x + w, y) << line(0, h);


   gout << move_to(x, y + h) << line(w, 0);
}

void Button::handle(genv::event ev) {

   bool inside = ev.pos_x >= x && ev.pos_x <= x + w &&
                 ev.pos_y >= y && ev.pos_y <= y + h;

   if (ev.type == ev_mouse) {

      // hover enter
      if (inside && !hovered) {
         hovered = true;
         if (onHover) onHover();
      }

      // hover leave
      if (!inside && hovered) {
         hovered = false;
         if (onLeave) onLeave();
      }

      // click
      if (inside && ev.button == btn_left) {
         if (onClick) onClick();
      }
   }
}