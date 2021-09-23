#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "gui_controller.h"
#include <QMenuBar>
MainWindow::MainWindow(model::GameData gameData ,QWidget *parent)
    : QWidget(parent),
    model::Observer(),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->erreur->setVisible(false);
    auto gridChilds =  ui->gridGroupBox->children().toVector();
        for (auto * child : gridChilds) {
            auto name =child->objectName().toStdString() ;
            if(name.length() == 2){
                QPushButton * button = reinterpret_cast<QPushButton*>(child);
                board_buttons.push_back(button);
                Button_Handler * b = new Button_Handler(button,&move);
                events.push_back(b);
                connect(button, &QPushButton::clicked,b,&Button_Handler::eventHandler_button );
            }
        }
        sortButtons();
        update(gameData);
}

MainWindow::~MainWindow()
{
    for (Button_Handler * event : events) {
        delete event ;
    }
    delete ui;
}

void MainWindow::sortButtons(){
    std::sort(board_buttons.begin(),board_buttons.end(),[](QPushButton * a, QPushButton *b ){
            auto name_a = a->objectName();
            auto name_b = b->objectName();
            if(name_a.at(0)==name_b.at(0)){
                return name_a.at(1)<name_b.at(1);
            }
            return name_a.at(0)>name_b.at(0);
        });

}
void MainWindow::updateButton(std::optional<bool> opt,QPushButton * button){
    if(opt.has_value() && opt.value()){
        button->setStyleSheet("QPushButton {background-color: white} " );
    }else if(opt.has_value() && !opt.value()){
        button->setStyleSheet("QPushButton {background-color: black} " );
    }else {
        button->setStyleSheet("QPushButton {background-color: #AD694A}");
    }
}

void MainWindow::update(model::GameData &gameData){
    ui->erreur->setVisible(false);

    auto hexboard_itr = gameData.board.cbegin();
    auto board_buttons_itr = board_buttons.begin();
    for (; hexboard_itr != gameData.board.cend() &&board_buttons_itr != board_buttons.cend()  ;hexboard_itr++,board_buttons_itr++ ) {
        auto optional = hexboard_itr->second ;
        updateButton(optional,*board_buttons_itr);
    }
    auto player_state = gameData.currentPlayer.getState();
    ui->current_player_color->setText(QString::fromStdString(player_state.value()?"White":"Black"));

    ui->out_1->setText(QString::number(gameData.firstPlayer.getNbBallsOut()));
    ui->player1->setText("Player 1 : " + QString::fromStdString(gameData.firstPlayer.getState().value()?"White":"Black"));

    ui->out_2->setText(QString::number(gameData.secondPlayer.getNbBallsOut()));
    ui->player2->setText("Player 2 : " + QString::fromStdString(gameData.secondPlayer.getState().value()?"White":"Black"));
}

void MainWindow::clear_move(){
    for (Button_Handler* handler : events) {
        handler->unclick_button();
    }
    move.clear();
}

void MainWindow::update(std::string messageError){
    clear_move();
    ui->erreur->setText(QString::fromStdString(messageError));
    ui->erreur->setVisible(true);
}

void MainWindow::addActionsOnButtons(void* ptr){
    QPushButton * button = ui->valider;

    Gui_Controller * ctrl = reinterpret_cast<Gui_Controller*>(ptr);

    connect(button, &QPushButton::clicked,ctrl,&Gui_Controller::play);
    connect(ui->reset, &QPushButton::clicked,this,&MainWindow::clear_move);
    connect(ui->restart,&QPushButton::clicked,ctrl,&Gui_Controller::reset);
}

std::string& MainWindow::getMove(){
    return move;
}
