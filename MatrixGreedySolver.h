//
// Created by LAMM_ on 21/10/2021.
//

#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include <memory>
#include <limits>
#include <chrono>
#include <iomanip>

#ifndef PRACTICA_3_MATRIXGREEDYSOLVER_H
#define PRACTICA_3_MATRIXGREEDYSOLVER_H

using intList = std::vector<int>;
using intMatrix = std::vector<intList>;
using MatrixList = std::vector<intMatrix>;
using milli_seconds = std::chrono::duration<double,std::milli>;
using Timer = std::chrono::system_clock;
using Checkpoint = std::chrono::system_clock::time_point;

class MatrixGreedySolver {
    public:
        MatrixGreedySolver() = delete;
        explicit MatrixGreedySolver(MatrixList&);
        void initSolution();
        void printDataResult();
        void resetLists(MatrixList&);
        static intMatrix makeProduct(intMatrix&, intMatrix&);
    private:
        //Support Functions
        static bool compareAsRowSize(intMatrix&, intMatrix&);
        static bool compareAsColumnSize(intMatrix&, intMatrix&);
        int findRowCompatible(size_t, bool&);
        static int findMatrixInList(MatrixList&, intMatrix&, bool&);
        static void printMatricesSizes(MatrixList&);
        //Class Attributes
        MatrixList column_list;
        MatrixList row_list;
        size_t arithmetic_operations = 0;
        size_t matrix_operations = 0;
        Checkpoint start, finish;
        milli_seconds time_frame;
};


#endif //PRACTICA_3_MATRIXGREEDYSOLVER_H
