//********* nodeBB.cpp *********

#include "nodeBB.hpp"
//#include <iostream>
//#include <fstream>

bool NodeBB::canBeRemoved() {
	return overCapacitated;
}

void NodeBB::init(int size){
	overCapacitated= false;

	isFixed.resize(size);
	isRemoved.resize(size);

/*
remarque: inutile car resize affecte des false par defaut, c'est bien ce qu'on veut comme initialisation
	for(int i=0; i<size;i++){
		isFixed[i] =false;
		isRemoved[i] =false;
	}
*/
    criticalIndex=-1;
    fractionalVariable=0;
    localLowerBound=0;
}

void NodeBB::primalHeuristic(int kpBound, int nbItems, vector<int> & weights,  vector<int> & values) {

	primalSolution.resize(nbItems);
    for (int i = 0; i < nbItems; i++)  primalSolution[i]=false;

    localLowerBound=0;
	int remaining = kpBound;

	for (int i=0 ; i < nbItems; ++i)
		if (isFixed[i]) {
			localLowerBound += values[i];
			remaining -= weights[i];
			primalSolution[i]=true;
		}

	for (int i = 0; i < nbItems; i++){
    	//cout << " Item: " << i << " Weight : " << weights[i]  << " Value : " << values[i] << " remaining : "<< remaining << endl;
		if (weights[i] <= remaining && !isFixed[i] && !isRemoved[i]){
			remaining -= weights[i];
			localLowerBound += values[i];
			primalSolution[i]=true;
			//cout << " Item: " << i << " is selected"  << endl;
		}
	}
 }

//V0: on recalcule tout, tant pis
//TODO: version optimisée ou on utilise le précedent
void NodeBB::solveUpperBound(int kpBound, int nbItems, vector<int> & weights,  vector<int> & values) {
	localUpperBound=0;
    float remaining = kpBound;
    int id = 0;
    bool b = true;


	for (int i=0 ; i < nbItems; ++i)
		if (isFixed[i]) {
			localUpperBound += values[i];
			remaining -= weights[i];
		}
	 criticalIndex =nbItems;
	 fractionalVariable=0;

	 if (remaining <0) {
		 overCapacitated = true;
		 return;
	 }

    while(b &&remaining >0 && id < nbItems){
    	//cout << " Item: " << id << " Weight : " << weights[id]  << " Value : " << values[id] << " remaining : "<< remaining << endl;
    	if (weights[id] <= remaining && !isFixed[id] && !isRemoved[id]) {
    		remaining -= weights[id];
    		localUpperBound += values[id];
    		id++;
    	}
    	else if (isFixed[id] || isRemoved[id]) {
    		id++;
    	}
    	else {
    		b = false;
    		criticalIndex =id;
    		fractionalVariable = ((float) values[id])  * remaining /  ((float) weights[id]);
    		localUpperBound += fractionalVariable;
    	}
	}
 }


void NodeBB::updateAfterbranching0(int id) {
	isRemoved[id]=true;

}

void NodeBB::updateAfterbranching1(NodeBB *nod, int id) {
	isFixed.clear();
	isFixed=nod->isFixed;
	isRemoved.clear();
	isRemoved=nod->isRemoved;
	isFixed[id]=true;
	localUpperBound = nod->getNodeUpperBound();
}
