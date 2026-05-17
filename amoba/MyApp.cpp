//
// Created by heged on 5/17/2026.
//
#include <sstream>
#include "MyApp.hpp"
MyApp::MyApp(){
    tabla = new Screen(this, 25, 25, 15, 30);


    log = new listBox_widget(this, 500, 25, 150, 200, {"--- JATEK NAPLO ---"});


    tb1= new Text_Block(this,500,280,100,30,"AI Level");
    nehezseg_allito = new counter_widget(this, 500, 290, 40, 200, 1, 3);

    uj_jatek_btn = new Button(this, 500, 200, 30, 100,"New Game",
    [this](){ action("reset"); },
    nullptr,
    nullptr
    );

    Button* exit_btn = new Button(this, 620, 200, 30, 100,"Exit",

    [](){ exit(0); }

    );
}
int MyApp::szamol_szomszed(int s, int o, int ds, int do_, Mezo m) {
    int db = 0;
    int ns = s + ds, no = o + do_;
    while (ns >= 0 && ns < 15 && no >= 0 && no < 15 && tabla->getMezo(ns, no) == m) {
        db++;
        ns += ds;
        no += do_;
    }
    return db;
}

int MyApp::mezo_ertekeles(int s, int o, Mezo ki_lep) {
    int ossz_ertek = 0;
    int iranyok[4][2] = {{0,1}, {1,0}, {1,1}, {1,-1}};
    for (auto &i : iranyok) {
        int sajat = 1;
        sajat += szamol_szomszed(s, o, i[0], i[1], ki_lep);
        sajat += szamol_szomszed(s, o, -i[0], -i[1], ki_lep);

        if (sajat >= 5) ossz_ertek += 100000;
        else if (sajat == 4) ossz_ertek += 5000;
        else if (sajat == 3) ossz_ertek += 500;
        else if (sajat == 2) ossz_ertek += 50;
    }
    return ossz_ertek;
}

bool MyApp::check_win(int s, int o, Mezo m) {
    int iranyok[4][2] = {{0,1}, {1,0}, {1,1}, {1,-1}};
    for (auto &i : iranyok) {
        int db = 1;
        db += szamol_szomszed(s, o, i[0], i[1], m);
        db += szamol_szomszed(s, o, -i[0], -i[1], m);
        if (db >= 5) return true;
    }
    return false;
}

void MyApp::ai_lepes() {
    if (jatek_vege) return;
    int legjobb_s = -1, legjobb_o = -1;
    int max_pont = -1;


    int szint = nehezseg_allito->getIntValue();


    double vedekezes_szorzo = 0.5;
    if (szint == 1) {
        vedekezes_szorzo = 0.1;
    } else if (szint == 3) {
        vedekezes_szorzo = 1.5;
    }

    for (int s = 0; s < 15; s++) {
        for (int o = 0; o < 15; o++) {
            if (tabla->getMezo(s, o) == URES) {
                int tamadas = mezo_ertekeles(s, o, O_JEL);
                int vedekezes = mezo_ertekeles(s, o, X_JEL);


                int aktualis_ertek = tamadas + (int)(vedekezes * vedekezes_szorzo);

                if (aktualis_ertek > max_pont) {
                    max_pont = aktualis_ertek;
                    legjobb_s = s;
                    legjobb_o = o;
                }
            }
        }
    }
    if (legjobb_s != -1) {
        action("lepes:" + std::to_string(legjobb_s) + "," + std::to_string(legjobb_o));
    }
}

void MyApp::action(std::string id) {
    if (id == "reset") {
        tabla->reset();
        x_jon = true;
        jatek_vege = false;
        lepesek = 0;
        log->clear();
        log->add("Uj jatek indult!");
        return;
    }

    if (jatek_vege) return;

    if (id.find("lepes:") == 0) {
        std::stringstream ss(id.substr(6));
        int s, o; char vesszo;
        ss >> s >> vesszo >> o;

        if (tabla->getMezo(s, o) == URES) {
            Mezo aktualis = x_jon ? X_JEL : O_JEL;
            tabla->setMezo(s, o, aktualis);
            lepesek++;

            log->add((x_jon ? "X lepes: " : "O lepes: ") + std::to_string(s) + "," + std::to_string(o));

            if (check_win(s, o, aktualis)) {
                log->add(x_jon ? ">>> X NYERT! <<<" : ">>> O NYERT! <<<");
                jatek_vege = true;
            } else if (lepesek == 15 * 15) {
                log->add("!!! DONTETLEN !!!");
                jatek_vege = true;
            } else {
                x_jon = !x_jon;
                if (!x_jon) ai_lepes();
            }
        }
    }
}