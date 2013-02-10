#include <QtGui/QApplication>
#include "WordsCounter.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    WordsCounter foo;
    foo.show();
    return app.exec();
}
