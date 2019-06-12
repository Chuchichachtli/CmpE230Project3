//Barış Başmak, Kayacan Vesek 2016400087, 2016400114

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QButtonGroup>
#include <QTest>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT




public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool deleted[24];                       // True if the corresponding button is removed from the game
    QPushButton *array[24] ;                // Stores the buttons
    QButtonGroup buttonGroup ;
    QString cardBack[25] ={"asddasdasdasd", "A", "A","B", "B","C", "C","D", "D","E", "E",   // Values that can be on a card's back
                           "F", "F","G", "G","H", "H","I",                                  // except at index = 0
                           "I","J", "J","K", "K","L", "L", } ;
    int places[24] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24} ;     // Will refer to cardBack's indexes
    static int const EXIT_CODE_REBOOT;                                                      // will be shuffled when the constructor's called
     QAction* actionReboot;

public slots:
    void push_clicked();  // Slot for when a card's clicked
    void resetGame() ;    // Slot for resetting the game
    void slotReboot();    // Slot for resetting the game

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
