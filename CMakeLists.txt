PROJECT(WordsCounter)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wno-long-long")

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE_DIRECTORIES(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

FIND_PACKAGE(Boost 1.45.0 REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

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

SET(RESOURCES resource.qrc)

QT4_ADD_RESOURCES(QRC_SOURCES ${RESOURCES})

ADD_EXECUTABLE(WordsCounter
    ${WordsCounter_SORCES}
    ${MOC_SOURCES}
    ${UI_HEADERS}
    ${QRC_SOURCES}
)

TARGET_LINK_LIBRARIES(WordsCounter ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

ADD_CUSTOM_COMMAND(
    TARGET WordsCounter
    PRE_BUILD
    COMMAND lupdate
    ARGS -no-obsolete -target-language ru -recursive . -ts share/translations/WordsCounter_ru.ts
    COMMAND lrelease
    ARGS share/translations/WordsCounter_ru.ts

    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

INSTALL(TARGETS WordsCounter RUNTIME DESTINATION bin)
