#include <iostream>
#include <vector>
#include <string>

using namespace std;

class FileSystemItem
{
public:
    virtual ~FileSystemItem() = default;
    virtual void ls(int indent = 0) = 0;
    virtual void openAll(int indent = 0) = 0;
    virtual int getSize() = 0;
    virtual FileSystemItem *cd(const string &name) = 0;
    virtual string getName() = 0;
    virtual bool isFolder() = 0;
};

class File : public FileSystemItem
{
    string name;
    int size;

public:
    File(const string &n, int size)
    {
        this->name = n;
        this->size = size;
    }

    int getSize() override
    {
        return this->size;
    }
    string getName() override
    {
        return this->name;
    }
    FileSystemItem *cd(const string &name) override
    {
        return nullptr;
    }

    void ls(int indent = 0) override
    {
        cout << string(indent, ' ') << this->getName() << endl;
    }
    bool isFolder() override
    {
        return false;
    }
    void openAll(int indent = 0)
    {
        cout << string(indent, ' ') << name << endl;
    }
};

class Folder : public FileSystemItem
{
    string name;
    vector<FileSystemItem *> items;

public:
    Folder(const string &n)
    {
        this->name = n;
    }
    void add(FileSystemItem *item)
    {
        this->items.push_back(item);
    }
    int getSize() override
    {
        int totalsize = 0;
        for (auto it : items)
        {
            totalsize += it->getSize();
        }
        return totalsize;
    }
    string getName() override
    {
        return name;
    }
    bool isFolder() override
    {
        return true;
    }
    void ls(int indent = 0) override
    {
        for (auto it : items)
        {
            if (it->isFolder())
            {
                cout << string(indent, ' ') << "[+]" << it->getName() << endl;
            }
            else
            {
                cout << string(indent, ' ') << it->getName() << endl;
            }
        }
    }

    void openAll(int indent = 0) override
    {
        cout << string(indent, ' ') << "[+]" << name << endl;
        for (auto it : items)
        {
            it->openAll(indent + 4);
        }
    }

    FileSystemItem *cd(const string &name)
    {
        for (auto it : items)
        {
            if (it->isFolder() && it->getName() == name)
            {
                return it;
            }
        }
    }
};

int main()
{

    Folder *root = new Folder("System Design");
    root->add(new File("Strategy Pattern.cpp", 1));
    root->add(new File("Factory Pattern.cpp", 4));
    root->add(new File("Singleton Pattern.cpp", 3));

    Folder *f1 = new Folder("Class UML Diagrams");
    f1->add(new File("Singleton Pattern UML.pdf", 3));
    f1->add(new File("Command Pattern UML.pdf", 6));
    f1->add(new File("Observer Pattern UML.pdf", 5));
    f1->add(new File("Adapter Pattern UML.pdf", 6));

    root->add(f1);

    FileSystemItem *f2 = root->cd("Class UML Diagrams");

    f2->ls();

    return 0;
}