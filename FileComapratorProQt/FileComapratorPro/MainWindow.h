#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

/**Applicatins main window class.*/
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = Q_NULLPTR);

	Ui::MainWindowClass getUi();

private:
	Ui::MainWindowClass ui;

public slots:
	void on_undo_clicked();
	void on_actionOpen_Left_triggered();
	void on_actionOpen_Right_triggered();
	void on_actionSave_Left_triggered();
	void on_actionSave_Right_triggered();

signals:
	/**Signal is emitted whenever open left file button will be clicked*/
	void openLeftClicked();

	/**Signal is emitted whenever open right file button will be clicked*/
	void openRightClicked();

	/**Signal is emitted whenever compare button will be clicked*/
	void compareClicked();

	/**Signal is emitted whenever next diffrence button will be clicked*/
	void nextDiffClicked();

	/**Signal is emitted whenever previous diffrence button will be clicked*/
	void prevDiffClicked();

	/**Signal is emitted whenever replace with left button will be clicked*/
	void replaceWithLeftClicked();

	/**Signal is emitted whenever replace with right button will be clicked*/
	void replaceWithRightClicked();

	/**Signal is emitted whenever left file scroll action*/
	void leftScrolled();

	/**Signal is emitted whenever on left file scroll action*/
	void rightScrolled();

	/**Signal is emitted whenever reset button will be clicked*/
	void resetClicked();

	/**Signal is emitted whenever save left file button will be clicked*/
	void saveLeftClicked();

	/**Signal is emitted whenever save right file button will be clicked*/
	void saveRightClicked();
};
