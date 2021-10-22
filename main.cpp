#include <iostream>
#include "MatrixGreedySolver.h"
#include "MatrixDynamicSolver.h"

int main() {
    intMatrix *A, *B, *C, *D, *E, *F;
    //----------------------------First test
    A = new intMatrix(50, std::vector<int>(30,1));
    B = new intMatrix(30, std::vector<int>(20,2));
    C = new intMatrix(20, std::vector<int>(100,3));
    MatrixList matrix_list = {*A, *B, *C};
    //Greedy
    MatrixGreedySolver greedy_solver(matrix_list);
    greedy_solver.initSolution();
    greedy_solver.printDataResult();
    //Dynamic
    MatrixDynamicSolver dynamic_solver(matrix_list);
    dynamic_solver.fillTables();
    dynamic_solver.resolveTree();
    dynamic_solver.printDataResult();
    delete A;
    delete B;
    delete C;
    matrix_list.clear();
    //----------------------------Second test
    A = new intMatrix(10, std::vector<int>(200,1));
    B = new intMatrix(200, std::vector<int>(300,2));
    C = new intMatrix(300, std::vector<int>(50,3));
    D = new intMatrix(50, std::vector<int>(90,4));
    E = new intMatrix(90, std::vector<int>(10,5));
    matrix_list = {*A, *B, *C, *D, *E};
    //Greedy
    greedy_solver.resetLists(matrix_list);
    greedy_solver.initSolution();
    greedy_solver.printDataResult();
    //Dynamic
    dynamic_solver.resetList(matrix_list);
    dynamic_solver.fillTables();
    dynamic_solver.resolveTree();
    dynamic_solver.printDataResult();
    delete A;
    delete B;
    delete C;
    delete D;
    delete E;
    matrix_list.clear();
    //----------------------------Third test
    A = new intMatrix(1, std::vector<int>(2,1));
    B = new intMatrix(2, std::vector<int>(3,2));
    C = new intMatrix(3, std::vector<int>(4,3));
    D = new intMatrix(4, std::vector<int>(5,4));
    E = new intMatrix(5, std::vector<int>(6,5));
    F = new intMatrix(6, std::vector<int>(7,6));
    matrix_list = {*A, *B, *C, *D, *E, *F};
    //Greedy
    greedy_solver.resetLists(matrix_list);
    greedy_solver.initSolution();
    greedy_solver.printDataResult();
    //Dynamic
    dynamic_solver.resetList(matrix_list);
    dynamic_solver.fillTables();
    dynamic_solver.resolveTree();
    dynamic_solver.printDataResult();
    delete A;
    delete B;
    delete C;
    delete D;
    delete E;
    return 0;
}