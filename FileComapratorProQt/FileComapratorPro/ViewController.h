#pragma once

#include <QTextEdit>
#include <vector>

/**Class acts as a view controller. It's responsible for changes which appear on screen.*/
class ViewController
{
private:
	QTextDocument* m_Document;
	QTextBlockFormat m_BlockFormat;

	QColor m_White;
	QColor m_Cyan;
	QColor m_Grey;

public:
	/**Contructor initializes document and colors.
	@param document Pointer to the document.
	*/
	ViewController(QTextDocument* document);

	/**Non parameter contructor, initializes colors.*/
	ViewController();

	/**Setup coloring for various elements.*/
	void initColors();

	/**Color lines containing differing content.
	* @param lowLimit Line in which coloring should be started.
	* @param upLimit Line in which coloring should be finished.
	* @param diffLines Vector of differing lines.
	*/
	void colorPart(int lowLimit, int upLimit, std::vector<int> diffLines);

	/**Sets document colors to default (white).
	*/
	void resetDocumentColor();

	/**Colors single line.
	* @form Format of text to be applied to line.
	* @lineNum Number of line to be colored.
	*/
	void colorLine(QTextBlockFormat form, int lineNum);

	/**Sets single color to default (white).
	* @lineNum Number of line to be colored;
	*/
	void resetLine(int lineNum);

	/**Prepares document for loading further parts of file in default color.
	*/
	void prepareForUpdate();
};
