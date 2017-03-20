#pragma once

#include <set>
#include <map>
#include <functional>
#include <boost/range/adaptor/reversed.hpp>

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

template <class T>
struct COrderedObserver : public IObserver<T>
{
	COrderedObserver(unsigned priorityParam = 0)
		: priority(priorityParam)
	{}

	unsigned priority;
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
	virtual void RegisterObserver(COrderedObserver<T> & observer) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(COrderedObserver<T> & observer) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef COrderedObserver<T> ObserverType;

	void RegisterObserver(ObserverType & observer) override
	{
		std::map<unsigned, std::set<ObserverType *>>::iterator it = m_observers.find(observer.priority);
		if (it == m_observers.end())
		{
			m_observers.insert(pair<unsigned, std::set<ObserverType *>>(observer.priority, std::set<ObserverType *>()));
		}
		m_observers.at(observer.priority).insert(&observer);
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();

		for (auto & observerSetPair : boost::adaptors::reverse(m_observers))
		{
			for (auto & observer : observerSetPair.second)
			{
				observer->Update(data);
			}
		}
	}

	void RemoveObserver(ObserverType & observer) override
	{
		m_observers.at(observer.priority).erase(&observer);
		if (m_observers.at(observer.priority).empty())
		{
			m_observers.erase(observer.priority);
		}
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:
	std::map<unsigned, std::set<ObserverType *>> m_observers;
};
