#ifndef DOUBLY_H
#define DOUBLY_H

#include <iostream>
#include "list.h"
#include <algorithm>

template <typename T>
class DoubleList : public List<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(T value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int nodes;

public:
    DoubleList() : head(nullptr), tail(nullptr), nodes(0) {}

    ~DoubleList() {
        clear();
    }

    T front() override {
        if (is_empty()) throw std::out_of_range("List is empty");
        return head->data;
    }

    T back() override {
        if (is_empty()) throw std::out_of_range("List is empty");
        return tail->data;
    }

    void push_front(T data) override {
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

    void push_back(T data) override {
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

    T pop_front() override {
        if (is_empty()) throw std::out_of_range("List is empty");
        Node* temp = head;
        T data = temp->data;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
        nodes--;
        return data;
    }

    T pop_back() override {
        if (is_empty()) throw std::out_of_range("List is empty");
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
        if (pos < 0 || pos > nodes) return false;
        if (pos == 0) {
            push_front(data);
            return true;
        }
        if (pos == nodes) {
            push_back(data);
            return true;
        }
        Node* temp = head;
        for (int i = 0; i < pos - 1; i++) {
            temp = temp->next;
        }
        Node* newNode = new Node(data);
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;
        nodes++;
        return true;
    }

    bool remove(int pos) override {
        if (pos < 0 || pos >= nodes) return false;
        if (pos == 0) {
            pop_front();
            return true;
        }
        if (pos == nodes - 1) {
            pop_back();
            return true;
        }
        Node* temp = head;
        for (int i = 0; i < pos; i++) {
            temp = temp->next;
        }
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;
        nodes--;
        return true;
    }

    T& operator[](int pos) override {
        if (pos < 0 || pos >= nodes) throw std::out_of_range("Index out of range");
        Node* temp = head;
        for (int i = 0; i < pos; i++) {
            temp = temp->next;
        }
        return temp->data;
    }

    bool is_empty() override {
        return nodes == 0;
    }

    int size() override {
        return nodes;
    }

    void clear() override {
        while (!is_empty()) {
            pop_front();
        }
    }

    void sort() override {
        if (nodes < 2) return;
        bool swapped;
        do {
            swapped = false;
            Node* temp = head;
            while (temp->next != nullptr) {
                if (temp->data > temp->next->data) {
                    std::swap(temp->data, temp->next->data);
                    swapped = true;
                }
                temp = temp->next;
            }
        } while (swapped);
    }

    bool is_sorted() override {
        if (is_empty()) return true;
        Node* temp = head;
        while (temp->next != nullptr) {
            if (temp->data > temp->next->data) return false;
            temp = temp->next;
        }
        return true;
    }

    void reverse() override {
        Node* temp = nullptr;
        Node* current = head;
        tail = head;
        while (current != nullptr) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        if (temp != nullptr) {
            head = temp->prev;
        }
    }

    std::string name() override {
        return "DoublyLinkedList";
    }
};

#endif