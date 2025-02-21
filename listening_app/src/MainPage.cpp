#include "MainPage.h"
#include "InputWindow.h"
#include "NoteWindow.h"
#include <QVBoxLayout>
#include <QPushButton>

MainPage::MainPage(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Main Page");
    resize(300, 150);

    QVBoxLayout *layout = new QVBoxLayout(this);

    inputWindowButton = new QPushButton("Open Input Window", this);
    noteWindowButton = new QPushButton("Open Note Window", this);

    layout->addWidget(inputWindowButton);
    layout->addWidget(noteWindowButton);

    // Connect button clicks to the corresponding slots.
    connect(inputWindowButton, &QPushButton::clicked, this, &MainPage::openInputWindow);
    connect(noteWindowButton, &QPushButton::clicked, this, &MainPage::openNoteWindow);
}

void MainPage::openInputWindow()
{
    // Create and show the InputWindow.
    InputWindow *inputWin = new InputWindow();
    inputWin->show();
    this->close();
}

void MainPage::openNoteWindow()
{
    // Create and show the NoteWindow.
    // Adjust the parameters as needed.
    NoteWindow *noteWin = new NoteWindow("Test_User", 2, nullptr);
    noteWin->show();
    this->close();
}
