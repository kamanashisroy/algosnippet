// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
binomial_calc.h file is part of Algosnippet.
Algosnippet is a collection of practice data-structures and algorithms
Copyright (C) 2018  Kamanashis Roy
Algosnippet is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
Algosnippet is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with Algosnippet.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef ALGO_BINOMIAL_CALC_H
#define ALGO_BINOMIAL_CALC_H

namespace algo_snippet {
    /*
      Pascals_Triangle
      1
      1  1
      1  2  1
      1  3  3  1
      1  4  6  4  1
      1  5  10 10 5 1

      ...
      ...
      tri[i][j] = tri[i-1][j] + tri[i-1][j-1]

     */
    std::size_t binomial_calc(const std::size_t xn, const std::size_t xk) {
        std::size_t tri[xn+1][xn+1];

        // initialize the vertial 1 and ending 1
        for(std::size_t row = 0; row <= xn; row++) {
            tri[row][0] = 1;
            tri[row][row] = 1;
        }

        // calculate pascal triangle
        for(std::size_t row = 2; row <= xn; row++) {
            for(std::size_t col = 1; col < row; col++) {
                tri[row][col] = tri[row-1][col] + tri[row-1][col-1];
            }
        }
        
        return tri[xn][xk];
    }
}

#endif // ALGO_BINOMIAL_CALC_H

