#include "stdafx.h"
#include "../WeatherStation/WeatherData.h"
#include <string>

class MockDisplay : public COrderedObserver<SWeatherInfo>
{

public: 
	MockDisplay(unsigned index, unsigned priority, std::string * indexSequence)
		: COrderedObserver(priority)
		, m_index(index)
		, m_indexSequence(indexSequence)
	{}

private:
	void Update(SWeatherInfo const& data) override
	{
		*m_indexSequence += std::to_string(m_index);
	}

	unsigned const m_index;
	std::string * m_indexSequence;
};

struct WeatherStationFixture
{
	CWeatherData wd;
	std::string indexSequence = "";
	MockDisplay mockDisplay1;
	MockDisplay mockDisplay2;
	MockDisplay mockDisplay3;

	WeatherStationFixture()
		: mockDisplay1(1, 3, &indexSequence)
		, mockDisplay2(2, 2, &indexSequence)
		, mockDisplay3(3, 1, &indexSequence)
	{
		wd.RegisterObserver(mockDisplay2);
		wd.RegisterObserver(mockDisplay1);
		wd.RegisterObserver(mockDisplay3);
		wd.SetMeasurements(3, 0.7, 760);
	}
};

// Метеостанция
BOOST_FIXTURE_TEST_SUITE(WeatherStation, WeatherStationFixture)

	// оповещает наблюдателей в порядке приоритета
	BOOST_AUTO_TEST_CASE(notifies_obververs_in_order_of_priority)
	{
		BOOST_CHECK_EQUAL(indexSequence, "123");
	}

BOOST_AUTO_TEST_SUITE_END()