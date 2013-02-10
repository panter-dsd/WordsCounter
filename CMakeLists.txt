project(WordsCounter)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(WordsCounter_SRCS WordsCounter.cpp main.cpp)
qt4_automoc(${WordsCounter_SRCS})
add_executable(WordsCounter ${WordsCounter_SRCS})
target_link_libraries(WordsCounter ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
install(TARGETS WordsCounter RUNTIME DESTINATION bin)
