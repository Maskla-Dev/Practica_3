//
// Created by LAMM_ on 21/10/2021.
//

#include "MatrixDynamicSolver.h"

MatrixDynamicSolver::MatrixDynamicSolver(MatrixList& matrix_list) : matrix_list(matrix_list) {
    S.assign(matrix_list.size(), intList(matrix_list.size(),0));
    M.assign(matrix_list.size(), intList(matrix_list.size(),0));
    //Fill P list
    P.push_back(matrix_list[0].size());
    for(auto & i : matrix_list)
        P.push_back(i[0].size());
    tree_root = new MatrixNode;
}

void MatrixDynamicSolver::fillTables() {
    for(int i = 0; i < M.size(); ++i){
        M[i][i] = 0;
    }

    for(int l = 2; l < M.size(); ++l){
        for(int i = 1, j; i < M.size() - l + 1; ++i){
            j = i + l - 1;
            M[i][j] = std::numeric_limits<int>::max();
            for(int k = i, q; k <= j - 1; ++k){
                q = M[i][k] + M[k + 1][j] + P[i - 1]*P[k]*P[j];
                if(q < M[i][j]){
                    M[i][j] = q;
                    S[i][j] = k;
                }
            }
        }
    }
    arithmetic_operations = M[1][M.size() - 1];
}

void MatrixDynamicSolver::buildTree(MatrixNode* current_node, int i, int j) {
    if(i == j){
        current_node->i_matrix = matrix_list[i];
        current_node->left = nullptr;
        current_node->right = nullptr;
    }
    else{
        current_node->left = new MatrixNode;
        current_node->right = new MatrixNode;
        buildTree(current_node->left, i, S[i][j]);
        buildTree(current_node->right, S[i][j] + 1, j);
    }
}

const intMatrix &MatrixDynamicSolver::getS() {
    return S;
}

void MatrixDynamicSolver::resetList(MatrixList &list) {
    matrix_list = list;
    S.clear();
    M.clear();
    P.clear();
    S.assign(list.size(), intList(list.size(),0));
    M.assign(list.size(), intList(list.size(),0));
    P.push_back(list[0].size());
    for(auto & i : list)
        P.push_back(i[0].size());
}

void MatrixDynamicSolver::resolveTree() {
    start = Timer::now();
    buildTree(tree_root, 0, S.size() - 1);
    combineNodes(tree_root);
    finish = Timer::now();
    time_frame = finish - start;
}

void MatrixDynamicSolver::printDataResult() {
    std::cout << std::endl;
    std::cout << "Dynamic Algorithm:\n";
    std::cout << std::setw(4) << "Arithmetic Operations: " << arithmetic_operations << std::endl;
    std::cout << std::setw(4) << "Matrices Multiplications: " << matrix_operations << std::endl;
    std::cout << std::setw(4) << "Time execution (milliseconds): " << time_frame.count() << "\n";
    std::cout << "------------------------------|\n" << std::endl;
}

void MatrixDynamicSolver::combineNodes(MatrixNode *current_node) {
    if(current_node->left->i_matrix.empty() && current_node->right->i_matrix.empty()){
        combineNodes(current_node->left);
        combineNodes(current_node->right);
    }
    else if(current_node->left->i_matrix.empty() && !current_node->right->i_matrix.empty()){
        combineNodes(current_node->left);
    }
    else if(!current_node->left->i_matrix.empty() && current_node->right->i_matrix.empty()){
        combineNodes(current_node->right);
    }
    current_node->i_matrix = MatrixGreedySolver::makeProduct(current_node->left->i_matrix, current_node->right->i_matrix);
    ++matrix_operations;
    delete current_node->left;
    delete current_node->right;
}
