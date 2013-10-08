#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCoreApplication>
#include <QApplication>
#include <QDesktopWidget>
#include <QGeoCoordinate>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_IsLocationEnabled(false),
      m_pLocationInfo(NULL)
{
    ui->setupUi(this);
    this->setWindowTitle("QtOnAndroid");

    // Connect button signal to appropriate slot
    connect(ui->LocationButton, SIGNAL(clicked()), this, SLOT(handleButtonClicked()));

    startLocationAPI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setOrientation(ScreenOrientation orientation)
{
    (void) orientation;
}

void MainWindow::showExpanded()
{
#if defined(Q_WS_SIMULATOR)
    showFullScreen();
    ui->infoLabel->setText("Simulator");
#elif defined(Q_WS_MAEMO_5)
    showMaximized();
    ui->infoLabel->setText("Maemo");
#else
    ui->infoLabel->setText("Qt on Android");
    ui->locationLabel->setText("Location Service disabled");
    showMaximized();
#endif
}

void MainWindow::handleButtonClicked()
{
    m_IsLocationEnabled = !m_IsLocationEnabled;
}

void MainWindow::updatePosition(QGeoPositionInfo geoPositionInfo)
{
    if (geoPositionInfo.isValid()) {
        // get current location coordinates
        QGeoCoordinate geoCoordinate = geoPositionInfo.coordinate();
        qreal latitude = geoCoordinate.latitude();
        qreal longitude = geoCoordinate.longitude();

        if (m_IsLocationEnabled) {
            ui->locationLabel->setText(QString("Latitude: %1 / Longitude: %2").arg(latitude).arg(longitude));
        }
        else {
            ui->locationLabel->setText(QString("Location Service disabled"));
        }
    }
}

void MainWindow::startLocationAPI()
{
    if (!m_pLocationInfo) {
        m_pLocationInfo = QGeoPositionInfoSource::createDefaultSource(this);

        m_pLocationInfo->setPreferredPositioningMethods(QGeoPositionInfoSource::NonSatellitePositioningMethods);
        connect(m_pLocationInfo, SIGNAL(positionUpdated(QGeoPositionInfo)), this, SLOT(updatePosition(QGeoPositionInfo)));

        // start listening for position updates
        m_pLocationInfo->startUpdates();
    }
}
