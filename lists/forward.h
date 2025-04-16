#ifndef FORWARD_H
#define FORWARD_H
#include <iostream>
#include "list.h"
#include <algorithm>

template <typename T>
class ForwardList : public List<T> {
private:
    struct Node {
        T data;
        Node* next;

        Node(T value) : data(value), next(nullptr) {}
    };

    Node* head;
    int nodes;

public:
    ForwardList() : head(nullptr), nodes(0) {}

    ~ForwardList() {
        clear();
    }

    T front() override {
        if (is_empty()) throw std::out_of_range("List is empty");
        return head->data;
    }

    T back() override {
        if (is_empty()) throw std::out_of_range("List is empty");
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        return temp->data;
    }

    void push_front(T data) override {
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
        nodes++;
    }

    void push_back(T data) override {
        Node* newNode = new Node(data);
        if (is_empty()) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        nodes++;
    }

    T pop_front() override {
        if (is_empty()) throw std::out_of_range("List is empty");
        Node* temp = head;
        T data = temp->data;
        head = head->next;
        delete temp;
        nodes--;
        return data;
    }

    T pop_back() override {
        if (is_empty()) throw std::out_of_range("List is empty");
        if (head->next == nullptr) {
            T data = head->data;
            delete head;
            head = nullptr;
            nodes--;
            return data;
        }
        Node* temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }
        T data = temp->next->data;
        delete temp->next;
        temp->next = nullptr;
        nodes--;
        return data;
    }

    bool insert(T data, int pos) override {
        if (pos < 0 || pos > nodes) return false;
        if (pos == 0) {
            push_front(data);
            return true;
        }
        Node* temp = head;
        for (int i = 0; i < pos - 1; i++) {
            temp = temp->next;
        }
        Node* newNode = new Node(data);
        newNode->next = temp->next;
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
        Node* temp = head;
        for (int i = 0; i < pos - 1; i++) {
            temp = temp->next;
        }
        Node* toDelete = temp->next;
        temp->next = toDelete->next;
        delete toDelete;
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
        Node* prev = nullptr;
        Node* curr = head;
        while (curr != nullptr) {
            Node* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }

    std::string name() override {
        return "ForwardList";
    }
};

#endif