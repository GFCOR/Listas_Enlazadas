#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>

// Clase base abstracta List (list.h)
template <typename T>
class List {
public:
    virtual ~List(){};
    // Contrato
    virtual T front() = 0;
    virtual T back() = 0;
    virtual void push_front(T) = 0;
    virtual void push_back(T) = 0;
    virtual T pop_front() = 0;
    virtual T pop_back() = 0;
    virtual bool insert(T, int) = 0;
    virtual bool remove(int) = 0;
    virtual T& operator[](int) = 0;
    virtual bool is_empty() = 0;
    virtual int size() = 0;
    virtual void clear() = 0;
    virtual void sort() = 0;
    virtual bool is_sorted() = 0;
    virtual void reverse() = 0;
    virtual std::string name() = 0;
};

//////////////////////////////////////////////////
// ForwardLinkedList Implementation
//////////////////////////////////////////////////
template <typename T>
class ForwardLinkedList : public List<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& d, Node* n = nullptr): data(d), next(n){}
    };
    Node* head;
    Node* tail;
    int listSize;
public:
    ForwardLinkedList(): head(nullptr), tail(nullptr), listSize(0) {}

    ~ForwardLinkedList(){
        clear();
    }

    T front() override {
        if (is_empty())
            throw std::runtime_error("List is empty");
        return head->data;
    }

    T back() override {
        if (is_empty())
            throw std::runtime_error("List is empty");
        return tail->data;
    }

    void push_front(T value) override {
        Node* newNode = new Node(value, head);
        head = newNode;
        if(listSize == 0)
            tail = newNode;
        listSize++;
    }

    void push_back(T value) override {
        Node* newNode = new Node(value, nullptr);
        if(is_empty()){
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        listSize++;
    }

    T pop_front() override {
        if(is_empty())
            throw std::runtime_error("List is empty");
        Node* temp = head;
        T value = temp->data;
        head = head->next;
        delete temp;
        listSize--;
        if(listSize == 0)
            tail = nullptr;
        return value;
    }

    T pop_back() override {
        if(is_empty())
            throw std::runtime_error("List is empty");
        T value = tail->data;
        if(listSize == 1){
            delete tail;
            head = tail = nullptr;
        } else {
            // Buscar el nodo anterior a tail
            Node* curr = head;
            while(curr->next != tail){
                curr = curr->next;
            }
            delete tail;
            tail = curr;
            tail->next = nullptr;
        }
        listSize--;
        return value;
    }

    bool insert(T value, int index) override {
        if(index < 0 || index > listSize)
            return false;
        if(index == 0){
            push_front(value);
            return true;
        } else if(index == listSize){
            push_back(value);
            return true;
        } else {
            Node* curr = head;
            for(int i = 0; i < index - 1; i++){
                curr = curr->next;
            }
            Node* newNode = new Node(value, curr->next);
            curr->next = newNode;
            listSize++;
            return true;
        }
    }

    bool remove(int index) override {
        if(index < 0 || index >= listSize)
            return false;
        if(index == 0){
            pop_front();
            return true;
        } else {
            Node* curr = head;
            for(int i = 0; i < index - 1; i++){
                curr = curr->next;
            }
            Node* temp = curr->next;
            curr->next = temp->next;
            if(temp == tail)
                tail = curr;
            delete temp;
            listSize--;
            return true;
        }
    }

    T& operator[](int index) override {
        if(index < 0 || index >= listSize)
            throw std::out_of_range("Index out of range");
        Node* curr = head;
        for(int i = 0; i < index; i++){
            curr = curr->next;
        }
        return curr->data;
    }

    bool is_empty() override {
        return listSize == 0;
    }

    int size() override {
        return listSize;
    }

    void clear() override {
        while(!is_empty()){
            pop_front();
        }
    }

    void sort() override {
        if(listSize < 2)
            return;
        bool swapped;
        do {
            swapped = false;
            Node* curr = head;
            while(curr != nullptr && curr->next != nullptr){
                if(curr->data > curr->next->data){
                    std::swap(curr->data, curr->next->data);
                    swapped = true;
                }
                curr = curr->next;
            }
        } while(swapped);
    }

    void reverse() override {
        Node* prev = nullptr;
        Node* curr = head;
        tail = head;
        while(curr){
            Node* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    std::string name() override {
        return "ForwardLinkedList";
    }
};

//////////////////////////////////////////////////
// DoublyLinkedList Implementation
//////////////////////////////////////////////////
template <typename T>
class DoublyLinkedList : public List<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& d, Node* p = nullptr, Node* n = nullptr)
                : data(d), prev(p), next(n){}
    };
    Node* head;
    Node* tail;
    int listSize;
public:
    DoublyLinkedList(): head(nullptr), tail(nullptr), listSize(0){}

    ~DoublyLinkedList(){
        clear();
    }

    T front() override {
        if(is_empty())
            throw std::runtime_error("List is empty");
        return head->data;
    }

    T back() override {
        if(is_empty())
            throw std::runtime_error("List is empty");
        return tail->data;
    }

    void push_front(T value) override {
        Node* newNode = new Node(value, nullptr, head);
        if(is_empty()){
            head = tail = newNode;
        } else {
            head->prev = newNode;
            head = newNode;
        }
        listSize++;
    }

    void push_back(T value) override {
        Node* newNode = new Node(value, tail, nullptr);
        if(is_empty()){
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        listSize++;
    }

    T pop_front() override {
        if(is_empty())
            throw std::runtime_error("List is empty");
        Node* temp = head;
        T value = temp->data;
        head = head->next;
        if(head)
            head->prev = nullptr;
        else
            tail = nullptr;
        delete temp;
        listSize--;
        return value;
    }

    T pop_back() override {
        if(is_empty())
            throw std::runtime_error("List is empty");
        Node* temp = tail;
        T value = temp->data;
        tail = tail->prev;
        if(tail)
            tail->next = nullptr;
        else
            head = nullptr;
        delete temp;
        listSize--;
        return value;
    }

    bool insert(T value, int index) override {
        if(index < 0 || index > listSize)
            return false;
        if(index == 0){
            push_front(value);
            return true;
        } else if(index == listSize){
            push_back(value);
            return true;
        } else {
            Node* curr = head;
            for(int i = 0; i < index; i++){
                curr = curr->next;
            }
            Node* newNode = new Node(value, curr->prev, curr);
            curr->prev->next = newNode;
            curr->prev = newNode;
            listSize++;
            return true;
        }
    }

    bool remove(int index) override {
        if(index < 0 || index >= listSize)
            return false;
        if(index == 0){
            pop_front();
            return true;
        } else if(index == listSize - 1){
            pop_back();
            return true;
        } else {
            Node* curr = head;
            for(int i = 0; i < index; i++){
                curr = curr->next;
            }
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            delete curr;
            listSize--;
            return true;
        }
    }

    T& operator[](int index) override {
        if(index < 0 || index >= listSize)
            throw std::out_of_range("Index out of range");
        Node* curr;
        // Optimización: recorrer desde head o tail según convenga
        if(index < listSize / 2){
            curr = head;
            for(int i = 0; i < index; i++)
                curr = curr->next;
        } else {
            curr = tail;
            for(int i = listSize - 1; i > index; i--)
                curr = curr->prev;
        }
        return curr->data;
    }

    bool is_empty() override {
        return listSize == 0;
    }

    int size() override {
        return listSize;
    }

    void clear() override {
        while(!is_empty()){
            pop_front();
        }
    }

    void sort() override {
        if(listSize < 2)
            return;
        bool swapped;
        do {
            swapped = false;
            Node* curr = head;
            while(curr && curr->next){
                if(curr->data > curr->next->data){
                    std::swap(curr->data, curr->next->data);
                    swapped = true;
                }
                curr = curr->next;
            }
        } while(swapped);
    }

    void reverse() override {
        Node* curr = head;
        Node* temp = nullptr;
        while(curr){
            temp = curr->prev;
            curr->prev = curr->next;
            curr->next = temp;
            curr = curr->prev;
        }
        if(temp)
            head = temp->prev;
        std::swap(head, tail);
    }

    std::string name() override {
        return "DoublyLinkedList";
    }
};

//////////////////////////////////////////////////
// CircularDoublyLinkedList Implementation (con centinela)
//////////////////////////////////////////////////
template <typename T>
class CircularDoublyLinkedList : public List<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        // El constructor por defecto permite crear el nodo centinela
        Node(const T& d = T(), Node* p = nullptr, Node* n = nullptr)
                : data(d), prev(p), next(n){}
    };
    Node* sentinel; // nodo centinela
    int listSize;

    // Inicializa el nodo centinela
    void init() {
        sentinel = new Node();
        sentinel->next = sentinel;
        sentinel->prev = sentinel;
    }

public:
    CircularDoublyLinkedList(): listSize(0) {
        init();
    }

    ~CircularDoublyLinkedList(){
        clear();
        delete sentinel;
    }

    T front() override {
        if(is_empty())
            throw std::runtime_error("List is empty");
        return sentinel->next->data;
    }

    T back() override {
        if(is_empty())
            throw std::runtime_error("List is empty");
        return sentinel->prev->data;
    }

    void push_front(T value) override {
        Node* newNode = new Node(value, sentinel, sentinel->next);
        sentinel->next->prev = newNode;
        sentinel->next = newNode;
        listSize++;
    }

    void push_back(T value) override {
        Node* newNode = new Node(value, sentinel->prev, sentinel);
        sentinel->prev->next = newNode;
        sentinel->prev = newNode;
        listSize++;
    }

    T pop_front() override {
        if(is_empty())
            throw std::runtime_error("List is empty");
        Node* target = sentinel->next;
        T value = target->data;
        sentinel->next = target->next;
        target->next->prev = sentinel;
        delete target;
        listSize--;
        return value;
    }

    T pop_back() override {
        if(is_empty())
            throw std::runtime_error("List is empty");
        Node* target = sentinel->prev;
        T value = target->data;
        sentinel->prev = target->prev;
        target->prev->next = sentinel;
        delete target;
        listSize--;
        return value;
    }

    bool insert(T value, int index) override {
        if(index < 0 || index > listSize)
            return false;
        if(index == 0){
            push_front(value);
            return true;
        } else if(index == listSize){
            push_back(value);
            return true;
        } else {
            Node* curr = sentinel->next;
            for(int i = 0; i < index; i++){
                curr = curr->next;
            }
            Node* newNode = new Node(value, curr->prev, curr);
            curr->prev->next = newNode;
            curr->prev = newNode;
            listSize++;
            return true;
        }
    }

    bool remove(int index) override {
        if(index < 0 || index >= listSize)
            return false;
        Node* curr = sentinel->next;
        for(int i = 0; i < index; i++){
            curr = curr->next;
        }
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        listSize--;
        return true;
    }

    T& operator[](int index) override {
        if(index < 0 || index >= listSize)
            throw std::out_of_range("Index out of range");
        Node* curr = sentinel->next;
        for(int i = 0; i < index; i++){
            curr = curr->next;
        }
        return curr->data;
    }

    bool is_empty() override {
        return listSize == 0;
    }

    int size() override {
        return listSize;
    }

    void clear() override {
        while(!is_empty()){
            pop_front();
        }
    }

    void sort() override {
        if(listSize < 2)
            return;
        bool swapped;
        do {
            swapped = false;
            Node* curr = sentinel->next;
            while(curr->next != sentinel){
                if(curr->data > curr->next->data){
                    std::swap(curr->data, curr->next->data);
                    swapped = true;
                }
                curr = curr->next;
            }
        } while(swapped);
    }

    void reverse() override {
        if(is_empty())
            return;
        // Recorremos todos los nodos, incluyendo el centinela, y se intercambian los punteros.
        Node* curr = sentinel;
        do {
            std::swap(curr->next, curr->prev);
            curr = curr->prev; // originalmente era "next"
        } while(curr != sentinel);
    }

    std::string name() override {
        return "CircularDoublyLinkedList";
    }
};

//////////////////////////////
// Ejemplo de uso (main)
//////////////////////////////
int main() {
    // Ejemplo básico para probar las implementaciones

    ForwardLinkedList<int> flist;
    flist.push_back(3);
    flist.push_front(1);
    flist.push_back(2);
    std::cout << flist.name() << " Front: " << flist.front() << ", Back: " << flist.back() << std::endl;
    flist.sort();
    std::cout << "Elemento en posición 1 luego de ordenar: " << flist[1] << std::endl;
    flist.reverse();
    std::cout << "Elemento en posición 1 luego de revertir: " << flist[1] << std::endl;

    DoublyLinkedList<int> dlist;
    dlist.push_back(10);
    dlist.push_front(5);
    dlist.push_back(15);
    std::cout << dlist.name() << " Front: " << dlist.front() << ", Back: " << dlist.back() << std::endl;

    CircularDoublyLinkedList<int> clist;
    clist.push_back(100);
    clist.push_front(50);
    clist.push_back(150);
    std::cout << clist.name() << " Front: " << clist.front() << ", Back: " << clist.back() << std::endl;

    return 0;
}