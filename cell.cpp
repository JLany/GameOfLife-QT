#include "cell.h"
#include "universe.h"
#include <QApplication>
#include <random>
#include <QStyle>
#include <ctime>

Cell::Cell(Universe* aUniverse, int x, int y)
    : universe{ aUniverse }
    , x_idx{ x }
    , y_idx{ y }
{
    // static here guarntees that we use the same seed for all randomized values
    static std::default_random_engine engine{
        static_cast<unsigned int>(std::time(0)) };
    std::uniform_int_distribution<unsigned int> randomValue{ 1, 10 };

    if (randomValue(engine) == 1)
        state = true;
    else
        state = false;

    setEnabled(state);
    this->setProperty("enabled", State());
    this->style()->unpolish(this);
    this->style()->polish(this);
}

Cell::Cell(int x, int y)
    : universe{ nullptr }
    , x_idx{ x }
    , y_idx{ y }
{
    state = false;
    setEnabled(state);
    this->setProperty("enabled", State());
    this->style()->unpolish(this);
    this->style()->polish(this);
}

bool Cell::State() const {
    return state;
}


void Cell::updateState()
{
    int neighbors = universe->countAliveNeighbors(x_idx, y_idx);

    if (State() && neighbors < 2) {
        state = false;
    }
    else if (State() && neighbors > 3) {
        state = false;
    }
    else if (!State() && neighbors == 3) {
        state = true;
    }

    this->setEnabled(State());
    this->setProperty("enabled", State());
    this->style()->unpolish(this);
    this->style()->polish(this);
}
