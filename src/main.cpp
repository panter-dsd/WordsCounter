/**
 * @author PanteR
 * @date 10.02.2013
 */

#include <QtGui/QApplication>

#include "mainwindow.h"

int main (int argc, char **argv)
{
	QApplication app (argc, argv);

	MainWindow win;
	win.show();

	return app.exec();
}
