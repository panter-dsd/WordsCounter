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

protected:
	virtual void closeEvent (QCloseEvent *);

private:
	Q_DISABLE_COPY (MainWindow)

private Q_SLOTS:
	void updateWindowTitle ();
	void updateButtons ();
	void selectFile ();

	void updateProgress ();

private:
	void init ();

private:
	std::auto_ptr<Ui::MainWindow> ui_;
	typedef QVector<class QThread*> Threads;
	Threads threads_;
	class FileParser *fileParser_;
	class WordsCounter *wordsCounter_;
};
