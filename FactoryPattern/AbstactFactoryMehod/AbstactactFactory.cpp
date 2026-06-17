#include <iostream>
using namespace std;

class Burger
{
public:
    virtual void prepare() = 0;
    virtual ~Burger() = default;
};

class Bread
{
public:
    virtual void prepare() = 0;
    virtual ~Bread() = default;
};

class BasicBurger : public Burger
{
public:
    void prepare() override
    {
        cout << "Preparing Basic Burger..." << endl;
    }
};

class PremiumBurger : public Burger
{
public:
    void prepare() override
    {
        cout << "Preparing Premium Burger..." << endl;
    }
};

class BasicBread : public Bread
{
public:
    void prepare() override
    {
        cout << "Preparing Basic Bread..." << endl;
    }
};

class PremiumBread : public Bread
{
public:
    void prepare() override
    {
        cout << "Preparing Premium Bread..." << endl;
    }
};

enum class Type
{
    Basic,
    Premium
};

class MealFactory
{
public:
    virtual Burger *createBurger(Type) = 0;
    virtual Bread *createBread(Type) = 0;
};

class ZomatoMealFactory : public MealFactory
{
public:
    Burger *createBurger(Type type) override
    {

        switch (type)
        {
        case Type::Basic:
            return new BasicBurger();
        default:
            cout << "Invalid Input" << endl;
            return nullptr;
        }
    }

    Bread *createBread(Type type) override
    {
        switch (type)
        {
        case Type::Basic:
            return new BasicBread();
        default:
            cout << "Invalid Input" << endl;
            return nullptr;
        }
    }
};

class SwiggyMealFactory : public MealFactory
{
public:
    Burger *createBurger(Type type) override
    {

        switch (type)
        {
        case Type::Premium:
            return new PremiumBurger();
        default:
            cout << "Invalid Input" << endl;
            return nullptr;
        }
    }

    Bread *createBread(Type type) override
    {
        switch (type)
        {
        case Type::Premium:
            return new PremiumBread();
        default:
            cout << "Invalid Input" << endl;
            return nullptr;
        }
    }
};

int main()
{

    MealFactory *mealfact = new ZomatoMealFactory();
    Burger *zomatoBurger = mealfact->createBurger(Type::Basic);
    Bread *zomatoBread = mealfact->createBread(Type::Basic);
    zomatoBurger->prepare();
    zomatoBread->prepare();
}