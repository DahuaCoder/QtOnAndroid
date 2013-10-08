#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>

QTM_USE_NAMESPACE

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
    void handleButtonClicked();
    void updatePosition(QGeoPositionInfo geoPositionInfo);

private:
    void startLocationAPI();

private:
    Ui::MainWindow *ui;
    bool m_IsLocationEnabled;
    QGeoPositionInfoSource* m_pLocationInfo;
};

#endif // MAINWINDOW_H
