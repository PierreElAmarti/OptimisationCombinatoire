//********* kpSolverBB.cpp *********

#include "kpSolverBB.hpp"
#include <math.h>
#include <stdlib.h>

double KpSolverBB::getUpperBound() {
    if (!nodes->isEmpty()) upperBoundOPT=nodes->getUpperBound();
    return upperBoundOPT;
}

void KpSolverBB::printStatus() {
    cout  << "nbNodes: " << nbNodes;
    cout  << " remaining Nodes: " << nodes->nbNodes();
	cout  << " LB: " << costSolution;
    cout  << " UB: " << getUpperBound();
    cout  << " rUB: " << static_cast<T>(floor(upperBoundOPT));
    cout << " gap : " << (floor(upperBoundOPT)- static_cast<double>(costSolution)) /( static_cast<double>(costSolution) * 0.01) << "%" << endl;
}


void KpSolverBB::init() {

    std::pair<std::pair<uint, uint>, T> p(solveGreedyUpperBound());
    uint i(p.first.first);
    upperBoundOPT = static_cast<double>(p.second) +
    static_cast<double>(values[i]*p.first.second)   /  (static_cast<double>(weights[i]));


    if(heurParams.heurRootNode==Heuristics::Greedy)
        solveGreedyLowerBound ();
    if(heurParams.heurRootNode==Heuristics::KernelSearch)
        solveLowerBound(p.first.first);

    nbNodes= 1;
    nodes->clear();
    if(static_cast<T>(floor(upperBoundOPT))- costSolution >= 1)
        nodes->insertNode(new NodeBB(this,p));
}

bool KpSolverBB::continueBB(size_t nbNod, size_t nbNodMem)
{
    if (nodes->isEmpty()) return false;
    /*
    for(auto s : bbParams.term)
        if (!s->continueBB(nbNod,  nbNodMem)) return false;
    return true;
    */
    for(size_t i(0); i< bbParams.term.size(); i++)
        if (bbParams.term[i]->continueBB(nbNod,  nbNodMem)) return false;
    return true;

}


void KpSolverBB::solve()
{
    init();
    NodeBB *nod;
    NodeBB *nod1;
    //if (bbParams.verboseMode==1)
     printStatus();


    while ( continueBB(nodes->nbNodes(),nbNodes)){

        if (bbParams.verboseMode>1) printStatus();
        nod = nodes->selectNode();


        if (nbNodes>1)
            nod->solveUpperBound();



        //pas necessaire, operation apres, pour unqiuement si amelioration de col entiere entre temps, peut probable avec sol initiale
        if (nod->isNotOptimal())   {delete nod;         nbNodes++; continue; };

        //si on a une solution entiere
        if (nod->isIntegral()){
            if (nod->getLocalUpperBoundInt()>=costSolution + 1 ){
            costSolution=nod->getLocalUpperBoundInt();
            nod->recoverPrimalSolution();
            if (bbParams.verboseMode==1) printStatus();
            if (isOptimal()) {
                if (bbParams.verboseMode>1) printStatus();
                nodes->clear();
            }

            };

            delete nod;
            nbNodes++;
            continue;
        }


        //if (bbParams.verboseMode>1) printStatus();
        nbNodes++;


        //if (nod->isNotOptimal())   {delete nod;  continue; };

        //on a une sol fractionnaire non coupee

            //uint id(nod->getCriticalIndex());
            //cout  << "on branche sur l'indice "<<id<< " ancienne  borne "<< nod->getNodeUpperBound()<< endl;
            nod1 = new NodeBB(*nod);
            nod1->fixVariable1();
            nod->fixVariable0();

            //cout  << "Nouveaux noeuds de bornes "<< nod->getNodeUpperBound()<< " et "<< nod1->getNodeUpperBound()<< endl;
            if ( nod1->getfixedWeight()<=knapsackBound)
                nodes->insertNodes(nod,nod1);
           else {nodes->insertNode(nod); delete nod1;};
            };



    if (nodes->isEmpty()) upperBoundOPT = static_cast<double>(costSolution);
    else {
        getUpperBound();
        nodes->clear();
    };
        

}



