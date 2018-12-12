import qbs

Module {
    Depends { name: "cpp" }

    cpp.includePaths: project.thirdPartyPath + "/ffmpeg-20180411-9825f77-win32-dev/include"
    cpp.libraryPaths: project.thirdPartyPath + "/ffmpeg-20180411-9825f77-win32-dev/lib"
    cpp.dynamicLibraries: [
        "avdevice",
        "avformat",
        "avfilter",
        "avcodec",
        "swresample",
        "swscale",
        "avutil"
    ]

    property string runtimaLibraryPath: project.thirdPartyPath + "/ffmpeg-20180411-9825f77-win32-shared/bin"
}
