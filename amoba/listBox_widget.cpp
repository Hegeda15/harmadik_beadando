#include "listBox_widget.hpp"
using namespace genv;

listBox_widget::listBox_widget(Application*parent,int x, int y, int w, int h, const std::vector<std::string>& items)
    : widget(parent,x,y,w,h), items(items)
{
    selectedItemIndex = 0;
    scrollOffset = 0;
    dragging = false;
}

void listBox_widget::draw()
{
    int lineHeight = 20;
    int maxVisible = h / lineHeight;


    gout << move_to(x, y)
         << color(220,220,220)
         << box(w, h);


    gout << move_to(x, y)
         << color(0,0,0)
         << line(w,0) << line(0,h) << line(-w,0) << line(0,-h);

    // elemek
    for (int i = 0; i < maxVisible; i++)
    {
        int actualIndex = i + scrollOffset;
        if (actualIndex >= items.size()) break;

        int itemY = y + i * lineHeight;

        if (actualIndex == selectedItemIndex)
        {
            gout << move_to(x+1, itemY+1)
                 << color(150,150,255)
                 << box(w-2, lineHeight-2);
        }

        gout << move_to(x + 5, itemY + lineHeight - 5)
             << color(0,0,0)
             << text(items[actualIndex]);
    }

    // scrollbar
    if (items.size() > 0)
    {
        int scrollW = 15;
        int scrollX = x + w - scrollW;

        int visible = maxVisible;
        double ratio = (double)visible / items.size();
        if (ratio > 1.0) ratio = 1.0;

        int scrollH = ratio * h;
        if (scrollH < 20) scrollH = 20;

        double scrollMove = 0;
        if (items.size() > visible)
        {
            scrollMove = (double)scrollOffset / (items.size() - visible);
        }

        int scrollY = y + scrollMove * (h - scrollH);

        gout << move_to(scrollX+2, scrollY)
             << color(100,100,100)
             << box(scrollW-4, scrollH);
    }
}

void listBox_widget::handle(event ev)
{
    int lineHeight = 20;
    int maxVisible = h / lineHeight;

    int scrollW = 15;
    int scrollX = x + w - scrollW;

    int visible = maxVisible;

    double ratio = (double)visible / items.size();
    if (ratio > 1.0) ratio = 1.0;

    int scrollH = ratio * h;
    if (scrollH < 20) scrollH = 20;

    double scrollMove = 0;
    if (items.size() > visible)
    {
        scrollMove = (double)scrollOffset / (items.size() - visible);
    }

    int scrollY = y + scrollMove * (h - scrollH);


    if (ev.type == ev_mouse && ev.button == btn_left)
    {
        if (ev.pos_x >= scrollX && ev.pos_x <= scrollX + scrollW &&
            ev.pos_y >= scrollY && ev.pos_y <= scrollY + scrollH)
        {
            dragging = true;
        }
    }


    if (ev.type == ev_mouse && dragging)
    {
        double ratio = (double)(ev.pos_y - y) / h;
        scrollOffset = ratio * (items.size() - visible);

        if (scrollOffset < 0) scrollOffset = 0;
        if (scrollOffset > items.size() - visible)
            scrollOffset = items.size() - visible;
    }


    if (ev.type == ev_mouse && ev.button == -btn_left)
    {
        dragging = false;
    }

    // kattintás listaelemre
    if (ev.type == ev_mouse && ev.button == btn_left)
    {
        if (ev.pos_x >= x && ev.pos_x <= x+w &&
            ev.pos_y >= y && ev.pos_y <= y+h)
        {
            int index = (ev.pos_y - y) / lineHeight + scrollOffset;

            if (index >= 0 && index < items.size())
            {
                selectedItemIndex = index;

            }



        }
    }


    if (ev.type == ev_mouse)
    {
        if (ev.button == btn_wheelup && scrollOffset > 0)
            scrollOffset--;

        if (ev.button == btn_wheeldown &&
            scrollOffset + visible < items.size())
            scrollOffset++;
    }
}



std::string listBox_widget::getValue() const
{
    if (selectedItemIndex >= 0 && selectedItemIndex < items.size())
        return items[selectedItemIndex];

    return "";
}

void listBox_widget::csere() {
    if (selectedItemIndex >= 0 && selectedItemIndex < items.size()) {
        items.erase(items.begin() + selectedItemIndex);
        selectedItemIndex = -1;

    }
}

void listBox_widget::add(const std::string& value) {
    items.push_back(value);
}

void listBox_widget::clear() {
    items.clear();
}