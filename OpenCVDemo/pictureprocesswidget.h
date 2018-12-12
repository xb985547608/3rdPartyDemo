#ifndef PICTUREPROCESSWIDGET_H
#define PICTUREPROCESSWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsProxyWidget>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QLabel>
#include <QPushButton>
#include <QDialog>

class AdjustDialog;
class HSLAdjustDialog;
class LightnessContrastAdjustDialog;
class BlackWhiteAdjustDialog;
class SelectiveColorAdjustDialog;

#define LIMIT_HANDLE_BYTES  1000000

namespace Ui {
class PictureProcessForm;
}

class PictureProcessWidget : public QFrame
{
    Q_OBJECT
public:
    explicit PictureProcessWidget(QWidget *parent = nullptr);

    QImage sampleImage();
protected:
    void resizeEvent(QResizeEvent *event) override;

signals:

public slots:
    void zoomIn(int level = 1);
    void zoomOut(int level = 1);
    void setupMatrix();
    void handleAdjustImage(QImage img);
    void handlePopupDialog(AdjustDialog *adjustDialog);

    void onCloseBtn();
    void onResetBtn();
    void onOpenBtn();
    void onSaveBtn();

private:
    Ui::PictureProcessForm *ui;

    QImage currentImage;                            //临时图像
    QImage originImage;                             //确认修改后的图像
    QString filePath;                               //处理的图像文件的路径

    QGraphicsView *graphicsView;                    //演示场景的视图
    QGraphicsScene *scene;                          //存放图元的场景
    QGraphicsPixmapItem *pixmapItem;                //图片图元
    QPushButton *openBtn;
    QGraphicsProxyWidget *proxyOpenBtn;
    int zoomValue;                                  //缩放值
    int rotateValue;                                //旋转值

    HSLAdjustDialog *hslAdjustDialog;               //调整色相/饱和度
    BlackWhiteAdjustDialog *bwAdjustDialog;         //调整黑白程度
    LightnessContrastAdjustDialog *lcAdjustDialog;  //调整亮度/对比度
    SelectiveColorAdjustDialog *scAdjustDialog;     //颜色调整
};

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView(PictureProcessWidget *d) : QGraphicsView(), d(d){ }

protected:
    void wheelEvent(QWheelEvent *event) override;

private:
    PictureProcessWidget *d;
};

#endif // PICTUREPROCESSWIDGET_H
