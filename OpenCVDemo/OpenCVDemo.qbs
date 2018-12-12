import qbs

CppApplication {

    Group {
        name: "Sources"
        files: "*.cpp"
    }

    Group {
        name: "Headers"
        files: "*.h"
    }

    Group {
        name: "Forms"
        files: "*.ui"
    }

    Group {
        name: "Images"
        files: "images/*"
        fileTags: "qt.core.resource_data"
        Qt.core.resourcePrefix: "images"
    }

    Group {
        name: "Runtime Librarys"
        files: opencv.runtimaLibraryPath + "/*.dll"
        qbs.install: true
        qbs.installDir: "bin"
    }

    Group {
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }

    Depends { name: "Qt.core" }
    Depends { name: "Qt.widgets" }
    Depends { name: "opencv" }
}
