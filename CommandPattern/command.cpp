#include <iostream>
#include <vector>
#include <string>

using namespace std;

class ICommand
{

public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~ICommand() = default;
};

class Light
{
public:
    void on()
    {
        cout << "Light on..." << endl;
    }
    void off()
    {
        cout << "Light off..." << endl;
    }
};
class Fan
{
public:
    void on()
    {
        cout << "fan on..." << endl;
    }
    void off()
    {
        cout << "fan off..." << endl;
    }
};

class LightCommand : public ICommand
{
    Light *light;

public:
    LightCommand(Light *f)
    {
        this->light = f;
    }
    void execute() override
    {
        light->on();
    }
    void undo() override
    {
        light->off();
    }
};
class FanCommand : public ICommand
{
    Fan *fan;

public:
    FanCommand(Fan *f)
    {
        this->fan = f;
    }
    void execute() override
    {
        fan->on();
    }
    void undo() override
    {
        fan->off();
    }
};

class RemoteControl
{
    static const int numButtons = 4;
    ICommand *commands[numButtons];
    bool commandState[numButtons];

public:
    RemoteControl()
    {
        for (int i = 0; i < numButtons; i++)
        {
            commands[i] = nullptr;
            commandState[i] = false;
        }
    }
    void setCommand(int idx, ICommand *cmd)
    {
        if (commands[idx] != nullptr)
        {
            delete commands[idx];
        }
        commands[idx] = cmd;
        commandState[idx] = false;
    }
    void pressButton(int idx)
    {
        if (idx >= 0 && idx < numButtons && commands[idx] != nullptr)
        {
            if (commandState[idx] == false)
            {
                commands[idx]->execute();
            }
            else
            {
                commands[idx]->undo();
            }
            commandState[idx] = !commandState[idx];
        }
        else
        {
            cout << "No command Assigned at this button: " << idx << endl;
        }
    }
    ~RemoteControl()
    {
        for (int i = 0; i < numButtons; i++)
        {
            if (commands[i] != nullptr)
            {
                delete commands[i];
                commandState[i] = false;
            }
        }
    }
};

int main()
{

    Light *light = new Light();
    Fan *fan = new Fan();

    RemoteControl *room = new RemoteControl();

    room->setCommand(0, new LightCommand(light));
    room->setCommand(1, new FanCommand(fan));

    room->pressButton(0);
    room->pressButton(0);

    room->pressButton(1);
    room->pressButton(1);

    delete room;
    delete fan;
    delete light;

    return 0;
}