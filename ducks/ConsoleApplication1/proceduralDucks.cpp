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

fFly Fly = []()
{
	cout << "Swoosh!" << endl;
};

fFly NoFly = []() {};

fDance DanceWaltz = []()
{
	cout << "Dance Waltz!" << endl;
};

fDance DanceMinuet = []()
{
	cout << "Dance Minuet!" << endl;
};

fQuack Quack = []()
{
	cout << "Quack!" << endl;
};

fQuack NoQuack = []() {};

fFly GetFlyAndCount()
{
	int counter = 0;
	return [counter]() mutable {
		cout << "Swoosh: " << counter++ << endl;
	};
}

void DrawDuck(LambdaDuck const& duck)
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
}

void main()
{
	LambdaDuck MallardDuck(GetFlyAndCount(), Quack, DanceWaltz);
	LambdaDuck ModelDuck(NoFly, NoQuack, DanceMinuet);

	PlayWithDuck(MallardDuck);
	PlayWithDuck(ModelDuck);
}