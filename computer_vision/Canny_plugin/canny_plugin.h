#ifndef CANNY_PLUGIN_H
#define CANNY_PLUGIN_H

#include "canny_plugin_global.h"
#include "cvplugininterface.h"
#include <QComboBox>
#include <QSpinBox>

namespace Ui {
    class PluginGui;
}

class CANNY_PLUGINSHARED_EXPORT Canny_Plugin: public QObject, public CvPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.computervision.cvplugininterface")
    Q_INTERFACES(CvPluginInterface)
public:
    Canny_Plugin();
    ~Canny_Plugin();

    QString title();
    QString version();
    QString description();
    QString help();
    void setupUi(QWidget *parent);
    void processImage(const cv::Mat &inputImage, cv::Mat &outputImage);

signals:
    void updateNeeded();
    void errorMessage(QString msg);
    void infoMessage(QString msg);

private slots:
    void on_spinBoxParameter1_valueChanged(int arg1);

    void on_spinBoxParameter2_valueChanged(int arg1);

private:
    Ui::PluginGui *ui;

};

#endif // TEMPLATE_PLUGIN_H
