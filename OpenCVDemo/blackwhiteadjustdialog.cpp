#include "blackwhiteadjustdialog.h"
#include "ui_blackwhiteadjustform.h"

BlackWhiteAdjustDialog::BlackWhiteAdjustDialog(PictureProcessWidget *d, QWidget *parent) :
    AdjustDialog(d, parent),
    ui(new Ui::BlackWhiteAdjustForm)
{
    ui->setupUi(this);

    connect(ui->redSlider,      &QSlider::valueChanged, this, static_cast<void (AdjustDialog::*)()>(&AdjustDialog::adjust));
    connect(ui->yellowSlider,   &QSlider::valueChanged, this, static_cast<void (AdjustDialog::*)()>(&AdjustDialog::adjust));
    connect(ui->greenSlider,    &QSlider::valueChanged, this, static_cast<void (AdjustDialog::*)()>(&AdjustDialog::adjust));
    connect(ui->cyanSlider,     &QSlider::valueChanged, this, static_cast<void (AdjustDialog::*)()>(&AdjustDialog::adjust));
    connect(ui->blueSlider,     &QSlider::valueChanged, this, static_cast<void (AdjustDialog::*)()>(&AdjustDialog::adjust));
    connect(ui->magentaSlider,  &QSlider::valueChanged, this, static_cast<void (AdjustDialog::*)()>(&AdjustDialog::adjust));

    QIntValidator *intVali = new QIntValidator(-200, 300, this);
    ui->redEdit->setValidator(intVali);
    ui->yellowEdit->setValidator(intVali);
    ui->greenEdit->setValidator(intVali);
    ui->cyanEdit->setValidator(intVali);
    ui->blueEdit->setValidator(intVali);
    ui->magentaEdit->setValidator(intVali);

    connect(ui->redEdit, &QLineEdit::textEdited, this, [this](const QString &text){
        ui->redSlider->setValue(text.toInt());
    });
    connect(ui->yellowEdit, &QLineEdit::textEdited, this, [this](const QString &text){
        ui->yellowSlider->setValue(text.toInt());
    });
    connect(ui->greenEdit, &QLineEdit::textEdited, this, [this](const QString &text){
        ui->greenSlider->setValue(text.toInt());
    });
    connect(ui->cyanEdit, &QLineEdit::textEdited, this, [this](const QString &text){
        ui->cyanSlider->setValue(text.toInt());
    });
    connect(ui->blueEdit, &QLineEdit::textEdited, this, [this](const QString &text){
        ui->blueSlider->setValue(text.toInt());
    });
    connect(ui->magentaEdit, &QLineEdit::textEdited, this, [this](const QString &text){
        ui->magentaSlider->setValue(text.toInt());
    });

    connect(ui->confirmBtn, &QPushButton::clicked, this, &BlackWhiteAdjustDialog::accept);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &BlackWhiteAdjustDialog::reject);
}

void BlackWhiteAdjustDialog::reset()
{
    ui->redSlider->setValue(40);
    ui->yellowSlider->setValue(60);
    ui->greenSlider->setValue(40);
    ui->cyanSlider->setValue(60);
    ui->blueSlider->setValue(20);
    ui->magentaSlider->setValue(80);

    ui->redEdit->setText(QString::number(40));
    ui->yellowEdit->setText(QString::number(60));
    ui->greenEdit->setText(QString::number(40));
    ui->cyanEdit->setText(QString::number(60));
    ui->blueEdit->setText(QString::number(20));
    ui->magentaEdit->setText(QString::number(80));
    adjust();
}

void BlackWhiteAdjustDialog::adjust()
{
    ui->redEdit->setText(QString::number(ui->redSlider->value()));
    ui->yellowEdit->setText(QString::number(ui->yellowSlider->value()));
    ui->greenEdit->setText(QString::number(ui->greenSlider->value()));
    ui->cyanEdit->setText(QString::number(ui->cyanSlider->value()));
    ui->blueEdit->setText(QString::number(ui->blueSlider->value()));
    ui->magentaEdit->setText(QString::number(ui->magentaSlider->value()));

    bw.red      = ui->redSlider->value() / 100.0;
    bw.yellow   = ui->yellowSlider->value() / 100.0;
    bw.green    = ui->greenSlider->value() / 100.0;
    bw.cyan     = ui->cyanSlider->value() / 100.0;
    bw.blue     = ui->blueSlider->value() / 100.0;
    bw.magenta  = ui->magentaSlider->value() / 100.0;

    bw.adjust(src, dst);
    //这里没有数据拷贝，所以dst需要设置成静态变量，否则会自行销毁，产生野指针
    QImage dstImage(dst.data, dst.cols, dst.rows, QImage::Format_RGB888);
    emit signalAdjustImage(dstImage);
}

QImage BlackWhiteAdjustDialog::adjust(QImage img)
{    
    if (img.isNull())
        return QImage();

    src.create(img.height(), img.width(), CV_8UC3);
    memcpy(src.data, img.scanLine(0), img.byteCount());

    bw.adjust(src, dst);
    QImage dstImage(dst.data, dst.cols, dst.rows, QImage::Format_RGB888);
    return dstImage;
}
