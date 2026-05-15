//
// Created by heged on 4/14/2026.
//

#include "widget.hpp"
#include "application.hpp"

widget::widget(Application* parent,int x, int y, int h, int w):_parent(parent),x(x),y(y),h(h),w(w) {
    _parent->register_widget(this);
}
