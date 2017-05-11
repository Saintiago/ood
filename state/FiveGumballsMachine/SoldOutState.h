#pragma once
#include "stdafx.h"

class CSoldOutState : public IState
{
public:
	CSoldOutState(IFiveGumballMachine & gumballMachine)
		:m_gumballMachine(gumballMachine)
	{}

	void Refill(unsigned numBalls)
	{
		m_gumballMachine.SetBallsCount(numBalls);
		std::cout << "Macine refilled successfully\n";
		if (numBalls > 0)
		{
			if (m_gumballMachine.GetCoinsCount() > 0)
			{
				m_gumballMachine.SetHasQuarterState();
			}
			else
			{
				m_gumballMachine.SetNoQuarterState();
			}
		}
	}

	void InsertQuarter() override
	{
		std::cout << "You can't insert a quarter, the machine is sold out\n";
	}
	void EjectQuarter() override
	{
		std::cout << "You can't eject, you haven't inserted a quarter yet\n";
	}
	void TurnCrank() override
	{
		std::cout << "You turned but there's no gumballs\n";
	}
	void Dispense() override
	{
		std::cout << "No gumball dispensed\n";
	}
	std::string ToString() const override
	{
		return "sold out";
	}
private:
	IFiveGumballMachine & m_gumballMachine;
};
