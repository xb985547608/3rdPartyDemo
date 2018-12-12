#include <vlc/vlc.h>
#include <windows.h>
#include <iostream>

/**
 * @brief 简单的播放器
 */

void mainSimple1() {
    libvlc_instance_t* instance;
    libvlc_media_player_t* player;
    libvlc_media_t* media;

    int waitTime = 5000;
    int width;
    int height;
    libvlc_time_t duration;

    std::cout << 1;

    // 加载VLC引擎
    instance = libvlc_new(0, NULL);
    std::cout << 1;

    // 打开本地路径
//    media = libvlc_media_new_path(instance, "h:\\cloudmusic\\mv\\out.mp4");
    // 打开协议地址
//    media = libvlc_media_new_location(instance, "rtsp://192.168.8.111:12120/1.mp4");
    media = libvlc_media_new_location(instance, "file:///h:/cloudmusic/mv/20s.mp4");
    std::cout << 1;

    // 根据媒体实例创建一个播放器
    player = libvlc_media_player_new_from_media(media);
    std::cout << 1;

    // 不需要保持媒体实例
    libvlc_media_release(media);
    std::cout << 1;

    // 开始播放
    libvlc_media_player_play(player);
    std::cout << 1;

    // 延时一会，等待轨道加载完成
    _sleep(waitTime);

    duration = libvlc_media_player_get_length(player);
    width = libvlc_video_get_width(player);
    height = libvlc_video_get_height(player);
    std::cout << "Stream Duration: " << duration/1000 << "s\n";
    std::cout << "Resolution: " << width << " x " << height << "\n";

    _sleep(duration);

    // 释放资源
    libvlc_media_player_stop (player);
    libvlc_media_player_release (player);
    libvlc_release (instance);
}
