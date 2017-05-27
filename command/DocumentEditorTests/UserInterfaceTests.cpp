#include "stdafx.h"
#include "../DocumentEditor/UserInterface.h"
#include <string>
#include <exception>
#include <iostream>
#include <fstream>

using namespace std;
namespace fs = boost::filesystem;

struct UserInterface_
{
	CUserInterface ui;
	stringstream stringInput;
	stringstream stringOutput;
	UserInterface_()
		: ui(stringInput, stringOutput)
	{
	}
};

// ���������������� ���������
BOOST_FIXTURE_TEST_SUITE(UserInterface, UserInterface_)

	// ������� ��������� � ���������� ��� ��������
	BOOST_AUTO_TEST_CASE(shows_ready_message)
	{
		ui.StartListeningInput();
		string expectedOut = "UI initialized and waiting for command.\n> ";
		BOOST_CHECK_EQUAL(expectedOut, stringOutput.str());
	}

	// ����� �������� ������� � ���������� ���������
	BOOST_AUTO_TEST_CASE(can_show_title_and_elements_list)
	{
		stringInput << "SetTitle This is document title" << endl;
		stringInput << "InsertParagraph end This is very first paragraph" << endl;
		stringInput << "InsertParagraph 1 This is second paragraph" << endl;

		ui.StartListeningInput();

		stringstream expected;
		expected << "Title : This is document title" << endl
			<< "0. Paragraph : This is very first paragraph" << endl
			<< "1. Paragraph : This is second paragraph" << endl;
		
		stringOutput.str(std::string());
		ui.List();

		BOOST_CHECK_EQUAL(expected.str(), stringOutput.str());

	}

	// ����� ��������� ������� InsertParagraph
	BOOST_AUTO_TEST_CASE(can_perform_insert_paragraph_command)
	{
		stringInput << "InsertParagraph end some text";

		ui.StartListeningInput();

		stringstream expected;
		expected << "Title : " << endl
			<< "0. Paragraph : some text" << endl;

		stringOutput.str(std::string());
		ui.List();

		BOOST_CHECK_EQUAL(expected.str(), stringOutput.str());
	}

	// ����� ��������� ������� ReplaceText
	BOOST_AUTO_TEST_CASE(can_perform_replace_text_command)
	{
		stringInput << "InsertParagraph end some text" << endl;
		stringInput << "ReplaceText 0 replaced text" << endl;

		ui.StartListeningInput();

		stringstream expected;
		expected << "Title : " << endl
			<< "0. Paragraph : replaced text" << endl;

		stringOutput.str(std::string());
		ui.List();

		BOOST_CHECK_EQUAL(expected.str(), stringOutput.str());
	}

	// ����� ��������� ������� ResizeImage
	BOOST_AUTO_TEST_CASE(can_resize_image_at_specified_position)
	{
		Path imagePath = fs::current_path() / "source/image.png";
		stringInput << "InsertImage end 50 100 " << imagePath.string() << endl;
		stringInput << "ResizeImage 0 200 300" << endl;

		ui.StartListeningInput();

		stringstream expected;
		expected << "Title : " << endl
			<< "0. Image : 200 300";

		stringOutput.str(std::string());
		ui.List();

		string outputStr = stringOutput.str();

		BOOST_CHECK_EQUAL(expected.str(), outputStr.substr(0, outputStr.size() - 25));
	}

	// ����� ��������� ������� SetTitle
	BOOST_AUTO_TEST_CASE(can_perform_set_title_command)
	{
		stringInput << "SetTitle Test title" << endl;

		ui.StartListeningInput();

		stringstream expected;
		expected << "Title : Test title" << endl;

		stringOutput.str(std::string());
		ui.List();

		BOOST_CHECK_EQUAL(expected.str(), stringOutput.str());
	}

	// ����� ��������� ������� DeleteItem
	BOOST_AUTO_TEST_CASE(can_perform_delete_item_command)
	{
		stringInput << "InsertParagraph end some paragraph" << endl;
		stringInput << "DeleteItem 0" << endl;

		ui.StartListeningInput();

		stringstream expected;
		expected << "Title : " << endl;

		stringOutput.str(std::string());
		ui.List();

		BOOST_CHECK_EQUAL(expected.str(), stringOutput.str());
	}

	// ����� ��������� ������� Save
	BOOST_AUTO_TEST_CASE(can_perform_save_command)
	{
		Path savePath = fs::current_path() / "ui_save_test";

		if (!fs::exists(savePath))
		{
			fs::create_directory(savePath);
		}

		Path saveFilePath = savePath / "index.html";

		stringInput << "SetTitle Title" << endl;
		stringInput << "Save " << saveFilePath.string() << endl;

		ui.StartListeningInput();

		BOOST_CHECK(fs::exists(savePath));

		fs::remove_all(savePath);
	}

	// InsertParagraph ReplaceText Undo Undo Redo Redo. ������ ����������� ���������� �����.
	BOOST_AUTO_TEST_CASE(replaced_text_should_stay)
	{
		stringInput << "InsertParagraph end Original text" << endl;
		stringInput << "ReplaceText 0 Replaced text" << endl;
		stringInput << "Undo" << endl;
		stringInput << "Undo" << endl;
		stringInput << "Redo" << endl;
		stringInput << "Redo" << endl;

		ui.StartListeningInput();

		stringstream expected;
		expected << "Title : " << endl
			<< "0. Paragraph : Replaced text" << endl;

		stringOutput.str(std::string());
		ui.List();

		BOOST_CHECK_EQUAL(expected.str(), stringOutput.str());
	}


BOOST_AUTO_TEST_SUITE_END()