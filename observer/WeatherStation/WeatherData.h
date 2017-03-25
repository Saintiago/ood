#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>
#include "Observer.h"

using namespace std;

class CWeatherData;

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	const CWeatherData * sender;
};

class CDisplay: public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class SensorStat
{
public:
	SensorStat(string name)
		: m_name(move(name))
	{}

	void Update(double value)
	{
		if (m_min > value)
		{
			m_min = value;
		}
		if (m_max < value)
		{
			m_max = value;
		}
		m_acc += value;
		++m_countAcc;
	}

	void Show()
	{
		std::cout << "Max " << m_name << " " << m_max << std::endl;
		std::cout << "Min " << m_name << " " << m_min << std::endl;
		std::cout << "Average " << m_name << " " << (m_acc / m_countAcc) << std::endl;
		std::cout << "----------------" << std::endl;
	}

private:
	string m_name;

	double m_min = std::numeric_limits<double>::infinity();
	double m_max = -std::numeric_limits<double>::infinity();
	double m_acc = 0;
	unsigned m_countAcc = 0;
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplay()
		: m_temperatureStat("Temperature")
		, m_humidityStat("Humidity")
		, m_pressureStat("Pressure")
	{}

private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		m_temperatureStat.Update(data.temperature);
		m_humidityStat.Update(data.humidity);
		m_pressureStat.Update(data.pressure);

		m_temperatureStat.Show();
		m_humidityStat.Show();
		m_pressureStat.Show();
		
	}

	SensorStat m_temperatureStat;
	SensorStat m_humidityStat;
	SensorStat m_pressureStat;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	CWeatherData() = default;

	// Температура в градусах Цельсия
	double GetTemperature()const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
	{
		return m_pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.sender = this;
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;	
	double m_pressure = 760.0;
};
