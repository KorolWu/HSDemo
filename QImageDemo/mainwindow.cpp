#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   // ui->label->setPixmap(QPixmap(QPixmap::fromImage(*mirroredImage(image,1))));
    //extractImage(image);
  QImage src("C:\\Users\\jian.shen\\Documents\\QImageDemo\\1.bmp");
  bitMap("C:\\Users\\jian.shen\\Documents\\QImageDemo\\1.bmp");
   qDebug()<<"width"<<src.width()<<"heitht:"<<src.height()<<"totle count byte:"<<src.sizeInBytes()<<" line byte count:"<<src.bytesPerLine()<<"format:"<<src.format();


    //creatGreyImage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

///
/// \brief MainWindow::grey
/// \param src  输入的QImage图像
/// \return 返回传入图像的灰度图像
///
QImage *MainWindow::grey(QImage *src)
{
    if(src == nullptr || src->width() == 0)
        return nullptr;
    QImage *image = new QImage(src->width(),src->height(),QImage::Format_Mono);//构建一张和原图一样大小的图
    for(int i = 0; i < image->height();i++)//遍历每一行
    {
        QRgb* line = reinterpret_cast<QRgb*>(src->scanLine(i));//拿到某一行的指针强转为QRgb类型
        for (int j = 0; j < image->width(); j++)//遍历这一行中每一个像素点，并重新赋值
        {
             int average = (qRed(line[j]) + qGreen(line[j]) + qRed(line[j]))/3;
            image->setPixel(j,i,qRgb(average,average,average));
        }
    }
    image->save("C:\\Users\\jian.shen\\Pictures\\beautiful1.png");
    return image;
}

///
/// \brief MainWindow::extractImage
/// \param src
/// \return
///
bool MainWindow::extractImage(QImage *src)
{
    if(src == nullptr || src->width() == 0)
    {
        return false;
    }
    src->convertTo(QImage::Format_Indexed8);
    QImage dst_frist (src->width(),src->height(),src->format());
    QImage dst_second(src->width(),src->height(),src->format());
    QVector<QRgb > colorTable;
    colorTable = src->colorTable();
//    for(int i = 0;i < 256; i++)
//    {
//        if(i == 0)
//        colorTable.push_back(qRgb(0,0,0));
//        else
//             colorTable.push_back(qRgb(255,255,255));
//    }
    dst_frist.setColorTable(colorTable);
    dst_second.setColorTable(colorTable);
   // src->setColorTable(colorTable);

    for (int y = 0; y < src->height();y++)
    {
      uchar *lienPer = src->scanLine(y);
       for(int x = 0; x < src->width();x++)
       {
            dst_frist.setPixel(x,y,0);// ??单色位图只有 0 1
            dst_second.setPixel(x,y,0);
            if(y%2 == 0)
            {
                if(lienPer[x] == 1)
                  dst_frist.setPixel(x,y,1);
                else
                    dst_frist.setPixel(x,y,0);
            }
            else
            {
                dst_second.setPixel(x,y,lienPer[x]);
            }
       }
    }

    dst_frist.save("C:\\Users\\jian.shen\\Pictures\\dst_frist.bmp");
    dst_second.save("C:\\Users\\jian.shen\\Pictures\\dst_second.bmp");
    return true;

}

void MainWindow::creatGreyImage()
{
    QImage * gray = new QImage(100,100,QImage::Format_Grayscale8);
    QVector<QRgb > colorTable;
    for(int i = 0;i < 256; i++)
    {
        colorTable.push_back(qRgb(i,i,i));
    }
    gray->setColorTable(colorTable);
    for(int y = 0; y < gray->height(); y++)
    {
        for(int x = 0; x < gray->width(); x++)
        {
            gray->setPixel(x,y,qRgb(y%255,y%255,y%255));//y%3 ? 0: 255);

        }
    }
    gray->save("C:\\Users\\jian.shen\\Pictures\\newGrey.png");
}

///
/// \brief MainWindow::mirroredImage  镜像图像
/// \param src  原图像
/// \param dir  方向 0=x方向     1=y方向
/// \return
///
QImage *MainWindow::mirroredImage(const QImage *src, int dir)
{
    QImage *dst = new QImage();
    if(dir == 0)
         *dst = src->mirrored(true,false);
    else if(dir == 1)
        *dst = src->mirrored(false,true);
    return dst;
}

///
/// \brief MainWindow::bitMap
/// path
/// 读取单色位图  位深度 = 1    QImage只支持位深度 = 1 =8 =16的图片
///
void MainWindow::bitMap(QString path)
{
    QImage bitmap(path);
    qDebug()<<"height:"<<bitmap.height()<<"width:"<<bitmap.width();
    if(bitmap.depth() != 1) //如果位深度不是==1
        return;
    for(int x = 0; x< bitmap.width();x++)
    {
        uchar *perLine = bitmap.scanLine(x);//这一样的首地址
        QVector<int> testVec;
        for(int y = 0; y < bitmap.width(); y++)
        {
            char value =perLine[y/8] >> (7 - y%8) & 0x01;//

            testVec.append(value);
        }
        qDebug()<<testVec;
    }


}


