#pragma once

#include "IBeverage.h"

class CBeverage : public IBeverage
{
public:
	CBeverage(double cost, std::string description)
		: m_cost(cost)
		, m_description(description)
	{}

	std::string GetDescription() const override
	{
		return m_description;
	}

	double GetCost() const override
	{
		return m_cost;
	}

private:
	double m_cost;
	std::string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(double cost = 60, std::string description = "Coffee") : CBeverage(cost, description) {}
};

enum class CapuccinoType
{
	Single,
	Double
};

// Капуччино
class CCapuccino : public CCoffee
{
public:
	CCapuccino(CapuccinoType capuccinoType)
		: CCoffee(determineCost(capuccinoType), determineDescription(capuccinoType))
	{}

private:
	double determineCost(CapuccinoType capuccinoType)
	{ 
		return (capuccinoType == CapuccinoType::Single) ? 80 : 120;
	}
	std::string determineDescription(CapuccinoType capuccinoType)
	{ 
		return (capuccinoType == CapuccinoType::Single) ? "Single capuccino" : "Double capuccino";
	}
};

enum class LatteType
{
	Single,
	Double
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(LatteType latteType)
		: CCoffee(determineCost(latteType), determineDescription(latteType))
	{}

private:
	double determineCost(LatteType latteType)
	{
		return (latteType == LatteType::Single) ? 90 : 130;
	}
	std::string determineDescription(LatteType latteType)
	{
		return (latteType == LatteType::Single) ? "Single Latte" : "Double Latte";
	}
};

enum class TeaType
{
	Nuri,
	Maiskiy,
	So_slonom,
	Lipton
};

// Чай
class CTea : public CBeverage
{
public:
	CTea(TeaType teaType)
		: CBeverage(30, determineDescription(teaType))
	{}

private:

	std::string determineDescription(TeaType teaType)
	{
		switch(teaType)
		{
			case TeaType::Nuri:
				return "Nuri tea";
				break;
			case TeaType::Maiskiy:
				return "Maiskiy tea";
				break;
			case TeaType::So_slonom:
				return "So slonom tea";
				break;
			case TeaType::Lipton:
				return "Lipton tea";
		}
	}

};

enum class MilkshakeType
{
	Small,
	Medium,
	Large
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkshakeType milkshakeType)
		: CBeverage(determineCost(milkshakeType), determineDescription(milkshakeType))
	{}
	
private:

	double determineCost(MilkshakeType milkshakeType)
	{
		switch (milkshakeType)
		{
		case MilkshakeType::Small:
			return 50;
			break;
		case MilkshakeType::Medium:
			return 60;
			break;
		case MilkshakeType::Large:
			return 80;
		}
	}

	std::string determineDescription(MilkshakeType milkshakeType)
	{
		switch (milkshakeType)
		{
		case MilkshakeType::Small:
			return "Small milkshake";
			break;
		case MilkshakeType::Medium:
			return "Medium milkshake";
			break;
		case MilkshakeType::Large:
			return "Large milkshake";
		}
	}
};