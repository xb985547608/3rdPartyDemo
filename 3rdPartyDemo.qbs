import qbs

Project {
    property string thirdPartyPath: sourceDirectory + "/3rdparty"

    qbsSearchPaths: "qbs"
    references: [
        "3rdparty/3rdparty.qbs",
        "FFmpegDemo/FFmpegDemo.qbs",
        "Live555Demo/Live555Demo.qbs",
        "MaterialDemo/MaterialDemo.qbs",
        "VLCDemo/VLCDemo.qbs",
        "OpenCVDemo/OpenCVDemo.qbs"
    ]
}
