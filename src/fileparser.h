/**
 * @author PanteR
 * @date 10.02.2013
 */

#pragma once

#include <QtCore/qobject.h>

class FileParser : public QObject
{
	Q_OBJECT

public:
	explicit FileParser (QObject *parent = 0);
	virtual ~FileParser ();

private:
	Q_DISABLE_COPY (FileParser)
};
