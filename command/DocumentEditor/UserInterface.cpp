#include "stdafx.h"
#include "UserInterface.h"
#include <exception>
#include <boost/algorithm/string/join.hpp>

using Params = std::vector<std::string>;
using namespace std;

Params ExplodeViaSpace(const string & commandLine);
string ImplodeViaSpace(Params params);

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
	string command = params.at(0);
	params.erase(params.begin());

	if (command == "InsertParagraph")
	{
		string index = params.at(0);
		params.erase(params.begin());
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
		string index = params.at(0);
		params.erase(params.begin());
		string text = ImplodeViaSpace(params);
		m_document.ReplaceText(stoi(index), text);
	}

	else if (command == "DeleteItem")
	{
		string index = params.at(0);
		m_document.DeleteItem(stoi(index));
	}

	else if (command == "Help")
	{
		m_document.Help(m_output);
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