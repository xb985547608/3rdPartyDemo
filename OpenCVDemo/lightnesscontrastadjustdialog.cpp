#include "lightnesscontrastadjustdialog.h"
#include "pictureprocesswidget.h"
#include "ui_lightnesscontrastadjustform.h"

LightnessContrastAdjustDialog::LightnessContrastAdjustDialog(PictureProcessWidget *d, QWidget *parent) :
    AdjustDialog(d, parent),
    ui(new Ui::LightnessContrastAdjustForm)
{
    ui->setupUi(this);
    connect(ui->lightnessSlider, &QSlider::valueChanged, this, static_cast<void (AdjustDialog::*)()>(&AdjustDialog::adjust));
    connect(ui->contrastSlider,  &QSlider::valueChanged, this, static_cast<void (AdjustDialog::*)()>(&AdjustDialog::adjust));

    QIntValidator *intVali = new QIntValidator(-255, 255, this);
    ui->lightnessEdit->setValidator(intVali);
    ui->contrastEdit->setValidator(intVali);

    connect(ui->lightnessEdit, &QLineEdit::textEdited, this, [this](const QString &text){
        ui->lightnessSlider->setValue(text.toInt());
    });
    connect(ui->contrastEdit, &QLineEdit::textEdited, this, [this](const QString &text){
        ui->contrastSlider->setValue(text.toInt());
    });

    connect(ui->confirmBtn, &QPushButton::clicked, this, &LightnessContrastAdjustDialog::accept);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &LightnessContrastAdjustDialog::reject);
}

void LightnessContrastAdjustDialog::reset()
{
    ui->lightnessSlider->setValue(0);
    ui->contrastSlider->setValue(0);
    ui->lightnessEdit->setText(QString::number(0));
    ui->contrastEdit->setText(QString::number(0));

    adjust();
}

void LightnessContrastAdjustDialog::adjust()
{
    algorithmAdjust(src, dst);
    //这里没有数据拷贝，所以dst需要设置成静态变量，否则会自行销毁，产生野指针
    QImage dstImage(dst.data, dst.cols, dst.rows, QImage::Format_RGB888);
    emit signalAdjustImage(dstImage);
}

QImage LightnessContrastAdjustDialog::adjust(QImage img)
{
    if (img.isNull())
        return QImage();

    src.create(img.height(), img.width(), CV_8UC3);
    memcpy(src.data, img.scanLine(0), img.byteCount());

    algorithmAdjust(src, dst);
    QImage dstImage(dst.data, dst.cols, dst.rows, QImage::Format_RGB888);
    return dstImage;
}

void LightnessContrastAdjustDialog::algorithmAdjust(InputArray src, OutputArray dst)
{
    Mat input = src.getMat();
    if( input.empty() ) {
        return;
    }

    dst.create(src.size(), src.type());
    Mat output = dst.getMat();

    int lightness = ui->lightnessSlider->value();
    int contrast = ui->contrastSlider->value();

    /**
    Algorithm of Brightness Contrast transformation
    The formula is:
        y = [x - 127.5 * (1 - B)] * k + 127.5 * (1 + B);

        x is the input pixel value
        y is the output pixel value
        B is brightness, value range is [-1,1]
        k is used to adjust contrast
            k = tan( (45 + 44 * c) / 180 * PI );
            c is contrast, value range is [-1,1]
    */

    double B = lightness / 255.0;
    double c = contrast / 255.0;
    double k = tan( (45 + 44 * c) / 180 * M_PI );

    Mat lookupTable(1, 256, CV_8U);
    uchar *p = lookupTable.data;
    for (int i = 0; i < 256; i++)
        p[i] = qBound(0.0, (i - 127.5 * (1 - B)) * k + 127.5 * (1 + B), 255.0);

    LUT(input, lookupTable, output);
}
