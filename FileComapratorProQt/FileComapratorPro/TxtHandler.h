#pragma once
#include "FileIOHandler.h"

/**Class handles both *.txt opening and saving.*/
class TxtHandler : public FileIOHandler
{
private:
	bool m_recursionGuard = false;

public:
	/**Method opens *.txt files and copies their contents to appications input/edit fields.
	@param path Reference to files path which is to be opened.
	@param textEdit Input/edit field where *.txt file content will be pasted.*/
	void openFile(QString& path, QTextEdit* textEdit) override;

	/**Method is responsible for saving appications input field contents into *.txt file.*/
	void save() override;

	/**Method is used by openFile() and it's purpose is to paste *.txt contents into appications input fields.*/
	void pasteDataToBox() override;

	~TxtHandler();
};
