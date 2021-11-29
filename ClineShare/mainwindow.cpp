#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pSharedMemory = new QSharedMemory(this);

    m_pSharedMemory->setKey("sharememory");
    if(!m_pSharedMemory->attach())//尝试访问该共享内存块
    {
        qDebug()<<" attach failed";
        return;
    }
    m_pSharedMemory->lock();
    char* sm = static_cast<char*>(m_pSharedMemory->data());
    char *out = new char[static_cast<unsigned int>(m_pSharedMemory->size())];
    memcpy(out,sm,static_cast<unsigned int>(m_pSharedMemory->size()));
    m_pSharedMemory->unlock();
    m_pSharedMemory->detach();
    QByteArray buff(out);
    qDebug()<<buff;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if(!m_pSharedMemory->attach())//尝试访问该共享内存块
    {
        qDebug()<<" attach failed";
        return;
    }
    m_pSharedMemory->lock();
    QString str = ui->strLine->text();
    QByteArray buff = str.toLatin1();
    memcpy(m_pSharedMemory->data(),buff.data(),buff.size());
    m_pSharedMemory->unlock();
    m_pSharedMemory->detach();
}
