import qbs

Module {
    Depends { name: "cpp" }

    cpp.includePaths: project.thirdPartyPath + "/vlc/include"
    cpp.libraryPaths: project.thirdPartyPath + "/vlc/lib"
    cpp.dynamicLibraries: [ "vlc", "vlccore" ]

    property string runtimaLibraryPath: project.thirdPartyPath + "/vlc"
}
