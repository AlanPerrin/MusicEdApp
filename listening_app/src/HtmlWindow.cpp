#include "HtmlWindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QDesktopServices>
#include <QUrl>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>

HtmlWindow::HtmlWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("HTML Output");
    resize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(this);
    openHtmlButton = new QPushButton("Open HTML", this);
    layout->addWidget(openHtmlButton);

    connect(openHtmlButton, &QPushButton::clicked, this, &HtmlWindow::openHtmlFile);
}

void HtmlWindow::openHtmlFile() {
    // 1. Get the path of your executable’s directory (or current directory).
    QString appDir = QCoreApplication::applicationDirPath();
    // 2. Construct the path to output.html in the python folder.
    //    Adjust the relative path as needed for your folder structure.
    //    If python folder is at the same level as src, you might need "../python/output.html"
    QString filePath = QDir(appDir).filePath("../release/output.html");

    // Debug to confirm the final path
    qDebug() << "Attempting to open file at:" << filePath;

    if (!QDesktopServices::openUrl(QUrl::fromLocalFile(filePath))) {
        // Optionally handle error, e.g., show a message box.
        qDebug() << "Failed to open HTML file at" << filePath;
    }
}
