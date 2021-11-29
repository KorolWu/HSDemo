#include "canny_plugin.h"

#include "ui_plugin.h"



Canny_Plugin::Canny_Plugin()
{

}

Canny_Plugin::~Canny_Plugin()
{

}

QString Canny_Plugin::title()
{
    return this->metaObject()->className();
}

QString Canny_Plugin::version()
{
    return "1.0.0";
}

QString Canny_Plugin::description()
{
    return "A <b>Template</b> plugin";
}

QString Canny_Plugin::help()
{
    return "This is a <b>Template</b> plugin. Clone and use it to create new plugins.";
}

void Canny_Plugin::setupUi(QWidget *parent)
{
    ui = new Ui::PluginGui;
    ui->setupUi(parent);
    // Connect signals for GUI elemnts manually here since they won't be connected by name in a plugin
     connect(ui->spinBoxParameter1,SIGNAL(valueChanged(int)),this,SLOT(on_spinBoxParameter1_valueChanged(int)));
     connect(ui->spinBoxParameter2,SIGNAL(valueChanged(int)),this,SLOT(on_spinBoxParameter2_valueChanged(int)));
    // ...
    // emit updateNeeded(); should be added whenever parameters on the plugin GUI change
}

void Canny_Plugin::processImage(const cv::Mat &inputImage, cv::Mat &outputImage)
{
    using namespace  cv;
    // Replace the following line with the actual image processing task
    inputImage.copyTo(outputImage);
    Mat gray,result;
    int parameter1 = ui->spinBoxParameter1->value();
    int parameter2 = ui->spinBoxParameter2->value();
//   if(inputImage.type() != CV_8U)
//    {
        cvtColor(inputImage,gray,COLOR_BGR2GRAY);

//    }
    Canny(gray,result,parameter1,parameter2);
    cvtColor(result,outputImage,COLOR_GRAY2BGR);



    // Otherwise, if the process doesn't affect the output image, update plugin GUI here ...
}


void Canny_Plugin::on_spinBoxParameter1_valueChanged(int arg1)
{
    Q_UNUSED(arg1)
    emit updateNeeded();
}

void Canny_Plugin::on_spinBoxParameter2_valueChanged(int arg1)
{
    Q_UNUSED(arg1)
    emit updateNeeded();
}
