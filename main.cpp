#include <QApplication>

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include "qmdxplayer.h"
#include "helper.h"
#include "playlistitem.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;

    QMDXPlayer mdxPlayer; // 音楽再生用
    engine.rootContext()->setContextProperty("mdxPlayer", &mdxPlayer);

    QList<QObject*> playList;
    engine.rootContext()->setContextProperty("playList", QVariant::fromValue(playList));

    Helper helper(engine.rootContext(), &playList);
    engine.rootContext()->setContextProperty("appHelper", &helper);

    // デフォルトのプレイリストをロード
    helper.loadDefaultPlaylist();
#ifdef QT_DEBUG
    engine.rootContext()->setContextProperty("debug", true);
#else
    engine.rootContext()->setContextProperty("debug", false);
#endif

    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
    return app.exec();
}
