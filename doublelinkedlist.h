#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H
#include "Imagen_.h"
#include<iostream>
#include <QDebug>
#include<QMessageBox>
#include<vector>
#include<fstream>
#include<sstream>
using namespace std;
class DoubleLinkedList
{
private:
    class Node {
    public:
        Imagen_ dato;
        Node *next;
        Node *previous;
        Node(Imagen_ x){
            dato=x;
            next=nullptr;
            previous=nullptr;
        }
        void setDato(Imagen_ image){
            dato=image;
        }
    };
    DoubleLinkedList::Node *first;
    DoubleLinkedList::Node *last;
    int size;
    int maxSize;
    void deleteNV(QString);
public:
    class iterator{
    private:
        Node *pNode;
    public:
        iterator():pNode(nullptr){}
        void operator =(Node* x)
        {
            pNode=x;

        }
        void operator ++()
        {
            pNode=pNode->next;
        }
        void operator --()
        {
            pNode=pNode->previous;
        }
        Imagen_ operator *()
        {
            return pNode->dato;
        }
        bool operator ==(iterator x)
        {
            return pNode==x.getPNode();
        }
        bool operator !=(Node *x)
        {
            return pNode!=x;
        }
        Node *getPNode() const{
            return pNode;
        }
        void clear(){
            pNode=nullptr;
        }
    };
    bool push_back(Imagen_);
    int fsize();
    void show();
    int deleteN(DoubleLinkedList::iterator);
    void showAll();
    int search(QString,DoubleLinkedList::iterator&);
    void showVector();
    void loadFile();
    void updateFile(Imagen_);
    DoubleLinkedList(int maxSize);
    Node *begin() const;
    Node *end() const;
    int getMaxsize() const;

private:
    vector<DoubleLinkedList::iterator> binarytree;
    int searchPosition(int,unsigned int,unsigned int,iterator&);
};

#endif // DOUBLELINKEDLIST_H
