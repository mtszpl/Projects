#include <fstream>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextBlock>
#include <QScrollBar>
#include <QTextCursor>

#include "TxtHandler.h"

#define UPLIMIT 19000

void TxtHandler::openFile(QString& path, QTextEdit* textBox)
{
	m_WhatsLeftToAdd.clear();
	QFile qFile(path);
	m_Goal = textBox;

	if (!qFile.open(QIODevice::ReadOnly))
	{
		QMessageBox::information(nullptr, "wrong file", "Unable to open file");
		return;
	}

	uchar* uData = qFile.map(0, qFile.size());
	char* data = reinterpret_cast<char*>(uData);

	m_WhatsLeftToAdd = QByteArray(data, qFile.size());

	pasteDataToBox();

	qFile.unmap(uData);
}

void TxtHandler::pasteDataToBox()
{
	if (m_WhatsLeftToAdd.isEmpty())
		return;

	if (m_recursionGuard)
		return;

	m_recursionGuard = true;
	int index = m_WhatsLeftToAdd.indexOf('\n', UPLIMIT);
	if (index >= 0)
		index++;

	QByteArray qArr;

	if (index > 0)
	{
		qArr = m_WhatsLeftToAdd.left(index);
		m_WhatsLeftToAdd = m_WhatsLeftToAdd.mid(index);
	}
	else
	{
		qArr = m_WhatsLeftToAdd.mid(index);
		m_WhatsLeftToAdd = "";
	}


	QString str(qArr);

	QTextCursor tmpCursor = m_Goal->textCursor();
	int tmpSliderVal = m_Goal->verticalScrollBar()->value();

	tmpCursor.movePosition(QTextCursor::End);
	tmpCursor.insertText(str);

	m_Goal->setTextCursor(tmpCursor);
	m_Goal->verticalScrollBar()->setValue(tmpSliderVal);
	m_recursionGuard = false;
}

void TxtHandler::save()
{
	QString saveFile = QFileDialog::getSaveFileName(nullptr, "Save", "Text files", "(*.txt)");

	if (saveFile.isEmpty())
	{
		QMessageBox::information(nullptr, "ERROR", "Unable to open file");
		return;
	}

	std::fstream f;
	std::string filenameSave = saveFile.toUtf8().constData();
	filenameSave += ".txt";

	f.open(filenameSave, std::ios::out);
	if (!f.good())
	{
		QMessageBox::information(nullptr, "ERROR", "Unable to open file");
		return;
	}
	for (int i = 0; i < m_Goal->document()->blockCount(); i++)
	{
		std::string outputBuffer = m_Goal->document()->findBlockByNumber(i).text().toStdString();
		if (outputBuffer.length() == 0)
			outputBuffer = "\r\n";
		f << outputBuffer;
	}
	f.close();
}

TxtHandler::~TxtHandler()
{
	if (m_recursionGuard)
		return;

	m_recursionGuard = true;

	m_Goal->moveCursor(QTextCursor::Start);
	m_Goal->document()->clear();
}