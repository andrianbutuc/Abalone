#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QPushButton>
#include <vector>
#include "button_handler.h"
#include "observer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


/*!
 * \brief The MainWindow class represents the main window of the application.
 */
class MainWindow : public QWidget,
                   public model::Observer
{
    Q_OBJECT


private:

    /*!
     * \brief ui is the section of the view generated from XML file.
     */
    Ui::MainWindow *ui;

    /*!
     * \brief board_buttons contains the 61 pointers to all the buttons on the game board.
     */
    std::vector<QPushButton *> board_buttons ;

    /*!
     * \brief events contains the 61 pointers to all Button_Handlers objects that defines the button actions.
     */
    std::vector<Button_Handler *> events ;

    /*!
     * \brief move represents the move to be processed
     */
    std::string move;

    /*!
     * \brief sortButtons sorts the pointers to the buttons in a specific order.
     */
    void sortButtons();

    /*!
     * \brief updateButton updates a button, applies a specific style depending on the state.
     * \param opt the state of the button
     * \param button the button pointer
     */
    void updateButton(std::optional<bool> opt,QPushButton * button);



public:

    /*!
     * \brief MainWindow constructor of MainWindow
     * \param gameData the data of the game that needs to be displayed
     * \param parent is a QWidget
     */
    MainWindow(model::GameData gameData ,QWidget *parent = nullptr);


    /*!
     * \brief MainWindow destructor of MainWindows
     *
     */
    ~MainWindow();

    /*!
     * \brief getMove simple getter of the move
     * \return a rerefence to the move
     */
    std::string& getMove();

    /*!
     * \brief clear_move empties the move string and unclick the button
     */
    void clear_move();

    /*!
     * \brief update updates the data. This method is called
     * when the move has passed.
     * \param gameData the data of the game that needs to be updated.
     */
    virtual void update(model::GameData& gameData) override final;

    /*!
     * \brief update update updates the data. This method is called
     * when the move has not passed.
     * \param messageError the error message to be displayed
     */
    virtual void update(std::string messageError)override final;

    /*!
     * \brief addActionsOnButtons defines the actions of the game controls buttons.
     * \param ctrl a pointer to the controller of the game.
     */
    void addActionsOnButtons(void* ctrl);
};
#endif // MAINWINDOW_H
