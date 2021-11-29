#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace  cv;
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Mat src,gray,binaryImage,canny;
    src = imread("C:\\Users\\jian.shen\\Pictures\\src.jpg");
    imshow("src",src);
    qDebug()<<"src Channels:"<<src.channels();
    cvtColor(src,gray,COLOR_BGR2GRAY);
     blur(gray,gray,Size(5,5));
    threshold(gray,binaryImage,0,255, THRESH_OTSU | THRESH_BINARY);
    imshow("thresh",binaryImage);
    //形态学操作
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3,3), Point(-1, -1));
    morphologyEx(binaryImage, binaryImage, MORPH_OPEN, kernel, Point(-1, -1));
    imshow("ex",binaryImage);

    //-----------------------------

    Canny(binaryImage,canny,0,255);
    imshow("canny",canny);
    std::vector<std::vector<cv::Point>> contours;
    vector<Vec4i>g_vHierarchy;
    std::vector<std::vector<cv::Point>> effectiveContours;
    //寻找轮廓，只找外轮廓，记录轮廓上的所有点
    findContours(canny,contours,g_vHierarchy,RETR_EXTERNAL,CHAIN_APPROX_NONE);
    vector<Point> cenVec;
    int interval = 72;  //每行之间的间距的像素值
    int pointFristY = 99999;
    for(uint i = 0;i<contours.size();i++)
    {
        if(contours[i].size() < 15 || contours[i].size()>35)
             continue;
           Moments  c =moments(contours[i]);

           Scalar color = Scalar(0, 0,255);
           //drawContours(src, contours, i, color,2,8);
           Point center = Point(int(c.m10 / c.m00), int(c.m01 / c.m00));
            pointFristY =  pointFristY < int(c.m01 / c.m00) ? pointFristY:int(c.m01 / c.m00);
           cenVec.push_back(center);
           circle(src,center,2,Scalar(0,0,255),2);
              // qDebug()<<center.x<<","<<center.y;
    }


    vector<Point> row1,row2,row3,row4;
    for(uint count = 0 ;count < cenVec.size(); count++)
    {
        if(cenVec.at(count).y< (pointFristY +5) && cenVec.at(count).y > (pointFristY -5))
        {
            row1.push_back(cenVec.at(count));
        }
        else if(cenVec.at(count).y < (pointFristY+(interval) +5) && cenVec.at(count).y > (pointFristY+(interval)-5))
        {
             row2.push_back(cenVec.at(count));
        }
        else if(cenVec.at(count).y < (pointFristY+(interval*2 )+5) && cenVec.at(count).y > (pointFristY+(interval*2)-5))
        {
             row3.push_back(cenVec.at(count));
        }
        else if(cenVec.at(count).y < (pointFristY+(interval*3) +5) && cenVec.at(count).y > (pointFristY+(interval*3)-5))
        {
             row4.push_back(cenVec.at(count));
        }
    }
    for(uint i = 0; i< 4;i++)
    {
        if(i == 0)
             checkPointInterval(i,row1);
        else if(i == 1)
            checkPointInterval(i,row2);
        else if(i == 2)
            checkPointInterval(i,row3);
        else if(i == 3)
            checkPointInterval(i,row4);
    }


   imshow("contours",src);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkPointInterval(uint row,std::vector<Point> &pointVec)
{
    if(pointVec.size() == 0)
        return;
    std::vector<Point> tempVec;
    for(uint i = 0; i< pointVec.size(); i++)
    {
        for(uint j = 0; j < pointVec.size();j++)
        {
            if(pointVec.at(i).x > pointVec.at(j).x)
            {
                Point temp;
                temp = pointVec.at(i);
                pointVec.at(i) = pointVec.at(j);
                pointVec.at(j) = temp;

            }
        }
    }
    for(uint count = 0; count < pointVec.size()-1;count ++)
    {
        if(row == 0)
            //qDebug()<<"--->"<< pointVec.at(count).x ;//<< pointVec.at(count+1).x;
        if((pointVec.at(count).x - pointVec.at(count+1).x) > m_interval)
        {
            qDebug()<<row<<"count = "<<count<<"pos"<<pointVec.at(count).x<<pointVec.at(count).y;
        }
    }
}

