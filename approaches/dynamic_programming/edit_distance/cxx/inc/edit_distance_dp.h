// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
edit_distance_dp.h file is part of Algosnippet.
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

#ifndef ALGO_DYNAMIC_PROGRAMMING_EDIT_DISTANCE_H
#define ALGO_DYNAMIC_PROGRAMMING_EDIT_DISTANCE_H

#include <algorithm>
#include <cstring>

#ifdef DEBUG_EDIT_DISTANCE
#include <iostream>
#include <tuple> // defines tie
#endif

namespace algo_snippet {
    namespace dynamic_programming {
        class edit_distance {
        public:
            enum {
                EDIT_MATCH = 0,
                EDIT_CHANGE,
                EDIT_XDEL,
                EDIT_YDEL,
                EDIT_KMAX,
            };
            static std::size_t calc(const char*x, std::size_t xlen, const char*y, std::size_t ylen) {
                if(!x || !y || 0 == xlen || 0 == ylen) {
                    return xlen+ylen;
                }
                std::size_t dist[xlen+1][ylen+1];
                std::pair<std::size_t,std::size_t> prev[xlen+1][ylen+1];
                int op[xlen+1][ylen+1];
                // initialize
                for(std::size_t xpos = 0; xpos <= xlen; xpos++) {
                    for(std::size_t ypos = 0; ypos <= ylen; ypos++) {
                        dist[xpos][ypos] = xlen+ylen;
                        op[xpos][ypos] = 0;
                    }
                }
                dist[0][0] = 0;

                // Notice similarities with Floyd-Warshall algorithm
                for(std::size_t xpos = 0; xpos < xlen; xpos++) {
                    for(std::size_t ypos = 0; ypos < ylen; ypos++) {
                        // try case 1: Character matched
                        if(x[xpos] == y[ypos]) {
                            if(dist[xpos][ypos] < dist[xpos+1][ypos+1]) {
                                dist[xpos+1][ypos+1] = dist[xpos][ypos];
                                prev[xpos+1][ypos+1] = std::make_pair(xpos,ypos);
                                op[xpos+1][ypos+1] = EDIT_MATCH;
                            }
                        } else {
                            // try case 2: Skip x-character mismatch(by deleting)
                            if((1 + dist[xpos][ypos]) < dist[xpos+1][ypos]) {
                                dist[xpos+1][ypos] = 1 + dist[xpos][ypos];
                                prev[xpos+1][ypos] = std::make_pair(xpos,ypos);
                                op[xpos+1][ypos] = EDIT_XDEL;
                            }
                            // try case 3: Skip y-charater mismatch(by deleting)
                            if((1 + dist[xpos][ypos]) < dist[xpos][ypos+1]) {
                                dist[xpos][ypos+1] = 1 + dist[xpos][ypos];
                                prev[xpos][ypos+1] = std::make_pair(xpos,ypos);
                                op[xpos][ypos+1] = EDIT_YDEL;
                            }
                            // try case 4: Change one character
                            if((1 + dist[xpos][ypos]) < dist[xpos+1][ypos+1]) {
                                dist[xpos+1][ypos+1] = 1 + dist[xpos][ypos];
                                prev[xpos+1][ypos+1] = std::make_pair(xpos,ypos);
                                op[xpos+1][ypos+1] = EDIT_CHANGE;
                            }
                        }
                    }
                }
#ifdef DEBUG_EDIT_DISTANCE
                /*for(std::size_t xpos = 0; xpos < xlen; xpos++) {
                    for(std::size_t ypos = 0; ypos < ylen; ypos++) {
                        std::cout << dist[xpos][ypos] << " " << std::endl;
                    }
                }*/
                // path reconstruction
                /*std::size_t xi = xlen-1;
                std::size_t yi = xlen-1;
                std::cout << '[' << std::endl;
                while(0 != xi && 0 != yi) {
                    std::cout << op[xi][yi] << ',';
                    std::tie(xi,yi) = prev[xi][yi];
                }
                std::cout << ']';*/
#endif
                return dist[xlen-1][ylen-1];
            }
        };
    }
}

#endif // ALGO_DYNAMIC_PROGRAMMING_EDIT_DISTANCE_H

