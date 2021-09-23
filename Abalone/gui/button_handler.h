#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H
#include <string>
#include <QObject>
#include <QPushButton>

#define POSITION_LEGHT 2

/*!
 * \brief The Button_Handler class handles the events related to the buttons in the GUI.
 */
class Button_Handler:public QObject{

    Q_OBJECT
private:
    /*!
     * \brief button a button linked to the Button_Handler class
     */
    QPushButton * button ;
    /*!
     * \brief mainMove a string containing the move to be processed, shared by all buttons
     */
    std::string* mainMove ;

    /*!
     * \brief clicked boolean that represents the clicked-state of a button, is true
     * if the button has been clicked, false otherwise.
     */
    bool clicked ;

    /*!
     * \brief delete_position_from_move removes the position represented by the name of the clicked button, from the current move to be processed.
     */
    void delete_position_from_move();

public:
    /*!
     * \brief Button_Handler constructor of Button_Handler
     * \param button a pointer to a QPushButton
     * \param move a pointer to the current move to be processed
     */
    Button_Handler(QPushButton * button,std::string* move );

    /*!
     * \brief eventHandler_button handles the click event on a button
     */
    void eventHandler_button();

    /*!
     * \brief unclick_button removes the clicked-state of
     * a button and apply a specific style
     * removes the position represented by the name of the clicked button
     * from the current move to be processed.
     */
    void unclick_button();
};

#endif // BUTTON_HANDLER_H
