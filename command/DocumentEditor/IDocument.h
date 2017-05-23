#pragma once
#include "stdafx.h"
#include "DocumentItem_fwd.h"

using namespace std;
using boost::optional;
using boost::none;

/*
�������� ���������
*/
class IDocument
{
public:
	// ��������� �������� ������ � ��������� ������� (������� ����������� ��������)
	// ���� �������� position �� ������, ������� ���������� � ����� ���������
	virtual void InsertParagraph(const string& text, optional<size_t> position = none) = 0;

	// ��������� ����������� � ��������� ������� (������� ����������� ��������)
	// �������� path ������ ���� � ������������ �����������
	// ��� ������� ����������� ������ ������������ � ���������� images 
	// ��� ������������� ��������������� ������
	virtual void InsertImage(const Path& path, int width, int height,
		optional<size_t> position = none) = 0;

	// ������� �������� � ������ ��������� ��������� � ����������� ����� ������
	virtual void List(ostream& output) = 0;

	// ������� ������� � ��������� �������� �������������� � �� ����������
	virtual void Help(ostream& output) = 0;

	// �������� ����� � ���������, ����������� � ��������� ������� ���������
	virtual void ReplaceText(size_t position, string newValue) = 0;

	// �������� ������ �����������, ������������ � ��������� ������� ���������
	virtual void ResizeImage(size_t position, int width, int height) = 0;

	// ���������� ���������� ��������� � ���������
//	virtual size_t GetItemsCount()const = 0;

	// ������ � ��������� �����������
	virtual DocumentItemPtr GetItem(size_t index)const = 0;
//	virtual CDocumentItem GetItem(size_t index) = 0;

	// ������� ������� �� ���������
	virtual void DeleteItem(size_t index) = 0;

	// ���������� ��������� ���������
	virtual string GetTitle()const = 0;
	// �������� ��������� ���������
	virtual void SetTitle(const string & title) = 0;

	// �������� � ����������� �������� Undo
	virtual bool CanUndo()const = 0;
	// �������� ������� ��������������
	virtual void Undo() = 0;

	// �������� � ����������� �������� Redo
	virtual bool CanRedo()const = 0;
	// ��������� ���������� ������� ��������������
	virtual void Redo() = 0;

	// ��������� �������� � ������� html. ����������� ����������� � ���������� images
	// ���� � ������������ ����������� ������������ ���� � ������������ HTML �����
	virtual void Save(const Path& path)const = 0;

	virtual ~IDocument() = default;
};
