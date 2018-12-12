#include <QGuiApplication>
#include <QQmlApplicationEngine>


// NOTE Test
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
