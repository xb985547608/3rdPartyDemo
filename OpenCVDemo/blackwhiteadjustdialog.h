#ifndef BLACKWHITEADJUSTDIALOG_H
#define BLACKWHITEADJUSTDIALOG_H

#include <QDialog>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "blackwhite.h"
#include <QImage>
#include "adjustdialog.h"

using namespace cv;
namespace Ui {
class BlackWhiteAdjustForm;
}

class BlackWhiteAdjustDialog : public AdjustDialog
{
    Q_OBJECT
public:
    explicit BlackWhiteAdjustDialog(PictureProcessWidget *d, QWidget *parent = nullptr);

public slots:
    void reset() override;
    void adjust() override;
    QImage adjust(QImage img) override;

private:
    Ui::BlackWhiteAdjustForm *ui;

    BlackWhite bw;
};

#endif // BLACKWHITEADJUSTDIALOG_H
