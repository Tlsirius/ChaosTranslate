#include "GlossaryDialog.h"

GlossaryDialog::GlossaryDialog(std::pair<QOnlineTranslator::Language, QOnlineTranslator::Language> languages, GlossaryModel* model):
	QDialog()
{
	ui.setupUi(this);

	m_tableView = findChild<QTableView*>("tableView");
	m_newButton = findChild<QPushButton*>("newButton");
	m_deleteButton = findChild<QPushButton*>("deleteButton");
	m_saveButton = findChild<QPushButton*>("saveButton");
	m_loadButton = findChild<QPushButton*>("loadButton");
	m_sourceLanLineEdit = findChild<QLineEdit*>("sourceLanguageLineEdit");
	m_targetLanLineEdit = findChild<QLineEdit*>("targetLanguageLineEdit");

	QString sourceLanguage = QOnlineTranslator::languageName(languages.first);
	QString targetLanguage = QOnlineTranslator::languageName(languages.second);
	m_sourceLanLineEdit->setText(sourceLanguage);
	m_targetLanLineEdit->setText(targetLanguage);

	connect(m_newButton, &QPushButton::clicked, this, &GlossaryDialog::onAddNewRow);
	connect(m_deleteButton, &QPushButton::clicked, this, &GlossaryDialog::onDeleteRow);
	connect(m_saveButton, &QPushButton::clicked, this, [this](bool clicked) {emit onSaveDictionary(); });
	connect(m_loadButton, &QPushButton::clicked, this, [this](bool clicked) {emit onLoadDictionary(); });
	m_tableView->setModel(model);
	m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

GlossaryDialog::~GlossaryDialog()
{
	if (m_newGlossaryDialog != nullptr)
	{
		delete m_newGlossaryDialog;
	}
}

void GlossaryDialog::onAddNewRow(bool clicked)
{
	//int rowCount = m_model->getGlossaryCount();
	//m_model->insertRow(rowCount);
	//QModelIndex index = m_model->index(rowCount, 0);
	//editTable(index);
	if (m_newGlossaryDialog != nullptr)
	{
		delete m_newGlossaryDialog;
	}
	m_newGlossaryDialog = new NewGlossaryDialog();
	m_newGlossaryDialog->show();
	connect(m_newGlossaryDialog, &NewGlossaryDialog::addGlossary, this, &GlossaryDialog::onAddEntry);
}

void GlossaryDialog::onDeleteRow(bool clicked)
{
	QItemSelectionModel* select = m_tableView->selectionModel();
	QModelIndexList selectedRows = select->selectedRows();
	for (auto row : selectedRows)
	{
		emit onDeleteEntry(row);
	}
}

void GlossaryDialog::editTable(const QModelIndex& index)
{
	m_tableView->edit(index);
}

void GlossaryDialog::checkEmptyWord(const QModelIndex& index)
{
}


void GlossaryDialog::setSourceLanguage(QOnlineTranslator::Language lan)
{
	QString sourceLanguage = QOnlineTranslator::languageName(lan);
	m_sourceLanLineEdit->setText(sourceLanguage);
}

void GlossaryDialog::setTargetLanguage(QOnlineTranslator::Language lan)
{
	QString targetLanguage = QOnlineTranslator::languageName(lan);
	m_targetLanLineEdit->setText(targetLanguage);
}
