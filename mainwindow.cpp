//Barış Başmak, Kayacan Vesek 2016400087, 2016400114

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QThread>
#include <algorithm>
#include <QAction>

QPushButton *clickedButton1 = nullptr ;                   // First card to be clicked
QPushButton *clickedButton2 = nullptr;                   // Second card to be clicked
bool first = true ;                                     // if the game's expecting the first card click
int const MainWindow::EXIT_CODE_REBOOT = -123456789;   // For reset

//RNG is here so that the random_shuffle function doesn't give the same result for all the games
struct RNG {
    int operator() (int n) {
        return std::rand() / (1.0 + RAND_MAX) * n;
    }
};



MainWindow::MainWindow(QWidget *parent) :  //constructor
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    srand(time(0));                                                     //seed set so that the card organization differs from game to game
    std::random_shuffle(std::begin(places), std::end(places), RNG());
    ui->setupUi(this);                                                  // Setting up the ui

    //constructing an array for all the push buttons that represent cards
    this->array[0] = ui->push01 ;
    array[1] = ui->push02 ;array[2] = ui->push03 ;array[3] = ui->push04 ;array[4] = ui->push05 ;array[5] = ui->push06 ;
    array[6] = ui->push07 ;array[7] = ui->push08 ;array[8] = ui->push09 ;array[9] = ui->push10 ;array[10] = ui->push11 ;
    array[11] = ui->push12 ;array[12] = ui->push13 ;array[13] = ui->push14 ;array[14] = ui->push15 ;array[15] = ui->push16 ;array[16] = ui->push17 ;
    array[17] = ui->push18 ;array[18] = ui->push19 ;array[19] = ui->push20 ;array[20] = ui->push21 ;array[21] = ui->push22 ;
    array[22] = ui->push23 ; array[23] = ui->push24 ;

    // Signals if a card is clicked on and acts accordingly
    // if the card was found its corresponding cell in deleted array becomes true
    for(int i = 0 ; i < 24 ; i++){

        if(!deleted[i])
            QObject::connect(array[i], SIGNAL(clicked()), this, SLOT(push_clicked())) ;
    }
    // Signal for resetting the game
    QObject::connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(resetGame())) ;
    QObject::connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(slotReboot()));

}
//Destructor
MainWindow::~MainWindow()
{
    delete ui;
}

//resets the game when clicked on.
void MainWindow::resetGame(){
    ui->tryNo->display(0) ;    //makes tries show 0
    ui->pairsNo->display(0) ;  //makes pairs show 0
    first = true ;             //makes first true so that the game'll expect the first card to be clicked on
    clickedButton1 = nullptr ; //resets the global qpushbuttons
    clickedButton2 = nullptr;


//prepares the buttons for the new game
    //makes them clickable if they were disabled.
    for(int i = 0 ; i < 24 ; i++){
        deleted[i] = false ;
        array[i]->setEnabled(true) ;
    }

}

//this slot's for when a card's been clicked
void MainWindow::push_clicked()
{

    QPushButton *a = (QPushButton *)sender();    // Retrieving which card's been clicked
    QString buttonLabel = a->text();            //text of the clicked card
    QString obje = a->objectName() ;           //name of the clicked card
    int x = obje[4].digitValue() ;            //the numbers from the cards name is extracted here
    int y = obje[5].digitValue() ;           //so that it can be used as an index
    y += 10*x ;
    a->setText(this->cardBack[this->places[y-1]]) ;         //A character from the string array (the array places is shuffled for randomization)

    for(int i = 0 ; i < 24 ; i++){
        if(!deleted[i])
            array[i]->setEnabled(false) ;   // Makes all the buttons unclickable so that a user doesn't click faster than the game can react and cheat.
    }
//If the click number is an odd one
    if(first && buttonLabel == "X"){

        clickedButton1 = a ;

        QString name =  a->objectName();

        first = false ;
    }else if(!first && buttonLabel == "X"){         // If the click number is even

        clickedButton2 = a ;

        ui->tryNo->display(ui->tryNo->value() + 1) ;        //Tries increase by one if the user's clicked 2 different cards.

        if(clickedButton1->text() == clickedButton2->text()){  // If their text are the same the cards are removed from the game.
            ui->pairsNo->display(ui->pairsNo->value() + 1) ;   // Pairs increase by one since a pair has been found.
            QString obje1 = clickedButton1->objectName() ;     // clickedButton1's name for index extraction
            int x1 = obje1[4].digitValue() ;
            int y1 = obje1[5].digitValue() ;
            y1 += 10*x1 ;                                     // Set true so that the game doesn't try to access a card
            deleted[y1-1] = true ;                            // that's been removed from the game

            QString obje2 = clickedButton2->objectName() ;    //Same process for clickedButton2
            x1 = obje2[4].digitValue() ;
            y1 = obje2[5].digitValue() ;
            y1 += 10*x ;
            deleted[y1-1] = true ;

            clickedButton1->setDisabled(true);      // Disabled the pairs'cards
            clickedButton2->setDisabled(true);

        }else {

            QTest::qWait(500) ;                     // Waits 0.5 seconds so that the use can see the second card

            clickedButton1->setText("X") ;          // If the guess was wrong both of the cards return back to X .
            clickedButton2->setText("X") ;          // They are, in a way turned back again.

            clickedButton1->setEnabled(true) ;      // They are made clickable again
            clickedButton2->setEnabled(true) ;
        }

        clickedButton1= nullptr ;                    // The global variables are cleared
        clickedButton2= nullptr ;

        first = true ;                               // Since a second card's been clicked, wait for the next odd numbered click.

    }

    for(int i = 0 ; i < 24 ; i++){                  // The others cards are enabled
        if(!deleted[i] )
            array[i]->setEnabled(true) ;
    }
    for(int i = 0 ; i < 24 ; i++){                  // The ones which were found remain unclickable.
        if(!deleted[i] && array[i]->text() != "X" ) // But the game still shows what they are, meaning, the cards' contents can be seen
            array[i]->setEnabled(false) ;
    }

}
//Rebooting slot
void MainWindow::slotReboot()
{
    qApp->exit( MainWindow::EXIT_CODE_REBOOT );
}
