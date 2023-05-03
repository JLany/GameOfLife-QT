#ifndef CELL_H
#define CELL_H

#include <QApplication>
#include <QPushButton>

class Universe;

class Cell : public QPushButton
{
    Q_OBJECT

public:
    Cell(Universe*, int, int);
    Cell(int, int);

    bool State() const;
    void updateState();

private:
    Universe* universe;
    int x_idx;
    int y_idx;
    bool state;

    // utility functions
    static int generateRandomNumber(unsigned, unsigned);
};

#endif // CELL_H
