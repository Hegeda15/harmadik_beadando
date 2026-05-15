#include "Application.hpp"
#include "screen.hpp"
#include "Button.hpp"
#include "listBox_widget.hpp"
#include <sstream>


class MyApp : public Application {
protected:
    Screen* tabla;
    Button* uj_jatek_btn;
    listBox_widget* log;

    bool x_jon = true;
    bool jatek_vege = false;
    int lepesek = 0;

    // Szabályellenőrzés
    bool check_win(int s, int o, Mezo m) {
        int iranyok[4][2] = {{0,1}, {1,0}, {1,1}, {1,-1}};
        for (auto &i : iranyok) {
            int db = 1;
            for (int j = 1; j < 5; j++) { // egy irányba
                int ns = s + i[0]*j, no = o + i[1]*j;
                if (ns>=0 && ns<15 && no>=0 && no<15 && tabla->getMezo(ns,no)==m) db++; else break;
            }
            for (int j = 1; j < 5; j++) { // ellentétes irányba
                int ns = s - i[0]*j, no = o - i[1]*j;
                if (ns>=0 && ns<15 && no>=0 && no<15 && tabla->getMezo(ns,no)==m) db++; else break;
            }
            if (db >= 5) return true;
        }
        return false;
    }

    // Egyszerű AI (Extra pont)
    void ai_lepes() {
        if (jatek_vege) return;
        for (int s = 0; s < 15; s++) {
            for (int o = 0; o < 15; o++) {
                if (tabla->getMezo(s, o) == URES) {
                    action("lepes:" + std::to_string(s) + "," + std::to_string(o));
                    return;
                }
            }
        }
    }

public:
    MyApp() {
        // Tábla: 15x15-ös, 30 pixel széles cellákkal
        tabla = new Screen( this, 25, 25, 15, 30);

        // Meglévő listbox logoláshoz
        log = new listBox_widget(this, 500, 25, 250, 350, {"--- JATEK NAPLO ---"});

        // Meglévő Button újraindításhoz
        uj_jatek_btn = new Button(this, 500, 390, 250, 40,
            [this](){ action("reset"); }, // Click
            nullptr, // Hover (opcionális)
            nullptr  // Leave (opcionális)
        );
        Button* exit_btn = new Button(this, 500, 440, 250, 40,
            [](){ exit(0); }
        );
    }

    virtual void action(std::string id) override {
        if (id == "reset") {
            tabla->reset();
            x_jon = true;
            jatek_vege = false;
            lepesek = 0;
            log->add("Uj jatek!");
            return;
        }

        if (jatek_vege) return;

        if (id.find("lepes:") == 0) {
            std::stringstream ss(id.substr(6));
            int s, o; char c;
            ss >> s >> c >> o;

            if (tabla->getMezo(s, o) == URES) {
                Mezo aktualis = x_jon ? X_JEL : O_JEL;
                tabla->setMezo(s, o, aktualis);
                lepesek++;

                log->add((x_jon ? "X: " : "O: ") + std::to_string(s) + "," + std::to_string(o));

                if (check_win(s, o, aktualis)) {
                    log->add(x_jon ? "X NYERT!" : "O NYERT!");
                    jatek_vege = true;
                } else if (lepesek == 15*15) {
                    log->add("DONTETLEN!");
                    jatek_vege = true;
                } else {
                    x_jon = !x_jon;
                    if (!x_jon) ai_lepes(); // Gép jön
                }
            }
        }
    }
};

int main() {
    genv::gout.open(800, 500);
    MyApp app;
    app.event_loop();
    return 0;
}