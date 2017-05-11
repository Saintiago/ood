#pragma once
#include <iostream>
#include <boost/format.hpp>

class CNaiveFiveGumballsMachine
{
public:
	enum class State
	{
		SoldOut,		// Жвачка закончилась
		NoQuarter,		// Нет монетки
		HasQuarter,		// Есть монетка
		Sold,			// Монетка выдана
	};

	CNaiveFiveGumballsMachine(unsigned count);
	~CNaiveFiveGumballsMachine() = default;

	void InsertQuarter();
	void EjectQuarter();
	void TurnCrank();
	void Refill(unsigned numBalls);
	std::string ToString()const;

private:
	void Dispense();

	unsigned m_count;	// Количество шариков
	unsigned m_coinsCount = 0; // Количество монет
	State m_state = State::SoldOut;
};

