#pragma once
#include "Circle.hpp"


class Node {
private:
    Node* pPrev_;
    Node* pNext_;
    Circle m_Data_;

public:
    Node();
    Node(const Circle& circle);
    ~Node();

    Node* getPrev() const { return pPrev_; }
    Node* getNext() const { return pNext_; }
    const Circle& getData() const { return m_Data_; }
    void setData(const Circle& other);

    void setPrev(Node* prev) { pPrev_ = prev; }
    void setNext(Node* next) { pNext_ = next; }

    void print() const;
};