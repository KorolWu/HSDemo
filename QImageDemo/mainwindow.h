#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QRgb>
#include <QPixmap>
#include <QDebug>
#include <QPointer>
#include <QBitmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QImage * grey(QImage * src);
    bool extractImage(QImage *src);
    void creatGreyImage();
    QImage *mirroredImage(const QImage *src,int dir);
    void bitMap(QString path);

    typedef union {
        struct kchar{
            char
            bit0:1,
            bit1:1,
            bit2:1,
            bit3:1,
            bit4:1,
            bit5:1,
            bit6:1,
            bit7:1;
        };
        char v;
    }Bit;
  };
#endif // MAINWINDOW_H
