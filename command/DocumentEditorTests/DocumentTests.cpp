#include "stdafx.h"
#include "../DocumentEditor/Document.h"
#include <string>
#include <exception>
#include <fstream>

using namespace std;
namespace fs = boost::filesystem;

struct Document_
{
	CDocument document;
	Document_()
		: document()
	{}
};

// Документ
BOOST_FIXTURE_TEST_SUITE(Document, Document_)
		
	// создается с пустым заголовком
	BOOST_AUTO_TEST_CASE(has_empty_title_by_default)
	{
		string expectedTitle = "";
		BOOST_CHECK_EQUAL(document.GetTitle(), expectedTitle);
	}

	struct when_title_set_ : Document_
	{
		when_title_set_()
			: Document_()
		{
			document.SetTitle("Test Title");
		}
	};

	// когда заголовок задан
	BOOST_FIXTURE_TEST_SUITE(when_title_set, when_title_set_)
	
		// он сохраняется в документе
		BOOST_AUTO_TEST_CASE(it_stored_in_document)
		{
			string expectedTitle = "Test Title";
			BOOST_CHECK_EQUAL(document.GetTitle(), expectedTitle);
		}

		// может быть отменен командой Undo
		BOOST_AUTO_TEST_CASE(can_be_undone)
		{
			BOOST_CHECK(document.CanUndo());
			document.Undo();
			string expectedTitle = "";
			BOOST_CHECK_EQUAL(document.GetTitle(), expectedTitle);
		}

		// может быть повторен командой Redo
		BOOST_AUTO_TEST_CASE(can_be_redone)
		{
			BOOST_CHECK(document.CanUndo());
			document.Undo();
			BOOST_CHECK(document.CanRedo());
			document.Redo();
			string expectedTitle = "Test Title";
			BOOST_CHECK_EQUAL(document.GetTitle(), expectedTitle);
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct when_paragraph_inserted_ : Document_
	{
		when_paragraph_inserted_()
			: Document_()
		{
			const string& text = "New Text";
			document.InsertParagraph(text);
		}
	};

	// когда параграф вставлен
	BOOST_FIXTURE_TEST_SUITE(when_paragraph_inserted, when_paragraph_inserted_)

		// параграф можно получить по номеру позиции
		BOOST_AUTO_TEST_CASE(can_get_paragraph_via_position)
		{
			std::string expectedText = "New Text";
			auto paragraphText = document.GetItem(0)->GetParagraph()->GetText();
			BOOST_CHECK_EQUAL(expectedText, paragraphText);
		}

		// можно вставить еще один параграф перед сущствующим
		BOOST_AUTO_TEST_CASE(can_insert_another_paragraph_before)
		{
			document.InsertParagraph("Another paragraph", 0);

			std::string expectedText = "Another paragraph";
			auto paragraphText = document.GetItem(0)->GetParagraph()->GetText();
			BOOST_CHECK_EQUAL(expectedText, paragraphText);

			expectedText = "New Text";
			paragraphText = document.GetItem(1)->GetParagraph()->GetText();
			BOOST_CHECK_EQUAL(expectedText, paragraphText);
		}

		// можно отменить вставку
		BOOST_AUTO_TEST_CASE(insertion_can_be_undone)
		{
			document.Undo();
			BOOST_CHECK_THROW(document.GetItem(0)->GetParagraph(), out_of_range);
		}

	BOOST_AUTO_TEST_SUITE_END()

	// можно вывести название и список элементов документа
	BOOST_AUTO_TEST_CASE(can_show_title_and_elements_list)
	{
		document.SetTitle("This is document title");
		document.InsertParagraph("This is very first paragraph");
		document.InsertImage(fs::current_path() / "source\\image.png", 400, 300);
		document.InsertParagraph("This is paragraph after image");

		stringstream ss;
		document.List(ss);

		Path imagePath = document.GetItem(1)->GetImage()->GetPath();

		stringstream expected;
		expected << "Title : This is document title" << endl
			<< "0. Paragraph : This is very first paragraph" << endl
			<< "1. Image : 400 300 " << imagePath << endl
			<< "2. Paragraph : This is paragraph after image" << endl;

		BOOST_CHECK_EQUAL(expected.str(), ss.str());

	}

	// можно заменить текст в параграфе на выбранной позиции
	BOOST_AUTO_TEST_CASE(can_replace_text_in_paragraph_at_specified_position)
	{
		string textBefore = "This is very first paragraph";
		document.InsertParagraph(textBefore);
		BOOST_CHECK_EQUAL(textBefore, document.GetItem(0)->GetParagraph()->GetText());

		string textAfter = "Replaced text";
		document.ReplaceText(0, textAfter);
		BOOST_CHECK_EQUAL(textAfter, document.GetItem(0)->GetParagraph()->GetText());

		BOOST_CHECK_THROW(document.ReplaceText(1, textAfter), out_of_range);
	}

	// Изменяет размер изображения, находящегося в указанной позиции документа
	BOOST_AUTO_TEST_CASE(can_resize_image_at_specified_position)
	{
		int widthBefore = 50;
		int heightBefore = 100;
		document.InsertImage(fs::current_path() / "source\\image.png", widthBefore, heightBefore);
		BOOST_CHECK_EQUAL(widthBefore, document.GetItem(0)->GetImage()->GetWidth());
		BOOST_CHECK_EQUAL(heightBefore, document.GetItem(0)->GetImage()->GetHeight());

		int widthAfter = 200;
		int heightAfter = 300;
		document.ResizeImage(0, widthAfter, heightAfter);
		BOOST_CHECK_EQUAL(widthAfter, document.GetItem(0)->GetImage()->GetWidth());
		BOOST_CHECK_EQUAL(heightAfter, document.GetItem(0)->GetImage()->GetHeight());

		BOOST_CHECK_THROW(document.ResizeImage(1, widthAfter, heightAfter), out_of_range);
	}

	// можно удалить элемент в заданной позиции
	BOOST_AUTO_TEST_CASE(can_delete_element_at_specified_position)
	{
		string text = "This is very first paragraph";
		document.InsertParagraph(text);
		BOOST_CHECK_EQUAL(text, document.GetItem(0)->GetParagraph()->GetText());
		document.DeleteItem(0);
		BOOST_CHECK_THROW(document.GetItem(0)->GetParagraph(), out_of_range);
		document.Undo();
		BOOST_CHECK_EQUAL(text, document.GetItem(0)->GetParagraph()->GetText());
	}

	// Сохраняет текущее состояние документа в файл формата html с изображениями
	BOOST_AUTO_TEST_CASE(can_be_saved_to_html)
	{
		string title = "This is document title";
		string p1 = "This is very first paragraph";
		string p2 = "This is paragraph after image";
		document.SetTitle(title);
		document.InsertParagraph(p1);
		document.InsertImage(fs::current_path() / "source\\image.png", 400, 300);
		document.InsertParagraph(p2);

		Path testBasePath = fs::current_path() / "test";
		fs::create_directory(testBasePath);
		document.Save(testBasePath);

		Path expectedImagesDir = testBasePath / "images";
		BOOST_CHECK(fs::exists(expectedImagesDir));

		Path imageFileName = document.GetItem(1)->GetImage()->GetPath().filename();
		Path expectedImagePath = expectedImagesDir / imageFileName;
		BOOST_CHECK(fs::exists(expectedImagePath));

		Path expectedIndexPath = testBasePath / "index.html";
		BOOST_CHECK(fs::exists(expectedIndexPath));

		Path expectedRelativeImagePath = { "images" / imageFileName };
		ifstream indexFile(expectedIndexPath.string());
		string indexFileContents;
		std::getline(indexFile, indexFileContents);
		stringstream expFileStream;
		expFileStream << "<!DOCTYPE html>"
			<< "<html><head>"
			<< "<title>" << title << "</title>"
			<< "</head><body>"
			<< "<p>" << p1 << "</p>"
			<< "<img width=\"400\" height=\"300\" src=" << expectedRelativeImagePath << " />"
			<< "<p>" << p2 << "</p>"
			<< "</body></html>";
		string expectedFileContents;
		std::getline(expFileStream, expectedFileContents);
		BOOST_CHECK_EQUAL(expectedFileContents, indexFileContents);

		indexFile.close();
		fs::remove_all(testBasePath);
	}

	// История содержит максимум 10 комманд
	BOOST_AUTO_TEST_CASE(remembers_10_commands_max)
	{
		for (int i = 1; i <= 11; i++)
		{
			document.InsertParagraph("p" + i);
		}

		for (int i = 0; i < 10; i++)
		{
			document.Undo();
		}

		BOOST_CHECK_THROW(document.Undo(), logic_error);
		BOOST_CHECK_EQUAL("p1", document.GetItem(0)->GetParagraph()->GetText());
		BOOST_CHECK_THROW(document.GetItem(1), out_of_range);
	}

BOOST_AUTO_TEST_SUITE_END()