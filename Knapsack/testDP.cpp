#include <chrono>
#include "kpSolverDP.hpp"
//#include "kpSolverDP2.hpp"
#include "kpSolverHeurDP.hpp"
#include "kpSolverDPsparseV2.hpp"
#include <sstream>


void testSolver(std::string const &instanceFile, bool verboseMode, MatDPType matrixType){
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    KpSolverDPv2 kp(instanceFile,matrixType);
    //KpSolverDPv1bis kp(instanceFile,matrixType);
    //KpSolverDPv1 kp(instanceFile,matrixType);
    //KpSolverDPv0 kp(instanceFile,matrixType);

    //if (verboseMode) kp.printKnapsackInstance();
    cout << endl
         << "Dynamic Programming with matrix of type " << tostring(matrixType) << " :" << endl
         << endl;
    start = std::chrono::steady_clock::now();
    kp.solve();
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "elapseeed time: " << elapsed_seconds.count() << "s" << endl;
    std::string s;
    kp.printKnapsackSolution(verboseMode,s);
    //if (verboseMode) kp.printFirstLineDP();
    if (verboseMode) kp.printMatrixDP();
}


std::string testSolver( KpSolver * kp,bool verboseMode = false){
    
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;


    //if (verboseMode) kp.printKnapsackInstance();

    std::stringstream ss;
    std::string s = "";

    start = std::chrono::steady_clock::now();
    kp->solve();
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "elapseed time: " << elapsed_seconds.count() << "s" << endl;

    s=kp->printKnapsackSolution(verboseMode,s);

    ss<<s<<elapsed_seconds.count()<<"\n";
    //std::cout << ss.str() ;
    return ss.str();
}

//TODO:1 sortie sur une instance tous les calculs possibles par matrice et solverus differents

//TODO:calcul sur toutes les instances (sauf trop grandes), sortir tableau .csv avec temps de calculs et valeurs obtenues
// kp_10000_1_0.03.in a 10000 objets passe, pas l'instance originale

void testDPSolvers(std::string const &instanceFile,std::string const &outputFile)
{

    vector<MatDPType> v = {
        //MatDPType::MatDPvectVect,
        //MatDPType::MatDPvect,
        //MatDPType::MatDPtabTab,
        MatDPType::MatDPtab
    };

    KpSolver * kp;

    ofstream fichier;
    fichier.open(outputFile,std::ios_base::app);//ouverture du fichier en mode app https://stackoverflow.com/questions/61895932/how-to-append-to-a-file-in-c
    
    
    for(auto matrixType : v){

        cout << endl
             << "DP v0 with matrix of type " << tostring(matrixType) << " :" << endl
             << endl;
        fichier <<instanceFile<<";";
        fichier << "DP v0 with matrix of type " << tostring(matrixType) << ";";
        kp = new KpSolverDPv0(instanceFile,matrixType);
        fichier << testSolver( kp);
        delete kp;

        cout << endl
             << "DP v1 with matrix of type " << tostring(matrixType) << " :" << endl
             << endl;
        fichier <<instanceFile<<";";
        fichier << "DP v1 with matrix of type " << tostring(matrixType) << ";";
        kp = new KpSolverDPv1(instanceFile,matrixType);
        fichier << testSolver( kp);
        delete kp;

        cout << endl
             << "DP v1bis with matrix of type " << tostring(matrixType) << " :" << endl
             << endl;
        fichier <<instanceFile<<";";
        fichier << "DP v1bis with matrix of type " << tostring(matrixType) << ";";
        kp = new KpSolverDPv1bis(instanceFile,matrixType);
        fichier << testSolver( kp);
        delete kp;

        cout << endl
             << "DP v2 with matrix of type " << tostring(matrixType) << " :" << endl
             << endl;
        fichier <<instanceFile<<";";
        fichier << "DP v2 with matrix of type " << tostring(matrixType) << ";";
        kp = new KpSolverDPv2(instanceFile,matrixType);
        fichier << testSolver( kp);
        delete kp;

    }


    //KpSolverDP * kpDP;

    cout << "\ntest kpSolverDPsparseV2 :" <<endl;
    fichier <<instanceFile<<";";
    fichier << "test kpSolverDPsparseV2"<< ";";
    kp = new kpSolverDPsparseV2(instanceFile);
    fichier << testSolver( kp);
    delete kp;


    cout << "\ntest KpSolverGreedy :" <<endl;
    fichier <<instanceFile<<";";
    fichier << "test KpSolverGreedy"<< ";";
    kp = new KpSolverGreedy(instanceFile);
    fichier << testSolver( kp);
    delete kp;

    cout << "\ntest KpSolverHeurDP :" <<endl;
    fichier <<instanceFile<<";";
    fichier << "test KpSolverHeurDP"<< ";";
    kp = new KpSolverHeurDP(instanceFile);
    fichier << testSolver( kp);
    delete kp;

    fichier.close();


/*
    cout << "\ntest KpSolverDPv2 :" <<endl;

    kpDP = new KpSolverDPv2(instanceFile);
    testSolver(kpDP);
    //kpDP->printMatrixDP();
    delete kpDP;

    cout << "\ntest KpSolverDP2 :" <<endl;

    kp = new KpSolverDP2(instanceFile);
    testSolver(kp);
    delete kp;
*/


}

int main(int argc, char** argv){

    const char* instanceFile;
    const char* outputFile;
    string cheminDefaut =  "../instances/courseExample.in";
    cheminDefaut ="../instances/kp_1000_2.in";
    //cheminDefaut ="../instances/kp_10000_1_0.1.in";

    if (argc < 3) {
        //cerr << "Usage: knapsack inputFile [heuristicMode] [verbosity]" << endl;
        //cerr << "Usage: a heuristic/exactMode implies comparisons of exact methods (for small instances), whereas no parameter implies heuristic search" << endl;
        //cerr << "A third parameter enable verbosity, useful for debugging" << endl;
        //return 1;

        instanceFile = cheminDefaut.c_str();
        outputFile="../resultats/default.txt";

    }
    else{     instanceFile = argv[1];
                outputFile=argv[2];
    }

    //bool verboseMode = true;
    //if (argc < 3) verboseMode = false;
/*
    cout << "______________________________" <<endl
         << "Instance :" << cheminDefaut << endl
         << "______________________________" << endl;
*/

    testDPSolvers(instanceFile,outputFile);

/*
    kp = new KpSolverHeurDP(instanceFile,10,10);
    testSolver(kp);
    delete kp;

    kp = new KpSolverHeurDP(instanceFile);
    testSolver(kp);
    delete kp;
*/

/*
    //testDP(instanceFile, verboseMode);
    testDP(instanceFile, verboseMode,MatDPType::MatDPtabTab);
    testDP(instanceFile, verboseMode, MatDPType::MatDPvectVect);
    testDP(instanceFile, verboseMode,MatDPType::MatDPvect);
    testDP(instanceFile, verboseMode,MatDPType::MatDPtab);

    cheminDefaut = "../instances/kp_100_1.in";
    instanceFile = cheminDefaut.c_str();

    cout << "______________________________" <<endl
         << "Instance :" << cheminDefaut << endl
         << "______________________________" << endl;

    testDP(instanceFile, verboseMode,MatDPType::MatDPtabTab);
    testDP(instanceFile, verboseMode, MatDPType::MatDPvectVect);
    testDP(instanceFile, verboseMode,MatDPType::MatDPvect);
    testDP(instanceFile, verynamique peuvent être utilisées pour trouver des solutions optimales ou proches de l'optimal.




    cheminDefaut = "../instances/kp_100_2.in";
    instanceFile = cheminDefaut.c_str();
    cout << "______________________________" <<endl
         << "Instance :" << cheminDefaut << endl
         << "______________________________" << endl;

    testDP(instanceFile, verboseMode,MatDPType::MatDPtabTab);
    testDP(instanceFile, verboseMode,MatDPType::MatDPtab);
    testDP(instanceFile, verboseMode,MatDPType::MatDPvect);
    testDP(instanceFile, verboseMode, MatDPType::MatDPvectVect);

    cheminDefaut = "../instances/kp_1000_1.in";
    instanceFile = cheminDefaut.c_str();

    cout << "______________________________" <<endl
         << "Instance :" << cheminDefaut << endl
         << "______________________________" << endl;

    testDP(instanceFile, verboseMode,MatDPType::MatDPtabTab);
    testDP(instanceFile, verboseMode,MatDPType::MatDPtab);
    testDP(instanceFile, verboseMode,MatDPType::MatDPvect);
    testDP(instanceFile, verboseMode, MatDPType::MatDPvectVect);


    cheminDefaut = "../instances/kp_1000_2.in";
    instanceFile = cheminDefaut.c_str();
    cout << "______________________________" <<endl
         << "Instance :" << cheminDefaut << endl
         << "______________________________" << endl;

    testDP(instanceFile, verboseMode,MatDPType::MatDPtabTab);
    testDP(instanceFile, verboseMode,MatDPType::MatDPtab);
    testDP(instanceFile, verboseMode,MatDPType::MatDPvect);
    testDP(instanceFile, verboseMode, MatDPType::MatDPvectVect);
*/
    return 0;
}
