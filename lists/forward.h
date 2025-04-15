#ifndef FORWARD_H
#define FORWARD_H
#include <iostream>
#include "list.h"

template <typename T>
class ForwardList : public List<T> {
private:
    struct Node {
        T data;
        Node* next;

        Node() {
            next = nullptr;
        }

        Node(T value) {
            data = value;
            next = nullptr;
        }

        void killSelf() {
            delete this;
        }
    };

private:
    Node* head;
    int nodes;

public:
    ForwardList() : List<T>(), head(nullptr), nodes(0) {}

    ~ForwardList() {
        clear();
    }

    T front() {
        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }
        return head->data;
    }

    T back() {
        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        return temp->data;
    }

    void push_front(T data) {
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
        nodes++;
    }

    void push_back(T data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
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

    T pop_front() {
        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }
        Node* temp = head;
        head = head->next;
        T data = temp->data;
        temp->killSelf();
        nodes--;
        return data;
    }

    T pop_back() {
        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }
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

    T insert(T data, int pos) {
        if (pos < 0 || pos > nodes) {
            throw std::out_of_range("out of range");
        }
        if (pos == 0) {
            push_front(data);
            return data;
        }
        Node* newNode = new Node(data);
        Node* temp = head;
        for (int i = 0; i < pos - 1; i++) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        nodes++;
        return data;
    }

    bool remove(int pos) {
        if (pos < 0 || pos >= nodes) {
            throw std::out_of_range("out of range");
        }
        if (pos == 0) {
            pop_front();
            return true;
        }
        Node* temp = head;
        for (int i = 0; i < pos - 1; i++) {
            temp = temp->next;
        }
        Node* nodeToRemove = temp->next;
        temp->next = temp->next->next;
        nodeToRemove->killSelf();
        nodes--;
        return true;
    }

    T& operator[](int pos) {
        if (pos < 0 || pos >= nodes) {
            throw std::out_of_range("out of range");
        }
        Node* temp = head;
        for (int i = 0; i < pos; i++) {
            temp = temp->next;
        }
        return temp->data;
    }

    bool is_empty() {
        return head == nullptr;
    }

    int size() {
        return nodes;
    }

    void clear() {
        while (!is_empty()) {
            pop_front();
        }
    }

    void sort() {

        if (nodes < 2) return;

        bool swapped;
        do {
            swapped = false;
            Node* current = head;
            while (current != nullptr && current->next != nullptr) {
                if (current->data > current->next->data) {
                    std::swap(current->data, current->next->data);
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }

    bool is_sorted() {
        Node* temp = head;
        while (temp != nullptr && temp->next != nullptr) {
            if (temp->data > temp->next->data) {
                return false;
            }
            temp = temp->next;
        }
        return true;
    }

    void reverse() {
        Node* current = head;
        Node* prev = nullptr;
        Node* next = nullptr;
        while (current != nullptr) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    std::string name() {
        return "ForwardList";
    }
};

#endif // FORWARD_H
