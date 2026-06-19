#include <iostream>
#include <mutex>

using namespace std;

class Singleton
{
private:
    static Singleton *instance;
    static mutex mtx;
    Singleton()
    {
        cout << "Singleton Constructor, New Object created" << endl;
    }

public:
    static Singleton *getInstance()
    {

        if (instance == nullptr)
        {
            lock_guard<mutex> lock(mtx); // lock for thread safety
            if (instance == nullptr) {
                return instance;
            }
            instance = new Singleton();
        }
        return instance;
    }
};
Singleton *Singleton::instance = nullptr;

int main()
{

    Singleton *s1 = Singleton::getInstance();
    Singleton *s2 = Singleton::getInstance();

    cout << (s1 == s2) << endl;
    return 0;
}