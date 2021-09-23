#include <iostream>
#include "console_controller.h"

int main()
{
    std::cout << "Interface console"   << std::endl;
    model::Game  g {};
    View_Console console {};
    g.addObserver(&console);
    Controller ctrl {&console,&g};
    ctrl.play();


}
