#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QVector2D>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static bool rightDownDetected;
    static bool rightUpDetected;
    static bool leftDownDetected;
    static bool leftUpDetected;

private slots:
    void handleTimeout();

private:
    Ui::MainWindow *ui;

    bool _trackingEnabled;

    bool _buttonOnePressed;
    bool _buttonTwoPressed;

    QDateTime _lastRightUpDetected;
    bool _vjdAcquired;
};
#endif // MAINWINDOW_H
