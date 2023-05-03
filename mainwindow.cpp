#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "universe.h"
#include "cell.h"
#include <QStyle>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , universe{ nullptr }
    , run{ true }
{
    ui->setupUi(this);
    setup();
    setFixedSize(size());

    setStyleSheet("Cell[enabled=true] { background-color: yellow; }"
                  "Cell[enabled=false] { background-color: grey; }" );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setup() {
    if (universe != nullptr) {
        delete universe;
    }

    universe = new Universe(&run);

    universe->initialize();

    QWidget* widget = new QWidget;
    widget->setLayout(universe);
    ui->centralLayout->addWidget(widget);
}


void MainWindow::start() {
    run = true;
    universe->start();
}


void MainWindow::stop() {
    run = false;
}



void MainWindow::on_stopBttn_clicked()
{
    stop();
    ui->resetBttn->setEnabled(true);
}


void MainWindow::on_resetBttn_clicked()
{
    universe->initialize();
}


void MainWindow::on_pushButton_clicked()
{
    run = true;
    ui->resetBttn->setEnabled(false);
    start();
}

