#include "cell.h"
#include "universe.h"
#include <QApplication>
#include <random>
#include <QStyle>
#include <ctime>

int Cell::generateRandomNumber(unsigned lBound, unsigned uBound) {
    // static here gurantees that we use the same seed for all random values
    static std::default_random_engine engine{
        static_cast<unsigned int>(std::time(0))
    };

    static std::uniform_int_distribution<unsigned int> random{ lBound, uBound };

    return random(engine);
}

Cell::Cell(Universe* aUniverse, int x, int y)
    : universe{ aUniverse }
    , x_idx{ x }
    , y_idx{ y }
{
    int randomValue = generateRandomNumber(1, 10);
    if (randomValue == 1) // 10% chance to be alive cell
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


void Cell::updateState() {
    state = universe->getState(x_idx, y_idx);

    this->setEnabled(State());
    this->setProperty("enabled", State());
    this->style()->unpolish(this);
    this->style()->polish(this);
}
