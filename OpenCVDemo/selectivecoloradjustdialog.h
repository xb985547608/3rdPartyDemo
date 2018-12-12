#ifndef SELECTIVECOLORADJUSTDIALOG_H
#define SELECTIVECOLORADJUSTDIALOG_H

#include <QDialog>
#include <cstdio>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "selectivecolor.h"
#include "adjustdialog.h"

using namespace cv;
namespace Ui {
class SelectiveColorAdjustForm;
}

class SelectiveColorAdjustDialog : public AdjustDialog
{
    Q_OBJECT
public:
    explicit SelectiveColorAdjustDialog(PictureProcessWidget *d, QWidget *parent = nullptr);

public slots:
    void reset() override;
    void adjust() override;
    QImage adjust(QImage img) override;

    void channelRead(int index);
    void channelWrite();

private:
    Ui::SelectiveColorAdjustForm *ui;

    SelectiveColor  selectiveColor;
    int color;
};

#endif // SELECTIVECOLORADJUSTDIALOG_H
