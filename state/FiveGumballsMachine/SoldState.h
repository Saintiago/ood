#pragma 
#include "stdafx.h"

class CSoldState : public IState
{
public:
	CSoldState(IFiveGumballMachine & gumballMachine)
		:m_gumballMachine(gumballMachine)
	{}

	void Refill(unsigned numBalls)
	{
		std::cout << "Wait until gumball is dispensed\n";
	}

	void InsertQuarter() override
	{
		std::cout << "Please wait, we're already giving you a gumball\n";
	}
	void EjectQuarter() override
	{
		std::cout << "Sorry you already turned the crank\n";
	}
	void TurnCrank() override
	{
		std::cout << "Turning twice doesn't get you another gumball\n";
	}
	void Dispense() override
	{
		m_gumballMachine.ReleaseBall();
		if (m_gumballMachine.GetBallCount() == 0)
		{
			std::cout << "Oops, out of gumballs\n";
			m_gumballMachine.SetSoldOutState();
		}
		else if (m_gumballMachine.GetCoinsCount() == 0)
		{
			m_gumballMachine.SetNoQuarterState();
		}
		else
		{
			m_gumballMachine.SetHasQuarterState();
		}
	}
	std::string ToString() const override
	{
		return "delivering a gumball";
	}
private:
	IFiveGumballMachine & m_gumballMachine;
};
