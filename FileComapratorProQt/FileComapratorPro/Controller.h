#pragma once
#include "MainWindow.h"
#include "FileIOHandler.h"
#include "ViewController.h"
#include "Comparator.h"
#include "TxtHandler.h"
#include <QtWidgets/QApplication>

/**Class acts as applications main controller.*/
class Controller :
	public QApplication
{
private:
	MainWindow m_Window;
	Comparator m_Comparator;

	std::unique_ptr<FileIOHandler> m_LeftFileHandler, m_RightFileHandler;
	std::unique_ptr<ViewController> m_ControllerLeft;
	std::unique_ptr<ViewController> m_ControllerRight;

	std::vector<int> m_diffVector;

	int m_selectedDifference = 0;
	bool m_compared;


public:
	Controller(int argc, char* argv[]);

public slots:

	/**Method promts user With windows file chooser. Then, calls handling method according to file type
	*@param textEdit Pointer to applications edit field.
	*@param handler Reference to appropriate handler.
	*/
	void openFile(QTextEdit* textEdit, std::unique_ptr<FileIOHandler>& handler);

	/**Method creates an instance of TxtHandler if *.txt file extension was choosen
	* @param handler Reference to appropriate handler
	* @param textEdit Pointer to applications edit field
	* @param path Path to file chosen by the user.
	*/
	void openTXT(std::unique_ptr<FileIOHandler>& handler, QTextEdit* textEdit, QString& path);

	/**Method controls the process of comparison of two files*/
	void wantCompare();

	/**Method controls the process of selecting diffrences.
	*/
	void pickDiff(int factor = 1);
	
	/**Method controls replacing parts of particular files */
	void replace(QTextEdit* textEditFrom, QTextEdit* textEditTo);

	/**Method controls resetting*/
	void reset();

	/**Method handles saving files
	*@param handler Reference to appropriate handler.*/
	void save(std::unique_ptr<FileIOHandler>& handler);

	/**Method calls methods responsible for updating text edit fields.
	* *@param handler Reference to appropriate handler.*/
	void updateTextEdit(std::unique_ptr<FileIOHandler>& handler);

	/**Method loads file untill amount of lines in both windows is equal. If size of file is not big enough, method appends \n signs.
	*/
	void equalizeLines();

	~Controller();
};
