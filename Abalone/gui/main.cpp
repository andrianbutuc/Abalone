#include "gui_controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    model::Game g{};
    MainWindow w{model::GameData(g.getBoard(),g.getCurrentPlayer(),g.getPlayer1(),g.getPlayer2())};
    Gui_Controller ctrl {&w,&g};
    g.addObserver(&w);
    w.addActionsOnButtons(&ctrl);
    w.show();
    return a.exec();
}
