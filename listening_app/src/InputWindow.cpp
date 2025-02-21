#include "InputWindow.h"
#include "HtmlWindow.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QProcess>
#include <QFile>
#include <QDebug>

InputWindow::InputWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Input Window");
    resize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(this);

    inputEdit = new QLineEdit(this);
    runButton = new QPushButton("Generate Response", this);
    outputEdit = new QTextEdit(this);
    outputEdit->setReadOnly(true);

    layout->addWidget(inputEdit);
    layout->addWidget(runButton);
    layout->addWidget(outputEdit);

    connect(runButton, &QPushButton::clicked, this, &InputWindow::handleSubmit);
}

void InputWindow::handleSubmit() {
    QString inputText = inputEdit->text();

    QProcess process;
    QString program;
    QStringList arguments;

    // Configuration (consider moving these to a separate config file or class)
    QString compiledPython = "C:/Users/guita/OneDrive/Desktop/Test-App/updates/listening_app/python/python_bridge_executable.exe";
    QString pythonScript = "C:/Users/guita/OneDrive/Desktop/Test-App/updates/listening_app/python/python_bridge.py";


    if (QFile::exists(compiledPython)) {
        program = compiledPython;
        qDebug() << "Using compiled Python executable:" << program;
    } else {
        program = "py";  // or "python3" if needed
        // Prepend the script path so that the final arguments are: [script, inputText]
        arguments.prepend(pythonScript);
        qDebug() << "Using Python script via system Python:" << program << arguments;
    }

    // Start the Python process
    qDebug() << "Starting Python process:" << program << arguments;
    process.start(program, arguments);

    // Wait for the process to finish or timeout
    if (!process.waitForFinished(-1)) { // Use a timeout (e.g., -1 for infinite)
        qDebug() << "Error: Python process did not finish:" << process.errorString();
        outputEdit->setText("Error: Python process failed to execute. " + process.errorString()); // Include error string
        return;
    }

    // Check exit code and handle errors
    if (process.exitCode()!= 0) {
        qDebug() << "Error: Python process exited with code:" << process.exitCode();
        QString errorMessage = "Error: Python process encountered an error.";
        if (process.exitCode() == 1) {
            errorMessage += " Check input text."; // Example of specific error message
        }
        outputEdit->setText(errorMessage);
        return;
    }

    // Read and display the output
    QString output = QString::fromLocal8Bit(process.readAllStandardOutput());
    outputEdit->setText(output);

    // Optionally, open the HTML window after the process finishes.
    HtmlWindow *htmlWindow = new HtmlWindow();
    htmlWindow->show();
    this->close();
}
