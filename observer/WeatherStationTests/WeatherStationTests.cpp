#include "stdafx.h"
#include "../WeatherStation/WeatherData.h"
#include <string>

class MockDisplay : public COrderedObserver<SWeatherInfo>
{

public: 
	MockDisplay(unsigned index, unsigned priority, std::string * indexSequence, std::string * wdTypeSequence)
		: COrderedObserver(priority)
		, m_index(index)
		, m_indexSequence(indexSequence)
		, m_wdTypeSequence(wdTypeSequence)
	{}

private:
	void Update(SWeatherInfo const& data) override
	{
		*m_indexSequence += std::to_string(m_index);
		std::string wdTypeNumber;
		if (data.wdType == WeatherStationType::IN)
		{
			wdTypeNumber = "0";
		}
		if (data.wdType == WeatherStationType::OUT)
		{
			wdTypeNumber = "1";
		}
		*m_wdTypeSequence += wdTypeNumber;
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
		: wdOut(WeatherStationType::OUT)
		, wdIn(WeatherStationType::IN)
		, mockDisplay1(3, 1, &indexSequence, &wdTypeSequence)
		, mockDisplay2(2, 2, &indexSequence, &wdTypeSequence)
		, mockDisplay3(1, 3, &indexSequence, &wdTypeSequence)
	{}
};

// Метеостанция
BOOST_FIXTURE_TEST_SUITE(WeatherStation, WeatherStationFixture)

	// оповещает наблюдателей в порядке приоритета
	BOOST_AUTO_TEST_CASE(notifies_obververs_in_order_of_priority)
	{
		wdOut.RegisterObserver(mockDisplay2);
		wdOut.RegisterObserver(mockDisplay1);
		wdOut.RegisterObserver(mockDisplay3);
		wdOut.SetMeasurements(3, 0.7, 760);

		BOOST_CHECK_EQUAL(indexSequence, "123");

		indexSequence = "";

		wdOut.RemoveObserver(mockDisplay1);
		wdOut.RemoveObserver(mockDisplay2);
		wdOut.RemoveObserver(mockDisplay3);

		wdOut.RegisterObserver(mockDisplay1);
		wdOut.RegisterObserver(mockDisplay3);
		wdOut.RegisterObserver(mockDisplay2);
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

		wdOut.SetMeasurements(3, 0.7, 760);
		BOOST_CHECK_EQUAL(wdTypeSequence, "111");
		wdIn.SetMeasurements(3, 0.7, 760);
		BOOST_CHECK_EQUAL(wdTypeSequence, "111000");
	}

BOOST_AUTO_TEST_SUITE_END()