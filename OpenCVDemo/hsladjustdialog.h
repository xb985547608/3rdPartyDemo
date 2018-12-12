#ifndef HSLADJUSTDIALOG_H
#define HSLADJUSTDIALOG_H

#include <QDialog>
#include "opencv/cv.h"
#include "opencv/cxcore.h"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "hsl.h"
#include <QImage>
#include "adjustdialog.h"

using namespace cv;
namespace Ui{
class HSLAdjustForm;
}

class HSLAdjustDialog : public AdjustDialog
{
    Q_OBJECT
public:
    explicit HSLAdjustDialog(PictureProcessWidget *d, QWidget *parent = nullptr);

public slots:
    void reset() override;
    void adjust() override;
    QImage adjust(QImage img) override;

    void adjustColor();

private:
    Ui::HSLAdjustForm *ui;

    HSL hsl;
    int colorIndex;
};

#endif // HSLADJUSTDIALOG_H
