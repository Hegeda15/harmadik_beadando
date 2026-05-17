//
// Created by heged on 5/17/2026.
//

#include "Text_Block.hpp"

#include "application.hpp"
using namespace genv;
Text_Block::Text_Block(Application *parent, int x, int y, int w, int h, std::string _text):widget(parent,x,y,w,h),_text(_text) {

}

void Text_Block::draw() {
    gout<<move_to(x,y)<<color(0,0,0)<<text(_text);
}
void Text_Block::handle(genv::event ev) {

}
std::string Text_Block::getValue() const {

}

