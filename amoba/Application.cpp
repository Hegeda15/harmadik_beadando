#include "application.hpp"
#include "graphics.hpp"
#include <iostream>
using namespace genv;


Application::Application() {
    _focus = -1;
}


void Application::register_widget(widget* w) {
    _widgets.push_back(w);
}

void Application::event_loop() {
    event ev;
    int screen_w = 800;
    int screen_h = 500;
    genv::gout.open(screen_w, screen_h);
    while (gin >> ev) {
        gout << move_to(0, 0) << color(240, 240, 240) << box(screen_w, screen_h);
        if (ev.type == ev_mouse && ev.button == btn_left) {
            _focus = -1;
            for (size_t i = 0; i < _widgets.size(); i++) {
                if (_widgets[i]->is_selected(ev.pos_x, ev.pos_y)) {
                    _focus = i;
                }
            }
        }


        if (ev.type == ev_mouse && (ev.button == btn_wheelup || ev.button == btn_wheeldown)) {
            for (widget* w : _widgets) {
                if (w->is_selected(ev.pos_x, ev.pos_y)) {
                    w->handle(ev);

                }
            }
        }

        else if (_focus != -1) {
            _widgets[_focus]->handle(ev);
        }

        if (ev.type == ev_key) {

            if (ev.keycode == 's' || ev.keycode == 'S') {

                action("save");
            }
            if (ev.keycode == 'a' || ev.keycode == 'A') {
                action("csere1");
            }
            if (ev.keycode == 'b' || ev.keycode == 'B') {
                action("csere2");
            }
        }


        gout << move_to(0, 0) << color(255, 255, 255) << box(screen_w, screen_h);
        for (widget* w : _widgets) {
            w->draw();
        }
        gout << refresh;
    }
}