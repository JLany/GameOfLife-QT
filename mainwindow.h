#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Universe;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_stopBttn_clicked();

    void on_resetBttn_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Universe* universe;
    bool run;

    // utility functions
    void setup();
    void start();
    void stop();
};
#endif // MAINWINDOW_H
