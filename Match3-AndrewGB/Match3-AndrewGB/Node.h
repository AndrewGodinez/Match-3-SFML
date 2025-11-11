#pragma once 

template <class Type>
class Node {
private:
    Type data;
    Node* next;
    Node* prev;
public:
    Node(Type value) : data(value), next(nullptr), prev(nullptr) {}
    Type getData() const { return data; }
    void setData(Type value) { data = value; }
    Node* getNext() const { return next; }
    void setNext(Node* nextNode) { next = nextNode; }
    Node* getPrev() const { return prev; }
    void setPrev(Node* prevNode) { prev = prevNode; }
};