//********* knapsackheurDP.cpp *********

#include "kpSolverHeurDP.hpp"
#include "kpSolverDP.hpp"

//#include <algorithm>



void KpSolverHeurDP::solveUpperBound() {

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

    lastIndex =id;
    if (id< nbItems-1 && (!b) &&remaining >0) lastIndex = id+1;

    //cout << "middle and decisive index : " << lastIndex << endl;


    if (id< nbItems && (!b)) upperBoundOPT += ((float) values[id])  * remaining /  ((float) weights[id]);

    //if (id< nbItems)  cout << " additional cost : " << ((float) values[id])  * remaining /  ((float) weights[id]) << endl;

 }

void KpSolverHeurDP::solve() {

	solveUpperBound();


	//extraire indice extremes de opt locale

	int idMax=min(nbItems-1,lastIndex + nbUnselectedReopt);
	int idMin= max(0,lastIndex - nbSelectedReopt);
	int i;

    //cout << "neighborhood defined by indexes : " << idMin << "  " << idMax << endl;

	//extraire vecteurs poids et prix correspodnant

	vector<int>  subWeights;
	vector<int>  subValues;

	for (i=idMin; i <= idMax; i++){
		subWeights.push_back(weights[i]);
		subValues.push_back(values[i]);
	}

	/*
	for (std::vector<int>::iterator it = subWeights.begin() ; it != subWeights.end(); ++it)
	    std::cout << ' ' << *it;
    std::cout << endl;
	for (std::vector<int>::iterator it2 = subValues.begin() ; it2 != subValues.end(); ++it2)
		    std::cout << ' ' << *it2;
    std::cout << endl;
    */

	int  fixedBound = 0;
	int  fixedCost = 0;

	solution.clear();
	solution.resize(nbItems);

	for (i=0; i < idMin; i++){
		fixedBound += weights[i];
		fixedCost += values[i];
		solution.push_back(true);
		//cout << "selection of item " << i << endl;
	}

	//cout << "knapsack neighborhood fixing cost " << fixedCost << endl;
	//cout << "knapsack neighborhood fixing weight " << fixedBound << endl;

	// definir sous pb de sac a dos et resoudre
	KpSolverDP kp;
	kp.updateKpSolverDP(subWeights, subValues,  knapsackBound - fixedBound);
	kp.solve();

	// se ramener aux solutions du probleme initial

	costSolution = kp.getSolutionCost() + fixedCost;

	for (i=idMin; i <= idMax; i++){
		solution.push_back(kp.isSelected(i-idMin));
	}
	for (i=idMax+1; i < nbItems; i++){
		solution.push_back(false);
	}

}

void KpSolverHeurDP::setNeighborhood(int nbSelectedOpt, int nbUnselectedOpt) {
	nbUnselectedReopt = nbUnselectedOpt;
	nbSelectedReopt = nbSelectedOpt;
}
