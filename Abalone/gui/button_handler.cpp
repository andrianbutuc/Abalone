#include "button_handler.h"
Button_Handler::Button_Handler(QPushButton * button,std::string* move):button{button},mainMove{move},clicked{false}
{}

void Button_Handler::eventHandler_button(){
    clicked = !clicked;
    if(clicked){
        mainMove->append(button->objectName().toStdString());
        auto color = button->palette().button().color();
        button->setStyleSheet("QPushButton{border-color: orange; background-color:" +color.name()+"}");
    }else {
        unclick_button();
    }
}
void Button_Handler::unclick_button(){

        auto color = button->palette().button().color();
        button->setStyleSheet("QPushButton{border-color: black; background-color:" +color.name()+"}QPushButton:hover{border: 2px solid rgb(85, 255, 255);}");
        clicked = false ;
        delete_position_from_move();
}

void Button_Handler::delete_position_from_move(){
    size_t pos = mainMove->find(button->objectName().toStdString());
        if (pos != std::string::npos)
        {
            mainMove->erase(pos, pos+POSITION_LEGHT);
        }
}
