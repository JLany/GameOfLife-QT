#include "universe.h"
#include "cell.h"
#include <QTime>

Universe::Universe(bool* aRun)
    : run{ aRun }
{
    // initialize hidden borders
    for (int i : {0, 31}) {
        for (int j{0}; j < 32; ++j) {
            cells[i][j] = new Cell(i, j);
        }
    }

    for (int i{1}; i < 31; ++i) {
        for (int j : {0, 31}) {
            cells[i][j] = new Cell(i, j);
        }
    }
}


void Universe::initialize()
{
    for (int i = 1; i < 31; ++i) {
        for (int j = 1; j < 31; ++j) {
            Cell* cell = new Cell(this, i, j);
            cell->setMinimumSize(24, 22);
            cell->setMaximumSize(24, 22);
            this->addWidget(cell, i - 1, j - 1);
            this->cells[i][j] = cell;
        }
    }
}


void Universe::start()
{
    while (*run) {
        nextGeneration();
        holdScreen(180);
    }
}


int Universe::countAliveNeighbors(int x, int y) const
{
    int sum = 0;

    for (int i{-1}; i <= 1; ++i)
        for (int j{-1}; j <= 1; ++j)
            sum += cells[x + i][y + j]->State();

    sum -= cells[x][y]->State();

    return sum;
}


void Universe::nextGeneration()
{
    for (int i{1}; i < 31; ++i) {
        for (int j{1}; j < 31; ++j) {
            cells[i][j]->updateState();
        }
    }
}


void Universe::holdScreen(int duration)
{
    QTime dieTime = QTime::currentTime().addMSecs( duration );
    while( QTime::currentTime() < dieTime )
       {
           QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
       }
}

