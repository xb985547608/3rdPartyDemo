import qbs

Application {
    name: "Live555Demo"
    files: [
        "*.cpp",
        "*.hh"
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }

    Depends { name: "Qt.core" }
    Depends { name: "Qt.network" }
    Depends { name: "Live555" }
}

