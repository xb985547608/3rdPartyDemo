#include "vlcwidget.h"
#include "ui_vlcform.h"
#include <QDebug>

VLCWidget::VLCWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VLCForm)
{
    ui->setupUi(this);

    mInstance = libvlc_new(0, NULL);

    urls.append("file:///h:/cloudmusic/mv/out.mp4");
    urls.append("rtsp://192.168.207.1:12120/out.mp4");
    urls.append("rtsp://192.168.207.1:12120/1.mp4");
    urls.append("rtsp://192.168.207.1:12120/2.mp4");
    urls.append("rtsp://192.168.207.1:12120/3.mp4");
    urls.append("rtsp://192.168.207.1:12120/4.mp4");
    urls.append("rtsp://192.168.207.1:12120/5.mp4");
    urls.append("rtsp://192.168.207.1:12120/6.mp4");
    urls.append("rtsp://192.168.207.1:12120/7.mp4");
    urls.append("rtsp://192.168.207.1:12120/8.mp4");
    urls.append("rtsp://192.168.207.1:12120/9.mp4");
    urls.append("rtsp://192.168.207.1:12120/10.mp4");

    QList<libvlc_event_e> list;
    list << libvlc_MediaPlayerMediaChanged
         << libvlc_MediaPlayerNothingSpecial
         << libvlc_MediaPlayerOpening
         << libvlc_MediaPlayerBuffering
         << libvlc_MediaPlayerPlaying
         << libvlc_MediaPlayerPaused
         << libvlc_MediaPlayerStopped
         << libvlc_MediaPlayerForward
         << libvlc_MediaPlayerBackward
         << libvlc_MediaPlayerEndReached
         << libvlc_MediaPlayerEncounteredError
         << libvlc_MediaPlayerTimeChanged
         << libvlc_MediaPlayerPositionChanged
         << libvlc_MediaPlayerSeekableChanged
         << libvlc_MediaPlayerPausableChanged
         << libvlc_MediaPlayerTitleChanged
         << libvlc_MediaPlayerSnapshotTaken
         << libvlc_MediaPlayerLengthChanged
         << libvlc_MediaPlayerVout;


    foreach (QObject* obj, children()) {
        QFrame* frame = qobject_cast<QFrame*>(obj);
        if (frame == NULL)
            continue;

        QString sout = QString(":sout=#duplicate{dst=display,dst=es{access-video=file,access-audio=dummy,mux=ts,dst=%1.ts}}")
                               .arg(obj->objectName());
        libvlc_media_t* media = libvlc_media_new_location(mInstance, urls.takeFirst().toLocal8Bit().data());
//        libvlc_media_add_option(media, ":sout-all");
//        libvlc_media_add_option(media, ":no-loop");
//        libvlc_media_add_option(media, sout.toStdString().c_str());

        libvlc_media_player_t* player = libvlc_media_player_new(mInstance);
        libvlc_media_player_set_hwnd(player, (void*)(frame->winId()));
        libvlc_media_player_set_media(player, media);

        libvlc_event_manager_t* vlcEvent = libvlc_media_player_event_manager(player);
        foreach (const libvlc_event_e &event, list) {
            libvlc_event_attach(vlcEvent, event, libvlc_callback, this);
        }

        libvlc_media_player_play(player);

        break;
    }
}

void VLCWidget::libvlc_callback(const libvlc_event_t *event, void *data)
{
    VLCWidget* vlcWidget = static_cast<VLCWidget*>(data);
    libvlc_media_player_t* player = static_cast<libvlc_media_player_t*>(event->p_obj);

    switch (event->type) {
    case libvlc_MediaPlayerPlaying:
//        libvlc_audio_toggle_mute(player);
        qDebug() << "libvlc_MediaPlayerPlaying";
        break;
    case libvlc_MediaPlayerStopped:
        libvlc_media_player_release(player);
        qDebug() << "libvlc_MediaPlayerStopped";
        break;
    case libvlc_MediaPlayerEndReached:
        libvlc_media_player_release(player);
        qDebug() << "libvlc_MediaPlayerEndReached";
        break;
    default:
        break;
    }

    if (event->type != libvlc_MediaPlayerBuffering)
        qDebug() << "**********************" << QString("%1").arg(event->type, 0, 16);
}
