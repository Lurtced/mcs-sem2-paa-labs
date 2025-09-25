#include "list.hpp"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <stdexcept>

List::List()
    : Head_(new Node()), Tail_(new Node()), m_size_(0)
{
    Head_->setNext(Tail_);
    Tail_->setPrev(Head_);
}

List::List(const List& other)
    : Head_(new Node()), Tail_(new Node()), m_size_(0)
{
    Head_->setNext(Tail_);
    Tail_->setPrev(Head_);

    Node* current = other.Head_->getNext();
    while (current != other.Tail_) {
        addBack(current->getData());
        current = current->getNext();
    }
}

List& List::operator=(const List& other) {
    if (this == &other) return *this;

    clear();

    Node* current = other.Head_->getNext();
    while (current != other.Tail_) {
        addBack(current->getData());
        current = current->getNext();
    }

    return *this;
}

List::~List() {
    clear();
    delete Head_;
    delete Tail_;
}

void List::addFront(const Circle& circle) {
    Node* newNode = new Node(circle);
    newNode->setNext(Head_->getNext());
    newNode->setPrev(Head_);
    Head_->getNext()->setPrev(newNode);
    Head_->setNext(newNode);
    m_size_++;
}

void List::addBack(const Circle& circle) {
    Node* newNode = new Node(circle);
    newNode->setNext(Tail_);
    newNode->setPrev(Tail_->getPrev());
    Tail_->getPrev()->setNext(newNode);
    Tail_->setPrev(newNode);
    m_size_++;
}

bool List::remove(const Circle& circle) {
    Node* current = Head_->getNext();
    while (current != Tail_) {
        if (current->getData() == circle) {
            current->getPrev()->setNext(current->getNext());
            current->getNext()->setPrev(current->getPrev());
            delete current;
            m_size_--;
            return true;
        }
        current = current->getNext();
    }
    return false;
}

int List::removeAll(const Circle& circle) {
    int count = 0;
    Node* current = Head_->getNext();

    while (current != Tail_) {
        if (current->getData() == circle) {
            Node* toDelete = current;
            current = current->getNext();

            toDelete->getPrev()->setNext(toDelete->getNext());
            toDelete->getNext()->setPrev(toDelete->getPrev());
            delete toDelete;
            m_size_--;
            count++;
        } else {
            current = current->getNext();
        }
    }

    return count;
}

void List::clear() {
    Node* current = Head_->getNext();
    while (current != Tail_) {
        Node* next = current->getNext();
        delete current;
        current = next;
    }

    Head_->setNext(Tail_);
    Tail_->setPrev(Head_);
    m_size_ = 0;
}

size_t List::size() const {
    return m_size_;
}

void List::saveToFile(const char* filename) const {
    std::ofstream fout(filename);

    if (!fout) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }

    Node* current = Head_->getNext();
    while (current != Tail_) {
        fout << "Circle: Center = (" 
             << current->getData().getCenter().getX() << ", "
             << current->getData().getCenter().getY() << "), "
             << "Radius = " << current->getData().getRadius() << "\n";
        current = current->getNext();
    }

    fout.close();
}

void List::loadFromFile(const char* filename) {
    clear();

    FILE* file = fopen(filename, "r");
    if (!file) {
        std::cerr << "Error opening file for reading." << std::endl;
        return;
    }

    const int LINE_SIZE = 256;
    char line[LINE_SIZE];

    while (fgets(line, LINE_SIZE, file)) {
        double x = 0.0, y = 0.0, radius = 0.0;

        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        if (sscanf(line, "Circle: Center = (%lf, %lf), Radius = %lf", &x, &y, &radius) == 3) {
            addBack(Circle(x, y, radius));
        }
    }

    fclose(file);
}

void List::sortByArea() {
    for (Iterator it1 = begin(); it1 != end(); ++it1) {
        for (Iterator it2 = it1; it2 != end(); ++it2) {
            if ((*it1).getArea() > (*it2).getArea()) {
                Circle tmp = *it1;
                *const_cast<Circle*>(&(*it1)) = *const_cast<Circle*>(&(*it2));
                *const_cast<Circle*>(&(*it2)) = tmp;
            }
        }
    }
}

Circle List::get(int index) const {
    if (index < 0 || index >= m_size_) {
        throw std::out_of_range("Index out of bounds");
    }

    Node* current = Head_->getNext();
    for (int i = 0; i < index; ++i) {
        current = current->getNext();
    }

    return current->getData();
}

std::ostream& operator<<(std::ostream& os, const List& list) {
    os << "List contents:" << std::endl;

    Node* current = list.Head_->getNext();
    while (current != list.Tail_) {
        os << "Circle: Center = (" 
           << current->getData().getCenter().getX() << ", "
           << current->getData().getCenter().getY() << "), "
           << "Radius = " << current->getData().getRadius() << std::endl;

        current = current->getNext();
    }

    os << "Size of list: " << list.m_size_ << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const List::Iterator& iterator) {
    os << "Circle: Center = (" 
       << iterator->getCenter().getX() << ", "
       << iterator->getCenter().getY() << "), "
       << "Radius = " << iterator->getRadius();
    
    return os;
}