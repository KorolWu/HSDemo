#include "copymakeborder_plugin.h"

#include "ui_plugin.h"

CopyMakeBorder_Plugin::CopyMakeBorder_Plugin()
{

}

CopyMakeBorder_Plugin::~CopyMakeBorder_Plugin()
{

}

QString CopyMakeBorder_Plugin::title()
{
    return this->metaObject()->className();
}

QString CopyMakeBorder_Plugin::version()
{
    return "1.0.0";
}

QString CopyMakeBorder_Plugin::description()
{
    return "A <b>Template</b> plugin";
}

QString CopyMakeBorder_Plugin::help()
{
    return "This is a <b>Template</b> plugin. Clone and use it to create new plugins.";
}

void CopyMakeBorder_Plugin::setupUi(QWidget *parent)
{
    ui = new Ui::PluginGui;
    ui->setupUi(parent);
    QStringList items;
    items.append("BORDER_CONSTANT");
    items.append("BORDER_REPLICATE");
    items.append("BORDER_REFLECT");
    items.append("BORDER_WRAP");
    items.append("BORDER_REFLECT_101");
    ui->borderTypeComboBox->addItems(items);
   // connect(ui->borderTypeComboBox,&QComboBox::currentIndexChanged,this,&CopyMakeBorder_Plugin::on_borderTypeComboBox_currentIndexChanged);
    connect(ui->borderTypeComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(on_borderTypeComboBox_currentIndexChanged(int)));// &CopyMakeBorder_Plugin::on_borderTypeComboBox_currentIndexChanged);
    // Connect signals for GUI elemnts manually here since they won't be connected by name in a plugin
    // ...
    // emit updateNeeded(); should be added whenever parameters on the plugin GUI change
}

void CopyMakeBorder_Plugin::processImage(const cv::Mat &inputImage, cv::Mat &outputImage)
{
    // Replace the following line with the actual image processing task
    int top,bot,left,right;
    top = bot = inputImage.rows/2;
    left = right = inputImage.cols/2;
    cv::copyMakeBorder(inputImage,outputImage,top,bot,left,right,ui->borderTypeComboBox->currentIndex());
    qDebug()<<"copyMakeBorder Plugin";
    // Otherwise, if the process doesn't affect the output image, update plugin GUI here ...
}


void CopyMakeBorder_Plugin::on_borderTypeComboBox_currentIndexChanged(int index)
{
    emit updateNeeded();
}
