
#include "graphics.hpp"

#ifndef CLIONGRAPHICSKIT_WIDGET_HPP
#define CLIONGRAPHICSKIT_WIDGET_HPP

class Application;
class widget {
protected:
    int x,y,w,h;
    Application* _parent;
    bool focused;
public:
    widget(Application* parent,int x,int y,int h,int w);
    virtual ~widget(){};
    virtual void draw()=0;
    virtual void handle(genv::event ev)=0;

    virtual std::string getValue() const =0;

    bool is_selected(int mx, int my) const {
        return mx >= x && mx <= x + w && my >= y && my <= y + h;
    }
    void setFocus(bool f) { focused = f; }
};


#endif //CLIONGRAPHICSKIT_WIDGET_HPP