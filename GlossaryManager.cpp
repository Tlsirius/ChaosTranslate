﻿#include "GlossaryManager.h"
#include <QStandardItemModel>
#include <QTableView>

GlossaryManager::GlossaryManager():
	GlossaryManager(LanguagePair(QOnlineTranslator::Japanese, QOnlineTranslator::SimplifiedChinese))
{
}

GlossaryManager::GlossaryManager(LanguagePair languages)
{
	m_sourceLanguage = languages.first;
	m_targetLanguage = languages.second;
	m_dialog = nullptr;
	m_codes.emplace_back(u8"💫");
	m_codes.emplace_back(u8"⚓");
	m_codes.emplace_back(u8"⚔");
	m_codes.emplace_back(u8"🌟");
	m_codes.emplace_back(u8"🐉"); 
}

GlossaryManager::~GlossaryManager()
{
}

void GlossaryManager::showDialog()
{
	if (m_dialog == nullptr)
	{
		using Lan = QOnlineTranslator::Language;
		m_dialog = new GlossaryDialog(std::pair<Lan, Lan>(m_sourceLanguage, m_targetLanguage));
	}
	m_dialog->show();
}

GlossaryManager::EncodeResult GlossaryManager::encode(
	QString text, LanguagePair languages)
{
	EncodeResult result(text, std::map<QString, QString>());
	if (m_dictionaries.find(languages) == m_dictionaries.end())
	{
		return result;
	}
	Dict dict = m_dictionaries.at(languages);
	if (dict.size() == 0)
	{
		return result;
	}
	int count = 0;
	for (auto entry : dict)
	{
		const auto& key = entry.first;
		int id = text.indexOf(key);
		while (id != -1)
		{
			text.replace(id, key.size(), m_codes[count]);
			id = text.indexOf(key);
			if (result.dictionary.find(m_codes[count]) == result.dictionary.end())
			{
				result.dictionary[m_codes[count]] = entry.second;
				count++;
			}
		}
	}
	return result;
}

void GlossaryManager::setSourceLanguage(QOnlineTranslator::Language lan)
{
	m_sourceLanguage = lan;
	m_dialog->setSourceLanguage(lan);
}

void GlossaryManager::setTargetLanguage(QOnlineTranslator::Language lan)
{
	m_targetLanguage = lan;
	m_dialog->setTargetLanguage(lan);
}

QString GlossaryManager::decode(QString text, const std::map<QString, QString>& dict)
{
	if (m_dialog == nullptr)
	{
		return text;
	}
	const auto& glossary = m_dialog->getGlossary();
	if (glossary.size() == 0)
	{
		return text;
	}
	text.replace("“", "\"");
	text.replace("”", "\"");
	for (auto kvp : dict)
	{
		const auto& key = kvp.first;
		const auto& value = kvp.second;
		int id = text.indexOf(key);
		while (id != -1)
		{
			text.replace(id, key.size(), value);
			id = text.indexOf(key);
		}
	}
	return text;
}
