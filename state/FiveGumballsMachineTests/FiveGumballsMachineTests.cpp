#include "stdafx.h"
#include "../FiveGumballsMachine/NaiveFiveGumballsMachine.h"
#include <string>

using namespace std;

/*
ƒоработать GumballMachine, чтобы автомат мог принимать до п€ти монеток. 
 аждый поворот рычага может выдавать по одному шарику. 
ѕри этом можно опускать дополнительные монетки, не дожида€сь выдачи всех шариков. 
ќдно нажатие кнопки возврата монетки должно возвращать все монетки.
≈сли монеток больше, чем шариков, то после выдачи последнего шарика пользователь 
должен иметь возможность монетки вернуть.
ƒанный функционал сделать в двух реализаци€х Ц наивной и использующей паттерн Ђ—осто€ниеї. 
—равнить характер проделанных изменений. —делать выводы.
*/

struct FiveGumballsMachine_
{
	boost::format fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: %1% gumball%2%, %3% coin%4%
Machine is %5%
)");

	CNaiveFiveGumballsMachine machine;
	FiveGumballsMachine_()
		: machine(5)
	{}
};

// Ќепустой автомат с п€тью монетками
BOOST_FIXTURE_TEST_SUITE(FiveGumballsMachine, FiveGumballsMachine_)

	// по умолчанию находитс€ в состо€нии ожидани€ монетки
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

	// может прин€ть до 5 монеток
	BOOST_FIXTURE_TEST_SUITE(can_accept_up_to_five_coins, can_accept_up_to_five_coins_)

		// может прин€ть п€ть монеток
		BOOST_AUTO_TEST_CASE(can_accept_five_coins)
		{
			string expectedGumballMachineString = (fmt % 5 % "s" % 5 % "s" % "waiting for turn of crank").str();
			BOOST_CHECK_EQUAL(machine.ToString(), expectedGumballMachineString);
		}

		// не может прин€ть шестую монетку
		BOOST_AUTO_TEST_CASE(cant_accept_six_coins)
		{
			machine.InsertQuarter();
			string expectedGumballMachineString = (fmt % 5 % "s" % 5 % "s" % "waiting for turn of crank").str();
			BOOST_CHECK_EQUAL(machine.ToString(), expectedGumballMachineString);
		}

		// каждый поворот рычага может выдавать по одному шарику
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

		// можно опускать дополнительные монетки, не дожида€сь выдачи всех шариков
		BOOST_AUTO_TEST_CASE(can_accept_coins_when_not_sold_out)
		{
			machine.TurnCrank();
			string expectedGumballMachineString = (fmt % 4 % "s" % 4 % "s" % "waiting for turn of crank").str();
			BOOST_CHECK_EQUAL(machine.ToString(), expectedGumballMachineString);

			machine.InsertQuarter();
			expectedGumballMachineString = (fmt % 4 % "s" % 5 % "s" % "waiting for turn of crank").str();
			BOOST_CHECK_EQUAL(machine.ToString(), expectedGumballMachineString);
		}

		// oдно нажатие кнопки возврата монетки должно возвращать все монетки
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

		// ≈сли монеток больше, чем шариков, то после выдачи последнего шарика
		BOOST_FIXTURE_TEST_SUITE(more_coins_than_gumballs, more_coins_than_gumballs_)

			// пользователь должен иметь возможность монетки вернуть
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