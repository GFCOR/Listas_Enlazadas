#ifndef FORWARD_H
#define FORWARD_H
#include <iostream>
#include "list.h"

// TODO: Implement all methods
template <typename T>
class ForwardList : public List<T> {
private:
    struct Node {
        T data;
        Node* next;

        Node(){
            next = nullptr;
        }

        Node(T value){
            data = value;
            next = nullptr;
        }

        void killSelf(){
            delete this;
        }
    };

private:
    Node* head;
    int nodes;

public:
    ForwardList() : List<T>() {}

    ~ForwardList(){
        // TODO
    }

    T front(){
        if(head == nullptr){
            throw std::out_of_range("List is empty");
        }
        return head->data;
    }

    T back(){
        if(head == nullptr){
            throw std::out_of_range("List is empty");
        }
        Node* p = head;
        while(p->next != nullptr){
            p = p->next;
        }
        return p->data;
    }

    void push_front(T data){
        if(head == nullptr){
            head = new Node(data);
        }
        Node* p = new Node(data);
        p->next = head;
        head = p;
    }

    void push_back(T data){
        if(head == nullptr){
            head = new Node(data);
        }
        Node* p = new Node(data);
        p->next = nullptr;
        Node* temp = head;
        while(temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = p;
    }

    T pop_front(){
        if(head == nullptr){
            throw std::out_of_range("List is empty");
        }

        Node* p = head;
        T data = head->data;
        head = p->next;
        delete p;
        return data;
    }

    T pop_back(){
        if(head == nullptr){
            throw std::out_of_range("List is empty");
        }
        if(head->next == nullptr){
            delete head;
        }
        Node* p = head;
        while(p->next->next != nullptr){
            p = p->next;
        }
        T data = p->next->data;
        delete p->next;
        p->next = nullptr; return data;
    }

    T insert(T data, int pos){
        if(pos > this->size()){
            throw std::out_of_range("List is out of range");
        }
        Node* p = head;
        for(int i = 0; i < pos; i++){
            p = p->next;
        }
        Node* p2 = new Node(data);
        p2->next = p->next;
        p->next = p2;
        return data;
    }

    bool remove(int pos){
        if(pos > this->size()){
            throw std::out_of_range("List is out of range");
        }
        if(pos == this->size()){
            pop_back();
            return true;
        }
        Node* p = head;
        for(int i = 0; i < pos-1; i++){
            p = p->next;
        }
        Node* p2 = p->next->next;
        delete p->next;
        p->next = p2;
        return true;
    }

    T& operator[](int pos){
        if(pos > this->size()){
            throw std::out_of_range("List is out of range");
        }
        Node* p = head;
        for(int i = 0; i < pos; i++){
            p = p->next;
        }
        return p->data;
    }

    bool is_empty(){
        if(head == nullptr){
            return true;
        }
    }

    int size(){
        int count = 0;
        Node* p = head;
        while(p != nullptr){
            p = p->next;
            count++;
        }
        return count;
    }

    void clear(){
        Node* p = head;
        while(p != nullptr){
            pop_front();
        }
    }

    void sort(){
        bool sorted = true;
        if(head == nullptr||head->next == nullptr){
            return;
        }
        Node* p = head;
        do{
            sorted = true;
            p=head;
            while(p->next != nullptr){
                if(p->next->data < p->data){
                    sorted = false;
                    swap(p->data, p->next->data);
                }
                p=p->next;
            }
        }while(sorted == false);
    }

    bool is_sorted(){
        if(head == nullptr){
            return false;
        }
        if(head->next == nullptr){
            return true;
        }
        Node* p = head;
        while(p->next != nullptr){
            if(p->next->data < p->data){
                return false;
            }
            p=p->next;
        }
        return true;
    }

    void reverse(){
        Node* newHead = nullptr;
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            temp->next = newHead;
            newHead = temp;
        }
        head = newHead;
    }

    std::string name(){
        return "ForwardList";
        }

};

#endif