import qbs

Module {
    Depends { name: "cpp" }

    cpp.includePaths: project.thirdPartyPath + "/opencv-3.2.0/include"
    cpp.libraryPaths: project.thirdPartyPath + "/opencv-3.2.0/lib"
    cpp.dynamicLibraries: [
        "opencv_calib3d320",
        "opencv_core320",
        "opencv_features2d320",
        "opencv_flann320",
        "opencv_highgui320",
        "opencv_imgproc320",
        "opencv_imgcodecs320",
        "opencv_ml320",
        "opencv_objdetect320",
        "opencv_photo320",
        "opencv_shape320",
        "opencv_stitching320",
        "opencv_superres320",
        "opencv_video320",
        "opencv_videoio320",
        "opencv_videostab320",
    ]

    property string runtimaLibraryPath: project.thirdPartyPath + "/opencv-3.2.0/bin"
}
