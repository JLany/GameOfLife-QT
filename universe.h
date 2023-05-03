#ifndef UINVERSE_H
#define UINVERSE_H

#include <QApplication>
#include <QGridLayout>

class Cell;

class Universe : public QGridLayout
{
    Q_OBJECT

public:
    Universe(bool*);

    void initialize();
    void start();
    bool getState(int, int) const;

private:
    Cell* cells[32][32];
    bool states[32][32];
    bool* run;

    // utility function
    int countAliveNeighbors(int, int) const;
    void nextGeneration();
    void holdScreen(int) const;
};

#endif // UINVERSE_H
