#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>

class QPushButton;

class MainPage : public QWidget {
    Q_OBJECT
public:
    explicit MainPage(QWidget *parent = nullptr);

private slots:
    void openInputWindow();
    void openNoteWindow();

private:
    QPushButton *inputWindowButton;
    QPushButton *noteWindowButton;
};

#endif // MAINPAGE_H
