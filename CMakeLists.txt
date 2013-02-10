PROJECT(WordsCounter)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE_DIRECTORIES(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

SET(WordsCounter_SORCES
    src/main.cpp
    src/wordscounter.cpp
)

SET(WordsCounter_HEADRES
    src/wordscounter.h
)

SET(WordsCounter_UI
    src/wordscounter.ui
)

QT4_AUTOMOC(${WordsCounter_SORCES})
QT4_WRAP_UI(UI_HEADERS ${WordsCounter_UI})

ADD_EXECUTABLE(WordsCounter ${WordsCounter_SORCES} ${UI_HEADERS})
TARGET_LINK_LIBRARIES(WordsCounter ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

INSTALL(TARGETS WordsCounter RUNTIME DESTINATION bin)
