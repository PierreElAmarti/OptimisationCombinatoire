#include "nodeManagement.hpp"


void NodeManagement::insertNodes(NodeBB* nod1, NodeBB* nod2)
{
    insertNode(nod1);
    insertNode(nod2);
}

NMdeque::~NMdeque()
{
    for (auto it : nodes)  delete it;
    nodes.clear();
}

double NMdeque::getUpperBound()
{
    //TODO: if (isEmpty()) ... sinon erreur si vide
    double upperBoundOPT = nodes.front()->getNodeUpperBound();
    for (std::deque<NodeBB*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
        upperBoundOPT = max(upperBoundOPT, (*it)->getNodeUpperBound());
    return upperBoundOPT;
}

NodeBB* NMdeque::selectNode()
{
    NodeBB* node = nodes.back();
    nodes.pop_back();
    return node;
}

NMvector::~NMvector()
{
    for (auto it : nodes)  delete it;
    nodes.clear();
}

double NMvector::getUpperBound()
{
    //TODO: if (isEmpty()) ... sinon erreur si vide

    double upperBoundOPT = nodes.back()->getNodeUpperBound();
    for (auto it : nodes)
        upperBoundOPT = max(upperBoundOPT, it->getNodeUpperBound());
    return upperBoundOPT;
}

NodeBB* NMvector::selectNode()
{
    NodeBB* node = nodes.back();
    nodes.pop_back();
    return node;
}


/* ============================================ */
/* RANDOM STRATEGY */
/* ============================================ */
NodeBB* RandomOld::selectNode()
{
    srand(time(NULL));
    size_t n = nodes.size();
    size_t id = rand() % n;
    /*
    swap(nodes[0], nodes[id]);
    NodeBB* node = nodes.front();
    nodes.pop_front();*/
    swap(nodes[nodes.size()-1], nodes[id]);
    NodeBB* node = nodes.back();
    nodes.pop_back();

    return node;
}

NodeBB* Random::selectNode()
{
    srand(time(NULL));
    size_t n = nodes.size();
    size_t id = rand() % n;
    swap(nodes[nodes.size()-1], nodes[id]);
    NodeBB* node = nodes.back();
    nodes.pop_back();
    return node;
}




/* ============================================ */
/* BFS Strategy */
/* ============================================ */


/* ============================================ */
/* BESTBOUND STRATEGY */
/* ============================================ */

void BestBoundOld::insertNode(NodeBB* nod)
{
    nodes.push_back(nod);
    sort(nodes.begin(), nodes.end(), [](NodeBB* i, NodeBB* j) { return i->getNodeUpperBound() < j->getNodeUpperBound(); });

}

void BestBoundOld::insertNodes(NodeBB* nod1, NodeBB* nod2)
{
    nodes.push_back(nod1);
    nodes.push_back(nod2);
    sort(nodes.begin(), nodes.end(), [](NodeBB* i, NodeBB* j) { return i->getNodeUpperBound() < j->getNodeUpperBound(); });

}

void BestBoundDeque::insertNode(NodeBB* nod)
{
    //TODO
    cout << "WARNING BestBoundDeque::insertNode not coded " <<endl;

}

void BestBoundVector::insertNode(NodeBB* nod)
{
    //NodeBB* nodBefore = nodes.back();
    nodes.push_back(nod);
    auto val = nod->getNodeUpperBound();
    if (nodes.size()<2) return;
    for (size_t i(nodes.size()-1) ; i>0 ; i--){
        if (nodes[i-1]->getNodeUpperBound() <= val) return;
        swap(nodes[i-1], nodes[i]);
    }
}





/* ============================================ */
/* DFS10 STRATEGY */
/* ============================================ */



/* ============================================ */
/* DFS01 STRATEGY */
/* ============================================ */

void DFS01old::insertNodes(NodeBB* nod1, NodeBB* nod2)
{
    insertNode(nod2);
    insertNode(nod1);
}

void DFS01::insertNodes(NodeBB* nod1, NodeBB* nod2)
{
    insertNode(nod2);
    insertNode(nod1);
}
