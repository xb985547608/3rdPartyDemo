#include "pictureprocesswidget.h"
#include "ui_pictureprocessform.h"
#include <QBoxLayout>
#include <QWheelEvent>
#include <qmath.h>
#include <QFileDialog>
#include <QDebug>
#include "hsladjustdialog.h"
#include "blackwhiteadjustdialog.h"
#include "lightnesscontrastadjustdialog.h"
#include "selectivecoloradjustdialog.h"

PictureProcessWidget::PictureProcessWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::PictureProcessForm),
    zoomValue(250),
    rotateValue(0)
{
    ui->setupUi(this);

    setFrameStyle(Sunken | StyledPanel);

    scene = new QGraphicsScene(this);
    pixmapItem = new QGraphicsPixmapItem;
    scene->addItem(pixmapItem);
    openBtn = new QPushButton("打开");
    proxyOpenBtn = scene->addWidget(openBtn);

    graphicsView = new GraphicsView(this);
    graphicsView->setScene(scene);
    //关闭抗锯齿
    graphicsView->setRenderHint(QPainter::Antialiasing, false);
    graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    //择优重绘
    graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    //鼠标位置作为锚点
    graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    //允许交互
    graphicsView->setInteractive(true);
    //隐藏滚动条
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setAlignment(Qt::AlignCenter);

    QVBoxLayout *vl = new QVBoxLayout(ui->displayArea);
    vl->setMargin(0);
    vl->addWidget(graphicsView);

    /*色相饱和度调节*/
    hslAdjustDialog = new HSLAdjustDialog(this, this);
    connect(ui->hslBtn, &QPushButton::clicked, this, [this](){
        handlePopupDialog(hslAdjustDialog);
    });
    connect(hslAdjustDialog, &HSLAdjustDialog::signalAdjustImage, this, &PictureProcessWidget::handleAdjustImage);
    /*黑白调节*/
    bwAdjustDialog = new BlackWhiteAdjustDialog(this, this);
    connect(ui->bwBtn, &QPushButton::clicked, this, [this](){
        handlePopupDialog(bwAdjustDialog);
    });
    connect(bwAdjustDialog, &BlackWhiteAdjustDialog::signalAdjustImage, this, &PictureProcessWidget::handleAdjustImage);
    /*亮度对比度调节*/
    lcAdjustDialog = new LightnessContrastAdjustDialog(this, this);
    connect(ui->lcBtn, &QPushButton::clicked, this, [this](){
        handlePopupDialog(lcAdjustDialog);
    });
    connect(lcAdjustDialog, &LightnessContrastAdjustDialog::signalAdjustImage, this, &PictureProcessWidget::handleAdjustImage);
    /*可选颜色调节*/
    scAdjustDialog = new SelectiveColorAdjustDialog(this, this);
    connect(ui->scBtn, &QPushButton::clicked, this, [this](){
        handlePopupDialog(scAdjustDialog);
    });
    connect(scAdjustDialog, &SelectiveColorAdjustDialog::signalAdjustImage, this, &PictureProcessWidget::handleAdjustImage);


    connect(openBtn,        &QPushButton::clicked, this, &PictureProcessWidget::onOpenBtn);
    connect(ui->resetBtn,   &QPushButton::clicked, this, &PictureProcessWidget::onResetBtn);
    connect(ui->closeBtn,   &QPushButton::clicked, this, &PictureProcessWidget::onCloseBtn);
    connect(ui->saveBtn,    &QPushButton::clicked, this, &PictureProcessWidget::onSaveBtn);
}

//获取预览的采样图像
QImage PictureProcessWidget::sampleImage()
{
    int bytes = currentImage.byteCount();
    QImage temp;

    //由于处理数据过大时会有迟滞感，所以图像过大时重采样，保证预览图像大小低于设定的值
    if (bytes <= LIMIT_HANDLE_BYTES) {
        temp = currentImage;
    } else {
        //计算缩放因子并获取缩放后的图像
        qreal scale = LIMIT_HANDLE_BYTES / (qreal)bytes;
        scale = sqrt(scale);
        temp = currentImage.scaled((int)(scale * currentImage.width()) / 4 * 4, scale * currentImage.height());

        //调整场景的大小，以保持在视图的中央
        scene->setSceneRect(0, 0, temp.width(), temp.height());

        //图像缩小了多少就放大多少倍
        scale = 1 / scale;
        QMatrix matrix = graphicsView->matrix();
        matrix.scale(scale, scale);
        graphicsView->setMatrix(matrix);
        graphicsView->centerOn(pixmapItem);
    }

    qDebug() << temp.size();
    return temp;
}

void PictureProcessWidget::resizeEvent(QResizeEvent *event)
{
    //保持按钮在视图中央
    if (originImage.isNull())
        graphicsView->centerOn(proxyOpenBtn);

    QWidget::resizeEvent(event);
}

//放大
void PictureProcessWidget::zoomIn(int level)
{
    if (filePath.isNull())
        return;
    zoomValue += level;
    zoomValue = qMin(500, zoomValue);
    setupMatrix();
}

//缩小
void PictureProcessWidget::zoomOut(int level)
{
    if (originImage.isNull())
        return;
    zoomValue -= level;
    zoomValue = qMax(0, zoomValue);
    setupMatrix();
}

//矩阵变换
void PictureProcessWidget::setupMatrix()
{
    qreal scale = qPow(qreal(2), (zoomValue - 250) / qreal(50));

    QMatrix matrix;
    matrix.scale(scale, scale);
    matrix.rotate(rotateValue);

    graphicsView->setMatrix(matrix);
}

//演示矫正过后的图片
void PictureProcessWidget::handleAdjustImage(QImage img)
{
    if (img.isNull())
        return;
    currentImage = img;
    pixmapItem->setPixmap(QPixmap::fromImage(currentImage));
}

//处理调整后的图像
void PictureProcessWidget::handlePopupDialog(AdjustDialog *adjustDialog)
{
    if (adjustDialog->exec() == QDialog::Accepted) {
        //确认修改图像，获取原图矫正后的图像，而非预览图像
        QImage temp = adjustDialog->adjust(originImage);
        if (!temp.isNull()) {
            originImage = temp;
        }
    }
    currentImage = originImage;
    pixmapItem->setPixmap(QPixmap::fromImage(currentImage));
    scene->setSceneRect(0, 0, currentImage.width(), currentImage.height());
    setupMatrix();
}

void PictureProcessWidget::onCloseBtn()
{
    filePath.clear();
    originImage = QImage();
    currentImage = QImage();
    pixmapItem->setPixmap(QPixmap());

    zoomValue = 250;
    rotateValue = 0;
    setupMatrix();

    openBtn->setVisible(true);
    pixmapItem->setVisible(false);
    scene->setSceneRect(0, 0, openBtn->width(), openBtn->height());
    graphicsView->centerOn(proxyOpenBtn);
}

void PictureProcessWidget::onResetBtn()
{
    originImage = QImage(filePath);
    if (originImage.isNull())
        return;

    originImage = originImage.convertToFormat(QImage::Format_RGB888);
    //保证图像的宽度4字节对齐
    originImage = originImage.scaled(originImage.width() / 4 * 4, originImage.height());
    pixmapItem->setPixmap(QPixmap::fromImage(originImage));
    currentImage = originImage;

    scene->setSceneRect(0, 0, originImage.width(), originImage.height());
    graphicsView->centerOn(pixmapItem);
}

void PictureProcessWidget::onOpenBtn()
{
    QString srcPath = QFileDialog::getOpenFileName(this, "选择需要打开的图片", QDir::currentPath(), "Images (*.png *.xpm *.jpg)");
    if (!srcPath.isNull()) {
        filePath = srcPath;
        onResetBtn();

        if (!originImage.isNull()) {
            openBtn->setVisible(false);
            pixmapItem->setVisible(true);
            graphicsView->centerOn(pixmapItem);
        }
    }
}

void PictureProcessWidget::onSaveBtn()
{
    currentImage.save("temp.jpg");
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier) {
        if (event->delta() > 0)
            d->zoomIn(6);
        else
            d->zoomOut(6);
        event->accept();
    } else {
        QGraphicsView::wheelEvent(event);
    }
}
