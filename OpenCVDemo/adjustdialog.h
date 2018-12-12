#ifndef ADJUSTDIALOG_H
#define ADJUSTDIALOG_H

#include <QDialog>
#include "pictureprocesswidget.h"
#include "opencv/cv.h"

using namespace cv;

//调整窗口的接口类
class AdjustDialog : public QDialog
{
    Q_OBJECT
public:
    AdjustDialog(PictureProcessWidget *d, QWidget *parent = nullptr) :
        QDialog(parent),
        d(d)
    { Q_ASSERT_X(this->d != NULL, "#AdjustDialog# AdjustDialog(PictureProcessWidget*, QWidget *): ", "member:d is NULL"); }

signals:
    void signalAdjustImage(QImage image);

public slots:
    int exec() override {
        //获取预览的采样图像
        QImage img = d->sampleImage();

        if (img.isNull())
            return -1;

        Mat temp;
        temp.create(img.height(), img.width(), CV_8UC3);
        memcpy(temp.data, img.scanLine(0), img.byteCount());

        src = temp;

        //复位调整的参数
        reset();
        return QDialog::exec();
    }


    virtual void reset() = 0;
    virtual void adjust() = 0;
    virtual QImage adjust(QImage img) = 0;
protected:
    PictureProcessWidget *d;

    Mat src;
    Mat dst;
};



#endif // ADJUSTDIALOG_H
