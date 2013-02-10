/**
 * @author PanteR
 * @date 10.02.2013
 */

#pragma once

#include <QtGui/QMainWindow>

#include <auto_ptr.h>

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow (QWidget *parent = 0, Qt::WindowFlags flags = 0);
	virtual ~MainWindow();

private:
	Q_DISABLE_COPY (MainWindow)

private Q_SLOTS:
	void updateButtons ();

private:
	std::auto_ptr<Ui::MainWindow> ui_;
	class FileParser *fileParser_;
};