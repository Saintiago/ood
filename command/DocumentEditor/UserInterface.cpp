#include "stdafx.h"
#include "UserInterface.h"
#include "ReplaceTextCommand.h"
#include "ResizeImageCommand.h"
#include <exception>
#include <boost/algorithm/string/join.hpp>

using Params = std::vector<std::string>;
using namespace std;

Params ExplodeViaSpace(const string & commandLine);
string ImplodeViaSpace(Params params);
string PopFront(Params & params);

CUserInterface::CUserInterface(istream & input, ostream & output)
	: m_input(input)
	, m_output(output)
{
}


CUserInterface::~CUserInterface()
{
}

void CUserInterface::StartListeningInput()
{
	m_output << "UI initialized and waiting for command." << endl << "> ";
	string line;
	while (std::getline(m_input, line))
	{
		try
		{
			ExecuteCommand(line);
		}
		catch (exception ex)
		{
			m_output << ex.what();
		}
		m_output << endl << "> ";
	}

}

void CUserInterface::ExecuteCommand(const string & commandLine)
{
	Params params = ExplodeViaSpace(commandLine);
	string command = PopFront(params);

	if (command == "InsertParagraph")
	{
		string index = PopFront(params);
		string text = ImplodeViaSpace(params);

		if (index == "end")
		{
			m_document.InsertParagraph(text);
		}
		else
		{
			m_document.InsertParagraph(text, stoi(index));
		}
	}

	if (command == "InsertImage")
	{
		string index = PopFront(params);
		int width = stoi(PopFront(params));
		int height = stoi(PopFront(params));
		Path path = { PopFront(params) };

		if (index == "end")
		{
			m_document.InsertImage(path, width, height);
		}
		else
		{
			m_document.InsertImage(path, width, height, stoi(index));
		}
	}

	else if (command == "SetTitle")
	{
		string text = ImplodeViaSpace(params);
		m_document.SetTitle(text);
	}

	else if (command == "List")
	{
		m_document.List(m_output);
	}

	else if (command == "ReplaceText")
	{
		int index = stoi(PopFront(params));
		string text = ImplodeViaSpace(params);
		shared_ptr<IParagraph> paragraph = m_document.GetItem(index)->GetParagraph();	
		m_document.AddAndExecuteCommand(make_unique<CReplaceTextCommand>(paragraph, text));
	}

	else if (command == "DeleteItem")
	{
		string index = params.at(0);
		m_document.DeleteItem(stoi(index));
	}

	else if (command == "Help")
	{
		Help();
	}

	else if (command == "Save")
	{
		Path savePath(params.at(0));
		m_document.Save(savePath);
	}

	else if (command == "Undo")
	{
		m_document.Undo();
	}

	else if (command == "Redo")
	{
		m_document.Redo();
	}

	else
	{
		throw invalid_argument("Unknown command");
	}
}

void CUserInterface::List()
{
	m_document.List(m_output);
}

void CUserInterface::SetTitle(const std::string & title)
{
	m_document.SetTitle(title);
}

void CUserInterface::Help()
{
	m_output << "Available commands:" << endl;
	m_output << "InsertParagraph <position>|end <text>" << endl;
	m_output << "InsertImage <position>|end <width> <height> <path>" << endl;
	m_output << "SetTitle <Title>" << endl;
	m_output << "List" << endl;
	m_output << "ReplaceText <position> <text>" << endl;
	m_output << "ResizeImage <position> <width> <height>" << endl;
	m_output << "DeleteItem <position>" << endl;
	m_output << "Help" << endl;
	m_output << "Undo" << endl;
	m_output << "Redo" << endl;
	m_output << "Save <path>" << endl;
}

Params ExplodeViaSpace(const string & commandLine)
{
	stringstream ss(commandLine);
	Params params;
	string param;
	while (ss >> param)
	{
		params.push_back(param);
	}

	return params;
}

string ImplodeViaSpace(Params params)
{
	return boost::algorithm::join(params, " ");
}

string PopFront(Params & params)
{
	string frontParam = params.at(0);
	params.erase(params.begin());
	return frontParam;
}