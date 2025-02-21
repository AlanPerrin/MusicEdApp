#ifndef HTMLWINDOW_H
#define HTMLWINDOW_H

#include <QWidget>

class QPushButton;

class HtmlWindow : public QWidget {
    Q_OBJECT
public:
    explicit HtmlWindow(QWidget *parent = nullptr);
private slots:
    void openHtmlFile();
private:
    QPushButton *openHtmlButton;
};

#endif // HTMLWINDOW_H
