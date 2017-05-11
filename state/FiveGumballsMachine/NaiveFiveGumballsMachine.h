#pragma once
#include <iostream>
#include <boost/format.hpp>

class CNaiveFiveGumballsMachine
{
public:
	enum class State
	{
		SoldOut,		// ������ �����������
		NoQuarter,		// ��� �������
		HasQuarter,		// ���� �������
		Sold,			// ������� ������
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

	unsigned m_count;	// ���������� �������
	unsigned m_coinsCount = 0; // ���������� �����
	State m_state = State::SoldOut;
};

