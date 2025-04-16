#ifndef CIRCULAR_H
#define CIRCULAR_H
#include <iostream>
#include "list.h"

// TODO: Implement all methods
template <typename T>
class CircularList : public List<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(){

            next = nullptr;
            prev = nullptr;
        }

        Node(T value){
            data = value;
            next = nullptr;
            prev = nullptr;
        }

        void killSelf(){
            delete this;
        }
    };

private:
    Node* head;//sentinel
    int nodes;

public:
    CircularList() : List<T>() {
        head = new Node();
        head->next = head;
        head->prev = head;
        nodes = 0;
    }

    ~CircularList(){
        clear();      // borra todos los nodos con pop_front
        delete head;  // finalmente borra el centinela
    }
    T front(){
        return head->next->data;

    }

    T back(){
        Node* p = head;
        while (p->next!=head){
            p = p->next;
        }
        return p->data;
    }
    void push_front(T data){
        Node* newNode = new Node(data);
        newNode->next = head->next;
        newNode->prev = head;
        head->next = newNode;
        nodes++;
        newNode->next->prev = newNode;
    }

    void push_back(T data){
        Node* newNode = new Node(data);
        newNode->next = head;
        newNode->prev = head->prev;
        head->prev = newNode;
        nodes++;
        newNode->prev->next = newNode;
    }

    T pop_front(){
        if (head->next == head){
            throw std::out_of_range("List is empty");
        }
        Node* temp = head->next;
        head->next = temp->next;
        temp->next->prev = head;
        T data = temp->data;
        temp->killSelf();
        nodes--;
        return data;
    }

    T pop_back(){
        if (head->prev == head){
            throw std::out_of_range("List is empty");
        }
        Node* temp = head->prev;
        head->prev = temp->prev;
        temp->prev->next = head;
        T data = temp->data;
        temp->killSelf();
        nodes--;
        return data;
    }
    T insert(T data, int pos){
        if (pos < 0 || pos >= nodes) {
            throw std::out_of_range("out of range");
        }
        if (pos == nodes) {
            push_back(data);
            return;
        }
        Node* newNode = new Node(data);
        Node* temp = head->next;
        for (int i = 0; i < pos-1; i++){
            temp = temp->next;
        }
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;
        nodes++;
        return data;
    }

    bool remove(int pos){
        if (pos < 0 || pos >= nodes) {
            throw std::out_of_range("out of range");
        }

        Node* temp = head->next;
        for (int i = 0; i < pos; i++){
            temp = temp->next;
        }
        temp->next->prev = temp->prev;
        temp->prev->next = temp->next;
        temp->killSelf();
        nodes--;
        return true;
    }

    T& operator[](int pos){
        if (pos < 0 || pos >= nodes) {
            throw std::out_of_range("out of range");
        }

        Node* temp = head->next;
        for (int i = 0; i < pos; i++){
            temp = temp->next;
        }
        return temp->data;
    }

    bool is_empty(){
        if (head->next == head){
            return true;
        }
        return false;
    }

    int size(){
        return nodes;
    }

    void clear(){
        if (head->next == head){
            return;
        }
        while (head->next != head){
            pop_front();
        }
    }

    void sort(){
        if (nodes < 2) return;

        bool swapped;
        do {
            swapped = false;
            Node* current = head->next;
            while (current->next != head) {
                if (current->data > current->next->data) {
                    std::swap(current->data, current->next->data);
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }


    bool is_sorted(){
        Node* temp = head->next;
        while (temp->next != head){
            if (temp->data > temp->next->data){
                return false;
            }
            temp = temp->next;
        }
        return true;

    }
    void reverse(){
        Node* current = head;
        do {
            swap(current->next, current->prev);
            current = current->prev;
        } while (current != head);
    }

    std::string name(){
        return "ForwardList";
        }
};

#endif