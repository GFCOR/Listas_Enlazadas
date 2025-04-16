#ifndef DOUBLY_H
#define DOUBLY_H

#include <iostream>
#include <stdexcept>
#include "list.h"

//TODO: Implement al methods
template <typename T>
class DoubleList : public List<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;


        Node() : data(T()), next(nullptr), prev(nullptr) {}
        //TODO
        Node(T value) : data(value), next(nullptr), prev(nullptr) {}
        //TODO
        void killSelf() {
            if (next) next->killSelf();
            delete this;
        }
    };

    Node* head;
    Node* tail;
    int nodes;

public:
    DoubleList() : head(nullptr), tail(nullptr), nodes(0) {}

    ~DoubleList() {
        clear();
    }

    T front() {
        if (is_empty()) throw std::runtime_error("La lista está vacía");
        return head->data;
        return head->data;
    }

    T back() {
        if (is_empty()) throw std::runtime_error("La lista está vacía");
        return tail->data;
    }

    void push_front(T data) {
        Node* newNode = new Node(data);
        if (is_empty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        nodes++;
    }

    void push_back(T data) {
        Node* newNode = new Node(data);
        if (is_empty()) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        nodes++;
    }

    T pop_front() {
        if (is_empty()) throw std::runtime_error("La lista está vacía");
        Node* temp = head;
        T data = temp->data;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
        nodes--;
        return data;
    }

    T pop_back() {
        if (is_empty()) throw std::runtime_error("La lista está vacía");
        Node* temp = tail;
        T data = temp->data;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
        nodes--;
        return data;
    }


    bool insert(T data, int pos) override {
        if (pos < 0 || pos > nodes) {
            throw std::out_of_range("Posición inválida");
        }
        if (pos == 0) {
            push_front(data);
            return true;
        }
        if (pos == nodes) {
            push_back(data);
            return true;
        }
        Node* newNode = new Node(data);
        Node* current = head;
        for (int i = 0; i < pos - 1; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        newNode->prev = current;
        current->next->prev = newNode;
        current->next = newNode;
        nodes++;
        return true;
    }


    bool remove(int pos) {
        if (pos < 0 || pos >= nodes) throw std::out_of_range("Posición inválida");
        if (pos == 0) {
            pop_front();
            return true;
        }
        if (pos == nodes - 1) {
            pop_back();
            return true;
        }
        Node* current = head;
        for (int i = 0; i < pos; ++i) {
            current = current->next;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        nodes--;
        return true;
    }

    T& operator[](int pos) {
        if (pos < 0 || pos >= nodes) throw std::out_of_range("Posición inválida");
        Node* current = head;
        for (int i = 0; i < pos; ++i) {
            current = current->next;
        }
        return current->data;
    }

    bool is_empty() {
        return nodes == 0;
    }

    int size() {
        return nodes;
    }

    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        nodes = 0;

    }

    void sort() {
        if (is_empty() || nodes == 1) return;
        for (Node* i = head; i->next != nullptr; i = i->next) {
            for (Node* j = i->next; j != nullptr; j = j->next) {
                if (i->data > j->data) {
                    std::swap(i->data, j->data);
                }
            }
        }
    }

    bool is_sorted() {
        if (is_empty() || nodes == 1) return true;
        for (Node* current = head; current->next != nullptr; current = current->next) {
            if (current->data > current->next->data) return false;
        }
        return true;
    }

    void reverse() {
        if (is_empty() || nodes == 1) return;
        Node* current = head;
        Node* temp = nullptr;
        while (current != nullptr) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        temp = head;
        head = tail;
        tail = temp;
    }

    std::string name() {
        return "DoublyLinkedList";
        }
};

#endif