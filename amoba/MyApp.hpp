//
// Created by heged on 5/17/2026.
//

#ifndef CLIONGRAPHICSKIT_MYAPP_HPP
#define CLIONGRAPHICSKIT_MYAPP_HPP
#include "Application.hpp"
#include "Button.hpp"
#include "listBox_widget.hpp"
#include "screen.hpp"


class MyApp:public Application {
protected:
    Screen* tabla;
    Button* uj_jatek_btn;
    listBox_widget* log;

    bool x_jon = true;
    bool jatek_vege = false;
    int lepesek = 0;

    int szamol_szomszed(int s, int o, int ds, int do_, Mezo m);
    int mezo_ertekeles(int s, int o, Mezo ki_lep);
    bool check_win(int s, int o, Mezo m);
    void ai_lepes();

    public:
    MyApp();
    virtual void action(std::string id) override;
};


#endif //CLIONGRAPHICSKIT_MYAPP_HPP