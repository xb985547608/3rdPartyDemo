import qbs

Project {
    minimumQbsVersion: "1.7.1"

    CppApplication {
        consoleApplication: true
        files: "main.cpp"
        cpp.includePaths: [
            "D:/Program Files (x86)/Microsoft Speech SDK 5.1/Include",
            "D:/Program Files/Microsoft Visual Studio 14.0/VC/atlmfc/include/"
        ]
        cpp.libraryPaths: [
            "D:/Program Files (x86)/Microsoft Speech SDK 5.1/Lib/i386"
        ]
        cpp.dynamicLibraries: [ "sapi", "ole32" ]

        Group {     // Properties for the produced executable
            fileTagsFilter: "application"
            qbs.install: true
        }
    }
}
