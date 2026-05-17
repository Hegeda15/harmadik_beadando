//
// Created by hegkr3 on 2026. 04. 30..
//

#include "Button.hpp"
using namespace genv;
Button::Button(Application* parent, int x, int y, int w, int h,
               std::string label,
               std::function<void()> click,
               std::function<void()> hover,
               std::function<void()> leave
               )

    : widget(parent,x,y,w,h), onClick(click), onHover(hover), onLeave(leave), label(label) {}

void Button::draw() {
   if (hovered) gout << color(200, 200, 210);
   else gout << color(220, 220, 220);

   gout << move_to(x, y) << box(w, h)<<move_to(x+10,y+20)<<color(0,0,0)<<text(label);


   gout << color(0, 0, 0) << move_to(x, y) << line(w, 0) << line(0, h) << line(-w, 0) << line(0, -h);



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