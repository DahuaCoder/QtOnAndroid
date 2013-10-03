#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum ScreenOrientation {
        ScreenOrientationLockPortrait,
        ScreenOrientationLockLandscape,
        ScreenOrientationAuto
    };

    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    void setOrientation(ScreenOrientation orientation);

    void showExpanded();

private slots:
    void handleButtonPressed();
    void handleButtonReleased();
    void handleButtonClicked();

private:

    Ui::MainWindow *ui;
    int m_Counter;
};

#endif // MAINWINDOW_H
