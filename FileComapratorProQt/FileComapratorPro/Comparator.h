#pragma once
#include <QTextEdit>
#include <vector>

/**Class is a part of applications model. It's responsible for comparing two files.*/
class Comparator
{
public:
	/**Method finds differing lines in two files.
	@param documentForLeft Pointer to document contaied in TextEdit field located on the left side of application.
	@param documentForRight pointer to document contaied in TextEdit located on the right side of application.
	@return Vector of differing lines numbers.
	*/
	std::vector<int> findDifferingLines(QTextDocument* documentForLeft, QTextDocument* documentForRight);

	/**Method is responsible for comparing of two text fragments.
	@param lowLimit Line number in which comparison should start.
	@param upLimit Line number in which comparison should end.
	@param documentForLeft Pointer to document contaied in TextEdit field located on the left side of application.
	@param documentForRight Pointer to document contaied in TextEdit located on the right side of application
	@param diffsSoFar number of differing line numbers found so far in the document
	*/
	void comparePartially(int lowLimit, int upLimit, QTextDocument* documentForLeft, QTextDocument* documentForRight, std::vector<int>& diffsSoFar);

	/**Method selects difference in text.
	@param inWhat Pointer to QTextDocument object contaied in TextEdit field in which difference is to be selected.
	@param difference Number of difference to select.
	@param diffLines Vector containing lines in which differences are found.
	*/
	void selectDifference(QTextEdit* inWhat, int difference, std::vector<int> diffLines);
	
	/**Method replaces choosen diffrence
	@param takeFrom Pointer to document from which replacement text is taken.
	@param takeTo Pointer to document where change replacement text is inserted.
	*/
	void replaceDifference(QTextEdit* takeFrom, QTextEdit* takeTo);

	/**Method clears selection in QTextEdit.
	@param inWhat Pointer to TextEdit where selection should be cleared.
	*/
	void deselect(QTextEdit* inWhat);
};
