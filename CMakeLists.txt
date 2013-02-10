PROJECT(WordsCounter)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE_DIRECTORIES(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

SET(WordsCounter_SORCES
    src/main.cpp
    src/wordscounter.cpp
    src/fileparser.cpp
)

SET(WordsCounter_HEADRES
    src/wordscounter.h
    src/fileparser.h
)

SET(WordsCounter_UI
    src/wordscounter.ui
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
