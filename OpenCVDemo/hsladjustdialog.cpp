#include "hsladjustdialog.h"
#include "ui_hsladjustform.h"
#include <qmath.h>
#include <QDebug>

HSLAdjustDialog::HSLAdjustDialog(PictureProcessWidget *d, QWidget *parent) :
    AdjustDialog(d, parent),
    ui(new Ui::HSLAdjustForm)
{
    ui->setupUi(this);

    ui->hueEdit->setValidator(new QIntValidator(-180, 180, this));
    ui->saturationEdit->setValidator(new QIntValidator(-100, 100, this));
    ui->lightnessEdit->setValidator(new QIntValidator(-100, 100, this));

    connect(ui->colorSelect, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &HSLAdjustDialog::adjustColor);
    connect(ui->hueSlider,        &QSlider::valueChanged, this, static_cast<void (AdjustDialog::*)()>(&AdjustDialog::adjust));
    connect(ui->saturationSlider, &QSlider::valueChanged, this, static_cast<void (AdjustDialog::*)()>(&AdjustDialog::adjust));
    connect(ui->lightnessSlider,  &QSlider::valueChanged, this, static_cast<void (AdjustDialog::*)()>(&AdjustDialog::adjust));

    QIntValidator *intVali1 = new QIntValidator(-180, 180, this);
    ui->hueEdit->setValidator(intVali1);
    QIntValidator *intVali2 = new QIntValidator(-100, 100, this);
    ui->saturationEdit->setValidator(intVali2);
    ui->lightnessEdit->setValidator(intVali2);

    connect(ui->hueEdit, &QLineEdit::textEdited, this, [this](const QString &text){
        ui->hueSlider->setValue(text.toInt());
    });
    connect(ui->saturationEdit, &QLineEdit::textEdited, this, [this](const QString &text){
        ui->saturationSlider->setValue(text.toInt());
    });
    connect(ui->lightnessEdit, &QLineEdit::textEdited, this, [this](const QString &text){
        ui->lightnessSlider->setValue(text.toInt());
    });

    connect(ui->confirmBtn, &QPushButton::clicked, this, &HSLAdjustDialog::accept);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &HSLAdjustDialog::reject);
    adjustColor();
}

void HSLAdjustDialog::reset()
{
    colorIndex = 0;
    ui->hueSlider->setValue(0);
    ui->saturationSlider->setValue(0);
    ui->lightnessSlider->setValue(0);
    adjustColor();
}

void HSLAdjustDialog::adjust()
{
    ui->hueEdit->setText(QString::number(ui->hueSlider->value()));
    ui->saturationEdit->setText(QString::number(ui->saturationSlider->value()));
    ui->lightnessEdit->setText(QString::number(ui->lightnessSlider->value()));

    hsl.channels[colorIndex].hue = ui->hueSlider->value();
    hsl.channels[colorIndex].saturation = ui->saturationSlider->value();
    hsl.channels[colorIndex].brightness = ui->lightnessSlider->value();

    hsl.adjust(src, dst);
    //这里没有数据拷贝，所以dst需要设置成静态变量，否则会自行销毁，产生野指针
    QImage dstImage(dst.data, dst.cols, dst.rows, QImage::Format_RGB888);
    emit signalAdjustImage(dstImage);
}

QImage HSLAdjustDialog::adjust(QImage img)
{
    if (img.isNull())
        return QImage();

    src.create(img.height(), img.width(), CV_8UC3);
    memcpy(src.data, img.scanLine(0), img.byteCount());

    hsl.adjust(src, dst);
    QImage dstImage(dst.data, dst.cols, dst.rows, QImage::Format_RGB888);
    return dstImage;
}

void HSLAdjustDialog::adjustColor()
{
    colorIndex = ui->colorSelect->currentIndex();
    colorIndex = qBound(0, colorIndex, 6);

    ui->hueSlider->setValue(hsl.channels[colorIndex].hue);
    ui->saturationSlider->setValue(hsl.channels[colorIndex].saturation);
    ui->lightnessSlider->setValue(hsl.channels[colorIndex].brightness);

    adjust();
}
