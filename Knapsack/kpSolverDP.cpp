#include "kpSolverDP.hpp"

string tostring(MatDPType _type){
    string s("");
        switch(_type){
        case MatDPType::MatDPvectVect:
            s= "MatDPvectVect"; break;
        case MatDPType::MatDPvect :
            s= "MatDPvect";break;
        case MatDPType::MatDPtabTab:
            s= "MatDPtabTab"; break;
        case MatDPType::MatDPtab :
            s= "MatDPtab";
    }
     return s;
}

void KpSolverDP::printMatrixDP()
{
    _matDP->display();
}

KpSolverDP::KpSolverDP(std::string const & filename,  MatDPType type //= MatDPType::MatDPvect
                       ) : KpSolver(filename) , _type(type){
    switch(_type){

    case MatDPType::MatDPvectVect:
        _matDP = std::make_unique<MatDPvectVect>(nbItems, knapsackBound+1);
                break;
    case MatDPType::MatDPvect :
        _matDP = std::make_unique<MatDPvect>(nbItems, knapsackBound+1);
        break;
    case MatDPType::MatDPtabTab:
        _matDP = std::make_unique<MatDPtabTab>(nbItems, knapsackBound+1);
        break;
    case MatDPType::MatDPtab :
        _matDP= std::make_unique<MatDPtab>(nbItems, knapsackBound+1);
        break;
}
}

void KpSolverDP::backtrack(){
    solution.clear();
    solution.resize(nbItems, false);
    uint m = knapsackBound;
    for (uint i(nbItems-1); i >=1 ; i--){
        if (_matDP->getElement(i-1,m) != _matDP->getElement(i,m)){
            solution[i]=true;
            m -= weights[i];
            if (m==0) return;
        }
    }
    if (m >= weights[0]) solution[0]=true;
}


void KpSolverDPv0::solve(){
    _matDP->fillFirstLineDP(values[0], weights[0]);
    for(uint i(1); i < nbItems; i++) {
        _matDP->createLineDP(i);
        for (uint m(1); m < knapsackBound+1; m++) {
			(*_matDP)[i][m] = (*_matDP)[i-1][m];
            if (m >= weights[i] && ((*_matDP)[i][m] < (*_matDP)[i-1][m-weights[i]] + values[i])) {
                (*_matDP)[i][m] = (*_matDP)[i-1][m-weights[i]] + values[i];
			}
		}
	}
	costSolution = (*_matDP)[nbItems-1][knapsackBound];
    upperBoundOPT=static_cast<double>(costSolution);
	KpSolverDP::backtrack();
}

void KpSolverDPv1::solve(){
    _matDP->fillFirstLineDP(values[0], weights[0]);
    for(uint i(1); i < nbItems; i++) {
        _matDP->createLineDP(i);
        for (uint m(1); m < knapsackBound+1; m++) {
			_matDP->setElement(i,m,_matDP->getElement(i-1,m));
            if (m >= weights[i] && _matDP->getElement(i,m) < _matDP->getElement(i-1,m-weights[i]) + values[i]) {
                _matDP->setElement( i,m, _matDP->getElement(i-1,m-weights[i]) + values[i]);
			}
		}
	}
	costSolution = _matDP->getElement(nbItems-1,knapsackBound);
    upperBoundOPT=static_cast<double>(costSolution);
	KpSolverDP::backtrack();
}

void KpSolverDPv1bis::solve(){
    _matDP->fillFirstLineDP(values[0], weights[0]);


    //calcul de borne inferieure de case DP a calculer
    vector<uint> lowerBoundId (nbItems,1);
    lowerBoundId[nbItems-1]=knapsackBound;

    for(uint i(nbItems-2); i > 0 ; i--) {
        if (lowerBoundId[i+1] >= weights[i+1] )
        lowerBoundId[i]= lowerBoundId[i+1] - weights[i+1];
        else lowerBoundId[i] =1;
        //cout << "valeur borne id : " << i << " : " << lowerBoundId[i] << endl;
        if (lowerBoundId[i] ==1 )        break;
    }

    for(uint i(1); i < nbItems; i++) {
        _matDP->createLineDP(i);
        for (uint m(lowerBoundId[i]); m < knapsackBound+1; m++) {
            _matDP->setElement(i,m,_matDP->getElement(i-1,m));
            if (m >= weights[i] && _matDP->getElement(i,m) < _matDP->getElement(i-1,m-weights[i]) + values[i]) {
                _matDP->setElement( i,m, _matDP->getElement(i-1,m-weights[i]) + values[i]);
            }
        }
    }
    costSolution = _matDP->getElement(nbItems-1,knapsackBound);
    upperBoundOPT=static_cast<double>(costSolution);
    KpSolverDP::backtrack();
}


void KpSolverDPv2::solve(){
     _matDP->fillFirstLineDP(values[0], weights[0]);
    for (uint n(1); n <= nbItems - 1; ++n)
	{
            _matDP->computeLineDP(n, values[n], weights[n]);
	}
    costSolution = _matDP->getElement(nbItems-1,knapsackBound);
    upperBoundOPT=static_cast<double>(costSolution);
    KpSolverDP::backtrack();
}

