#include <cassert>
#include <iostream>
#include <memory>
#include <typeinfo>

class Engine
{
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual ~Engine() = default;
};

class Diesel : public Engine
{
public:
    virtual void start() override
    {
        std::cout << "Diesel starts\n";
    }

    virtual void stop() override
    {
        std::cout << "Diesel stops\n";
    }
};

class TDI : public Diesel
{
public:
    virtual void start() override
    {
        std::cout << "TDI starts\n";
    }

    virtual void stop() override
    {
        std::cout << "TDI stops\n";
    }
};

class Hybrid : public Engine
{
public:
    virtual void start() override
    {
        std::cout << "Hybrid starts\n";
    }

    virtual void stop() override
    {
        std::cout << "Hybrid stops\n";
    }
};

class Car
{
    std::unique_ptr<Engine> engine_;

public:
    Car(std::unique_ptr<Engine> engine)
        : engine_{std::move(engine)}
    {
    }

    Car(const Car& other)
        : engine_{}
    {
        if (typeid(*other.engine_) == typeid(Diesel))
            engine_ = std::make_unique<Diesel>();
        else if (typeid(*other.engine_) == typeid(TDI))
            engine_ = std::make_unique<TDI>();
        else if (typeid(*other.engine_) == typeid(Hybrid))
            engine_ = std::make_unique<Hybrid>();
        else
            assert(false && "Unknown engine type");
    }

    void drive(int km)
    {
        engine_->start();
        std::cout << "Driving " << km << " kms\n";
        engine_->stop();
    }
};

int main()
{
    Car c1{std::make_unique<Hybrid>()};
    c1.drive(100);

    std::cout << "\n";

    Car c2 = c1;
}
