#include "NoteWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>
#include <QTimer>
#include <QDebug>

// ---- CustomDialog Implementation ----
CustomDialog::CustomDialog(QWidget *parent, bool isCorrect, QString correctAnswer)
    : QDialog(parent) {
    setWindowTitle(isCorrect ? "Correct!" : "Oops");
    setStyleSheet(isCorrect ? "background-color: rgba(111,189,165,0.8);"
                            : "background-color: rgba(212,96,98,0.8);");

    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *message = new QLabel(QString("<b>%1</b><br>Correct answer: <u>%2</u>")
                                 .arg(isCorrect ? "Correct!" : "Incorrect")
                                 .arg(correctAnswer), this);
    QPushButton *continueButton = new QPushButton("Continue", this);

    connect(continueButton, &QPushButton::clicked, this, &QDialog::accept);
    
    layout->addWidget(message);
    layout->addWidget(continueButton);
    setLayout(layout);
}

// ---- NoteWindow Implementation ----

// Updated constructor that accepts a username and a level.
NoteWindow::NoteWindow(const QString &username, int level, QWidget *parent)
    : QMainWindow(parent), m_username(username), m_level(level)
{
    qDebug() << "NoteWindow created for user:" << m_username << "with level:" << m_level;
    qDebug() << "Setting up UI..."; // Add debugging output
    setupUI();
    qDebug() << "Loading question...";
    loadQuestion();
    // Setup keyboard after question load, so the widget is added last
    QWidget *keyboardWidget = setupKeyboard();
    // Add keyboard widget to the main layout
    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout *>(centralWidget()->layout());
    if (mainLayout) {
        mainLayout->addWidget(keyboardWidget);
    }
    qDebug() << "NoteWindow initialization complete."; 
}

NoteWindow::~NoteWindow() {}

void NoteWindow::setupUI() {
    setWindowTitle("Note Recognition");
    setGeometry(400, 100, 800, 650);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout  = new QVBoxLayout(centralWidget);

    // Progress bar
    progressBar = new QProgressBar(this);
    progressBar->setMaximum(3);  // Placeholder for question count
    layout->addWidget(progressBar);

    // Question Label and Play Button (Horizontal Layout)
    QWidget *questionPanel = new QWidget(this); // Widget to hold label and button
    QHBoxLayout *questionLayout = new QHBoxLayout(questionPanel);

    //Question
    questionLabel = new QLabel("Identify the Note in the Image Below", this);
    questionLayout->addWidget(questionLabel);
    //Play Button
    playButton = new QPushButton("Play Track", this);
    playButton->setFixedSize(150, 50); // Set specific size for the button
    connect(playButton, &QPushButton::clicked, this, &NoteWindow::playTrack);
    questionLayout->addWidget(playButton);
    questionLayout->addStretch(5); // Add stretchable space to push button to the right
    layout->addWidget(questionPanel); // Add the container widget to the main layout

    // SVG Display
    view = new QGraphicsView(this);
    scene = new QGraphicsScene(this);
    view->setScene(scene);
    layout->addWidget(view);

    // Pressed keys label
    pressedKeysLabel = new QLabel("Pressed Keys: ", this);
    layout->addWidget(pressedKeysLabel);

    // Remove last button
    removeLastButton = new QPushButton("Remove Last", this);
    connect(removeLastButton, &QPushButton::clicked, this, &NoteWindow::removeLastPressed);
    layout->addWidget(removeLastButton);

    // Submit Button (Bottom)
    submitButton = new QPushButton("Submit", this);
    connect(submitButton, &QPushButton::clicked, this, &NoteWindow::submit);
    layout->addWidget(submitButton);

    setCentralWidget(centralWidget);

}

void NoteWindow::loadQuestion() {
    QFile file("questions.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QStringList questions;
    while (!in.atEnd()) {
        questions.append(in.readLine());
    }
    file.close();

    if (!questions.isEmpty()) {
        int randIndex = QRandomGenerator::global()->bounded(questions.size());
        QStringList data = questions[randIndex].split(",");
        correctAnswer = data[1];

        // Load SVG
        QString svgPath = "Questions/Note_Questions/" + data[0];
        scene->clear();
        svgItem = new QGraphicsSvgItem(svgPath);
        svgItem->setScale(2);
        scene->addItem(svgItem);
    }
}

void NoteWindow::playTrack() {
  // Instead of playing an audio track, simply output "Playing note"
  qDebug() << "Playing note";
  // Optionally, update a label on the GUI to inform the user:
  // pressedKeysLabel->setText("Playing note");
}

QWidget *NoteWindow::setupKeyboard() {
    QWidget *keyboardWidget = new QWidget(this);
    keyboardWidget->setFixedHeight(220);

    int whiteKeyWidth = static_cast<int>(60 / 1.7);
    int blackKeyWidth = static_cast<int>(40 / 1.7);
    int blackKeyHeight = static_cast<int>(125 / 1.7);
    int whiteKeyHeight = static_cast<int>(200 / 1.7);
    int startPos = 15;

    QStringList whiteKeys = {"C", "D", "E", "F", "G", "A", "B"};
    QStringList blackKeys = {"C#", "D#", "F#", "G#", "A#"};
    QMap<QString, QString> enharmonicPairs = {{"C#", "Db"}, {"D#", "Eb"}, {"F#", "Gb"}, {"G#", "Ab"}, {"A#", "Bb"}};

    int startOctave = 3;

    // Create white keys
    for (int i = 0; i < 22; i++) {
        int octave = startOctave + (i / 7);
        QString note = whiteKeys[i % whiteKeys.size()] + QString::number(octave);
        QPushButton *button = new QPushButton(note, keyboardWidget);
        button->setFixedSize(whiteKeyWidth, whiteKeyHeight);
        button->setStyleSheet("QPushButton { background-color: white; color: black; font-size: 10px; padding:50px; padding-top:80px; border: 1px solid black;}");
        button->setGeometry(startPos + i * whiteKeyWidth, 0, whiteKeyWidth, whiteKeyHeight);
        connect(button, &QPushButton::clicked, this, &NoteWindow::keyPressed);
    }

    // Create black keys
    QList<int> blackKeyOffsets = {1, 2, 4, 5, 6};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < blackKeys.size(); j++) {
            int offset = blackKeyOffsets[j];
            QString noteName = blackKeys[j];
            QString enharmonicName = enharmonicPairs[noteName];
            QString noteLabel = QString("%1%2\n%3%2").arg(noteName).arg(i + 3).arg(enharmonicName);

            QPushButton *button = new QPushButton(noteLabel, keyboardWidget);
            button->setFixedSize(blackKeyWidth, blackKeyHeight);
            button->setStyleSheet(
                "QPushButton { background-color: black; color: white; font-size: 10px; text-align: center; border: 1px solid black;}"
                "QPushButton:pressed { background-color: darkgray; color: lightgray; }"
            );

            int xPos = startPos + (i * 7 + offset) * whiteKeyWidth - blackKeyWidth / 2;
            button->setGeometry(xPos, 0, blackKeyWidth, blackKeyHeight); // Fixed y-position
            button->raise();
            connect(button, &QPushButton::clicked, this, &NoteWindow::keyPressed);
        }
    }

    return keyboardWidget; // Return the created widget
}

void NoteWindow::keyPressed() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        pressedKeys.append(button->text());
        pressedKeysLabel->setText("Pressed Keys: " + pressedKeys.join(", "));
    }
}

void NoteWindow::removeLastPressed() {
    if (!pressedKeys.isEmpty()) {
        pressedKeys.removeLast();
        pressedKeysLabel->setText("Pressed Keys: " + pressedKeys.join(", "));
    }
}

void NoteWindow::submit() {
    bool isCorrect = pressedKeys.contains(correctAnswer);
    showFeedbackDialog(isCorrect, correctAnswer);
}

void NoteWindow::showFeedbackDialog(bool isCorrect, QString correctAnswer) {
    CustomDialog *dlg = new CustomDialog(this, isCorrect, correctAnswer);
    dlg->exec();
}
