/**
 * @author PanteR
 * @date 10.02.2013
 */

#include <QtGui/QApplication>

#include "WordsCounter.h"

int main (int argc, char **argv)
{
	QApplication app (argc, argv);

	WordsCounter wordsCounter;
	wordsCounter.show();

	return app.exec();
}
