//
// Created by heged on 5/15/2026.
//
#include "Application.hpp"
#include "Screen.hpp"
using namespace genv;

Screen::Screen(Application* parent, int x, int y, int meret, int cella)
    : widget(parent, x, y, meret * cella, meret * cella), _meret(meret), _cella(cella) {
    _tabla.resize(_meret, std::vector<Mezo>(_meret, URES));
}

void Screen::draw() {
    gout << move_to(x-2, y-2) << color(80, 80, 80) << box(w+4, h+4);

    for (int s = 0; s < _meret; s++) {
        for (int o = 0; o < _meret; o++) {
            int cx = x + o * _cella;
            int cy = y + s * _cella;

            gout << move_to(cx, cy) << color(180, 180, 180) << box(_cella, _cella);
            gout << move_to(cx + 1, cy + 1) << color(255, 255, 255) << box(_cella - 2, _cella - 2);

            // Jelek kirajzolása
            if (_tabla[s][o] == X_JEL) {
                gout << color(200, 0, 0);
                for(int i=-1; i<=1; i++) {
                    gout << move_to(cx + 6 + i, cy + 6) << line(_cella - 12, _cella - 12);
                    gout << move_to(cx + _cella - 6 + i, cy + 6) << line(-(_cella - 12), _cella - 12);
                }
            } else if (_tabla[s][o] == O_JEL) {
                gout << color(0, 0, 150);
                gout << move_to(cx + 8, cy + 8) << box(_cella - 16, _cella - 16);
                gout << move_to(cx + 10, cy + 10) << color(255, 255, 255) << box(_cella - 20, _cella - 20);
            }
        }
    }
}

void Screen::handle(event ev) {
    if (ev.type == ev_mouse && ev.button == btn_left) {
        int o = (ev.pos_x - x) / _cella;
        int s = (ev.pos_y - y) / _cella;

        if (s >= 0 && s < _meret && o >= 0 && o < _meret) {
            // Jelzés a JatekMesternek
            _parent->action("lepes:" + std::to_string(s) + "," + std::to_string(o));
        }
    }
}

void Screen::reset() {
    for (auto &sor : _tabla) std::fill(sor.begin(), sor.end(), URES);
}