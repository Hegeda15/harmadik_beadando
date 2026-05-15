//
// Created by heged on 5/15/2026.
//

#ifndef CLIONGRAPHICSKIT_SCREEN_HPP
#define CLIONGRAPHICSKIT_SCREEN_HPP
#include "widget.hpp"

enum Mezo { URES, X_JEL, O_JEL };
class Screen:public widget {
protected:
    int _meret;
    int _cella;
    std::vector<std::vector<Mezo>> _tabla;
public:
    Screen(Application* parent, int x, int y, int meret, int cella_szelesseg);

    virtual void draw() override;
    virtual void handle(genv::event ev) override;
    virtual std::string getValue() const override { return ""; }

    void setMezo(int s, int o, Mezo m) { _tabla[s][o] = m; }
    Mezo getMezo(int s, int o) const { return _tabla[s][o]; }
    void reset();
    int getMeret() const { return _meret; }
};



#endif //CLIONGRAPHICSKIT_SCREEN_HPP