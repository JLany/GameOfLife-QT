#include "universe.h"
#include "cell.h"
#include <QTime>

Universe::Universe(bool* aRun)
    : states{}
    , run{ aRun }
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
            this->states[i][j] = cell->State();
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

bool Universe::getState(int xIdx, int yIdx) const {
    return states[xIdx][yIdx];
}

int Universe::countAliveNeighbors(int x, int y) const
{
    int sum = 0;

    for (int i{-1}; i <= 1; ++i)
        for (int j{-1}; j <= 1; ++j)
            sum += states[x + i][y + j];

    sum -= states[x][y];

    return sum;
}


void Universe::nextGeneration()
{
    for (int xIdx{1}; xIdx <= 30; ++xIdx) {
        for (int yIdx{1}; yIdx <= 30; ++yIdx) {
            int neighbors = countAliveNeighbors(xIdx, yIdx);

            bool& thisCell = states[xIdx][yIdx];
            if (thisCell && neighbors < 2)
                thisCell = false;
            else if (thisCell && neighbors > 3)
                thisCell = false;
            else if (!thisCell && neighbors == 3)
                thisCell = true;

            cells[xIdx][yIdx]->updateState();
        }
    }
}


void Universe::holdScreen(int duration) const {
    QTime dieTime = QTime::currentTime().addMSecs( duration );
    while( QTime::currentTime() < dieTime )
       {
           QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
       }
}

