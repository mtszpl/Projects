#include "Controller.h"
#include <QFileDialog>
#include <QScrollBar>
#include <QMessageBox>
Controller::Controller(int argc, char* argv[]) : QApplication(argc, argv)
{
	m_ControllerLeft = std::make_unique<ViewController>(m_Window.getUi().leftFileEdit->document());
	m_ControllerRight = std::make_unique<ViewController>(m_Window.getUi().rightFileEdit->document());

	QObject::connect(&m_Window, &MainWindow::openLeftClicked,
		this, [this]() {openFile(m_Window.getUi().leftFileEdit, m_LeftFileHandler); });
	QObject::connect(&m_Window, &MainWindow::openRightClicked,
		this, [this]() {openFile(m_Window.getUi().rightFileEdit, m_RightFileHandler); });

	QObject::connect(&m_Window, &MainWindow::compareClicked, this, [this]() {wantCompare(); });

	QObject::connect(&m_Window, &MainWindow::nextDiffClicked, this, [this]() {pickDiff(); });
	QObject::connect(&m_Window, &MainWindow::prevDiffClicked, this, [this]() {pickDiff(-1); });

	QObject::connect(&m_Window, &MainWindow::replaceWithLeftClicked,
		this, [this]() {replace(m_Window.getUi().leftFileEdit, m_Window.getUi().rightFileEdit); });
	QObject::connect(&m_Window, &MainWindow::replaceWithRightClicked,
		this, [this]() {replace(m_Window.getUi().rightFileEdit, m_Window.getUi().leftFileEdit); });

	QObject::connect(&m_Window, &MainWindow::resetClicked, this, [this]() {reset(); });

	QObject::connect(&m_Window, &MainWindow::saveLeftClicked, this, [this]() {save(m_LeftFileHandler); });
	QObject::connect(&m_Window, &MainWindow::saveRightClicked, this, [this]() {save(m_RightFileHandler); });

	QObject::connect(&m_Window, &MainWindow::leftScrolled, this, [this]() {updateTextEdit(m_LeftFileHandler); });
	QObject::connect(&m_Window, &MainWindow::rightScrolled, this, [this]() {updateTextEdit(m_RightFileHandler); });

	m_Window.getUi().differenceSelection->setText(QString::fromStdString(std::to_string(0)));
	m_Window.getUi().differenceShower->setText(QString::fromStdString(std::to_string(0)));

	m_Window.show();
}

void Controller::openFile(QTextEdit* textEdit, std::unique_ptr<FileIOHandler>& handler)
{
	m_compared = false;
	handler.reset();
	m_diffVector.clear();

	QString filePath = QFileDialog::getOpenFileName(nullptr, "Open File");

	if (filePath.isEmpty()) {
		QMessageBox::information(nullptr, "ERROR", "Unable to open file!");
		return;
	}

	textEdit->moveCursor(QTextCursor::Start);
	textEdit->document()->clear();

	QFileInfo fileInfo;
	fileInfo.setFile(filePath);

	if (fileInfo.suffix() == "txt")
		openTXT(handler, textEdit, filePath);
}

void Controller::openTXT(std::unique_ptr<FileIOHandler>& handler, QTextEdit* _textEdit, QString& _path)
{
	handler = std::make_unique<TxtHandler>();
	handler->openFile(_path, _textEdit);
}

void Controller::wantCompare()
{
	reset();

	m_compared = true;

	equalizeLines();

	m_diffVector = m_Comparator.findDifferingLines(m_Window.getUi().leftFileEdit->document(), m_Window.getUi().rightFileEdit->document());

	m_ControllerLeft->colorPart(0, m_Window.getUi().leftFileEdit->document()->blockCount(), m_diffVector);
	m_ControllerRight->colorPart(0, m_Window.getUi().rightFileEdit->document()->blockCount(), m_diffVector);

	m_Window.getUi().differenceShower->setText(QString::fromStdString(std::to_string(m_diffVector.size())));
}

void Controller::pickDiff(int factor)
{
	if (m_diffVector.size() == 0)
		return;

	m_selectedDifference = m_Window.getUi().differenceSelection->text().toInt();
	m_selectedDifference += factor;

	if (m_selectedDifference > m_diffVector.size())
		m_selectedDifference = 1;

	if (m_selectedDifference < 1)
		m_selectedDifference = m_diffVector.size();

	if (m_Window.getUi().leftFileEdit->document()->blockCount() >= m_diffVector[m_selectedDifference - 1] &&
		m_Window.getUi().rightFileEdit->document()->blockCount() >= m_diffVector[m_selectedDifference - 1])
	{
		m_Comparator.selectDifference(m_Window.getUi().leftFileEdit, m_selectedDifference, m_diffVector);
		m_Comparator.selectDifference(m_Window.getUi().rightFileEdit, m_selectedDifference, m_diffVector);
	}
	else if (m_Window.getUi().leftFileEdit->document()->blockCount() < m_diffVector[m_selectedDifference - 1])
	{
		m_Window.getUi().leftFileEdit->moveCursor(QTextCursor::End);
		m_selectedDifference -= factor;
	}
	else if (m_Window.getUi().rightFileEdit->document()->blockCount() < m_diffVector[m_selectedDifference - 1])
	{
		m_Window.getUi().rightFileEdit->moveCursor(QTextCursor::End);
		m_selectedDifference -= factor;
	}

	m_Window.getUi().differenceSelection->setText(QString::fromStdString(std::to_string(m_selectedDifference)));
}

void Controller::replace(QTextEdit* textEditFrom, QTextEdit* textEditTo)
{
	m_selectedDifference = m_Window.getUi().differenceSelection->text().toInt();
	m_selectedDifference--;

	if (m_selectedDifference < 0)
		return;

	if (m_selectedDifference > m_diffVector.size())
		m_selectedDifference = m_diffVector.size() - 1;

	m_ControllerLeft->resetLine(m_diffVector[m_selectedDifference]);
	m_ControllerRight->resetLine(m_diffVector[m_selectedDifference]);

	m_Comparator.replaceDifference(textEditFrom, textEditTo);

	m_diffVector.erase(m_diffVector.begin() + m_selectedDifference);

	m_Window.getUi().differenceShower->setText(QString::fromStdString(std::to_string(m_diffVector.size())));
	m_Window.getUi().differenceSelection->setText(QString::fromStdString(std::to_string(m_selectedDifference)));

	pickDiff(1);
}

void Controller::reset()
{
	m_compared = false;

	m_ControllerLeft->resetDocumentColor();
	m_ControllerRight->resetDocumentColor();

	m_Comparator.deselect(m_Window.getUi().leftFileEdit);
	m_Comparator.deselect(m_Window.getUi().rightFileEdit);

	m_Window.getUi().differenceSelection->setText(QString::fromStdString(std::to_string(0)));
	m_Window.getUi().differenceShower->setText(QString::fromStdString(std::to_string(0)));

	m_selectedDifference = 0;
	m_diffVector.clear();
}

void Controller::save(std::unique_ptr<FileIOHandler>& handler)
{
	if (handler == nullptr) {
		QMessageBox::information(nullptr, "ERROR", "First open file");
		return;
	}
	handler->save();
}

void Controller::updateTextEdit(std::unique_ptr<FileIOHandler>& handler)
{
	if (handler)
	{
		int beg = handler->getGoal()->document()->blockCount();
		m_ControllerLeft->prepareForUpdate();
		m_ControllerRight->prepareForUpdate();

		handler->pasteDataToBox();
		if (m_compared)
		{
			int end = handler->getGoal()->document()->blockCount();
			m_Comparator.comparePartially(
				beg, end, m_Window.getUi().leftFileEdit->document(), m_Window.getUi().rightFileEdit->document(), m_diffVector);
			m_ControllerLeft->colorPart(beg, end, m_diffVector);
			m_ControllerRight->colorPart(beg, end, m_diffVector);

			m_Window.getUi().differenceShower->setText(QString::fromStdString(std::to_string(m_diffVector.size())));
		}
	}
}

void Controller::equalizeLines()
{
	while (m_Window.getUi().leftFileEdit->document()->blockCount() != m_Window.getUi().rightFileEdit->document()->blockCount())
	{
#ifdef DEBUG
		int i1 = m_Window.getUi().rightFileEdit->document()->blockCount();
		int i2 = m_Window.getUi().leftFileEdit->document()->blockCount();
#endif // DEBUG
		if (m_Window.getUi().leftFileEdit->document()->blockCount() > m_Window.getUi().rightFileEdit->document()->blockCount())
		{
			if (m_RightFileHandler != nullptr && m_RightFileHandler->hasToAdd())
				m_RightFileHandler->pasteDataToBox();
			else
				m_Window.getUi().rightFileEdit->textCursor().insertBlock();
		}
		if (m_Window.getUi().leftFileEdit->document()->blockCount() < m_Window.getUi().rightFileEdit->document()->blockCount())
		{
			if (m_LeftFileHandler != nullptr && m_LeftFileHandler->hasToAdd())
				m_LeftFileHandler->pasteDataToBox();
			else
				m_Window.getUi().leftFileEdit->textCursor().insertBlock();
		}
	}

#ifdef DEBUG
	int i1 = m_Window.getUi().rightFileEdit->document()->blockCount();
	int i2 = m_Window.getUi().leftFileEdit->document()->blockCount();
#endif // DEBUG
}

Controller::~Controller()
{
	bool blocked = m_Window.blockSignals(true);
}