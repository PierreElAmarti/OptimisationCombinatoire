#include "kpSolverHeurDP.hpp"
#include <chrono>
#include <sstream>

using namespace std;

std::string testSolver(KpSolver *kp, bool verboseMode = false)
{
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::stringstream ss;
    std::string s = "";
    // if (verboseMode) kp.printKnapsackInstance();

    start = std::chrono::steady_clock::now();
    kp->solve();
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "elapseed time: " << elapsed_seconds.count() << "s" << endl;

    s = kp->printKnapsackSolution(verboseMode, s);
    ss << s << elapsed_seconds.count() << "\n";

    return ss.str();
}

int main(int argc, char **argv)
{

    const char *instanceFile;
    const char *outputFile;
    string cheminDefaut = "../instances/courseExample.in";
    // cheminDefaut ="../instances/kp_1000_2.in";
    cheminDefaut = "../instances/kp_10000_2.in";

    if (argc < 3)
    {
        // cerr << "Usage: knapsack inputFile [heuristicMode] [verbosity]" << endl;
        // cerr << "Usage: a heuristic/exactMode implies comparisons of exact methods (for small instances), whereas no parameter implies heuristic search" << endl;
        // cerr << "A third parameter enable verbosity, useful for debugging" << endl;
        // return 1;

        instanceFile = cheminDefaut.c_str();
        outputFile = "../resultats/default.txt";
    }
    else
    {
        instanceFile = argv[1];

        outputFile = argv[2];
    }

    // bool verboseMode = true;
    // if (argc < 3) verboseMode = false;
    /*
        cout << "______________________________" <<endl
             << "Instance :" << cheminDefaut << endl
             << "______________________________" << endl;
    */

    ofstream fichier;
    fichier.open(outputFile, std::ios_base::app); // ouverture du fichier en mode app https://stackoverflow.com/questions/61895932/how-to-append-to-a-file-in-c

    KpSolver *kp;

    cout << "\ntest KpSolverGreedy :" << endl;
    fichier <<instanceFile<<";";
    fichier << "test KpSolverGreedy"<< ";";
    kp = new KpSolverGreedy(instanceFile);
    fichier<<testSolver(kp);
    delete kp;

    cout << "\ntest KpSolverHeurDP (10,20):" << endl;
    fichier <<instanceFile<<";";
    fichier << "test KpSolverHeurDP"<< ";";
    kp = new KpSolverHeurDP(instanceFile, 10, 20);
    fichier<<testSolver(kp);
    delete kp;

    cout << "\ntest KpSolverHeurDP (50,50):" << endl;
    fichier <<instanceFile<<";";
    fichier << "test KpSolverHeurDP"<< ";";
    kp = new KpSolverHeurDP(instanceFile, 50, 50);
    fichier<<testSolver(kp);
    delete kp;

    cout << "\ntest KpSolverHeurDP basique (20, 60):" << endl;
    fichier <<instanceFile<<";";
    fichier << "test KpSolverHeurDP"<< ";";
    kp = new KpSolverHeurDP(instanceFile);
    fichier<<testSolver(kp);
    delete kp;

    cout << "\ntest KpSolverHeurDP (50,100):" << endl;
    fichier <<instanceFile<<";";
    fichier << "test KpSolverHeurDP"<< ";";
    kp = new KpSolverHeurDP(instanceFile, 50, 100);
    fichier<<testSolver(kp);
    delete kp;

    fichier.close();
    return 0;
}
