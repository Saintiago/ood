#pragma once
#include "stdafx.h"
#include "HasQuarterState.h"
#include "NoQuarterState.h"
#include "SoldOutState.h"
#include "SoldState.h"

class CFiveGumballsMachine : private IGumballMachine
{
public:
	CFiveGumballsMachine(unsigned numBalls);
	~CFiveGumballsMachine() = default;

	void EjectQuarter();
	void InsertQuarter();
	void TurnCrank();
	std::string ToString()const;
private:
	unsigned GetBallCount() const override;
	virtual void ReleaseBall() override;
	void SetSoldOutState() override;
	void SetNoQuarterState() override;
	void SetSoldState() override;
	void SetHasQuarterState() override;
private:
	unsigned m_count = 0;
	CSoldState m_soldState;
	CSoldOutState m_soldOutState;
	CNoQuarterState m_noQuarterState;
	CHasQuarterState m_hasQuarterState;
	IState * m_state;

};