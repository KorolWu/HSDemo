#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pSharememory = new QSharedMemory(this);
    m_pSharememory->setKey("sharememory");
    if(m_pSharememory->isAttached())//盘算是否连接到了共享内存块，如果是 就先分离
    {
        m_pSharememory->detach();
    }
    if(!m_pSharememory->create(256,QSharedMemory::ReadWrite))
    {
        qDebug()<<"ShareMemory creat failed";
        return;
    }

    m_pSharememory->lock();
    char *sm = static_cast<char *>(m_pSharememory->data());
    QByteArray buff = "hello shareMemory";
    memcpy(sm,buff.data(),static_cast<unsigned int>(buff.size()));
    m_pSharememory->unlock();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    //读自己创建的内存不需要去绑定了
    m_pSharememory->lock();
    char *data = static_cast<char*>(m_pSharememory->data());
    QByteArray buff(data);
    qDebug()<<"--->"<<buff;
    m_pSharememory->unlock();

}
