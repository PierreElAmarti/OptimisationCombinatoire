//********* nodeBB.cpp *********

#include "nodeBB.hpp"
#include <math.h>
//#include <iostream>
//#include <fstream>

/*
bool NodeBB::canBeRemoved() {
	return overCapacitated;
}*/

T NodeBB::getLocalUpperBoundInt() const
{
    return localUpperBoundInt;
}



NodeBB::NodeBB(KpSolverGreedy * instance, const std::pair <std::pair <uint,uint>,T> & p):
    criticalIndex(p.first.first), remainingToInt(p.first.second),fixedWeight(0),localUpperBoundInt(p.second),fixedValue(0),solver(instance) {
//    fixedWeight= 0;
    uint size = instance->getNbItems();
	isFixed.resize(size);
	isRemoved.resize(size);

}
//V0: on recalcule tout, tant pis
// node suppose realisable, contrainte deja verifiee
void NodeBB::solveUpperBound() {
    uint nbItems(solver->getNbItems());

    /*
    // en cas de depassement, UB=0, alors BB detruit le noeud
    if (solver->getKnapsackBound() < fixedWeight) {
        localUpperBoundInt = 0;
        remainingToInt=0;
        return;
    }*/

    localUpperBoundInt= fixedValue;
    remainingToInt =  solver->getKnapsackBound() - fixedWeight;
    criticalIndex = 0;

    while( criticalIndex < nbItems){
        if (isFixed[criticalIndex] || isRemoved[criticalIndex]) {
            criticalIndex++ ;
            continue;
        };
        uint w( solver->getWeight(criticalIndex));
        if (w > remainingToInt ) return;
            remainingToInt -= w;
            localUpperBoundInt += solver->getValue(criticalIndex);
            criticalIndex++;
	}
    remainingToInt=0;
    //criticalIndex =nbItems;

 }


void NodeBB::fixVariable1()
{
       isFixed[criticalIndex]=true;
       fixedWeight += solver->getWeight(criticalIndex);
       fixedValue += solver->getValue(criticalIndex);
       }

double NodeBB::getNodeUpperBound() const
{
    double d(static_cast<double>(localUpperBoundInt));
    if (remainingToInt>0) d+= static_cast<double>(solver->getValue(criticalIndex)*remainingToInt)
            /  (static_cast<double>(solver->getWeight(criticalIndex)));
    return d;
}

void NodeBB::printNode()
{
    cout << "impression node courant:" << endl;
    cout << "items imposes : " ;
    for (uint i(0); i<isFixed.size(); i++ )
        if (isFixed[i]) cout << i << " " ;
    cout << endl;
    cout << "items eneleves : " ;
    for (uint i(0); i<isRemoved.size(); i++ )
        if (isRemoved[i]) cout << i << " " ;
    cout << endl;
    cout << "fixedValue: " << fixedValue   << endl;
    cout << "localUpperBoundInt: " << localUpperBoundInt   << endl;
    cout << "fixedWeight: " << fixedWeight   << endl;
    cout << "remainingToInt: " << remainingToInt   << endl;
    cout << "criticalIndex: " << criticalIndex   << endl;
    cout << "NodeUpperBound: " << getNodeUpperBound()   << endl;


}



void NodeBB::recoverPrimalSolution()
{
    //if (fractionalVariable> epsilon) return;
    vector<bool> primalSolution(isFixed);
    //primalSolution.reserve(nbItems);
    //primalSolution=isFixed;

    for (uint i = 0; i < criticalIndex; i++){
        //cout << " Item: " << i << " Weight : " << weights[i]  << " Value : " << values[i] << " remaining : "<< remaining << endl;
        if (!isFixed[i] && !isRemoved[i])   primalSolution[i]=true;
     }
    //T cost(localUpperBoundInt)));
    solver->importSolution(primalSolution,localUpperBoundInt);

}
