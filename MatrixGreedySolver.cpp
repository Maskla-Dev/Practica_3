//
// Created by LAMM_ on 21/10/2021.
//

#include "MatrixGreedySolver.h"

MatrixGreedySolver::MatrixGreedySolver(MatrixList& matrix_list) : row_list(matrix_list), column_list(matrix_list){
    printMatricesSizes(matrix_list);
    //Sorting row list
    std::sort(row_list.begin(), row_list.end(), MatrixGreedySolver::compareAsRowSize);
    std::sort(column_list.begin(), column_list.end(), MatrixGreedySolver::compareAsColumnSize);
}

void MatrixGreedySolver::initSolution() {
    intMatrix A_k, A_j, B_i;
    int row_list_index, column_list_index = 0;
    bool was_successful_search;
    start = Timer::now();
    while(!column_list.empty()){
        A_k = column_list.front();
        row_list_index = findRowCompatible(A_k.size(), was_successful_search);
        if(!was_successful_search){
            if(column_list_index + 1 < column_list.size()){
                A_j = column_list[column_list_index + 1];
                row_list_index = column_list_index + 1;
                arithmetic_operations += A_j.size() * A_j[0].size() * A_k[0].size();
                try{
                    B_i = makeProduct(A_j, A_k);
                }catch (std::exception& e){
                    std::cout << "Cannot be solved: " << e.what() << std::endl;
                    arithmetic_operations = 0;
                    matrix_operations = 0;
                    break;
                }
                column_list.erase(column_list.begin() + column_list_index);
                column_list.erase(column_list.begin() + row_list_index);
                row_list.erase(row_list.begin() + findMatrixInList(row_list, A_k, was_successful_search));
                row_list.erase(row_list.begin() + findMatrixInList(row_list, A_j, was_successful_search));
                row_list.push_back(B_i);
                std::sort(row_list.begin(), row_list.end(), MatrixGreedySolver::compareAsRowSize);
            }
        }
        else{
            A_j = row_list[row_list_index];
            arithmetic_operations += A_j.size() * A_j[0].size() * A_k[0].size();
            try{
                B_i = makeProduct(A_j, A_k);
            }catch (std::exception& e){
                std::cout << "Cannot be solved: " << e.what() << std::endl;
                arithmetic_operations = 0;
                matrix_operations = 0;
                break;
            }
            column_list.erase(column_list.begin() + column_list_index);
            column_list_index = findMatrixInList(column_list, A_j, was_successful_search);
            if(was_successful_search)
                column_list.erase(column_list.begin() + column_list_index);
            row_list.erase(row_list.begin() + row_list_index);
            row_list.erase(row_list.begin() + findMatrixInList(row_list, A_k, was_successful_search));
            row_list.push_back(B_i);
            std::sort(row_list.begin(), row_list.end(), MatrixGreedySolver::compareAsRowSize);
        }
        column_list_index = 0;
        ++matrix_operations;
    }
    finish = Timer::now();
    time_frame = finish - start;
}

void MatrixGreedySolver::printDataResult() {
    std::cout << std::endl;
    std::cout << "Arithmetic Operations: " << arithmetic_operations << std::endl;
    std::cout << "Matrices Multiplications: " << matrix_operations << std::endl;
    std::cout << "Time execution (milliseconds): " << time_frame.count() << "\n" << std::endl;
}

void MatrixGreedySolver::resetLists(MatrixList& matrix_list) {
    printMatricesSizes(matrix_list);
    row_list.clear();
    column_list.clear();
    row_list = matrix_list;
    column_list = matrix_list;
    //Sorting row list
    std::sort(row_list.begin(), row_list.end(), MatrixGreedySolver::compareAsRowSize);
    std::sort(column_list.begin(), column_list.end(), MatrixGreedySolver::compareAsColumnSize);
    arithmetic_operations = 0;
    matrix_operations = 0;
    time_frame = milli_seconds::zero();
}

bool MatrixGreedySolver::compareAsRowSize(intMatrix& i, intMatrix& j) {
    return i.size() > j.size();
}

bool MatrixGreedySolver::compareAsColumnSize(intMatrix& i, intMatrix& j) {
    return i[0].size() < j[0].size();
}

int MatrixGreedySolver::findRowCompatible(size_t column_size, bool& was_successful_search) {
    for(int i = 0; i < row_list.size(); ++i){
        if(row_list[i][0].size() == column_size){
            was_successful_search = true;
            return i;
        }
    }
    was_successful_search = false;
    return std::numeric_limits<int>::max();
}

intMatrix MatrixGreedySolver::makeProduct(intMatrix& A, intMatrix& B) {
    if(A[0].size() != B.size())
        throw std::invalid_argument("Undefined product");
    intMatrix C(A.size(), intList(B[0].size(), 0));
    for(int i = 0; i < A.size(); ++i)
        for(int j = 0; j < B[0].size(); ++j)
            for(int k = 0; k < A[0].size(); ++k)
                C[i][j] = A[i][k]*B[k][j];
    return C;
}

int MatrixGreedySolver::findMatrixInList(MatrixList& list, intMatrix& matrix, bool& was_successful_search) {
    for(int i = 0; i < list.size(); ++i)
        if(list[i].size() == matrix.size() && list[i][0].size() == matrix[0].size() && list[i][0][0] == matrix[0][0]){
            was_successful_search = true;
            return i;
        }
    was_successful_search = false;
    return std::numeric_limits<int>::max();
}

void MatrixGreedySolver::printMatricesSizes(MatrixList & source) {
    char letter = 'A';
    std::cout << "|-------Greedy Algorithm with:\n";
    for(auto& i : source){
        std::cout << "\t" << letter << "[" << i.size() << "," << i[0].size() << "]" << std::endl;
        ++letter;
    }
}