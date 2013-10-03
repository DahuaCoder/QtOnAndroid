#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCoreApplication>
#include <QApplication>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_Counter(0)
{
    ui->setupUi(this);
    this->setWindowTitle("QtOnAndroid");

    setGeometry(QApplication::desktop()->screenGeometry());

    // Connect button signal to appropriate slot
    connect(ui->pushButton, SIGNAL(pressed()), this, SLOT(handleButtonPressed()));
    connect(ui->pushButton, SIGNAL(released()), this, SLOT(handleButtonReleased()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(handleButtonClicked()));
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
    ui->infoLabel->setText("Some other platform");
    ui->statusLabel->setText("Button released!");
    showMaximized();
#endif
}

void MainWindow::handleButtonPressed()
{
    ui->statusLabel->setText("Button pressed!");
}

void MainWindow::handleButtonReleased()
{
    ui->statusLabel->setText("Button released!");
}

void MainWindow::handleButtonClicked()
{
    ui->countLabel->setText(QString::number(++m_Counter));
}
