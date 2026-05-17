//
// Created by heged on 5/17/2026.
//

#ifndef AMOBA_TEXT_BLOCK_HPP
#define AMOBA_TEXT_BLOCK_HPP
#include "widget.hpp"


class Text_Block:public widget {
    protected:
    std::string _text;
    public:
    Text_Block(Application* parent, int x, int y, int w, int h,
               std::string _text);

    void draw() override;
    void handle(genv::event ev) override;
    virtual std::string getValue() const override;
};


#endif //AMOBA_TEXT_BLOCK_HPP