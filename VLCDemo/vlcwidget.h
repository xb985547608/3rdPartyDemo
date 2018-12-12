#ifndef VLCWIDGET_H
#define VLCWIDGET_H

#include <QWidget>
#include <vlc/vlc.h>

namespace Ui {
class VLCForm;
};

class VLCWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VLCWidget(QWidget *parent = nullptr);

signals:

public slots:
    static void libvlc_callback(const libvlc_event_t* event, void* data);

private:
    Ui::VLCForm* ui;

    libvlc_instance_t* mInstance;
    QList<QPair<libvlc_media_t*, libvlc_media_player_t*>> mMediaHandles;
    QStringList urls;
};

#endif // VLCWIDGET_H
