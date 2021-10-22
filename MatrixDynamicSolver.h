//
// Created by LAMM_ on 21/10/2021.
//
#include "MatrixGreedySolver.h"

#ifndef PRACTICA_3_MATRIXDYNAMICSOLVER_H
#define PRACTICA_3_MATRIXDYNAMICSOLVER_H

struct MatrixNode{
    intMatrix i_matrix;
    MatrixNode *left;
    MatrixNode * right;
};

class MatrixDynamicSolver {
    public:
        MatrixDynamicSolver() = delete;
        explicit MatrixDynamicSolver(MatrixList&);
        void fillTables();
        void buildTree(MatrixNode*, int, int);
        void resetList(MatrixList&);
        void resolveTree();
        void printDataResult();
        const intMatrix& getS();
    private:
        void combineNodes(MatrixNode*);

        intMatrix M, S;
        intList P;
        MatrixList& matrix_list;
        size_t arithmetic_operations = 0;
        size_t matrix_operations = 0;
        Checkpoint start, finish;
        milli_seconds time_frame;
        MatrixNode *tree_root;
};


#endif //PRACTICA_3_MATRIXDYNAMICSOLVER_H
