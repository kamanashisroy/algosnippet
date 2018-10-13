// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
floyd_warshall.h file is part of Algosnippet.
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

#ifndef ALGO_DYNAMIC_PROGRAMMING_FLOYD_WARSHALL_H
#define ALGO_DYNAMIC_PROGRAMMING_FLOYD_WARSHALL_H

#include <algorithm>
#include <limits>
#include <vector>

#ifdef DEBUG_FLOYD_WARSHALL
#include <iostream>
#include <tuple> // defines tie
#include <cstring>
#endif

namespace algo_snippet {
    namespace dynamic_programming {
        template <typename INTTYPE,typename WEIGHTTYPE>
        class floyd_warshall {
        public:
            floyd_warshall(const INTTYPE num_nodes) : dist(num_nodes),prev(num_nodes),num_nodes(num_nodes) {

                // initialize NxN matrix
                for(INTTYPE i = 0; i < num_nodes; i++ ) {
                    dist[i].resize(num_nodes,std::numeric_limits<WEIGHTTYPE>::max());
                    dist[i][i] = 0;
                    prev[i].resize(num_nodes,i);
                }
            }

            void add_undirected_edge(INTTYPE u, INTTYPE v, WEIGHTTYPE weight) {
                dist[u][v] = weight;
                dist[v][u] = weight;
            }

            void add_edge(INTTYPE u, INTTYPE v, WEIGHTTYPE weight) {
                dist[u][v] = weight;
            }

            inline int get_undirected_dist(INTTYPE u, INTTYPE v) const {
                return ((u<=v)?dist[u][v]:dist[v][u]);
            }
            
            void calc() {
                for(INTTYPE k = 0; k < num_nodes; k++) {
                    for(INTTYPE i = 0; i < num_nodes; i++) {
                        if(std::numeric_limits<WEIGHTTYPE>::max() == dist[i][k]) {
                            continue;
                        }
                        for(INTTYPE j = 0; j < num_nodes; j++) {
                            if(std::numeric_limits<WEIGHTTYPE>::max() == dist[k][j]) {
                                continue;
                            }
                            WEIGHTTYPE via = dist[i][k]+dist[k][j];
                            if(via < dist[i][j]) {
                                dist[i][j] = via;
                                prev[i][j] = k;
                            }
                        }
                    }
                }
            }
            void calc_undirected() {
                for(INTTYPE k = 0; k < num_nodes; k++) {
                    for(INTTYPE i = 0; i < num_nodes; i++) {
                        const INTTYPE distik = get_undirected_dist(i,k);
                        if(k == i || std::numeric_limits<WEIGHTTYPE>::max() == distik) {
                            continue;
                        }
                        for(INTTYPE j = i+1; j < num_nodes; j++) {
                            const INTTYPE distkj = get_undirected_dist(k,j);
                            if(j == k || std::numeric_limits<WEIGHTTYPE>::max() == distkj) {
                                continue;
                            }
                            WEIGHTTYPE via = distik+distkj;
                            if(via < dist[i][j]) {
                                dist[i][j] = via;
                                prev[i][j] = k;
                            }
                        }
                    }
                }
            }

            void reconstruct_matrix(INTTYPE u, INTTYPE v) {
                char path[num_nodes][num_nodes];
                memset(path, ' ', sizeof(path));
                // reconstruct path
                if(std::numeric_limits<WEIGHTTYPE>::max() != dist[u][v]) {
                    while(u!=v) {
                        path[u][v] = '*';
                        v = prev[u][v];
                    }
                }

                std::cout << "Infinity=" << std::numeric_limits<WEIGHTTYPE>::max() << std::endl;
                // show column header
                std::cout << "*\t";
                for(INTTYPE i = 0; i < num_nodes; i++) {
                    std::cout << i << "\t";
                }
                std::cout << std::endl;

                // dump matrix
                for(INTTYPE i = 0; i < num_nodes; i++) {
                    // show row header on left
                    std::cout << i << "\t";
                    for(INTTYPE j = 0; j < num_nodes; j++) {
                        // show distance of i to j
                        if(std::numeric_limits<WEIGHTTYPE>::max() == dist[i][j]) {
                            std::cout << "-" << "\t"; // no path
                        } else {
                            std::cout << dist[i][j] << path[i][j] << "\t";
                        }
                    }
                    std::cout << std::endl;
                }
            }
        private:
            //! NxN matrix that contains the edges
            std::vector<std::vector<WEIGHTTYPE>> dist;
            std::vector<std::vector<INTTYPE>> prev;
            const INTTYPE num_nodes;
        };
    }
}

#endif // ALGO_DYNAMIC_PROGRAMMING_FLOYD_WARSHALL_H

