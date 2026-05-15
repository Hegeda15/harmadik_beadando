#include "input_widget.hpp"

using namespace genv;

input_widget::input_widget(Application* parent,
                           int x,
                           int y,
                           int w,
                           int h)
    : widget(parent, x, y, w, h),
      focused(false),
      cursorPos(0),
        text("")
{
}

void input_widget::draw()
{
    // háttér
    gout << move_to(x, y)
         << color(255,255,255)
         << box(w, h);

    // keret
    if (focused)
        gout << color(0,120,255);
    else
        gout << color(100,100,100);

    // felső
    gout << move_to(x,y)
         << line(w,0);

    // jobb
    gout << move_to(x+w,y)
         << line(0,h);

    // alsó
    gout << move_to(x+w,y+h)
         << line(-w,0);

    // bal
    gout << move_to(x,y+h)
         << line(0,-h);

    // szöveg
    gout << move_to(x + 5,
                     y + h/2 + gout.cascent()/2 - 2)
         << color(0,0,0);


    // kurzor
    if (focused) {

        int cursorX =
            x + 5 +
            gout.twidth(text.substr(0, cursorPos));

        gout << move_to(cursorX,
                        y + 5)
             << color(0,0,0)
             << line(0,h - 10);
    }
}

void input_widget::handle(event ev)
{
    // fókusz
    if (ev.type == ev_mouse &&
        ev.button == btn_left)
    {
        focused =
            ev.pos_x >= x &&
            ev.pos_x <= x + w &&
            ev.pos_y >= y &&
            ev.pos_y <= y + h;
    }

    // billentyűzet
    if (focused && ev.type == ev_key)
    {
        // backspace
        if (ev.keycode == key_backspace)
        {
            if (!text.empty() &&
                cursorPos > 0)
            {
                text.erase(cursorPos - 1, 1);
                cursorPos--;
            }
        }

        // bal nyíl
        else if (ev.keycode == key_left)
        {
            if (cursorPos > 0)
                cursorPos--;
        }

        // jobb nyíl
        else if (ev.keycode == key_right)
        {
            if (cursorPos < text.size())
                cursorPos++;
        }

        // normál karakter
        else if (ev.keycode >= 32 &&
                 ev.keycode <= 126)
        {
            text.insert(cursorPos,
                        1,
                        char(ev.keycode));

            cursorPos++;
        }
    }
}

std::string input_widget::getValue() const
{
    return text;
}

void input_widget::setValue(const std::string& value)
{
    text = value;
    cursorPos = text.size();
}