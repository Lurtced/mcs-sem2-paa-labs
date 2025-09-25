#include "Node.hpp"
#include <iostream>


Node::Node()
    : pPrev_(nullptr), pNext_(nullptr), m_Data_(Circle()) {}

Node::Node(const Circle& circle)
    : pPrev_(nullptr), pNext_(nullptr), m_Data_(circle) {}

Node::~Node() {
    if (pPrev_) {
        pPrev_->setNext(pNext_);
    }
    if (pNext_) {
        pNext_->setPrev(pPrev_);
    }
}

void Node::setData(const Circle& other) {
    m_Data_ = other;
}

void Node::print() const {
    std::cout << "Node: ";
    m_Data_.print();
    std::cout << "Prev = " << pPrev_ << ", Next = " << pNext_ << std::endl;
}