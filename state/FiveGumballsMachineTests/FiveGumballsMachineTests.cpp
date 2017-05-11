#include "stdafx.h"
#include "../FiveGumballsMachine/NaiveFiveGumballsMachine.h"
#include "../FiveGumballsMachine/FiveGumballsMachine.h"
#include <string>

using namespace std;

/*
���������� GumballMachine, ����� ������� ��� ��������� �� ���� �������. 
������ ������� ������ ����� �������� �� ������ ������. 
��� ���� ����� �������� �������������� �������, �� ��������� ������ ���� �������. 
���� ������� ������ �������� ������� ������ ���������� ��� �������.
���� ������� ������, ��� �������, �� ����� ������ ���������� ������ ������������ 
������ ����� ����������� ������� �������.
������ ���������� ������� � ���� ����������� � ������� � ������������ ������� ����������. 
�������� �������� ����������� ���������. ������� ������.
*/

struct FiveGumballsMachine_
{
	boost::format fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: %1% gumball%2%, %3% coin%4%
Machine is %5%
)");

	//CNaiveFiveGumballsMachine machine;
	CFiveGumballsMachine machine;
	FiveGumballsMachine_()
		: machine(5)
	{}
};

// �������� ������� � ����� ���������
BOOST_FIXTURE_TEST_SUITE(FiveGumballsMachine, FiveGumballsMachine_)
	
	// � ��������� HasQuarterState
	struct in_has_quarter_state_ : FiveGumballsMachine_
	{
		in_has_quarter_state_()
			: FiveGumballsMachine_()
		{
			machine.InsertQuarter();
		}
	};

	BOOST_FIXTURE_TEST_SUITE(in_has_quarter_state, in_has_quarter_state_)

		// ����� ��������� ��������
		BOOST_AUTO_TEST_CASE(can_be_refilled)
		{
			machine.Refill(10);
			string expectedGumballMachineString = (fmt % 10 % "s" % 1 % "" % "waiting for turn of crank").str();
			BOOST_CHECK_EQUAL(machine.ToString(), expectedGumballMachineString);
		}

	BOOST_AUTO_TEST_SUITE_END()

	// � ��������� NoQuarterState
	struct in_no_quarter_state_ : FiveGumballsMachine_
	{
		in_no_quarter_state_()
			: FiveGumballsMachine_()
		{
		}
	};

	BOOST_FIXTURE_TEST_SUITE(in_no_quarter_state, in_no_quarter_state_)

		// ����� ��������� ��������
		BOOST_AUTO_TEST_CASE(can_be_refilled)
		{
			machine.Refill(10);
			string expectedGumballMachineString = (fmt % 10 % "s" % 0 % "s" % "waiting for quarter").str();
			BOOST_CHECK_EQUAL(machine.ToString(), expectedGumballMachineString);
		}

	BOOST_AUTO_TEST_SUITE_END()

	// � ��������� SoldOutState
	struct in_sold_out_state_ : FiveGumballsMachine_
	{
		CFiveGumballsMachine soldOutMachine;
		in_sold_out_state_()
			: FiveGumballsMachine_()
			, soldOutMachine(0)
		{}
	};

	BOOST_FIXTURE_TEST_SUITE(in_sold_out_state, in_sold_out_state_)

		// ����� ��������� ��������
		BOOST_AUTO_TEST_CASE(can_be_refilled)
		{
			soldOutMachine.Refill(10);
			string expectedGumballMachineString = (fmt % 10 % "s" % 0 % "s" % "waiting for quarter").str();
			BOOST_CHECK_EQUAL(soldOutMachine.ToString(), expectedGumballMachineString);
		}

	BOOST_AUTO_TEST_SUITE_END()

	// �� ��������� ��������� � ��������� �������� �������
	BOOST_AUTO_TEST_CASE(is_in_no_quarter_state)
	{
		string expectedGumballMachineString = (fmt % 5 % "s" % 0 % "s" % "waiting for quarter").str();
		BOOST_CHECK_EQUAL(machine.ToString(), expectedGumballMachineString);
	}

	struct can_accept_up_to_five_coins_ : FiveGumballsMachine_
	{
		can_accept_up_to_five_coins_()
			: FiveGumballsMachine_()
		{
			machine.InsertQuarter();
			machine.InsertQuarter();
			machine.InsertQuarter();
			machine.InsertQuarter();
			machine.InsertQuarter();
		}
	};

	// ����� ������� �� 5 �������
	BOOST_FIXTURE_TEST_SUITE(can_accept_up_to_five_coins, can_accept_up_to_five_coins_)

		// ����� ������� ���� �������
		BOOST_AUTO_TEST_CASE(can_accept_five_coins)
		{
			string expectedGumballMachineString = (fmt % 5 % "s" % 5 % "s" % "waiting for turn of crank").str();
			BOOST_CHECK_EQUAL(machine.ToString(), expectedGumballMachineString);
		}

		// �� ����� ������� ������ �������
		BOOST_AUTO_TEST_CASE(cant_accept_six_coins)
		{
			machine.InsertQuarter();
			string expectedGumballMachineString = (fmt % 5 % "s" % 5 % "s" % "waiting for turn of crank").str();
			BOOST_CHECK_EQUAL(machine.ToString(), expectedGumballMachineString);
		}

		// ������ ������� ������ ����� �������� �� ������ ������
		BOOST_AUTO_TEST_CASE(each_crank_turn_gives_a_gumball)
		{
			for (int i = 4; i > 0; --i)
			{
				machine.TurnCrank();
				string wordEnding = (i != 1 ? "s" : "");
				string expectedGumballMachineString = (fmt % i % wordEnding % i % wordEnding % "waiting for turn of crank").str();
				BOOST_CHECK_EQUAL(machine.ToString(), expectedGumballMachineString);
			}

			machine.TurnCrank();
			string expectedGumballMachineString = (fmt % 0 % "s" % 0 % "s" % "sold out").str();
			BOOST_CHECK_EQUAL(machine.ToString(), expectedGumballMachineString);
		}

		// ����� �������� �������������� �������, �� ��������� ������ ���� �������
		BOOST_AUTO_TEST_CASE(can_accept_coins_when_not_sold_out)
		{
			machine.TurnCrank();
			string expectedGumballMachineString = (fmt % 4 % "s" % 4 % "s" % "waiting for turn of crank").str();
			BOOST_CHECK_EQUAL(machine.ToString(), expectedGumballMachineString);

			machine.InsertQuarter();
			expectedGumballMachineString = (fmt % 4 % "s" % 5 % "s" % "waiting for turn of crank").str();
			BOOST_CHECK_EQUAL(machine.ToString(), expectedGumballMachineString);
		}

		// o��� ������� ������ �������� ������� ������ ���������� ��� �������
		BOOST_AUTO_TEST_CASE(ejects_all_coins_at_once)
		{
			machine.EjectQuarter();
			string expectedGumballMachineString = (fmt % 5 % "s" % 0 % "s" % "waiting for quarter").str();
			BOOST_CHECK_EQUAL(machine.ToString(), expectedGumballMachineString);
		}

		
		struct more_coins_than_gumballs_ : can_accept_up_to_five_coins_
		{
			more_coins_than_gumballs_()
				: can_accept_up_to_five_coins_()
			{
				machine.TurnCrank();
				machine.InsertQuarter();
				machine.TurnCrank();
				machine.TurnCrank();
				machine.TurnCrank();
				machine.TurnCrank();
			}
		};

		// ���� ������� ������, ��� �������, �� ����� ������ ���������� ������
		BOOST_FIXTURE_TEST_SUITE(more_coins_than_gumballs, more_coins_than_gumballs_)

			// ������������ ������ ����� ����������� ������� �������
			BOOST_AUTO_TEST_CASE(can_eject_coins)
			{
				string expectedGumballMachineString = (fmt % 0 % "s" % 1 % "" % "sold out").str();
				BOOST_CHECK_EQUAL(machine.ToString(), expectedGumballMachineString);
				machine.EjectQuarter();
				expectedGumballMachineString = (fmt % 0 % "s" % 0 % "s" % "sold out").str();
				BOOST_CHECK_EQUAL(machine.ToString(), expectedGumballMachineString);
			}

		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()