#include <iostream>
#include <string>

using namespace std;

class IReport
{
public:
    virtual string getJsonData(string data) = 0;
    virtual ~IReport() = default;
};

class XmlDataProvider
{
public:
    string getXmlData(string data)
    {
        return "<user>" + data + "</user>";
    }
};

class XmlDataProviderAdapter : public IReport
{
    XmlDataProvider *xmlProvider;

public:
    XmlDataProviderAdapter(XmlDataProvider *xml)
    {
        this->xmlProvider = xml;
    }
    string getJsonData(string data)
    {
       string res =  xmlProvider->getXmlData(data);
        return "{ data :" + data + res + " }";
    }
};

class Client
{
public:
    void getReport(IReport *report, string data)
    {
        cout << "Processed JSON :" << report->getJsonData(data) << endl;
    }
};

int main(){

    XmlDataProvider * xmlProv = new XmlDataProvider();

    IReport* adapter = new XmlDataProviderAdapter(xmlProv);

    Client * client = new Client();

    client->getReport(adapter,"demoData:123");

    delete xmlProv;
    delete adapter;
    delete client;
}