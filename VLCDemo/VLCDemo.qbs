import qbs

Project {
    name: "VLCDemo"

    CppApplication {
        consoleApplication: false
        files: [
            "main.cpp",
            "simple-1.cpp",
            "simple-2.cpp",
        ]

        Depends { name: "vlc" }

        Group {     // Properties for the produced executable
            fileTagsFilter: "application"
            qbs.install: true
            qbs.installDir: "bin"
        }

        Group {
            name: "Runtime Librarys"
            files: vlc.runtimaLibraryPath + "/*.dll"
            qbs.install: true
            qbs.installDir: "bin"
        }
    }

    QtApplication {
        files: [
            "mainqt.cpp",
            "vlcform.ui",
            "vlcwidget.cpp",
            "vlcwidget.h",
        ]
        name: "VLCDemo-Qt"

        Depends { name: "Qt.widgets" }
        Depends { name: "vlc" }

        Group {     // Properties for the produced executable
            fileTagsFilter: "application"
            qbs.install: true
            qbs.installDir: "bin"
        }
    }

}

