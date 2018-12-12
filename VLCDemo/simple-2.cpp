#include <windows.h>
#include <vlc/vlc.h>

/**
 * @brief 定制sout -- 流输出
 */

void mainSimple2() {
    libvlc_instance_t* instance;
    const char* url;


    //Send File
    //Transcode it. Video codec use x264. Audio codec use mpga.
    //Mux it to mpegts format.
    //And stream it to udp://233.233.233.233:6666

//    const char *sout = "#transcode{vcodec=h264,fps=25,venc=x264{preset=ultrafast,"\
//        "profile=main,tune=zerolatency},vb=512,scale=0.5,"                        \
//        "acodec=mpa,aenc=ffmpeg,ab=64,channels=2}"                                \
//        ":standard{access=udp,mux=ts,dst=233.233.233.233:6666}";

    //Send and playing at same time
//    const char *sout = "#transcode{vcodec=h264,fps=25,venc=x264{preset=ultrafast,"\
//        "profile=baseline,tune=zerolatency},vb=512,"                              \
//        "acodec=mpga,ab=64,channels=2}"                                           \
//        ":duplicate{dst=display,dst=standard{access=udp,mux=ts,dst=233.233.233.233:6666}}";
    const char* sout = "#duplicate{dst=display,dst=es{access-video=file,access-audio=dummy,mux=ts,dst=123.ts}}";
    const char* media_name = "Lei's test";

    //Screen Capture
    //url = "screen://";

//    url = "h:\\cloudmusic\\mv\\123.mp4";
    url = "rtsp://192.168.8.111:12120/1.mp4";

    instance = libvlc_new(0, NULL);
    libvlc_vlm_add_broadcast(instance, "media1", "rtsp://192.168.8.111:12120/1.mp4",
                             "#duplicate{dst=display,dst=es{access-video=file,access-audio=dummy,mux=ts,dst=123.ts}}",
                             0, NULL, true, false);
    libvlc_vlm_add_broadcast(instance, "media2", "rtsp://192.168.8.111:12120/7.mp4",
                             "#duplicate{dst=display,dst=es{access-video=file,access-audio=dummy,mux=ts,dst=456.ts}}",
                             0, NULL, true, false);
    libvlc_vlm_play_media(instance, "media1");
    libvlc_vlm_play_media(instance, "media2");

    //play 30s
    _sleep(30000);

    libvlc_vlm_stop_media(instance, "media1");
    libvlc_vlm_stop_media(instance, "media2");
    libvlc_vlm_release(instance);


}
