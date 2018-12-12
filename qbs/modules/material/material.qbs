import qbs
import qbs.Environment

Module {
    setupRunEnvironment: {
        console.log("setup Environment")
        Environment.putEnv("QML_IMPORT_PATH", project.thirdPartyPath);
        Environment.putEnv("QML2_IMPORT_PATH", project.thirdPartyPath);
    }
}
