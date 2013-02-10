PROJECT(WordsCounter)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE_DIRECTORIES(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

SET(WordsCounter_SORCES
    src/main.cpp
    src/mainwindow.cpp
    src/fileparser.cpp
    src/wordscounter.cpp
)

SET(WordsCounter_HEADRES
    src/mainwindow.h
    src/fileparser.h
    src/wordscounter.h
)

SET(WordsCounter_UI
    src/mainwindow.ui
)

QT4_WRAP_CPP(MOC_SOURCES ${WordsCounter_HEADRES})
QT4_WRAP_UI(UI_HEADERS ${WordsCounter_UI})

ADD_EXECUTABLE(WordsCounter
    ${WordsCounter_SORCES}
    ${MOC_SOURCES}
    ${UI_HEADERS}
)

TARGET_LINK_LIBRARIES(WordsCounter ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

INSTALL(TARGETS WordsCounter RUNTIME DESTINATION bin)
