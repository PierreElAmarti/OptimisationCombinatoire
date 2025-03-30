#include "kpSolverGreedy.hpp"
#include "kpSolverBB.hpp"
#include <chrono>
#include <string>
#include <sstream>

using namespace std;

std::string name(BranchingStrategies b);

BranchingStrategies& operator ++ (BranchingStrategies& e)
{
    if (e == BranchingStrategies::End) {
        throw std::out_of_range("for E& operator ++ (E&)");
    }
    e = BranchingStrategies(static_cast<std::underlying_type<BranchingStrategies>::type>(e) + 1);
    return e;
}

std::string printModeBranching(BranchingStrategies  b){
	std::cout<<name(b);
    return name(b);
}

std::string name(  BranchingStrategies b){
    switch (b) {
	        case BestBound: return "BestBound"; break;
	        case BFS: return"BFS";  break;
	        case DFS10: return "DFS10"; break;
	        case DFS01: return "DFS01"; break;
	        case Random: return"Random";
	                break;              //execution of subsequent statements is terminated
	        case End: return "err";
	}
}

std::string printResultmodeBranching(KpSolverBB & kpBB, BranchingStrategies  b){
    std::stringstream ss;
	cout  << endl << "         BB mode Branchement ";
	std::string s=printModeBranching(b);
    ss<<s<<";";
	cout << endl << endl;

	kpBB.setBranchingStrategy(b);

	auto start = std::chrono::steady_clock::now();
	kpBB.solve();
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double>  elapsed_seconds = end-start;
	std::cout << endl  << "elapsed time: " << elapsed_seconds.count() << "s" << endl;
    ss<<elapsed_seconds.count()<<";";
	ss<<kpBB.printKnapsackSolution(false);

    return ss.str();

}


int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: knapsack inputFile [heuristicMode] [verbosity]" << endl;
        cerr << "Usage: a heuristic/exactMode implies comparisons of exact methods (for small instances), whereas no parameter implies heuristic search" << endl;
        cerr << "A third parameter enable verbosity, useful for debugging" << endl;
        return 1;
    }

    bool verboseMode = true;
    if (argc < 3) verboseMode = false;
    const char* instanceFile = argv[1];
    const char *outputFile= argv[2];;


    ofstream fichier;
    fichier.open(outputFile, std::ios_base::app); // ouverture du fichier en mode app https://stackoverflow.com/questions/61895932/how-to-append-to-a-file-in-c
    

    KpSolverGreedy kpGreedy;
    kpGreedy.importInstance(instanceFile);
    //kpGreedy.extractSubInstance(0,1000);

    if (verboseMode) kpGreedy.printKnapsackInstance();

    fichier<<instanceFile<<";";
    fichier<<"Greedy Bounds;;";
    cout  << endl << "Greedy bounds :"  << endl << endl;
    auto start = std::chrono::steady_clock::now();
    kpGreedy.solve();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << endl<< endl;
    fichier<<elapsed_seconds.count()<<";";
    std::string s=kpGreedy.printKnapsackSolution(false);
    fichier<<s<<"\n";

    KpSolverBB kpBB;
	kpBB.importInstance(instanceFile);
	kpBB.setVerboseMode(verboseMode);
	kpBB.setNbMaxNodeBb(10000);
	kpBB.setSizeDPheur(100);
	kpBB.setWithPrimalHeuristics(false);
	kpBB.setWithDPinitPrimalHeuristic(false);

/* */
    cout  << endl << "Resultats sans heuristique gloutonne:"  << endl << endl;

    for ( BranchingStrategies modeBranch = BranchingStrategies::BestBound; modeBranch != BranchingStrategies::End; ++modeBranch){
        fichier<<instanceFile<<";";
        fichier<<"sans heuristique gloutonne"<<";";
    	fichier<<printResultmodeBranching(kpBB,modeBranch);
        fichier<<"\n";

    }

    cout  << endl << "Resultats avec heuristique gloutonne:"  << endl << endl;

	kpBB.setWithPrimalHeuristics(true);

    for ( BranchingStrategies modeBranch = BranchingStrategies::BestBound; modeBranch != BranchingStrategies::End; ++modeBranch){
    	fichier<<instanceFile<<";";
        fichier<<"avec heuristique gloutonne"<<";";
    	fichier<<printResultmodeBranching(kpBB,modeBranch);
        fichier<<"\n";

    }

    cout  << endl << "Resultats avec heuristique prog dynamique:"  << endl << endl;

    kpBB.setWithDPinitPrimalHeuristic(true);

    for ( BranchingStrategies modeBranch = BranchingStrategies::BestBound; modeBranch != BranchingStrategies::End; ++modeBranch){
    	fichier<<instanceFile<<";";
        fichier<<"sans heuristique prog dynamique"<<";";
    	fichier<<printResultmodeBranching(kpBB,modeBranch);
        fichier<<"\n";

    }

    return 0;

}
