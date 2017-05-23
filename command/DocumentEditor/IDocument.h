#pragma once
#include "stdafx.h"
#include "DocumentItem_fwd.h"

using namespace std;
using boost::optional;
using boost::none;

/*
Интерфес документа
*/
class IDocument
{
public:
	// Вставляет параграф текста в указанную позицию (сдвигая последующие элементы)
	// Если параметр position не указан, вставка происходит в конец документа
	virtual void InsertParagraph(const string& text, optional<size_t> position = none) = 0;

	// Вставляет изображение в указанную позицию (сдвигая последующие элементы)
	// Параметр path задает путь к вставляемому изображению
	// При вставке изображение должно копироваться в подкаталог images 
	// под автоматически сгенерированным именем
	virtual void InsertImage(const Path& path, int width, int height,
		optional<size_t> position = none) = 0;

	// Выводит название и список элементов документа в стандартный поток вывода
	virtual void List(ostream& output) = 0;

	// Выводит справку о доступных командах редактирования и их аргументах
	virtual void Help(ostream& output) = 0;

	// Заменяет текст в параграфе, находящемся в указанной позиции документа
	virtual void ReplaceText(size_t position, string newValue) = 0;

	// Изменяет размер изображения, находящегося в указанной позиции документа
	virtual void ResizeImage(size_t position, int width, int height) = 0;

	// Возвращает количество элементов в документе
//	virtual size_t GetItemsCount()const = 0;

	// Доступ к элементам изображения
	virtual DocumentItemPtr GetItem(size_t index)const = 0;
//	virtual CDocumentItem GetItem(size_t index) = 0;

	// Удаляет элемент из документа
	virtual void DeleteItem(size_t index) = 0;

	// Возвращает заголовок документа
	virtual string GetTitle()const = 0;
	// Изменяет заголовок документа
	virtual void SetTitle(const string & title) = 0;

	// Сообщает о доступности операции Undo
	virtual bool CanUndo()const = 0;
	// Отменяет команду редактирования
	virtual void Undo() = 0;

	// Сообщает о доступности операции Redo
	virtual bool CanRedo()const = 0;
	// Выполняет отмененную команду редактирования
	virtual void Redo() = 0;

	// Сохраняет документ в формате html. Изображения сохраняются в подкаталог images
	// пути к изображениям указываются относительно пути к сохраняемому HTML файлу
	virtual void Save(const Path& path)const = 0;

	virtual ~IDocument() = default;
};
