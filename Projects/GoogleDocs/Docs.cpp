#include <string>
#include <iostream>
#include <vector>
using namespace std;

class DocumentElement
{
public:
  virtual string render() = 0;
};

class TextElement : public DocumentElement
{
private:
  string text;

public:
  TextElement(string text)
  {
    this->text = text;
  }
  string render() override
  {
    return this->text;
  }
};
class ImageElement : public DocumentElement
{
private:
  string path;

public:

  ImageElement(string path){
    this->path = path;
  }
  string render() override
  {
    return "[Image:" + this->path + "]";
  }
};
class NewLineElement : public DocumentElement
{
public:
  string render() override
  {
    return "\n";
  }
};

class Persistance
{
public:
  virtual void save() = 0;
};

class FileStorage : public Persistance
{
public:
  void save() override
  {
    cout << "Saving in File..." << endl;
  }
};

class DBStorage : public Persistance
{
public:
  void save() override
  {
    cout << "Saving in Database..." << endl;
  }
};

class Document
{
private:
  vector<DocumentElement *> docElements;

public:
  void addElement(DocumentElement *el)
  {
    docElements.push_back(el);
  }
  vector<DocumentElement *> getElementList()
  {
    return this->docElements;
  }
};

class DocEditor
{
private:
  Document *document = new Document();
public:
  void addText(string text)
  {
    document->addElement(new TextElement(text));
  }

  void addImage(string path)
  {
    document->addElement(new ImageElement(path));
  }
  void addNewLine()
  {
    document->addElement(new NewLineElement());
  }

  Document* getDocument(){
    return this->document;
  }
};

class DocumentRenderer
{
public:
  string render( Document *doc)
  {
    string renderedData = "";
    for (auto it : doc->getElementList())
    {
      renderedData += it->render();
    }
    return renderedData;
  }
};

int main()
{ 
  //creating an Document
  DocEditor *editor = new DocEditor();
  editor->addText("This is Google Doc's");
  editor->addNewLine();
  editor->addText("Welcome To you document");
  editor->addNewLine();
  editor->addImage("abhi.jpg");
  editor->addNewLine();
  editor->addText("End Of Document");

  // rendering the document
  DocumentRenderer *render = new DocumentRenderer();
  string data = render->render(editor->getDocument());
  cout << data << endl;


  //storing document in db
  Persistance *storage = new DBStorage();
  storage->save();

  return 0;
}