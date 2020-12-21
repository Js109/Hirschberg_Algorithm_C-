#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <locale>
#include <codecvt>
#include <functional>
#include <iterator>
#include "stringutil.hpp"
#include "matrix.hpp"

/**
 * This implementation for the course Object-Oriented Programming with C++ as part of the term paper implements the
 * Hirschberg algorithm for determining the longest common subsequence.
 *
 * This is implemented as in the paper "A Linear Space Algorithm for Computing Maximal Common Subsequences" by
 * D.S. Hirschberg using the algorithms B and C described there. It has a linear memory requirement for the input.
 *
 * @author Julian Stier
 */
// generic class Hirschberg_JS
template<typename Container, typename Element>
class Hirschberg_JS {
public:
    // constructor with two generic elements and a predicate, which returns a boolean
    Hirschberg_JS(const std::function<bool(const Element &, const Element &)> predicate)
            : predicate(predicate) {}

    /**
     * Algorithm C as described in the paper by Hirschberg
     * Applies the theorem recursively to divide the problem into two smaller problems until a subproblem gets trivial.
     * It produces a common subsequence c of a and b
     *
     * @param m length of Input container a as m
     * @param n length of Input container b as n
     * @param a Input container a (A1m in the paper)
     * @param b Input container b (B1n in the paper)
     * @return c is the output of a common subsequence of a and b
     */
    Container hirschbergAlgoC(int m, int n, const Container &a, const Container &b) {
        int i = 0;
        int j = 0;
        Container c = L"";
        int m_s4 = 0;
        int k_s4 = 0;

        typename Container::const_iterator a_it = a.begin();
        typename Container::const_iterator b_it = b.begin();

        // Step 1 as described in the paper, trivial problem
        if (n == 0) {
            c = L"";
        } else if (m == 1) {
            c = L"";
            for (j = 0; j < n; j++) {
                // Call of pedicate on both elements which you get back from the iterators,
                // Iterators give access to element
                if (predicate(a_it[0], b_it[j])) {
                    c = L"" + StringUtil::toString(a[0]);
                    break;
                }
            }
            // Step 2 as described in the paper, split problem
        } else {
            i = static_cast<int>(std::floor((static_cast<double>(m)) / 2));

            // Step 3 as described in the paper, applies theorem recursively
            std::vector<int> l1 = hirschbergAlgoB(i, n, a.substr(0, i), b);
            std::vector<int> l2 = hirschbergAlgoB(m - i, n, StringUtil::reverseString(a.substr(i)),
                                                  StringUtil::reverseString(b));

            // Step 4 as described in the paper, finds the index k of the maximum sum of Ll and l2
            // j from the paper was replaced with l in the loop
            for (int l = 0; l <= n; l++) {
                if (m_s4 < (l1[l] + l2[n - l])) {
                    m_s4 = l1[l] + l2[n - l];
                    k_s4 = l;
                }
            }
            int k = k_s4;

            // Step 5 as described in the paper, solves simpler problems
            // c1 is longest common subsequence of first half
            Container c1 = hirschbergAlgoC(i, k, a.substr(0, i), b.substr(0, k));
            // c2 is longest common subsequence of second half
            Container c2 = hirschbergAlgoC(m - i, n - k, a.substr(i), b.substr(k));

            // Step 6 as described in the paper, give output
            c = c1 + c2;
        }

        return c;
    }

private:
    const std::function<bool(const Element &, const Element &)> predicate;

    /**
     * Algorithm B as described in the paper by Hirschberg
     * produces and returns the last line of the Needleman Wunsch matrix as vector Score(i,j)
     *
     * @param m length of Input container a as m
     * @param n length of Input container b as n
     * @param a Input container a (A1m in the paper)
     * @param b Input container b (B1n in the paper)
     * @return k[1] is last line of Needleman Wunsch matrix as vector and represents LL(j) of the paper
     */
    std::vector<int> hirschbergAlgoB(int m, int n, const Container &a, const Container &b) {

        // Step 1 as described in the paper, Initialization
        std::vector <std::vector<int>> k = Matrix::createMatrix(2, n + 1);

        for (int j = 0; j <= n; j++) {
            k[1][j] = 0;
        }
        // define iterators to the beginning of a and b  
        typename Container::const_iterator a_it = a.begin();
        typename Container::const_iterator b_it = b.begin();

        // Step 2 as described in the paper
        for (int i = 1; i <= m; i++) {

            // Step 3 as described in the paper
            for (int j = 0; j <= n; j++) {
                k[0][j] = k[1][j];
            }

            // Step 4 as described in the paper
            for (int j = 1; j <= n; j++) {
                // Call of pedicate on both elements which you get back from the iterators,
                // Iterators give access to element
                if (predicate(a_it[i - 1], b_it[j - 1])) {
                    k[1][j] = k[0][j - 1] + 1;
                } else {
                    k[1][j] = std::max(k[1][j - 1], k[0][j]);
                }
            }
        }

        // Step 5 as described in the paper
        return k[1];
    }
};