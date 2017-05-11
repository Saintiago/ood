#include "stdafx.h"
#include "FiveGumballsMachine.h"


CFiveGumballsMachine::CFiveGumballsMachine(unsigned numBalls)
	: m_soldState(*this)
	, m_soldOutState(*this)
	, m_noQuarterState(*this)
	, m_hasQuarterState(*this)
	, m_state(&m_soldOutState)
	, m_count(numBalls)
{
	if (m_count > 0)
	{
		m_state = &m_noQuarterState;
	}
}
void CFiveGumballsMachine::EjectQuarter()
{
	m_state->EjectQuarter();
}
void CFiveGumballsMachine::InsertQuarter()
{
	m_state->InsertQuarter();
}
void CFiveGumballsMachine::TurnCrank()
{
	m_state->TurnCrank();
	m_state->Dispense();
}
std::string CFiveGumballsMachine::ToString()const
{
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Machine is %3%
)");
	return (fmt % m_count % (m_count != 1 ? "s" : "") % m_state->ToString()).str();
}

unsigned CFiveGumballsMachine::GetBallCount() const
{
	return m_count;
}
void CFiveGumballsMachine::ReleaseBall()
{
	if (m_count != 0)
	{
		std::cout << "A gumball comes rolling out the slot...\n";
		--m_count;
	}
}
void CFiveGumballsMachine::SetSoldOutState()
{
	m_state = &m_soldOutState;
}
void CFiveGumballsMachine::SetNoQuarterState()
{
	m_state = &m_noQuarterState;
}
void CFiveGumballsMachine::SetSoldState()
{
	m_state = &m_soldState;
}
void CFiveGumballsMachine::SetHasQuarterState()
{
	m_state = &m_hasQuarterState;
}