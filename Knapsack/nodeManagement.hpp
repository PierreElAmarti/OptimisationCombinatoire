#pragma once

//#include "KpSolver.hpp"
#include "nodeBB.hpp"
#include <algorithm>
#include <deque>
#include <iostream>
#include <time.h>
#include <vector>
using namespace std;

class NodeManagement {
//private:
//    KpSolver * kp;

public:
    virtual ~NodeManagement() =  default;
    virtual void insertNode(NodeBB* node) = 0;
    virtual void insertNodes(NodeBB* nod1, NodeBB* nod2);
    virtual NodeBB* selectNode() = 0;
    virtual double getUpperBound() = 0;
    virtual bool isEmpty() = 0;
    virtual void clear() = 0;
    virtual size_t nbNodes() = 0;
    virtual string to_string() =0;
};

class NMdeque : public NodeManagement {
protected:
    std::deque<NodeBB*> nodes;
public:
    virtual ~NMdeque();
    virtual NodeBB* selectNode() override;
    virtual void insertNode(NodeBB* nod) override {nodes.push_back(nod);};
    virtual double getUpperBound() override;
    bool isEmpty() override { return nodes.empty(); }
    void clear() override { for (auto it : nodes)  delete it;  nodes.clear(); }
    size_t nbNodes() override { return nodes.size(); }
};

class NMvector : public NodeManagement {
protected:
    std::vector<NodeBB*> nodes;
public:
    virtual ~NMvector();
    NodeBB* selectNode() override;
    virtual void insertNode(NodeBB* nod) override {nodes.push_back(nod);};
    virtual double getUpperBound() override;
    bool isEmpty() override { return nodes.empty(); }
    void clear() override { for (auto it : nodes)  delete it;  nodes.clear(); }
    size_t nbNodes() override { return nodes.size(); }
};

class RandomOld : public NMdeque {
public:
    NodeBB* selectNode() override;
    string to_string() override {return "RandomOld";};
};

class Random : public NMvector {
public:
    NodeBB* selectNode() override;
    string to_string() override {return "Random";};
};

/*
class BFSdeque : public NMdeque {

public:
    NodeBB* selectNode() override;
    void insertNode(NodeBB* nod) override {nodes.push_front(nod);};
    string to_string() override {return "BFSdeque";};
};
*/

class BestBoundOld : public NMdeque {

public:

    void insertNode(NodeBB* nod) override;
    void insertNodes(NodeBB* nod1, NodeBB* nod2) override;
    double getUpperBound() override {return nodes.back()->getNodeUpperBound();};
    string to_string() override {return "BestBoundOld";};
};

class BestBoundDeque : public NMdeque {

public:
    void insertNode(NodeBB* nod) override;
    double getUpperBound() override {return nodes.back()->getNodeUpperBound();};
    string to_string() override {return "BestBoundDeque";};
};

class BestBoundVector : public NMvector {

public:
    void insertNode(NodeBB* nod) override;
    double getUpperBound() override {return nodes.back()->getNodeUpperBound();};
    string to_string() override {return "BestBoundVector";};
};



class DFS01old : public NMdeque {
public:
    void insertNodes(NodeBB* nod0, NodeBB* nod1) override;
    string to_string() override {return "DFS01old";};
};

class DFS01 : public NMvector {
public:
    void insertNodes(NodeBB* nod0, NodeBB* nod1) override;
    string to_string() override {return "DFS01";};
};


class DFS10old : public NMdeque {
public:
    string to_string() override {return "DFS01old";};
};

class DFS10 : public NMvector {
public:
    string to_string() override {return "DFS01";};
};

