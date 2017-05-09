#include "stdafx.h"
#include "../gumball_machine/GumballMachineWithState.h"
#include <string>
#include <boost/format.hpp>

using namespace std;

struct GumballMachine_
{
	boost::format fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Machine is %3%
)");
};

// ������� � �������
BOOST_FIXTURE_TEST_SUITE(GumballMachine, GumballMachine_)

	struct when_created_with_no_gumballs_ : GumballMachine_
	{
		with_state::CGumballMachine machine;
		when_created_with_no_gumballs_()
			: machine(0)
		{}
	};

	// ����� ������ ������
	BOOST_FIXTURE_TEST_SUITE(when_created_with_no_gumballs, when_created_with_no_gumballs_)

		// ��������� � ��������� "��� ������"
		BOOST_AUTO_TEST_CASE(is_in_sold_out_state)
		{
			string expectedGumballMachineString = (fmt % 0 % "s" % "sold out").str();
			BOOST_CHECK_EQUAL(machine.ToString(), expectedGumballMachineString);
		}

		// �� ����� ������� ������
		BOOST_AUTO_TEST_CASE(cannot_accept_a_coin)
		{
			machine.InsertQuarter();
			string expectedGumballMachineString = (fmt % 0 % "s" % "sold out").str();
			BOOST_CHECK_EQUAL(machine.ToString(), expectedGumballMachineString);
		}

		// �� ����� ������� ������
		BOOST_AUTO_TEST_CASE(cannot_eject_a_coin)
		{
			machine.EjectQuarter();
			string expectedGumballMachineString = (fmt % 0 % "s" % "sold out").str();
			BOOST_CHECK_EQUAL(machine.ToString(), expectedGumballMachineString);
		}

		// �� ��������� �� ������� ������
		BOOST_AUTO_TEST_CASE(does_nothing_when_crank_turned)
		{
			machine.TurnCrank();
			string expectedGumballMachineString = (fmt % 0 % "s" % "sold out").str();
			BOOST_CHECK_EQUAL(machine.ToString(), expectedGumballMachineString);
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct when_creating_machine_with_two_gumballs_ : GumballMachine_
	{
		with_state::CGumballMachine machine;
		when_creating_machine_with_two_gumballs_()
			: machine(2)
		{
		}
	};

	// ����� ������ ��������
	BOOST_FIXTURE_TEST_SUITE(when_creating_machine_with_two_gumballs, when_creating_machine_with_two_gumballs_)

		// ���������� � ��������� �������� �������
		BOOST_AUTO_TEST_CASE(is_in_no_quarter_state)
		{
			string expectedGumballMachineString = (fmt % 2 % "s" % "waiting for quarter").str();
			BOOST_CHECK_EQUAL(machine.ToString(), expectedGumballMachineString);
		}

		struct when_coin_inserted_ : when_creating_machine_with_two_gumballs_
		{
			when_coin_inserted_()
				: when_creating_machine_with_two_gumballs_()
			{
				machine.InsertQuarter();
			}
		};

		// ����� ��������� �������
		BOOST_FIXTURE_TEST_SUITE(when_coin_inserted, when_coin_inserted_)

			// ��������� � ��������� "�������� �������� ������"
			BOOST_AUTO_TEST_CASE(is_in_waiting_for_turn_of_crank_state)
			{
				string expectedGumballMachineString = (fmt % 2 % "s" % "waiting for turn of crank").str();
				BOOST_CHECK_EQUAL(machine.ToString(), expectedGumballMachineString);
			}

			// �� ����� ������� ������
			BOOST_AUTO_TEST_CASE(cannot_accept_another_coin)
			{
				machine.InsertQuarter();
				string expectedGumballMachineString = (fmt % 2 % "s" % "waiting for turn of crank").str();
				BOOST_CHECK_EQUAL(machine.ToString(), expectedGumballMachineString);
			}

			// ����� ������� ������
			BOOST_AUTO_TEST_CASE(ejects_a_coin)
			{
				machine.EjectQuarter();
				string expectedGumballMachineString = (fmt % 2 % "s" % "waiting for quarter").str();
				BOOST_CHECK_EQUAL(machine.ToString(), expectedGumballMachineString);
			}

			struct when_crank_turned_ : when_coin_inserted_
			{
				when_crank_turned_()
					: when_coin_inserted_()
				{
					machine.TurnCrank();
				}
			};

			// ����� ����� ��������
			BOOST_FIXTURE_TEST_SUITE(when_crank_turned, when_crank_turned_)

				// ������ ������ � ��������� � ��������� �������� �������
				BOOST_AUTO_TEST_CASE(gives_gumball_and_waiting_for_quarter)
				{
					string expectedGumballMachineString = (fmt % 1 % "" % "waiting for quarter").str();
					BOOST_CHECK_EQUAL(machine.ToString(), expectedGumballMachineString);
				}

			BOOST_AUTO_TEST_SUITE_END()

			// ����� ������ ����������� ��������� � ��������� "��� �������"
			BOOST_AUTO_TEST_CASE(becomes_sold_out_when_out_of_gumballs)
			{
				machine.TurnCrank();
				machine.InsertQuarter();
				machine.TurnCrank();
				string expectedGumballMachineString = (fmt % 0 % "s" % "sold out").str();
				BOOST_CHECK_EQUAL(machine.ToString(), expectedGumballMachineString);
			}

		BOOST_AUTO_TEST_SUITE_END()

		// �� ����� ������� ������
		BOOST_AUTO_TEST_CASE(cannot_eject_a_coin)
		{
			machine.EjectQuarter();
			string expectedGumballMachineString = (fmt % 2 % "s" % "waiting for quarter").str();
			BOOST_CHECK_EQUAL(machine.ToString(), expectedGumballMachineString);
		}

		// �� ��������� �� ������� ������
		BOOST_AUTO_TEST_CASE(does_nothing_when_crank_turned)
		{
			machine.TurnCrank();
			string expectedGumballMachineString = (fmt % 2 % "s" % "waiting for quarter").str();
			BOOST_CHECK_EQUAL(machine.ToString(), expectedGumballMachineString);
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()