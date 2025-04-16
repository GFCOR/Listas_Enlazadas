#ifndef CIRCULAR_H
#define CIRCULAR_H
#include <iostream>
#include "list.h"
#include <algorithm>

template <typename T>
class CircularList : public List<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(T value = T()) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head; // Sentinel node
    int nodes;

public:
    CircularList() : nodes(0) {
        head = new Node();
        head->next = head;
        head->prev = head;
    }

    ~CircularList() {
        clear();
        delete head;
    }

    T front() override {
        if (is_empty()) throw std::out_of_range("List is empty");
        return head->next->data;
    }

    T back() override {
        if (is_empty()) throw std::out_of_range("List is empty");
        return head->prev->data;
    }

    void push_front(T data) override {
        Node* newNode = new Node(data);
        newNode->next = head->next;
        newNode->prev = head;
        head->next->prev = newNode;
        head->next = newNode;
        nodes++;
    }

    void push_back(T data) override {
        Node* newNode = new Node(data);
        newNode->next = head;
        newNode->prev = head->prev;
        head->prev->next = newNode;
        head->prev = newNode;
        nodes++;
    }

    T pop_front() override {
        if (is_empty()) throw std::out_of_range("List is empty");
        Node* temp = head->next;
        T data = temp->data;
        head->next = temp->next;
        temp->next->prev = head;
        delete temp;
        nodes--;
        return data;
    }

    T pop_back() override {
        if (is_empty()) throw std::out_of_range("List is empty");
        Node* temp = head->prev;
        T data = temp->data;
        head->prev = temp->prev;
        temp->prev->next = head;
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
        Node* temp = head->next;
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
        Node* temp = head->next;
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
        Node* temp = head->next;
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
            Node* temp = head->next;
            while (temp->next != head) {
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
        Node* temp = head->next;
        while (temp->next != head) {
            if (temp->data > temp->next->data) return false;
            temp = temp->next;
        }
        return true;
    }

    void reverse() override {
        Node* current = head;
        do {
            std::swap(current->next, current->prev);
            current = current->prev;
        } while (current != head);
    }

    std::string name() override {
        return "CircularList";
    }
};

#endif