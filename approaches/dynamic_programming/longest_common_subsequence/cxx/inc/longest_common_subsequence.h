// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
longest_common_subsequence_dp.h file is part of Algosnippet.
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

#ifndef ALGO_DYNAMIC_PROGRAMMING_LONGEST_COMMON_SUBSEQUENCE_H
#define ALGO_DYNAMIC_PROGRAMMING_LONGEST_COMMON_SUBSEQUENCE_H

#include <algorithm> //defines max
#include <vector>

#ifdef DEBUG_LONGEST_COMMON_SUBSEQUENCE
#include <iostream>
#include <cstring>
#endif

namespace algo_snippet {
    namespace dynamic_programming {
        class longest_common_subsequence {
        public:
            longest_common_subsequence(const char*x, int m, const char*y, int n)
                : x(x),m(m),y(y),n(n),mtx(m+1) {
                for(int i = 0; i <= m; i++) {
                    mtx[i].resize(n+1,0);
                }
            }
            //! Dynamic programming gives `O(n*n)` runtime.
            int calc() {
                int result = 0;
                
                for(int i = 0; i < m; i++) {
                    for(int j = 0; j < n; j++) {
                        if(x[i] == y[j]) {
                            // case 0: match case
                            // NOTE relaxation is not needed here because none did set mtx[i+1][j+1] yet
                            mtx[i+1][j+1] = mtx[i][j]+1;
                            if(result < mtx[i+1][j+1]) {
                                result = mtx[i+1][j+1];
                                result_posx = i+1;
                                result_posy = j+1;
                            }
                        } else {
                            // case 1: try to discard x[i] 
                            if(mtx[i+1][j] < mtx[i][j]) {
                                mtx[i+1][j] = mtx[i][j];
                            }
                            // case 2: try to discard y[j]
                            if(mtx[i][j+1] < mtx[i][j]) {
                                mtx[i][j+1] = mtx[i][j];
                            }
                        }
                    }
                }
                return result;
            }
#ifdef DEBUG_LONGEST_COMMON_SUBSEQUENCE
            void print(std::ostream& outstrm) {
                // reconstruct path
                char path_marker[m+1][n+1];
                memset(path_marker, ' ', sizeof(path_marker));
                int posx = result_posx,posy = result_posy;
                while(true) {
                    path_marker[posx][posy] = '*';
                    if((posx-1) >= 0 && (posy-1) >= 0 && (mtx[posx-1][posy-1]+1) == mtx[posx][posy]) {
                        posx--;
                        posy--;
                    } else if((posx-1) >= 0 && mtx[posx-1][posy] == mtx[posx][posy]) {
                        posx--;
                    } else if((posy-1) >= 0 && mtx[posx][posy-1] == mtx[posx][posy]) {
                        posy--;
                    } else {
                        break;
                    }
                }
                
                outstrm << ".\t\t";
                for(int j = 0; j < n; j++) {
                    outstrm << y[j] << "\t\t";
                }
                outstrm << std::endl;
                for(int i = 0; i < m; i++) {
                    // show x on left
                    outstrm << x[i] << "\t\t";
                    for(int j = 0; j < n; j++) {
                        outstrm << mtx[i+1][j+1] << ',' << path_marker[i][j] << "\t\t";
                    }
                    outstrm << std::endl;
                }
            }
#endif
        private:
            const char* const x;
            const int m;
            const char* const y;
            const int n;
            std::vector<std::vector<int>> mtx;
            int result_posx;
            int result_posy;
        };
    }
}

#endif // ALGO_DYNAMIC_PROGRAMMING_LONGEST_COMMON_SUBSEQUENCE_H

