import qbs 1.0


Project {
    name: "Third Paries"

    StaticLibrary {
        id: product
        name: "live555-0.91"

        cpp.includePaths: [
            product.sourceDirectory + "/FFmpeg/ffmpeg-20180411-9825f77-win32-dev/include",
            product.sourceDirectory + "/live555-latest-0.91/live/BasicUsageEnvironment/include",
            product.sourceDirectory + "/live555-latest-0.91/live/groupsock/include",
            product.sourceDirectory + "/live555-latest-0.91/live/liveMedia/include",
            product.sourceDirectory + "/live555-latest-0.91/live/UsageEnvironment/include"
        ]
        cpp.libraryPaths: [
            product.sourceDirectory + "/FFmpeg/ffmpeg-20180411-9825f77-win32-dev/lib"
        ]
        cpp.dynamicLibraries: [
            "avdevice",
            "avformat",
            "avfilter",
            "avcodec",
            "swresample",
            "swscale",
            "avutil",
            "ws2_32",
            "wsock32"
        ]

        Group {
            name: "Sources"
            files: [
                "live555-latest-0.91/live/BasicUsageEnvironment/*.cpp",
                "live555-latest-0.91/live/groupsock/*.cpp",
                "live555-latest-0.91/live/groupsock/*.c",
                "live555-latest-0.91/live/liveMedia/*.cpp",
                "live555-latest-0.91/live/liveMedia/*.c",
                "live555-latest-0.91/live/UsageEnvironment/*.cpp"
            ]
        }

        Group {
            name: "Headers"
            files: [
                "live555-latest-0.91/live/BasicUsageEnvironment/include/*.hh",
                "live555-latest-0.91/live/groupsock/include/*.hh",
                "live555-latest-0.91/live/liveMedia/include/*.hh",
                "live555-latest-0.91/live/UsageEnvironment/include/*.hh"
            ]
            fileTags: "hpp"
        }

        Depends { name: "cpp" }

        Group {
            fileTagsFilter: "staticlibrary"
            qbs.install: true
            qbs.installDir: "lib"
        }

        Group {
            name: "DynamicLibrary"
            files: "FFmpeg/ffmpeg-20180411-9825f77-win32-shared/bin/*.dll"
            qbs.install: true
            qbs.installDir: "bin"
        }

        Export {
            Depends { name: "cpp" }

            cpp.includePaths: product.cpp.includePaths
            cpp.libraryPaths: product.cpp.libraryPaths
            cpp.cxxFlags: product.cxxFlags
            cpp.linkerFlags: product.cxxFlags
        }
    }
}

