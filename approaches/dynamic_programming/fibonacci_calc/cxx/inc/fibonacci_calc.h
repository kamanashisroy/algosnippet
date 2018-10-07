// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
fibonacci_calc.h file is part of Algosnippet.
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

#ifndef ALGO_FIBONACCI_CALC_H
#define ALGO_FIBONACCI_CALC_H

namespace algo_snippet {
    /*

      fib(0) = 1
      fib(1) = 1
      fib(2) = fib(2-1)+fib(2-2) = fib(1)+fib(0) = 1 + 1 = 2
      fib(3) = fib(3-1)+fib(3-2) = fib(2)+fib(1) = 2 + 1 = 3
      fib(4) = fib(4-1)+fib(4-2) = fib(3)+fib(3) = 3 + 2 = 5

      ...
      ...
      fib(n) = fib(n-1)+fib(n-2) 
             = fib((n-1)-1)+fib((n-1)-2) + fib((n-2)-1) + fib((n-2)-2)
             = fib(n-2) + fib(n-3) + fib(n-3) + fib(n-4)
             = fib(n-2) + 2*fib(n-3) + fib(n-4)

     */
    std::size_t fibonacci_calc(const std::size_t xn) {
        std::size_t fib_prev = 1;
        std::size_t fib_before_prev = 1;
        if(0 == xn || 1 == xn) {
            return 1; // handle special cases
        }

        for(std::size_t i = 2; i <= xn; i++) {
            std::size_t result = fib_prev+fib_before_prev;
            fib_before_prev = fib_prev;
            fib_prev = result;
        }
        return fib_prev;
    }
}

#endif // ALGO_FIBONACCI_CALC_H

