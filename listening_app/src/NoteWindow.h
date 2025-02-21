#ifndef NOTE_WINDOW_H
#define NOTE_WINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QDialog>
#include <QString>

class CustomDialog : public QDialog {
    Q_OBJECT

public:
    explicit CustomDialog(QWidget *parent = nullptr, bool isCorrect = false, QString correctAnswer = "");
};

class NoteWindow : public QMainWindow {
    Q_OBJECT

public:
    // Updated constructor with username and level.
    explicit NoteWindow(const QString &username, int level, QWidget *parent = nullptr);
    ~NoteWindow();
    

private slots:
    void playTrack();
    void keyPressed();
    void removeLastPressed();
    void submit();

private:
    void setupUI();
    void loadQuestion();
    void showFeedbackDialog(bool isCorrect, QString correctAnswer);
    QWidget* setupKeyboard();

    QGraphicsView *view;
    QGraphicsScene *scene;
    QGraphicsSvgItem *svgItem;
    QPushButton *playButton;
    QPushButton *submitButton;
    QPushButton *removeLastButton;
    QLabel *questionLabel;
    QLabel *pressedKeysLabel;
    QProgressBar *progressBar;

    QList<QString> pressedKeys;
    QString correctAnswer;
    int currentQuestionIndex;

    // New member variables.
    QString m_username;
    int m_level;
};

#endif // NOTE_WINDOW_H
