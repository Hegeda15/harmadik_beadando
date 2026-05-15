#include "counter_widget.hpp"
#include "graphics.hpp"
#include "Application.hpp"
#include "widget.hpp"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

#include "Button.hpp"
#include "listBox_widget.hpp"
using namespace genv;

struct Vmi {
    std::string berlo;
    std::string kocsi;
};

class MyApp : public Application {
public:
    MyApp() {

        std::vector<std::string>lwItems={"Zohan","Keleti Barat","Karika","T-home","Hege","Szolti","Roni"};
        std::vector<std::string> lwItems2 = {"Audi", "BMW", "Honda", "Toyota", "Mercedes", "Opel"};
        std::vector<std::string> lwItems3 = {};

       lw1= new listBox_widget(this, 10, 200, 100, 200, lwItems);
       lw2= new listBox_widget(this, 300, 200, 100, 200, lwItems2);
        lw3= new listBox_widget(this, 10, 400, 100, 200, lwItems3);

        b = new Button(this, 10, 40, 40, 40,
     [this]() { action("berles"); },
     []() { std::cout << "hover\n"; },
     []() { std::cout << "leave\n"; });

        b2 = new Button(this, 100, 40, 40, 40,
     [this]() { action("vissza"); },          // click
     []() { std::cout << "hover\n"; },        // hover
     []() { std::cout << "leave\n"; });
    }

    virtual void action(std::string id) override {

        std::string bérlő = lw1->getValue();
        std::string autó = lw2->getValue();
        std::string kiválasztottBérlés = lw3->getValue();

        Vmi v;
        v.berlo = bérlő;
        v.kocsi = autó;

        if (id == "berles" && !autó.empty()) {
                lw2->csere();
                lw3->add(v.berlo + " : " + v.kocsi);
                berlovec.push_back(v);
        }

        if (id == "vissza"&& !kiválasztottBérlés.empty()) {
            if (!berlovec.empty()) {
                Vmi utolso = berlovec.back();

                lw3->csere();

                lw2->add(utolso.kocsi);

                berlovec.pop_back();
            }
        }
    }
protected:
    listBox_widget* lw1;
    listBox_widget* lw2;
    listBox_widget* lw3;
    std::vector<Vmi> berlovec;
    Button* b;
    Button* b2;

};



int main()
{
    gout.open(600, 600);
    MyApp app;
    app.event_loop();





    return 0;
}
