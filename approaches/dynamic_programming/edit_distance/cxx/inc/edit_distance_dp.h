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

#ifdef DEBUG_EDIT_DISTANCE
#include <iostream>
#include <tuple> // defines tie
#include <cstring>
#endif

namespace algo_snippet {
    namespace dynamic_programming {
        class edit_distance {
        public:
            enum {
                EDIT_MATCH = 0,
                EDIT_CHANGE,
                EDIT_XDEL,
                EDIT_XADD,
                EDIT_KMAX,
            };
            
            static std::size_t calc(const char*x, std::size_t xlen, const char*y, std::size_t ylen) {
                if(!x || !y || 0 == xlen || 0 == ylen) {
                    return xlen+ylen;
                }
                std::size_t dist[xlen+1][ylen+1];
#ifdef DEBUG_EDIT_DISTANCE
                std::pair<std::size_t,std::size_t> prev[xlen+1][ylen+1];
                int op[xlen+1][ylen+1];
#endif
                // initialize
                for(std::size_t xpos = 0; xpos <= xlen; xpos++) {
                    for(std::size_t ypos = 0; ypos <= ylen; ypos++) {
                        dist[xpos][ypos] = xlen+ylen; // highest distance
#ifdef DEBUG_EDIT_DISTANCE
                        op[xpos][ypos] = EDIT_MATCH;
#endif
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
#ifdef DEBUG_EDIT_DISTANCE
                                prev[xpos+1][ypos+1] = std::make_pair(xpos,ypos);
                                op[xpos+1][ypos+1] = EDIT_MATCH;
#endif
                            }
                        } else {
                            // try case 2: Skip x-character mismatch(by deleting)
                            if((1 + dist[xpos][ypos]) < dist[xpos+1][ypos]) {
                                dist[xpos+1][ypos] = 1 + dist[xpos][ypos];
#ifdef DEBUG_EDIT_DISTANCE
                                prev[xpos+1][ypos] = std::make_pair(xpos,ypos);
                                op[xpos+1][ypos] = EDIT_XDEL;
#endif
                            }
                            // try case 3: Add x-character to match y
                            if((1 + dist[xpos][ypos]) < dist[xpos][ypos+1]) {
                                dist[xpos][ypos+1] = 1 + dist[xpos][ypos];
#ifdef DEBUG_EDIT_DISTANCE
                                prev[xpos][ypos+1] = std::make_pair(xpos,ypos);
                                op[xpos][ypos+1] = EDIT_XADD;
#endif
                            }
                            // try case 4: Change one character
                            if((1 + dist[xpos][ypos]) < dist[xpos+1][ypos+1]) {
                                dist[xpos+1][ypos+1] = 1 + dist[xpos][ypos];
#ifdef DEBUG_EDIT_DISTANCE
                                prev[xpos+1][ypos+1] = std::make_pair(xpos,ypos);
                                op[xpos+1][ypos+1] = EDIT_CHANGE;
#endif
                            }
                        }
                    }
                }
                // one last time(do vertial memoization)
                for(std::size_t ypos = 0; ypos < ylen; ypos++) {
                    const std::size_t xpos = xlen;
                    // try case 3: Add x-character to match y
                    if((1 + dist[xpos][ypos]) < dist[xpos][ypos+1]) {
                        dist[xpos][ypos+1] = 1 + dist[xpos][ypos];
#ifdef DEBUG_EDIT_DISTANCE
                        prev[xpos][ypos+1] = std::make_pair(xpos,ypos);
                        op[xpos][ypos+1] = EDIT_XADD;
#endif
                    }
                }
                for(std::size_t xpos = 0; xpos < xlen; xpos++) {
                    const std::size_t ypos = ylen;
                    // try case 2: Skip x-character mismatch(by deleting)
                    if((1 + dist[xpos][ypos]) < dist[xpos+1][ypos]) {
                        dist[xpos+1][ypos] = 1 + dist[xpos][ypos];
#ifdef DEBUG_EDIT_DISTANCE
                        prev[xpos+1][ypos] = std::make_pair(xpos,ypos);
                        op[xpos+1][ypos] = EDIT_XDEL;
#endif
                    }
                }
#ifdef DEBUG_EDIT_DISTANCE
                std::cout << "match=" << EDIT_MATCH << ",change=" << EDIT_CHANGE << ",xdel=" << EDIT_XDEL << ",xadd=" << EDIT_XADD << std::endl;
                char marker[xlen+1][ylen+1];
                memset(marker,0,sizeof(marker));
                // path reconstruction
                std::size_t xi = xlen;
                std::size_t yi = ylen;
                while(!(0 == xi && 0 == yi)) {
                    marker[xi][yi] = '*';
                    std::tie(xi,yi) = prev[xi][yi];
                }

                const char op_name[EDIT_KMAX] = {'M','C','D','A'};
                // dump dp table
                for(std::size_t xpos = 0; xpos <= xlen; xpos++) {
                    if(0 == xpos) {
                        // Show each column header
                        std::cout << "*\t\t";
                        for(std::size_t ypos = 0; ypos <= ylen; ypos++) {
                            // Show column header
                            std::cout << ((0==ypos)?'.':y[ypos-1]) << "\t\t";
                        }
                        std::cout << std::endl;
                    }
                    // Show row-header
                    std::cout << ((0==xpos)?'.':x[xpos-1]) << "\t\t";

                    for(std::size_t ypos = 0; ypos <= ylen; ypos++) {
                        std::cout << dist[xpos][ypos] << ',' << op_name[op[xpos][ypos]] << marker[xpos][ypos] << "\t\t";
                    }
                    std::cout << std::endl;
                }
#endif
                return dist[xlen][ylen];
            }
        };
    }
}

#endif // ALGO_DYNAMIC_PROGRAMMING_EDIT_DISTANCE_H

