import qbs

StaticLibrary {
    id: product
    name: "Live555"

    cpp.includePaths: [
        "live/BasicUsageEnvironment/include",
        "live/groupsock/include",
        "live/liveMedia/include",
        "live/UsageEnvironment/include"
    ]
    cpp.dynamicLibraries: [ "ws2_32", "wsock32" ]

    Group {
        name: "Sources"
        files: [
            "live/BasicUsageEnvironment/*.cpp",
            "live/groupsock/*.cpp",
            "live/groupsock/*.c",
            "live/liveMedia/*.cpp",
            "live/liveMedia/*.c",
            "live/UsageEnvironment/*.cpp"
        ]
    }

    Group {
        name: "Headers"
        files: [
            "live/BasicUsageEnvironment/include/*.hh",
            "live/groupsock/include/*.hh",
            "live/liveMedia/include/*.hh",
            "live/UsageEnvironment/include/*.hh"
        ]
        fileTags: "hpp"
    }

    Group {
        name: "Runtime Librarys"
        files: ffmpeg.runtimaLibraryPath + "/*.dll"
        qbs.install: true
        qbs.installDir: "bin"
    }

    Group {
        fileTagsFilter: "staticlibrary"
        qbs.install: true
        qbs.installDir: "lib"
    }

    Depends { name: "cpp" }
    Depends { name: "ffmpeg" }

    Export {
        Depends { name: "cpp" }
        Depends { name: "ffmpeg" }

        cpp.includePaths: product.cpp.includePaths
        cpp.libraryPaths: product.cpp.libraryPaths
        cpp.cxxFlags: product.cxxFlags
        cpp.linkerFlags: product.cxxFlags
    }
}
