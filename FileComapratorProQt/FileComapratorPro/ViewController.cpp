#include <QTextBlock>
#include "ViewController.h"

ViewController::ViewController(QTextDocument* document) :
	m_Document (document)
{
	initColors();
}

ViewController::ViewController() : 
	m_Document(nullptr)
{
	initColors();
}

void ViewController::initColors() 
{
	m_White.setRgb(255, 255, 255);
	m_Cyan.setRgb(50, 255, 255);
	m_Grey.setRgb(128, 128, 128);
}

void ViewController::colorPart(int lowLimit, int upLimit, std::vector<int> diffLines)
{
	int i = 0;
	while (i < diffLines.size() && diffLines[i] < m_Document->blockCount() && diffLines[i] < upLimit)
	{
		if (diffLines[i] < lowLimit)
		{
			i++;
			continue;
		}
		if (m_Document->findBlockByLineNumber(diffLines[i]).text() == "")
			m_BlockFormat.setBackground(m_Grey);
		else
			m_BlockFormat.setBackground(m_Cyan);
		colorLine(m_BlockFormat, diffLines[i]);
		i++;
	}

	m_BlockFormat.setBackground(m_White);
}

void ViewController::resetDocumentColor()
{
	m_BlockFormat.setBackground(m_White);
	for (int i = 0; i < m_Document->blockCount(); i++)
		colorLine(m_BlockFormat, i);
}

void ViewController::colorLine(QTextBlockFormat form, int lineNum)
{
	QTextCursor(m_Document->findBlockByLineNumber(lineNum)).setBlockFormat(form);
}

void ViewController::resetLine(int lineNum)
{
	m_BlockFormat.setBackground(m_White);
	QTextCursor(m_Document->findBlockByLineNumber(lineNum)).setBlockFormat(m_BlockFormat);
}

void ViewController::prepareForUpdate()
{
	m_BlockFormat.setBackground(m_White);
	QTextCursor(m_Document->findBlockByLineNumber(m_Document->lineCount())).setBlockFormat(m_BlockFormat);
}