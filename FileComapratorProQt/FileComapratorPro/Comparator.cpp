#include "Comparator.h"

#include <QTextBlock>
#include <QMessageBox>

std::vector<int> Comparator::findDifferingLines(QTextDocument* documentForLeft, QTextDocument* documentForRight)
{
	std::vector<int> diffLines;
	int i = 0;
	if (documentForLeft == nullptr || documentForRight == nullptr) {
		QMessageBox::information(nullptr, "ERROR", "Unable to compare. Lack of file.");
		return diffLines;
	}

	if (documentForLeft->isEmpty() || documentForRight->isEmpty()) {
		QMessageBox::information(nullptr, "WARNING", "At least one of documents is blank");
		return diffLines;
	}
	while (i < documentForLeft->blockCount() || i < documentForRight->blockCount())
	{
#ifdef DEBUG
		QString lText = documentForLeft->findBlockByLineNumber(i).text();
		QString rText = documentForRight->findBlockByLineNumber(i).text();
#endif // DEBUG
		if (documentForLeft->findBlockByLineNumber(i).text() != documentForRight->findBlockByLineNumber(i).text())
			diffLines.push_back(i);
		i++;
	}

	return diffLines;
}

void Comparator::comparePartially(int lowLimit, int upLimit, QTextDocument* documentForLeft, QTextDocument* documentForRight,
	std::vector<int>& diffsSoFar)
{
	int i = lowLimit;
#ifdef DEBUG
	int i1 = documentForRight->blockCount();
	int i2 = documentForLeft->blockCount();
#endif // DEBUG

	while (i < documentForLeft->blockCount() && i < documentForRight->blockCount()  && i < upLimit)
	{
		if (documentForLeft->findBlockByLineNumber(i).text() != documentForRight->findBlockByLineNumber(i).text())
			diffsSoFar.push_back(i);
		else if (documentForLeft->findBlockByLineNumber(i).text() == documentForRight->findBlockByLineNumber(i).text() &&
			std::find(diffsSoFar.begin(), diffsSoFar.end(), i) != diffsSoFar.end())
			diffsSoFar.erase(std::remove(diffsSoFar.begin(), diffsSoFar.end(), i));

		i++;
	}
}

void Comparator::selectDifference(QTextEdit* inWhat, int difference, std::vector<int> diffLines)
{
	if (difference <= 0 || difference > diffLines.size())
		return;

	QTextCursor selectCursor = inWhat->textCursor();
	selectCursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
	selectCursor.movePosition(QTextCursor::NextBlock, QTextCursor::MoveAnchor, diffLines[difference - 1]);

	selectCursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);

	inWhat->setTextCursor(selectCursor);
}

void Comparator::replaceDifference(QTextEdit* takeFrom, QTextEdit* takeTo)
{
	QString text = takeFrom->textCursor().selectedText();

	takeTo->textCursor().insertText(text);
}

void Comparator::deselect(QTextEdit* inWhat)
{
	QTextCursor tmpCursor = inWhat->textCursor();
	tmpCursor.clearSelection();
	inWhat->setTextCursor(tmpCursor);
}