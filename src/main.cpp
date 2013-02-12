/**
 * @author PanteR
 * @date 10.02.2013
 */

#include <QtCore/QTranslator>
#include <QtCore/QLocale>

#include <QtGui/QApplication>

#include "mainwindow.h"

int main (int argc, char **argv)
{
	QApplication app (argc, argv);

	QTranslator translator;
	translator.load (":share/translations/WordsCounter_ru.qm");
	QApplication::installTranslator (&translator);

	MainWindow win;
	win.show();

	return app.exec();
}
