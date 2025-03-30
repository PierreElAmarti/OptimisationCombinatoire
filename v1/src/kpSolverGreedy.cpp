//********* knapsackGreedy.cpp *********

#include "kpSolverGreedy.hpp"


void KpSolverGreedy::solveUpperBound() {

	upperBoundOPT=0;
    float remaining = knapsackBound;
    int id = 0;
    bool b = true;

    while(b &&remaining >0 && id < nbItems){
    	//cout << " Item: " << id << " Weight : " << weights[id]  << " Value : " << values[id] << " remaining : "<< remaining << endl;
    	if (weights[id] <= remaining) {
    		remaining -= weights[id];
    		upperBoundOPT += values[id];
    		id++;
    	}
    	else b = false;

	}

    if (id< nbItems && (!b)) upperBoundOPT += ((float) values[id])  * remaining /  ((float) weights[id]);

    //if (id< nbItems)  cout << " additional cost : " << ((float) values[id])  * remaining /  ((float) weights[id]) << endl;

 }

void KpSolverGreedy::solveLowerBound() {

    solution.resize(nbItems);
    for (int i = 0; i < nbItems; i++)  solution[i]=false;

	costSolution=0;
	int remaining = knapsackBound;

	for (int i = 0; i < nbItems; i++){
    	//cout << " Item: " << i << " Weight : " << weights[i]  << " Value : " << values[i] << " remaining : "<< remaining << endl;
		if (weights[i] <= remaining){
			remaining -= weights[i];
			costSolution += values[i];
			solution[i]=true;
			//cout << " Item: " << i << " is selected"  << endl;
		}
	}
 }

void KpSolverGreedy::solve() {
	solveUpperBound();
	solveLowerBound();
}
