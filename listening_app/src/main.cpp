#include <QApplication>
#include "MainPage.h"
#include <QFile>
#include <QTextStream>

void applyStyleSheet(QApplication &app) {
    QFile file(":/stylesheet.qss");  // Load from Qt resources
    if (!file.exists()) {
        qDebug() << "ERROR: Stylesheet file not found in resources!";
        return;
    }
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        app.setStyleSheet(stream.readAll());
        file.close();
    } else {
        qDebug() << "ERROR: Could not open stylesheet.qss!";
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    applyStyleSheet(app);
    
    MainPage mainPage;  // Replace with your main window class
    mainPage.show();
    return app.exec();
}
