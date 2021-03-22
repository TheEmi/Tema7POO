#include <iostream>
#include <string.h>
class Node
{
private:
    int value;
    Node* next;
    Node* prev;
public:
    Node(int Value, Node* Next, Node* Prev) : value(Value), next(Next), prev(Prev) {}
    Node(Node* node){}
    void setValue(int v) { value = v; }
    void setNext(Node* n) { next = n; }
    void setPrev(Node* n) { prev = n; }

    int getValue() { return value; }
    Node* getNext() { return next; }
    Node* getPrev() { return prev; }

    ~Node()
    {
      std::cout << std::endl << "Deleted node: " << value << std::endl;
    }
};
class List
{
private:
    Node* first;
    Node* last;
    bool init=false;
public:
    List(){
    }
    List(List* lista){
        first = lista->first;
        last = lista->last;
        init = lista->init;
    }
    void Add(int position, int value) {
        Node* newNode = new Node(value, nullptr, nullptr);
        if (position == 1) {
            if(!init){
                init=true;
                first = newNode;
                last = newNode;
            }else{
                newNode->setNext(first);
                first->setPrev(newNode);
                first = newNode;
            }
        }else if(position == -1){
            if(!init){
                init=true;
                first = newNode;
                last = newNode;
            }else{
                newNode->setPrev(last);
                last->setNext(newNode);
                last = newNode;}
        }
        else{
            Node* temp = first;
            if(!init){
                init=true;
                first = newNode;
                last = newNode;
            }else{
                while (temp->getNext() != nullptr && position != 1) {
                    temp->setNext(temp->getNext());
                    position--;
                }
                if (position == 1) {
                    if(!init){
                        init=true;
                        first = newNode;
                        last = newNode;
                    }else if(temp->getNext() != nullptr){
                        temp->getNext()->setPrev(newNode);
                        newNode->setNext(temp->getNext());
                        newNode->setPrev(temp);
                        temp->setNext(newNode);
                    }else{
                        newNode->setPrev(last);
                        last->setNext(newNode);
                        last = newNode;
                    }
                }
                else{
                    if(!init){
                        init=true;
                        first = newNode;
                        last = newNode;
                    }else{
                        newNode->setPrev(last);
                        last->setNext(newNode);
                        last = newNode;
                    }
                }
            }
        }
    }
    void Delete(int position) {
        Node* temp = first;
        if(last==first){
            init=false;
            temp->setValue(0);
        }else if(position==1){
            first = first->getNext();
            first->setPrev(nullptr);
            delete temp;
        }else{
            while (temp->getNext() != nullptr && position != 1 && init)
            {
                temp = temp->getNext();
                position--;
            }

            Node* toDelete = temp;
            if(position==1){
                    if(temp->getNext()!=nullptr){
                        temp->getPrev()->setNext(temp->getNext());
                        temp->getNext()->setPrev(temp->getPrev());
                    }else{
                        last= last->getPrev();
                        last->setNext(nullptr);
                    }
            }else{
                last= last->getPrev();
                last->setNext(nullptr);
            }
            delete toDelete;
        }
    }
    List& operator>>(int value){
        Add(-1,value);
        return *this;
    }
    List& operator+(List& l){
        List* lista = new List;
        Node* temp = first;
        while (temp != nullptr)
        {
            lista->Add(-1,temp->getValue());
            temp = temp->getNext();
        }
        temp = l.first;

        while (temp != nullptr)
        {
            lista->Add(-1,temp->getValue());
            temp = temp->getNext();
        }
        return *lista;
    }
    friend std::ostream& operator<<(std::ostream& output,List& l);
};
std::ostream& operator<<(std::ostream& output,List& l) {
        if(l.init==true){
        Node* temp = l.first;
        output << std::endl;
        while (temp != nullptr)
        {
            output << temp->getValue() << ' ';
            temp = temp->getNext();
        }
         output << std::endl;
        temp = l.last;
        while (temp != nullptr)
        {
             output << temp->getValue() << ' ';
            temp = temp->getPrev();
        }
         output << std::endl;}
         return output;
}

int main()
{
    std::string in;
    int nr1,nr2;
    List x;
    std:: cout << "Possible commands:\nADD\nDEL\nPRINT\nSTOP\n";
    std::cin >> in;
    while(in!="STOP"){
        if(in=="ADD"){
          std:: cout << "Value to be added:";
          std::cin>> nr2;
          std:: cout << "Position to be added to:";
          std::cin>> nr1;
          x.Add(nr1,nr2);
        }else if(in == "DEL"){
            std:: cout << "Position to be deleted:";
            std::cin>> nr2;
            x.Delete(nr2);

        }else if(in=="PRINT"){
            std::cout << "Lista de la cap la coada si de la coada la cap este:\n";
            std::cout << x;
        }else{
            std::cout << "COMMAND NOT FOUND! TRY AGAIN!";
        }
        std:: cout << "\nPossible commands:\nADD\nDEL\nPRINT\nSTOP\n";
        std::cin >> in;
    }
    /*
        Possible commands:
        x.Add(position,value);
        x.Delete(position);
        x >> int; - adds to the end of the list
        cout << x; prints the list both ways
        z = x + y; concatenates 2 lists.
    */
   return 0;
}
