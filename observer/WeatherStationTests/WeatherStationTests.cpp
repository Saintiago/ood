#include "stdafx.h"
#include "../WeatherStation/WeatherData.h"
#include <string>

class MockDisplay : public IObserver<SWeatherInfo>
{

public: 
	MockDisplay(unsigned index, std::string * indexSequence, std::string * wdTypeSequence)
		: m_index(index)
		, m_indexSequence(indexSequence)
		, m_wdTypeSequence(wdTypeSequence)
	{}

private:
	void Update(SWeatherInfo const& data) override
	{
		*m_indexSequence += std::to_string(m_index);
		*m_wdTypeSequence += std::to_string((int) & * data.sender) + " ";
	}

	unsigned const m_index;
	std::string * m_indexSequence;
	std::string * m_wdTypeSequence;
};

struct WeatherStationFixture
{
	CWeatherData wdOut, wdIn;
	std::string indexSequence = "";
	std::string wdTypeSequence = "";
	MockDisplay mockDisplay1;
	MockDisplay mockDisplay2;
	MockDisplay mockDisplay3;

	WeatherStationFixture()
		: mockDisplay1(3, &indexSequence, &wdTypeSequence)
		, mockDisplay2(2, &indexSequence, &wdTypeSequence)
		, mockDisplay3(1, &indexSequence, &wdTypeSequence)
	{}
};

// Метеостанция
BOOST_FIXTURE_TEST_SUITE(WeatherStation, WeatherStationFixture)

	// оповещает наблюдателей в порядке приоритета
	BOOST_AUTO_TEST_CASE(notifies_obververs_in_order_of_priority)
	{
		wdOut.RegisterObserver(mockDisplay2, 2);
		wdOut.RegisterObserver(mockDisplay1, 3);
		wdOut.RegisterObserver(mockDisplay3, 1);
		wdOut.SetMeasurements(3, 0.7, 760);

		BOOST_CHECK_EQUAL(indexSequence, "123");

		indexSequence = "";

		wdOut.RemoveObserver(mockDisplay1);
		wdOut.RemoveObserver(mockDisplay2);
		wdOut.RemoveObserver(mockDisplay3);

		wdOut.RegisterObserver(mockDisplay1, 3);
		wdOut.RegisterObserver(mockDisplay3, 1);
		wdOut.RegisterObserver(mockDisplay2, 2);
		wdOut.SetMeasurements(3, 0.7, 760);

		BOOST_CHECK_EQUAL(indexSequence, "123");
	}

	// сообщает от какой именно станции пришло оповещение
	BOOST_AUTO_TEST_CASE(notifies_observers_about_data_origin)
	{
		wdOut.RegisterObserver(mockDisplay1);
		wdOut.RegisterObserver(mockDisplay2);
		wdOut.RegisterObserver(mockDisplay3);

		wdIn.RegisterObserver(mockDisplay1);
		wdIn.RegisterObserver(mockDisplay2);
		wdIn.RegisterObserver(mockDisplay3);

		std::string wdOutAddress = std::to_string((int) & wdOut);
		std::string wdInAddress = std::to_string((int) & wdIn);

		wdOut.SetMeasurements(3, 0.7, 760);
		BOOST_CHECK_EQUAL(wdTypeSequence, wdOutAddress + " " + wdOutAddress + " " + wdOutAddress + " ");
		wdTypeSequence = "";
		wdIn.SetMeasurements(3, 0.7, 760);
		BOOST_CHECK_EQUAL(wdTypeSequence, wdInAddress + " " + wdInAddress + " " + wdInAddress + " ");
	}

BOOST_AUTO_TEST_SUITE_END()