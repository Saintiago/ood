#include "stdafx.h"
#include "NaiveFiveGumballsMachine.h"


CNaiveFiveGumballsMachine::CNaiveFiveGumballsMachine(unsigned count)
	: m_count(count)
	, m_state(count > 0 ? State::NoQuarter : State::SoldOut)
{
}

void CNaiveFiveGumballsMachine::InsertQuarter()
{
	using namespace std;
	switch (m_state)
	{
	case State::SoldOut:
		cout << "You can't insert a quarter, the machine is sold out\n";
		break;
	case State::NoQuarter:
	case State::HasQuarter:
		m_state = State::HasQuarter;
		if (m_coinsCount < 5)
		{
			cout << "You inserted a quarter\n";
			++m_coinsCount;
		}
		else
		{
			cout << "You can't insert another quarter\n";
		}
		break;
	case State::Sold:
		cout << "Please wait, we're already giving you a gumball\n";
		break;
	}
}

void CNaiveFiveGumballsMachine::EjectQuarter()
{
	using namespace std;
	switch (m_state)
	{
	case State::HasQuarter:
		cout << "Quarters returned\n";
		m_state = State::NoQuarter;
		m_coinsCount = 0;
		break;
	case State::NoQuarter:
		cout << "You haven't inserted a quarter\n";
		break;
	case State::Sold:
		cout << "Sorry you already turned the crank\n";
		break;
	case State::SoldOut:
		if (m_coinsCount > 0)
		{
			cout << "Quarters returned\n";
			m_coinsCount = 0;
		}
		cout << "You can't eject, you haven't inserted a quarter yet\n";
		break;
	}
}

void CNaiveFiveGumballsMachine::TurnCrank()
{
	using namespace std;
	switch (m_state)
	{
	case State::SoldOut:
		cout << "You turned but there's no gumballs\n";
		break;
	case State::NoQuarter:
		cout << "You turned but there's no quarter\n";
		break;
	case State::HasQuarter:
		cout << "You turned...\n";
		--m_coinsCount;
		m_state = State::Sold;
		Dispense();
		break;
	case State::Sold:
		cout << "Turning twice doesn't get you another gumball\n";
		break;
	}
}

void CNaiveFiveGumballsMachine::Refill(unsigned numBalls)
{
	m_count = numBalls;
	m_state = numBalls > 0 ? State::NoQuarter : State::SoldOut;
}

std::string CNaiveFiveGumballsMachine::ToString()const
{
	std::string state =
		(m_state == State::SoldOut) ? "sold out" :
		(m_state == State::NoQuarter) ? "waiting for quarter" :
		(m_state == State::HasQuarter) ? "waiting for turn of crank"
		: "delivering a gumball";
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: %1% gumball%2%, %3% coin%4%
Machine is %5%
)");
	return (fmt % m_count % (m_count != 1 ? "s" : "") % m_coinsCount % (m_coinsCount != 1 ? "s" : "") % state).str();
}

void CNaiveFiveGumballsMachine::Dispense()
{
	using namespace std;
	switch (m_state)
	{
	case State::Sold:
		cout << "A gumball comes rolling out the slot\n";
		--m_count;
		if (m_count == 0)
		{
			cout << "Oops, out of gumballs\n";
			m_state = State::SoldOut;
		}
		else if (m_coinsCount == 0)
		{
			m_state = State::NoQuarter;
		}
		else
		{
			m_state = State::HasQuarter;
		}
		break;
	case State::NoQuarter:
		cout << "You need to pay first\n";
		break;
	case State::SoldOut:
	case State::HasQuarter:
		cout << "No gumball dispensed\n";
		break;
	}
}