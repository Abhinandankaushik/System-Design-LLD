#include <iostream>
#include <string>

using namespace std;

class ICharacter
{
public:
    virtual string getAbilities() = 0;
    virtual ~ICharacter() = default;
};

class Mario : public ICharacter
{
public:
    string getAbilities() override
    {
        return "Mario";
    }
};

class DecoratorCharacter : public ICharacter
{
protected:
    ICharacter *character;

public:
    DecoratorCharacter(ICharacter *character)
    {
        this->character = character;
    }
    string getAbilities() = 0;

    virtual ~DecoratorCharacter() = default;
};

class CharacterWithGunPower : public DecoratorCharacter
{
public:
    CharacterWithGunPower(ICharacter *c) : DecoratorCharacter(c) {}
    string getAbilities() override
    {

        return this->character->getAbilities() + " With Gun Power";
    }
    virtual ~CharacterWithGunPower() = default;
};

class CharacterWithHieghtPower : public DecoratorCharacter
{
public:
    CharacterWithHieghtPower(ICharacter *c) : DecoratorCharacter(c) {}
    string getAbilities() override
    {

        return this->character->getAbilities() + " With Hight Power";
    }
    virtual ~CharacterWithHieghtPower() = default;
};

int main()
{

    // Simple Mario character
    ICharacter *mario = new Mario();

    cout << mario->getAbilities() << endl;

    // Mario with Gun power
    ICharacter *gunMario = new CharacterWithGunPower(mario);

    cout << gunMario->getAbilities() << endl;

    // Mario with Hieght power
    ICharacter *hgunMario = new CharacterWithHieghtPower(gunMario);

    cout << hgunMario->getAbilities() << endl;

    return 0;
}