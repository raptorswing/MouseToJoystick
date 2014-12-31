#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QTimer>
#include <QCursor>
#include <QVector2D>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QMessageBox>

#include <Windows.h>
#include "vjoyInc/public.h"
#include "vjoyInc/vjoyinterface.h"

const long AXIS_MAX = 0x8000;
const long AXIS_MIN = 0x1;
const long AXIS_MID = AXIS_MAX - (AXIS_MAX - AXIS_MIN) / 2;

const quint32 VJDINTERFACE = 1;

bool MainWindow::rightDownDetected = false;
bool MainWindow::rightUpDetected = false;
bool MainWindow::leftDownDetected = false;
bool MainWindow::leftUpDetected = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _trackingEnabled = false;
    _buttonOnePressed = false;
    _buttonTwoPressed = false;
    _lastRightUpDetected = QDateTime::currentDateTime();

    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
    timer->start(30);

    MainWindow::rightDownDetected = false;
    MainWindow::rightUpDetected = false;
    MainWindow::leftDownDetected = false;
    MainWindow::leftUpDetected = false;

    _vjdAcquired = false;
}

MainWindow::~MainWindow()
{
    RelinquishVJD(VJDINTERFACE);
    _vjdAcquired = false;
    delete ui;
}

//private slot
void MainWindow::handleTimeout()
{
    // If we haven't acquired the VJD device, do it now
    if (!_vjdAcquired)
    {
        // Check for vJoy
        if (!vJoyEnabled())
        {
            QMessageBox::critical(this, "VJoy is not enabled", "vJoy is not enabled - we can't do anything");
            QApplication::quit();
        }

        // Try to acquire vJoy
        if (!AcquireVJD(VJDINTERFACE))
        {
            QMessageBox::critical(this, "Error", QString("Failed to acquire vjoy interface %1").arg(VJDINTERFACE));
            QApplication::quit();
        }
        _vjdAcquired = true;
    }

    // Handle mouse inputs from win32
    if (MainWindow::rightDownDetected)
    {
        MainWindow::rightDownDetected = false;

        _buttonTwoPressed = true;
    }

    if (MainWindow::rightUpDetected)
    {
        MainWindow::rightUpDetected = false;

        const QDateTime current = QDateTime::currentDateTime();
        if (_lastRightUpDetected.msecsTo(current) <= 500)
        {
            _trackingEnabled = !_trackingEnabled;
            ResetVJD(VJDINTERFACE);
        }
        _lastRightUpDetected = current;

        _buttonTwoPressed = false;
    }

    if (MainWindow::leftDownDetected)
    {
        MainWindow::leftDownDetected = false;
        _buttonOnePressed = true;
    }

    if (MainWindow::leftUpDetected)
    {
        MainWindow::leftUpDetected = false;
        _buttonOnePressed = false;
    }

    if (!_trackingEnabled)
    {
        return;
    }

    // Based on current screen size, calculate distance of cursor from center
    const QRect rec = QApplication::desktop()->screenGeometry();
    const QPoint screenCenter(rec.width() / 2, rec.height() / 2);
    const QPoint currentPos = QCursor::pos();

    const QVector2D delta(currentPos.x() - screenCenter.x(), currentPos.y() - screenCenter.y());

    // Set cursor back to center
    QCursor::setPos(screenCenter);

    // Allow inverting X/Y axes
    int xInv = 1;
    int yInv = 1;

    if (this->ui->invertXCheckbox->isChecked())
        xInv = -1;
    if (this->ui->invertYCheckbox->isChecked())
        yInv = -1;

    // Calculate the outputs to apply to the joystick axes
    const long xOut = qBound<long>(AXIS_MIN, AXIS_MID + xInv * (delta.x() * (delta.x() * -1.0/1.1 + 500)), AXIS_MAX);
    const long yOut = qBound<long>(AXIS_MIN, AXIS_MID + yInv * (delta.y() * (delta.y() * -1.0/1.1 + 500)), AXIS_MAX);

    /*
    JOYSTICK_POSITION joystickStatus;
    joystickStatus.bDevice = VJDINTERFACE;

    joystickStatus.wAxisX = xOut;
    joystickStatus.wAxisY = yOut;
    joystickStatus.wAxisZ = AXIS_MAX;
    joystickStatus.lButtons = 0;
    if (_buttonOnePressed)
        joystickStatus.lButtons += 1;
    if (_buttonTwoPressed)
        joystickStatus.lButtons += 2;

    UpdateVJD(VJDINTERFACE, (PVOID)&joystickStatus);
    */

    SetAxis(xOut, VJDINTERFACE, HID_USAGE_X);
    SetAxis(yOut, VJDINTERFACE, HID_USAGE_Y);

    SetBtn(_buttonOnePressed, VJDINTERFACE, 1);
    SetBtn(_buttonTwoPressed, VJDINTERFACE, 2);

    // Update UI
    this->ui->mousePosLabel->setText( QString("X: %1, Y: %2").arg(currentPos.x()).arg(currentPos.y()) );
    this->ui->deltaLabel->setText( QString("%1, %2").arg(delta.x()).arg(delta.y()) );
    this->ui->joystickOutLabel->setText( QString("X: %1, Y: %2").arg(xOut).arg(yOut) );
}
