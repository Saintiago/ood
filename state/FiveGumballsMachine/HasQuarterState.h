#pragma once
#include "stdafx.h"

class CHasQuarterState : public IState
{
public:
	CHasQuarterState(IFiveGumballMachine & gumballMachine)
		:m_gumballMachine(gumballMachine)
	{}

	void Refill(unsigned numBalls)
	{
		m_gumballMachine.SetBallsCount(numBalls);
		std::cout << "Macine refilled successfully\n";
		if (numBalls > 0)
		{
			m_gumballMachine.SetHasQuarterState();
		}
		else
		{
			m_gumballMachine.SetSoldOutState();
		}
	}

	void InsertQuarter() override
	{
		if (m_gumballMachine.GetCoinsCount() < 5)
		{
			m_gumballMachine.AddCoin();
			std::cout << "You inserted a quarter\n";
		}
		else
		{
			std::cout << "You can't insert another quarter\n";
		}
	}
	void EjectQuarter() override
	{
		std::cout << "Quarters returned\n";
		m_gumballMachine.SetNoQuarterState();
	}
	void TurnCrank() override
	{
		std::cout << "You turned...\n";
		m_gumballMachine.SpendCoin();
		m_gumballMachine.SetSoldState();
	}
	void Dispense() override
	{
		std::cout << "No gumball dispensed\n";
	}
	std::string ToString() const override
	{
		return "waiting for turn of crank";
	}
private:
	IFiveGumballMachine & m_gumballMachine;
};
