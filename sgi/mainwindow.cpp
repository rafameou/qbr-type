#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setWindowFlags(Qt::Drawer); //transparent on sway :O
    this->setFixedSize(this->width(),this->height());
    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    this->setWindowTitle("qbr-type");
    this->setCentralWidget(ui->frame);
    ui->frame->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

