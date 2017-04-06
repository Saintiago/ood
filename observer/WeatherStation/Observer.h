#pragma once

#include <set>
#include <map>
#include <vector>
#include <functional>

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс, 
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;
	virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T> & observer, unsigned priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T> & observer) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType & observer, unsigned priority = 0) override
	{
		ClearIdleObservers();

		std::map<unsigned, std::set<ObserverType *>>::iterator it = m_observers.find(priority);
		if (it == m_observers.end())
		{
			m_observers.insert(pair<unsigned, std::set<ObserverType *>>(priority, std::set<ObserverType *>()));
		}
		m_observers.at(priority).insert(&observer);
	}

	void NotifyObservers() override
	{
		ClearIdleObservers();

		T data = GetChangedData();

		for (auto & observerSetPair : m_observers)
		{
			for (auto & observer : observerSetPair.second)
			{
				observer->Update(data);
			}
		}
	}

	void RemoveObserver(ObserverType & observer) override
	{
		m_idleObserversList.push_back(&observer);
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:
	std::map<unsigned, std::set<ObserverType *>> m_observers;
	std::vector<ObserverType *> m_idleObserversList = {};

	void ClearIdleObservers()
	{
		for (auto & observer : m_idleObserversList)
		{
			EraseObserver(*observer);
		}

		m_idleObserversList.clear();
	}

	void EraseObserver(ObserverType & observer)
	{
		for (auto & observerSetPair : m_observers)
		{
			for (auto & obs : observerSetPair.second)
			{
				if (obs == &observer)
				{
					m_observers.at(observerSetPair.first).erase(&observer);
					break;
				}
			}
		}
	}
};
