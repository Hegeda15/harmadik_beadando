#include "MyApp.hpp"
#include "graphics.hpp"



int main() {
    genv::gout.open(800, 500);
    MyApp app;
    app.event_loop();
    return 0;
}