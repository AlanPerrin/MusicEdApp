#ifndef INPUTWINDOW_H
#define INPUTWINDOW_H

#include <QWidget>

class QLineEdit;
class QPushButton;
class QTextEdit;

class InputWindow : public QWidget {
    Q_OBJECT
public:
    explicit InputWindow(QWidget *parent = nullptr);
signals:
    void processed(); // Optional signal to notify that processing is complete.
private slots:
    void handleSubmit();
private:
    QLineEdit *inputEdit;
    QPushButton *runButton;
    QTextEdit *outputEdit;
};

#endif // INPUTWINDOW_H
