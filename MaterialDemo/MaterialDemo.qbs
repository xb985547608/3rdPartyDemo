import qbs
import qbs.TextFile
import "StringExtend.js" as StringExtend

QtGuiApplication {
    name: "MaterialDemo"

    Depends {
        name: "Qt"
        submodules: [
            "gui", "qml", "quick"
        ]
        versionAtLeast: project.minimumQtVersion
    }
    Depends { name: "material" }

    Group {
        name: "QML"
        files: ["*.qml"]
        fileTags: ["qt.core.resource_data"]
    }

    Group {
        name: "Image"
        files: ["images/**"]
        fileTags: ["images"]
    }

    Group {
        name: "Icons"
        files: ["icons/*.svg"]
        fileTags: ["icons"]
    }

    Group {
        name: "Sources"
        files: ["*.cpp"]
    }

    Group {
        name: "Headers"
        files: ["*.h"]
    }

    Rule {
        multiplex: true
        inputs: ["images"]
        Artifact {
            filePath: "images.qrc"
            fileTags: ["qrc"]
        }

        prepare: {
            var cmd = new JavaScriptCommand();
            cmd.description = "generated images.qrc";
            cmd.highlight = "filegen";
            cmd.sourceCode = function () {
                var content = '<!DOCTYPE RCC>\n<RCC version="1.0">\n\n';

                content += String('<qresource prefix="/images">\n');
                inputs["images"].forEach(function (value) {
                    content += String('\t<file alias="{name}">{cname}</file>\n')
                               .format({ 'name': value.fileName,
                                         'cname': value.filePath })
                })
                content += '</qresource>\n\n';
                content += '</RCC>'

                var file = new TextFile(output.filePath, TextFile.WriteOnly);
                file.truncate();
                file.write(content);
                file.close();
            }
            return [cmd];
        }
    }

    Rule {
        multiplex: true
        inputs: ["icons"]
        Artifact {
            filePath: "icons.qrc"
            fileTags: ["qrc"]
        }
        // NOTE 生成特定格式的资源文件
        prepare: {
            var cmd = new JavaScriptCommand();
            cmd.description = "generated icons.qrc";
            cmd.highlight = "filegen";
            cmd.sourceCode = function () {
                var groups = {}
                for (var i=0; i<inputs["icons"].length; i++) {
                    var fileName = inputs["icons"][i].baseName;
                    var group = fileName.slice(0, fileName.indexOf("_"));
                    if (groups[group] === undefined)
                        groups[group] = [];
                    groups[group].push(fileName.slice(fileName.indexOf("_")+1,
                                                      fileName.length));
                }

                var path = inputs["icons"][0].filePath;
                var prefixPath = path.slice(0, path.lastIndexOf('/'));

                var content = '<!DOCTYPE RCC>\n<RCC version="1.0">\n\n';
                for (var key in groups) {
                    content += String('<qresource prefix="/icons/{group}">\n').format({'group': key});
                    groups[key].forEach(function (value) {
                        content += String('\t<file alias="{name}.svg">{prefix}/{group}_{name}.svg</file>\n')
                                         .format({ 'group': key,
                                                   'name': value,
                                                   'prefix': prefixPath });
                    });
                    content += '</qresource>\n\n';
                }
                content += '</RCC>'

                var file = new TextFile(output.filePath, TextFile.WriteOnly);
                file.truncate();
                file.write(content);
                file.close();
            }
            return [cmd];
        }
    }
}
