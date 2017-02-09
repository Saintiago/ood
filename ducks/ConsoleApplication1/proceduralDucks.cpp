#include "stdafx.h"
#include <iostream>
#include <memory>
#include <cassert>
#include <vector>
#include <functional>

using namespace std;
typedef function<void()> fFly;
typedef function<void()> fQuack;
typedef function<void()> fDance;

/*void DrawDuck(LambdaDuck const& duck)
{
	duck.Display();
}

void PlayWithDuck(LambdaDuck & duck)
{
	duck.Quack();
	duck.Dance();
	duck.Fly();
	duck.Fly();
	DrawDuck(duck);
}*/

class LambdaDuck
{
public:
	LambdaDuck(
		function<void()> fly,
		function<void()> quack,
		function<void()> dance
		)
		: m_Fly(fly)
		, m_Quack(quack)
		, m_Dance(dance)
	{
	}
	void Quack() const
	{
		m_Quack();
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		m_Fly();
	}
	virtual void Dance()
	{
		m_Dance();
	}
	void Display() const
	{
		cout << "I'm procedural duck." << endl;
	}

	~LambdaDuck() {};
private:
	fFly m_Fly;
	fQuack m_Quack;
	fDance m_Dance;
};

void Fly()
{
	cout << "Swoosh!" << endl;
}

void Dance()
{
	cout << "Dance!" << endl;
}

void Quack()
{
	cout << "Quack!" << endl;
}

fFly GetFlyAndCount()
{
	int counter = 0;
	return [counter]() mutable {
		cout << "Swoosh: " << counter++ << endl;
	};
}

void main()
{
	LambdaDuck lambdaDuck(GetFlyAndCount(), Quack, Dance);
	LambdaDuck lambdaDuck2(GetFlyAndCount(), Quack, Dance);

	lambdaDuck.Quack();
	lambdaDuck.Dance();
	lambdaDuck.Fly();
	lambdaDuck.Fly();
	lambdaDuck.Fly();

	lambdaDuck.Display();

	lambdaDuck2.Fly();
	lambdaDuck2.Fly();
	lambdaDuck2.Fly();

	lambdaDuck.Fly();
}