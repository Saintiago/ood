#include "stdafx.h"
#include "../DocumentEditor/Document.h"
#include <string>
#include <exception>
#include "../DocumentEditor/Image.h"
#include "../DocumentEditor/InsertImageCommand.h"
#include <iostream>
#include <fstream>

using namespace std;
namespace fs = boost::filesystem;

struct Image_
{
	shared_ptr<IImage> image;
	Image_()
	{
		Path destination = fs::current_path() / "images\\image_test.png";
		fs::copy_file(fs::current_path() / "source\\image.png", destination, fs::copy_option::overwrite_if_exists);
		image = shared_ptr<IImage>(new CImage(100, 100, destination));
	}
};

// Изображение
BOOST_FIXTURE_TEST_SUITE(Image, Image_)

	// создается с заданными шириной и высотой
	BOOST_AUTO_TEST_CASE(created_with_given_width_and_height)
	{
		int expectedWidth = 100;
		int expectedHeight = 100;
		BOOST_CHECK_EQUAL(image->GetWidth(), expectedWidth);
		BOOST_CHECK_EQUAL(image->GetHeight(), expectedHeight);
	}

BOOST_AUTO_TEST_SUITE_END()

struct InsertImageCommand_
{
	CDocumentStorage storage;
	CInsertImageCommand insertImage;

	InsertImageCommand_()
		: insertImage(storage, 100, 100, { fs::current_path() / "source/image.png" }, 0)
	{
		insertImage.Execute();
	}
};

// при вставке изображение 
BOOST_FIXTURE_TEST_SUITE(InsertImageCommand, InsertImageCommand_)

	// копируется в папку images с документом
	BOOST_AUTO_TEST_CASE(copied_to_image_dir)
	{
		Path imagesDirPath = "images";
		Path insertedImagePath = storage.GetItem(0)->GetImage()->GetPath();
		BOOST_CHECK(std::equal(imagesDirPath.begin(), imagesDirPath.end(), insertedImagePath.begin()));
	}

	// копируется с уникальным именем и своим расширением
	BOOST_AUTO_TEST_CASE(copied_with_unique_name)
	{
		CInsertImageCommand insertImage2(storage, 100, 100, { fs::current_path() / "source/image.png" }, 1);
		insertImage2.Execute();
		BOOST_CHECK(storage.GetItem(0)->GetImage()->GetPath() != storage.GetItem(1)->GetImage()->GetPath());
	}

	// вставка может быть отменена
	BOOST_AUTO_TEST_CASE(can_be_undone)
	{
		insertImage.Unexecute();
		BOOST_CHECK_THROW(storage.GetItem(0)->GetImage(), out_of_range);
	}

	// если команда удалена после ее отмены то ресурс удаляется
	BOOST_AUTO_TEST_CASE(resource_deleted_if_command_deleted_after_undoing)
	{
		string resourceLocation;
		{
			insertImage.Execute();
			CInsertImageCommand insertImage2(storage, 100, 100, { boost::filesystem::current_path() / "source/image.png" }, 1);
			insertImage2.Execute();
			resourceLocation = storage.GetItem(1)->GetImage()->GetPath().string();
			insertImage2.Unexecute();
		}
		
		BOOST_CHECK(!boost::filesystem::exists(resourceLocation));
	}

	// если команда удалена после ее выполнения то ресурс сохраняется
	BOOST_AUTO_TEST_CASE(resource_remains_if_command_deleted_after_executing)
	{
		string resourceLocation;
		CInsertImageCommand insertImage2(storage, 100, 100, { boost::filesystem::current_path() / "source/image.png" }, 0);
		insertImage2.Execute();
		resourceLocation = storage.GetItem(0)->GetImage()->GetPath().string();
		BOOST_CHECK(boost::filesystem::exists(resourceLocation));
	}

BOOST_AUTO_TEST_SUITE_END()