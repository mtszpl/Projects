#pragma once
#include <string>
#include <QPlainTextEdit>

/**
* Base class for file handlers that implement opening and saving files which have diffrent extensions.
Responsibility of the class is to copy data from a fle to QTextEdit and back. It's also responsible for
* saving files.
*/
class FileIOHandler
{
protected:

	QByteArray m_WhatsLeftToAdd;
	QTextEdit* m_Goal;
public:
	/**Pure virtual method. Classes which override that method will implement opening files of type they are
	responsible for here.
	@param path Reference to the input file path.
	@param textEdit QTextEdit field of application.
	*/
	virtual void openFile(QString& path, QTextEdit* textEdit) = 0;

	/**Pure virtual method. Classes which override that method will implement saving files of type they are
	responsible for here.
	*/
	virtual void save() = 0;

	/**Pure virtual method. Classes which override that method will implement pasting files contents here.
	*/
	virtual void pasteDataToBox() = 0;

	/**Returns pointer to QTextEdit contained in object.*/
	QTextEdit* getGoal();

	/**Method checks if there are elements to inser to QTextEdit field.
	* Returns true if remains, otherwise returns false.
	*/
	bool hasToAdd();

	virtual ~FileIOHandler() {};
};
