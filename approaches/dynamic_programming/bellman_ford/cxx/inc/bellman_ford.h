// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
bellman_ford.h file is part of Algosnippet.
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

#ifndef ALGO_DYNAMIC_PROGRAMMING_BELLMAN_FORD_H
#define ALGO_DYNAMIC_PROGRAMMING_BELLMAN_FORD_H

#include <algorithm>
#include <limits>
#include <tuple> // defines tie
#include <vector>

#ifdef DEBUG_BELLMAN_FORD
#include <iostream>
#include <cstring>
#endif

namespace algo_snippet {
    namespace dynamic_programming {
        template <typename INTTYPE,typename WEIGHTTYPE>
        class bellman_ford {
        public:
            bellman_ford(const INTTYPE num_nodes) : dist(num_nodes),pred(num_nodes),num_nodes(num_nodes) {
            }

            void add_edge(INTTYPE u, INTTYPE v, WEIGHTTYPE weight) {
                edges.emplace_back(u,v,weight);
            }

            //! return false when negative cycle
            bool calc(INTTYPE source) {
                std::fill(dist.begin(),dist.end(),std::numeric_limits<INTTYPE>::max());

                // run Bellman-Ford
                INTTYPE u = 0,v = 0;
                WEIGHTTYPE w = 0;
                INTTYPE num_relaxation = num_nodes;
                dist[source] = 0;
                while(num_relaxation--) {
                    bool has_relaxation = false;
                    for(const auto xedge : edges) {
                        std::tie(u,v,w) = xedge;

                        if(std::numeric_limits<INTTYPE>::max() == dist[u]) {
                            continue;
                        }

                        if((dist[u]+w) < dist[v]) {
                            // relaxation
                            dist[v] = dist[u]+w;
                            pred[v] = u;
                            has_relaxation = true;
                        }
                    }
                    if(!has_relaxation) {
                        break; // no more loop needed
                    }
                }
                for(const auto xedge : edges) {
                    std::tie(u,v,w) = xedge;
                    if(std::numeric_limits<INTTYPE>::max() == dist[u]) {
                        continue;
                    }
                    if((dist[u]+w) < dist[v]) {
                        return false; // negative cycle
                    }
                }
                return true;
            }

            WEIGHTTYPE get_distance(INTTYPE dest) {
                return dist[dest];
            }

            void dump(std::ostream& ostrm) {
                for(int i = 0; i < num_nodes; i++) {
                    ostrm << i << "\t\t";
                }
                ostrm << std::endl;
                for(int i = 0; i < num_nodes; i++) {
                    if((std::numeric_limits<WEIGHTTYPE>::max()==dist[i])) {
                        ostrm << '-' << "\t\t";
                    } else {
                        ostrm << dist[i] << "\t\t";
                    }
                }
                ostrm << std::endl;
                for(int i = 0; i < num_nodes; i++) {
                    ostrm << pred[i] << "\t\t";
                }
                ostrm << std::endl;
            }
        private:
            //! edge list
            std::vector<std::tuple<INTTYPE,INTTYPE,WEIGHTTYPE>> edges;
            std::vector<WEIGHTTYPE> dist;
            std::vector<INTTYPE> pred;
            const INTTYPE num_nodes;
        };
    }
}

#endif // ALGO_DYNAMIC_PROGRAMMING_BELLMAN_FORD_H

