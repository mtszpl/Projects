#include "FileIOHandler.h"
#include <sstream>
#include <streambuf>
#include <fstream>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextBlock>

QTextEdit* FileIOHandler::getGoal()
{
	return m_Goal;
}

bool FileIOHandler::hasToAdd()
{
	if (m_WhatsLeftToAdd.isEmpty())
		return false;
	else
		return true;
}