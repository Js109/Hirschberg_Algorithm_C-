#pragma once

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>

/**
* A headerfile which provides one method createMatrix, which creates 
* a two dimensional vector matrix
*/
class Matrix {
public:
    /**
    * converts the value to a wstring
    *
	  * @param dimensionOneSize size of the first dimension
    * @param dimensionTwoSize size of the second dimension
	  * @return matrix as two dimensional vector matrix 
	  */
    static std::vector<std::vector<int>> createMatrix(int dimensionOneSize, int dimensionTwoSize) {
        std::vector<std::vector<int>> matrix(dimensionOneSize);
        for (int vectorDimOne = 0; vectorDimOne < dimensionOneSize; vectorDimOne++) {
            matrix[vectorDimOne] = std::vector<int>(dimensionTwoSize);
        }
        return matrix;
    }
};
#endif