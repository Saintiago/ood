#pragma once
#include "Document.h"

class CUserInterface
{
public:
	CUserInterface(istream & input, ostream & output);
	~CUserInterface();

	void StartListeningInput();
	void List();
	void SetTitle(const std::string & title);

private:
	CDocument m_document;
	istream & m_input;
	ostream & m_output;

	void ExecuteCommand(const std::string & commandLine);
};

