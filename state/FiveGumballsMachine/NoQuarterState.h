#pragma once
#include "stdafx.h"

class CNoQuarterState : public IState
{
public:
	CNoQuarterState(IFiveGumballMachine & gumballMachine)
		: m_gumballMachine(gumballMachine)
	{}

	void Refill(unsigned numBalls)
	{
		m_gumballMachine.SetBallsCount(numBalls);
		std::cout << "Macine refilled successfully\n";
		if (numBalls > 0)
		{
			m_gumballMachine.SetNoQuarterState();
		}
		else
		{
			m_gumballMachine.SetSoldOutState();
		}
	}

	void InsertQuarter() override
	{
		m_gumballMachine.AddCoin();
		std::cout << "You inserted a quarter\n";
		m_gumballMachine.SetHasQuarterState();
	}
	void EjectQuarter() override
	{
		std::cout << "You haven't inserted a quarter\n";
	}
	void TurnCrank() override
	{
		std::cout << "You turned but there's no quarter\n";
	}
	void Dispense() override
	{
		std::cout << "You need to pay first\n";
	}
	std::string ToString() const override
	{
		return "waiting for quarter";
	}
private:
	IFiveGumballMachine & m_gumballMachine;
};
