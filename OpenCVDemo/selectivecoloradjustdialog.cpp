#include "selectivecoloradjustdialog.h"
#include "ui_selectivecoloradjustform.h"
#include <QListWidget>

SelectiveColorAdjustDialog::SelectiveColorAdjustDialog(PictureProcessWidget *d, QWidget *parent) :
    AdjustDialog(d, parent),
    ui(new Ui::SelectiveColorAdjustForm)
{
    ui->setupUi(this);

    QListWidget *listWidget = new QListWidget(this);
    ui->comboBox->setModel(listWidget->model());
    ui->comboBox->setView(listWidget);
    QPixmap pixmap(16, 16);
    QListWidgetItem *item;
    Q_UNUSED(item);
    pixmap.fill(Qt::red);
    item = new QListWidgetItem(QIcon(pixmap), "红色", listWidget);
    pixmap.fill(Qt::yellow);
    item = new QListWidgetItem(QIcon(pixmap), "黄色", listWidget);
    pixmap.fill(Qt::green);
    item = new QListWidgetItem(QIcon(pixmap), "绿色", listWidget);
    pixmap.fill(Qt::cyan);
    item = new QListWidgetItem(QIcon(pixmap), "青色", listWidget);
    pixmap.fill(Qt::blue);
    item = new QListWidgetItem(QIcon(pixmap), "蓝色", listWidget);
    pixmap.fill(Qt::magenta);
    item = new QListWidgetItem(QIcon(pixmap), "洋红", listWidget);
    pixmap.fill(Qt::white);
    item = new QListWidgetItem(QIcon(pixmap), "白色", listWidget);
    pixmap.fill(Qt::gray);
    item = new QListWidgetItem(QIcon(pixmap), "中性色", listWidget);
    pixmap.fill(Qt::black);
    item = new QListWidgetItem(QIcon(pixmap), "黑色", listWidget);

    connect(ui->comboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &SelectiveColorAdjustDialog::channelRead);

    connect(ui->absBtn,         &QRadioButton::toggled, this, static_cast<void (AdjustDialog::*)()>(&AdjustDialog::adjust));
    connect(ui->cyanSlider,     &QSlider::valueChanged, this, static_cast<void (AdjustDialog::*)()>(&AdjustDialog::adjust));
    connect(ui->magentaSlider,  &QSlider::valueChanged, this, static_cast<void (AdjustDialog::*)()>(&AdjustDialog::adjust));
    connect(ui->yellowSlider,   &QSlider::valueChanged, this, static_cast<void (AdjustDialog::*)()>(&AdjustDialog::adjust));
    connect(ui->blackSlider,    &QSlider::valueChanged, this, static_cast<void (AdjustDialog::*)()>(&AdjustDialog::adjust));

    QIntValidator *intVali = new QIntValidator(-100, 100, this);
    ui->cyanEdit->setValidator(intVali);
    ui->magentaEdit->setValidator(intVali);
    ui->yellowEdit->setValidator(intVali);
    ui->blackEdit->setValidator(intVali);

    connect(ui->cyanEdit, &QLineEdit::textEdited, this, [this](const QString &text){
        ui->cyanSlider->setValue(text.toInt());
    });
    connect(ui->magentaEdit, &QLineEdit::textEdited, this, [this](const QString &text){
        ui->magentaSlider->setValue(text.toInt());
    });
    connect(ui->yellowEdit, &QLineEdit::textEdited, this, [this](const QString &text){
        ui->yellowSlider->setValue(text.toInt());
    });
    connect(ui->blackEdit, &QLineEdit::textEdited, this, [this](const QString &text){
        ui->blackSlider->setValue(text.toInt());
    });

    connect(ui->confirmBtn,     &QPushButton::clicked, this, &SelectiveColorAdjustDialog::accept);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &SelectiveColorAdjustDialog::reject);
}

void SelectiveColorAdjustDialog::reset()
{
    color = 0;
    ui->comboBox->setCurrentIndex(0);

    ui->cyanSlider->setValue(0);
    ui->magentaSlider->setValue(0);
    ui->yellowSlider->setValue(0);
    ui->blackSlider->setValue(0);

    ui->cyanEdit->setText(QString::number(0));
    ui->magentaEdit->setText(QString::number(0));
    ui->yellowEdit->setText(QString::number(0));
    ui->blackEdit->setText(QString::number(0));

    selectiveColor.reset();
    channelRead(0);
}

void SelectiveColorAdjustDialog::adjust()
{
    channelWrite();
    selectiveColor.adjust(src, dst);

    //这里没有数据拷贝，所以dst需要设置成静态变量，否则会自行销毁，产生野指针
    QImage dstImage(dst.data, dst.cols, dst.rows, QImage::Format_RGB888);
    emit signalAdjustImage(dstImage);
}

QImage SelectiveColorAdjustDialog::adjust(QImage img)
{
    if (img.isNull())
        return QImage();

    src.create(img.height(), img.width(), CV_8UC3);
    memcpy(src.data, img.scanLine(0), img.byteCount());

    selectiveColor.adjust(src, dst);
    QImage dstImage(dst.data, dst.cols, dst.rows, QImage::Format_RGB888);
    return dstImage;
}

void SelectiveColorAdjustDialog::channelRead(int index)
{
    color = index;
    SelectiveColorAdjust * current = NULL;
    if ( color >=0 && color <= 9)
        current = &(selectiveColor.colors[color]);
    if ( current == NULL ) return;

    int cyan = current->cyan * 100;
    int magenta = current->magenta * 100;
    int yellow = current->yellow * 100;
    int black = current->black * 100;

    ui->cyanSlider->setValue(cyan);
    ui->magentaSlider->setValue(magenta);
    ui->yellowSlider->setValue(yellow);
    ui->blackSlider->setValue(black);

    ui->cyanEdit->setText(QString::number(cyan));
    ui->magentaEdit->setText(QString::number(magenta));
    ui->yellowEdit->setText(QString::number(yellow));
    ui->blackEdit->setText(QString::number(black));

    ui->absBtn->setChecked(selectiveColor.isAbsolute);

    adjust();
}

void SelectiveColorAdjustDialog::channelWrite()
{
    SelectiveColorAdjust * current = NULL;
    if ( color >=0 && color <= 9)
        current = &(selectiveColor.colors[color]);
    if ( current == NULL ) return;

    current->cyan = ui->cyanSlider->value() / 100.0;
    current->magenta =  ui->magentaSlider->value() / 100.0;
    current->yellow =  ui->yellowSlider->value() / 100.0;
    current->black =  ui->blackSlider->value() / 100.0;

    ui->cyanEdit->setText(QString::number(ui->cyanSlider->value()));
    ui->magentaEdit->setText(QString::number(ui->magentaSlider->value()));
    ui->yellowEdit->setText(QString::number(ui->yellowSlider->value()));
    ui->blackEdit->setText(QString::number(ui->blackSlider->value()));

    selectiveColor.isAbsolute = ui->absBtn->isChecked();
}
