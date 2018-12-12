#ifndef LIGHTNESSCONTRASTADJUSTDIALOG_H
#define LIGHTNESSCONTRASTADJUSTDIALOG_H

#include <QDialog>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "adjustdialog.h"


#define M_PI       3.1415926535897931160E0

using namespace cv;
namespace Ui {
class LightnessContrastAdjustForm;
}

class LightnessContrastAdjustDialog : public AdjustDialog
{
    Q_OBJECT
public:
    explicit LightnessContrastAdjustDialog(PictureProcessWidget *d, QWidget *parent = nullptr);

public slots:
    void reset() override;
    void adjust() override;
    QImage adjust(QImage img) override;

private:
    void algorithmAdjust(InputArray src, OutputArray dst);

private:
    Ui::LightnessContrastAdjustForm *ui;

};

#endif // LIGHTNESSCONTRASTADJUSTDIALOG_H
