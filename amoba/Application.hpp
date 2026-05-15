
#ifndef CLIONGRAPHICSKIT_APPLICATION_HPP
#define CLIONGRAPHICSKIT_APPLICATION_HPP
#include "widget.hpp"

class widget;

class Application {
protected:

    std::vector<widget*> _widgets;
    int _focus;

public:
    Application();
    virtual ~Application() {}

    void register_widget(widget* w);

    void event_loop();

    virtual void action(std::string id) = 0;
};


#endif //CLIONGRAPHICSKIT_APPLICATION_HPP