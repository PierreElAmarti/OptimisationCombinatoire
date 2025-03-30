//********* kpSolverBB.cpp *********

#include "kpSolverBB.hpp"
#include "kpSolverDP.hpp"
#include <math.h>
#include <stdlib.h>
#include <time.h>


double KpSolverBB::getUpperBound() {
	upperBoundOPT=costSolution;
	for (std::deque<NodeBB*>::iterator it = nodes.begin() ; it != nodes.end(); ++it)
		upperBoundOPT=max(upperBoundOPT,(*it)->getNodeUpperBound());
	return upperBoundOPT;
}


void KpSolverBB::printStatus() {
	getUpperBound();
	cout  << "nbNodes: " << nbNodes;
	cout  << " remaining Nodes: " << nodes.size();
	cout  << " LB: " << costSolution;
	cout  << " UB: " << upperBoundOPT;
	cout << " gap : " << (floor(upperBoundOPT)- (double)costSolution) /( (double)costSolution) * 100 << "%" << endl;
/*
	cout  << "nodes UB: ";
	for (std::deque<NodeBB*>::iterator it = nodes.begin() ; it != nodes.end(); ++it)
		cout  << (*it)->getNodeUpperBound() << " ";
	cout  << endl;
*/
}


void KpSolverBB::init() {
    nbNodes= 0;
    //nbMaxNodeBB= -1;
    //withPrimalHeuristics = primalHeuristics;
    nodes.clear();
    NodeBB* node0 = new NodeBB();
    node0->init(nbItems);
    node0->solveUpperBound(knapsackBound, nbItems, weights, values);
    if (withPrimalHeuristics) {
    	node0->primalHeuristic(knapsackBound, nbItems, weights, values);
    	costSolution=node0->getNodePrimalBound();
    	node0->copyPrimalSolution(&solution);
    }
    else {
    	costSolution=0;
    	solution.resize(nbItems);
    	for (int i = 0; i < nbItems; i++) solution[i]=false;
    }

    nodes.push_back(node0);

    if(!withDPinitPrimalHeuristic) return;

    int lastIndex = node0->getCriticalIndex();
    int nbUnselectedReopt = sizeDPheur/2;
    int nbSelectedReopt = sizeDPheur/2;
	int idMax=min(nbItems-1,lastIndex + nbUnselectedReopt);
	int idMin= max(0,lastIndex - nbSelectedReopt);
	int i;

	//extraire vecteurs poids et prix correspodnant

	vector<int>  subWeights;
	vector<int>  subValues;

	for (i=idMin; i <= idMax; i++){
		subWeights.push_back(weights[i]);
		subValues.push_back(values[i]);
	}

	int  fixedBound = 0;
	int  fixedCost = 0;

	solution.clear();
	solution.resize(nbItems);

	for (i=0; i < idMin; i++){
		fixedBound += weights[i];
		fixedCost += values[i];
		solution.push_back(true);
	}

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

NodeBB* KpSolverBB::selectNodeRandom() {

	  srand (time(NULL));

	  int n = nodes.size() ;
	  int id= rand() % n ;

	  swap(nodes[0],nodes[id]);

	NodeBB* node = nodes.front();
	nodes.pop_front();
	return node;

}

NodeBB* KpSolverBB::selectNode() {

	if(branchingStrategy == Random) return selectNodeRandom();

	if(branchingStrategy == BestBound){
	std::sort(nodes.begin(), nodes.end(),
			[](NodeBB* i, NodeBB* j) {return i->getNodeUpperBound() < j->getNodeUpperBound();}
	);
	}

	if(branchingStrategy == BFS){
		NodeBB* node = nodes.front();
		nodes.pop_front();
		return node;
	}

	NodeBB* nod = nodes.back();
	nodes.pop_back();
	return nod;
}

void KpSolverBB::insertNode(NodeBB *nod) {


	if ((nod->canBeRemoved()) || nod->getNodeUpperBound()<costSolution + 1) {
		delete nod;
	}
	else nodes.push_back(nod);
}

void KpSolverBB::insertNodes(NodeBB *nod1, NodeBB *nod2) {

	if(branchingStrategy == DFS01) {
		insertNode(nod1);
		insertNode(nod2);
	}
	else {
		insertNode(nod2);
		insertNode(nod1);
	}
}



//premiere version naive sans ameliorations avec recalculs
void KpSolverBB::solve() {
	nbNodes = 0;
	NodeBB *nod;
	NodeBB *nod1;
	int id;

	init();
	//TODO: heuristique initiale

	//printStatus(0);


	while ((nbMaxNodeBB <0 || nbNodes < nbMaxNodeBB ) && !(nodes.empty())) {
		nbNodes++;
		nod = selectNode();

		//un calcul heuristique si necessaire et parametre

		if ( withPrimalHeuristics &&  nod->getFractionalVariable()>0.0000001 && nod->getNodeUpperBound()>=costSolution + 1) {
			nod->primalHeuristic(knapsackBound, nbItems, weights, values);
			if (costSolution < nod->getNodePrimalBound()){
				costSolution=nod->getNodePrimalBound();
				nod->copyPrimalSolution(&solution);

			}

		};

		//cas 1: le probleme est plus toujours realisable, une valeur fractionnaire et relaxation continue permettrait d'ameliorer, on branche:
		if (!(nod->canBeRemoved()) && nod->getFractionalVariable()>0.0000001 && nod->getNodeUpperBound()>=costSolution + 1) {
			//branchements
			id = nod->getCriticalIndex();
			//cout  << "on branche sur l'indice "<<id<< " ancienne  borne "<< nod->getNodeUpperBound()<< endl;
			nod1 = new NodeBB();
			nod1->init(nbItems);
			nod1->updateAfterbranching1(nod,id);
			nod1->solveUpperBound(knapsackBound, nbItems, weights, values);
			nod->updateAfterbranching0(id);
			nod->solveUpperBound(knapsackBound, nbItems, weights, values);
			//cout  << "Nouveaux noeuds de bornes "<< nod->getNodeUpperBound()<< " et "<< nod1->getNodeUpperBound()<< endl;
			insertNodes(nod,nod1);
			if (verboseMode) printStatus();
			continue;
		};

		//cas 2: une solution entière a été trouvée, et améliore la meileure solution courante:
		if (!(nod->canBeRemoved()) && nod->getFractionalVariable()<0.0000001 && nod->getNodeUpperBound()>costSolution + 0.99999) {
			nod->primalHeuristic(knapsackBound, nbItems, weights, values);
			costSolution=nod->getNodePrimalBound();
			nod->copyPrimalSolution(&solution);
			//removeNodes();
		};

		//on suppprime le noeud courant
		delete nod;

		if (verboseMode) printStatus();
		}

	if (!verboseMode) printStatus();

	if (nodes.empty()) {
		upperBoundOPT = costSolution;
		//return;
	}
	else{
	upperBoundOPT = getUpperBound();
	for (auto n : nodes) delete n;
	nodes.clear();

	}

}

/*
void KpSolverBB::removeNodes(){
	for (std::deque<NodeBB*>::iterator it =  (nodes.end()--) ; it != (nodes.begin()--); --it)
		if ((*it)->getNodeUpperBound()<costSolution + 1) nodes.erase(it);
}
*/

/*
void KpSolverBB::insertNodesBestBound(NodeBB *nod1, NodeBB *nod2) {
	if (!(nod1->canBeRemoved()) && nod1->getNodeUpperBound()>costSolution + 0.99999)  nodes.push_front(nod1);
		else delete nod1;
	if (!(nod2->canBeRemoved()) && nod2->getNodeUpperBound()>costSolution + 0.99999)  nodes.push_front(nod2);
		else delete nod2;

	std::sort(nodes.begin(), nodes.end(),
			[](NodeBB* i, NodeBB* j) {return i->getNodeUpperBound() > j->getNodeUpperBound();}
	);
}

void KpSolverBB::insertNodesBFS(NodeBB *nod1, NodeBB *nod2) {
	if (!(nod1->canBeRemoved()) && nod1->getNodeUpperBound()>costSolution + 0.99999)  nodes.push_back(nod1);
		else delete nod1;
	if (!(nod2->canBeRemoved()) && nod2->getNodeUpperBound()>costSolution + 0.99999)  nodes.push_back(nod2);
		else delete nod2;
}

void KpSolverBB::insertNodesDFS(NodeBB *nod1, NodeBB *nod2) {
	if (!(nod1->canBeRemoved()) && nod1->getNodeUpperBound()>costSolution + 0.99999)  nodes.push_front(nod1);
		else delete nod1;
	if (!(nod2->canBeRemoved()) && nod2->getNodeUpperBound()>costSolution + 0.99999)  nodes.push_front(nod2);
		else delete nod2;
}
*/

