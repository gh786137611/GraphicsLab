#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenu>
#include <QActionGroup>
#include <QDebug>
#include "glwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
        ui->setupUi(this);
        GLWidget *w = new GLWidget(this);
        setCentralWidget(w);
        setMenu();

        this->showMaximized();
}

MainWindow::~MainWindow()
{
        delete ui;
}

void MainWindow::setMenu()
{
}

