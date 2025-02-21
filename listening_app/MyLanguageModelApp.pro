QT += widgets svg svgwidgets core gui 
CONFIG += console c++17

SOURCES += src/main.cpp \
           src/MainPage.cpp \
           src/InputWindow.cpp \
           src/HtmlWindow.cpp \
           src/NoteWindow.cpp

HEADERS += src/MainPage.h \
           src/InputWindow.h \
           src/HtmlWindow.h \
           src/NoteWindow.h
           
# Include the stylesheet in the project
RESOURCES += resources.qrc