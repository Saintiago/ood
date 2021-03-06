#pragma once

struct IGumballMachine
{
	virtual void ReleaseBall() = 0;
	virtual unsigned GetBallCount()const = 0;

	virtual void SetSoldOutState() = 0;
	virtual void SetNoQuarterState() = 0;
	virtual void SetSoldState() = 0;
	virtual void SetHasQuarterState() = 0;

	virtual ~IGumballMachine() = default;
};

struct IFiveGumballMachine : IGumballMachine
{
	virtual unsigned GetCoinsCount()const = 0;
	virtual void AddCoin() = 0;
	virtual void SpendCoin() = 0;
	virtual void SetBallsCount(unsigned) = 0;
};