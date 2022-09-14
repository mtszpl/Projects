#include <QFileDialog>
#include <QTextBlock>
#include <QScrollBar>

#include "MainWindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QObject::connect(ui.openLeft, &QPushButton::clicked, this, [this]() {emit openLeftClicked(); });
	QObject::connect(ui.openRight, &QPushButton::clicked, this, [this]() {emit openRightClicked(); });
	QObject::connect(ui.comparatorBut, &QPushButton::clicked, this, [this]() {emit compareClicked(); });
	//QObject::connect(ui.undoLeft, QPushButton::clicked, this, [this]() {emit openRightClicked; });

	QObject::connect(ui.nextDifference, &QPushButton::clicked, this, [this]() {emit nextDiffClicked(); });
	QObject::connect(ui.previousDifference, &QPushButton::clicked, this, [this]() {emit prevDiffClicked(); });

	QObject::connect(ui.replaceWithLeft, &QPushButton::clicked, this, [this]() {emit replaceWithLeftClicked(); });
	QObject::connect(ui.replaceWithRight, &QPushButton::clicked, this, [this]() {emit replaceWithRightClicked(); });

	QObject::connect(ui.reset, &QPushButton::clicked, this, [this]() {emit resetClicked(); });

	QScrollBar* leftScrollBar = ui.leftFileEdit->verticalScrollBar();
	QObject::connect(leftScrollBar, &QScrollBar::valueChanged, this, [this, leftScrollBar](int value)
		{if (leftScrollBar->value() == leftScrollBar->maximum()) emit leftScrolled(); });

	QScrollBar* rightScrollBar = ui.rightFileEdit->verticalScrollBar();
	QObject::connect(rightScrollBar, &QScrollBar::valueChanged, this, [this, rightScrollBar]()
		{if (rightScrollBar->value() == rightScrollBar->maximum()) emit rightScrolled(); });

	this->setWindowState((windowState() & ~(Qt::WindowMinimized | Qt::WindowFullScreen))
		| Qt::WindowMaximized);
	this->setMinimumSize(600, 500);
}

Ui::MainWindowClass MainWindow::getUi()
{
	return ui;
}

void MainWindow::on_undo_clicked()
{
	QMessageBox::information(nullptr, "Warning", "Feauture doesn't work yet!");
}

void MainWindow::on_actionOpen_Left_triggered()
{
	emit openLeftClicked();
}

void MainWindow::on_actionOpen_Right_triggered()
{
	emit openRightClicked();
}

void MainWindow::on_actionSave_Left_triggered()
{
	emit saveLeftClicked();
}

void MainWindow::on_actionSave_Right_triggered()
{
	emit saveRightClicked();
}