#include <iostream>
#include "TSegment.h"
#pragma once

struct Node
{
    int height;
    Node* par;
    Node* l;
    Node* r;
    Segment seg;
    explicit Node(const Segment& seg_, Node* _parent = nullptr,
        Node* left = nullptr, Node* right = nullptr, int h = 0) :
        seg(seg_), height(h), l(left), r(right), par(_parent) {};
    Node* getPrev();
    Node* getNext();
    Node* getMin();
    Node* getMax();
    bool leaf() const;
    ~Node() { l = nullptr; r = nullptr; }
};

class Tree
{
    Node* root;
    Segment nonIntSeg1;
    Segment nonIntSeg2;

    static void swap(Node* a, Node* b);
    static void updateHeight(Node* node);
    int getHeight(Node* node);
    int getBalance(Node* node);
    static void rightRot(Node* node);
    static void leftRot(Node* node);
    void balance(Node* node);

public:
    Tree()
    {
        root = nullptr;
        nonIntSeg1 = Segment(Point(200, 300), Point(201, 301));
        nonIntSeg2 = Segment(Point(-200, -300), Point(-201, -301));
    }
    void insert(Node* node, Segment seg_);
    Node* del(Node* node, Segment seg_);
    Node* remove(Segment seg_);
    Node* getRoot() { return root; }
    void printTree(Node* node);
    Segment getPrev(Node* node);
    Segment getNext(Node* node);
    Node* search(Node* node, Segment seg_, double t);
};
