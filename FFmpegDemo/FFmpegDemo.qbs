import qbs


CppApplication {
    name: "FFmpegDemo"
    files: [
        "main.cpp",
        "metadata.c",
        "mux.c",
    ]

    Depends { name: "cpp" }
    Depends { name: "ffmpeg" }

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
