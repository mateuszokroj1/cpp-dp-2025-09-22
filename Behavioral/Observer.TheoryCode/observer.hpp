#ifndef OBSERVER_HPP_
#define OBSERVER_HPP_

#include <iostream>
#include <set>
#include <string>

//////////////////////////////////////////////////////////////////////////////////////
template <typename TSource, typename... TEventArgs>
class Observer
{
public:
    virtual void update(TSource&, TEventArgs... args) = 0;
    virtual ~Observer() = default;
};

//////////////////////////////////////////////////////////////////////////////////////
template <typename TSource, typename... TEventArgs>
struct Observable
{
    using ObserverType = Observer<TSource, TEventArgs...>;
    using ObserverWeakPtr = std::weak_ptr<ObserverType>;
    using ObserverSharedPtr = std::shared_ptr<ObserverType>;

    void subscribe(ObserverSharedPtr observer)
    {
        observers_.insert(observer);
    }

    void unsubscribe(ObserverSharedPtr observer)
    {
        observers_.erase(observer);
    }

protected:
    void notify(TSource& source, TEventArgs... args)
    {
        for (auto&& weak_observer : observers_)
        {
            std::shared_ptr<ObserverType> observer = weak_observer.lock();
            if (observer)
            {
                observer->update(static_cast<TSource&>(*this), std::move(args...));
            }
        }
    }

private:
    using ObserverType = Observer<TSource, TEventArgs...>;
    using ObserverPtr = std::weak_ptr<ObserverType>;
    std::set<ObserverPtr, std::owner_less<ObserverPtr>> observers_;
};

#endif /*OBSERVER_HPP_*/
