// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
bidirectional_chess_piece.h file is part of Algosnippet.
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

#ifndef ALGO_GRAPH_BIDIRECTIONAL_CHESS_MOVE_H
#define ALGO_GRAPH_BIDIRECTIONAL_CHESS_MOVE_H

#include <algorithm>
#include <iterator>
#include <vector>
#include <deque>
#include <tuple>
#include <limits>
#include <cassert>

namespace algo_snippet {
    namespace chess_board {
        struct chess_piece {
            // Queen move = rook_move + bishop_move
            // King move = pawn_move
            // Knight move = TODO
            chess_piece(bool is_rook, bool is_bishop, bool is_pawn, size_t board_size)
                : is_rook(is_rook)
                 , is_bishop(is_bishop)
                 , is_pawn(is_pawn)
                 , BOARD_SIZE(board_size)
                 , xstart(0)
                 , ystart(0)
                 , state(0)
                 , dist(1) {

                // cannot be rook and the pawn
                assert(!(is_rook && is_pawn));
            }
            void place(size_t x, size_t y) {
                xstart = x;
                ystart = y;
                state = 0;
                dist = 1;
            }
            void next_phase() {
                state++;
                dist = 1;
            }
            auto next_move() {
               int x = (int)xstart;
               int y = (int)ystart;
               switch(state) {
                        case 0:
                    if(is_rook) {
                            // try up
                            if( (x-dist) >= 0) {
                                x-=dist;
                                dist++;
                                break;
                            }
                            dist = 1;
                        case 1:
                            // try left
                            state = 1;
                            if((y-dist) >= 0) {
                                y-=dist;
                                dist++;
                                break;
                            }
                            dist = 1;
                        case 2:
                            // try down
                            state = 2;
                            if( (x+dist) < (int)BOARD_SIZE ) {
                                x+=dist;
                                dist++;
                                break;
                            }
                            dist = 1;
                        case 3:
                            // try right
                            state = 3;
                            if( (y+dist) < (int)BOARD_SIZE ) {
                                y+=dist;
                                dist++;
                                break;
                            }
                            dist = 1;
                    }
                        case 4:
                    if(is_bishop) {
                            state = 4;
                            // go to right-bottom corner
                            if( (x+dist) < (int)BOARD_SIZE && (y+dist) < (int)BOARD_SIZE ) {
                                x+=dist;
                                y+=dist;
                                dist++;
                                break;
                            }
                            dist = 1;
                        case 5:
                            state = 5;
                            // go to left-top corner
                            if( (x-dist) >= 0 && (y-dist) >= 0) {
                                x-=dist;
                                y-=dist;
                                dist++;
                                break;
                            }
                            dist = 1;
                        case 6:
                            state = 6;
                            // go to right-top corner
                            if( (x-dist) >= 0 && (y+dist) < (int)BOARD_SIZE) {
                                x-=dist;
                                y+=dist;
                                dist++;
                                break;
                            }
                            dist = 1;
                        case 7:
                            state = 7;
                            // go to left-bottom corner
                            if( (x+dist) < (int)BOARD_SIZE && (y-dist) >= 0) {
                                x+=dist;
                                y-=dist;
                                dist++;
                                break;
                            }
                            state = 8;
                            dist = 1;
                    } // is_bishop
                        case 8:
                    if(is_pawn) {
                            state = 8;
                            // try up
                            if( (x-1) >= 0) {
                                x--;
                                state++;
                                break;
                            }
                        case 9:
                            // try left
                            state = 9;
                            if((y-1) >= 0) {
                                y--;
                                state++;
                                break;
                            }
                        case 10:
                            // try down
                            state = 10;
                            if( (x+1) < (int)BOARD_SIZE ) {
                                x++;
                                state++;
                                break;
                            }
                        case 11:
                            // try right
                            state = 11;
                            if( (y+1) < (int)BOARD_SIZE ) {
                                y++;
                                state++;
                                break;
                            }
                    }

                    default:
                        break;
                }
                //std::cout << x << ',' << y << std::endl;
                return std::make_pair(x,y);
            }
        private:
            bool is_rook;
            bool is_bishop;
            bool is_pawn;
            const size_t BOARD_SIZE;
            size_t xstart;
            size_t ystart;
            size_t state;
            int dist;
        };
        class count_chess_move {
        public:
            template <typename INTTYPE>
            static void draw_board(const std::vector<std::vector<INTTYPE>> &board) {
                std::cout << "-----------------" << std::endl;
                for(auto row : board) {
                    for(auto col : row) {
                        std::cout << (size_t)col << ',';
                    }
                    std::cout << std::endl;
                }
                std::cout << "-----------------" << std::endl;
            }
            static size_t bidirectional_bfs_end_on_explore(std::vector<std::vector<char>> &color
                , chess_piece &piece
                , int startX
                , int startY
                , int goalX
                , int goalY
                , bool is_bidirectional) {
                size_t pathXS=0,pathYS=0;
                size_t pathXG=0,pathYG=0;
                // convert string dist to distances
                std::vector<std::vector<int>> dist(color.size());
                std::vector<std::vector<std::pair<size_t,size_t>>> pred(color.size());
                for(size_t i = 0; i < color.size(); i++) {
                    pred[i].resize(color.size(),std::make_pair((size_t)startX,(size_t)startY));
                    dist[i].resize(color.size(),std::numeric_limits<int>::max());
                }

                // do breadth-first traversal
                std::deque<std::pair<int,int>> fringe;
                
                // add start to the fringe
                color[startX][startY] |= START_GROUP;
                dist[startX][startY] = 0;
                fringe.push_back(std::make_pair(startX,startY));
              
                // add goal
                color[goalX][goalY] |= GOAL_GROUP;
                dist[goalX][goalY] = 0;
                if(is_bidirectional) {
                    fringe.push_back(std::make_pair(goalX,goalY));
                }
              
                size_t result = std::numeric_limits<size_t>::max();
                bool reached_goal = false;
                while(!fringe.empty() && !reached_goal) {
                    int x = 0, y =0;
                    std::tie(x,y) = fringe.front();
                    fringe.pop_front();
                  
                    const int mydist = dist[x][y];
                    const int mycolor = (color[x][y] & LINK);
                    // mark expanded
                    assert(LINK != mycolor);
                  
                    // add neighbors to the fringe
                    piece.place(x,y);
                    do {
                          int xnext = 0,ynext = 0;
                          std::tie(xnext,ynext) = piece.next_move();
                          if(xnext == x && ynext == y) {
                               break;
                          }
                      
                          if((color[xnext][ynext] & BLOCKED)) {
                               continue;
                          }
                          
                          if((color[xnext][ynext] & mycolor)) {
                              continue;
                          }
                          fringe.push_back(std::make_pair(xnext,ynext));
                          color[xnext][ynext] |= mycolor;
                          if((color[xnext][ynext] & LINK) == LINK) {
                              // found
                              result = dist[xnext][ynext] + mydist + 1;
                              reached_goal = true;
                              if(mycolor & GOAL_GROUP) {
                                  pathXG = x;
                                  pathYG = y;
                                  pathXS = xnext;
                                  pathYS = ynext;
                              } else {
                                  pathXG = xnext;
                                  pathYG = ynext;
                                  pathXS = x;
                                  pathYS = y;
                              }
                                break;
                          }
                          pred[xnext][ynext] = std::make_pair(x,y);
                          dist[xnext][ynext] = mydist+1;
                    } while(!reached_goal);
                }

                if(reached_goal) {
                    // now reconstruct path
                    size_t x = pathXG,y = pathYG;
                    color[startX][startY] |= FROM;
                    color[goalX][goalY] |= TO;
                    while( !(x == (size_t)goalX && y == (size_t)goalY) ) {
                        color[x][y] |= PATH;
                        std::tie(x,y) = pred[x][y];
                    }
                    x = pathXS;
                    y = pathYS;
                    while( !(x == (size_t)startX && y == (size_t)startY) ) {
                        color[x][y] |= PATH;
                        std::tie(x,y) = pred[x][y];
                    }
                }
                return result;
            } // bidirectional_bfs
            static size_t bidirectional_bfs_end_on_expand(std::vector<std::vector<char>> &color
                    , chess_piece &piece
                    , const size_t startX
                    , const size_t startY
                    , const size_t goalX
                    , const size_t goalY
                    , bool bidirectional) {
                // convert string grid to distances
                std::vector<std::vector<size_t>> start_dist(color.size());
                std::vector<std::vector<std::pair<size_t,size_t>>> start_pred(color.size());
                std::vector<std::vector<size_t>> goal_dist(color.size());
                std::vector<std::vector<std::pair<size_t,size_t>>> goal_pred(color.size());
                size_t pathX = goalX;
                size_t pathY = goalY;

                for(size_t i = 0; i < color.size(); i++) {
                    start_dist[i].resize(color.size(),std::numeric_limits<int>::max());
                    start_pred[i].resize(color.size(),std::make_pair((size_t)startX,(size_t)startY));
                    goal_dist[i].resize(color.size(),std::numeric_limits<int>::max());
                    goal_pred[i].resize(color.size(),std::make_pair((size_t)goalX,(size_t)goalY));
                }

                // do breadth-first traversal
                std::deque<std::pair<size_t,size_t>> fringe;
                
                // add start to the fringe
                color[startX][startY] |= START_GROUP;
                start_dist[startX][startY] = 0;
                fringe.push_back(std::make_pair(startX,startY));
              
                // add goal
                color[goalX][goalY] |= GOAL_GROUP;
                goal_dist[goalX][goalY] = 0;
                if(bidirectional) {
                    fringe.push_back(std::make_pair(goalX,goalY));
                }
              
                bool reached_goal = false;
                size_t result = std::numeric_limits<size_t>::max();
                while(!fringe.empty()) {
                    size_t x = 0, y =0;
                    std::tie(x,y) = fringe.front();
                    fringe.pop_front();
                  
                    const char mycolor = (color[x][y] & LINK);
                    assert(!(color[x][y] & BLOCKED));
                    if(LINK == mycolor) {
                        // reached goal
                        reached_goal = true;
                        break;
                    }
                    assert(LINK != mycolor);
                    #ifdef DEBUG_MOVE
                    std::cout << "Expanding " << x << ',' << y << std::endl;
                    #endif // DEBUG_MOVE
                    const size_t mydist = (mycolor&START_GROUP) ? start_dist[x][y] : goal_dist[x][y];
                  
                    // add neighbors to the fringe
                    piece.place(x,y);
                    do {
                          size_t xnext = 0,ynext = 0;
                          std::tie(xnext,ynext) = piece.next_move();
                          if(xnext == x && ynext == y) {
                               break;
                          }
                          if((color[xnext][ynext] & BLOCKED)) {
                               piece.next_phase();
                               continue;
                          }
                          if((color[xnext][ynext] & mycolor)) {
                               // piece.next_phase();
                               continue;
                          }
                          #ifdef DEBUG_MOVE
                          std::cout << "Exploring " << xnext << ',' << ynext << std::endl;
                          #endif // DEBUG_MOVE
                          fringe.push_back(std::make_pair(xnext,ynext));
                          color[xnext][ynext] |= mycolor;
                          if(mycolor & START_GROUP) {
                              // try to do relaxation
                                if(start_dist[xnext][ynext] > (mydist+1)) {
                                    start_dist[xnext][ynext] = mydist+1;
                                    start_pred[xnext][ynext] = std::make_pair(x,y);
                                }
                          } else { // when exploring GOAL_GROUP
                                if(goal_dist[xnext][ynext] > (mydist+1)) {
                                    goal_dist[xnext][ynext] = mydist+1;
                                    goal_pred[xnext][ynext] = std::make_pair(x,y);
                                }
                          }
                          if((color[xnext][ynext] & LINK) == LINK) {
                              // Relax the goal
                              #ifdef DEBUG_MOVE
                              draw_board(start_dist);
                              draw_board(goal_dist);
                              draw_board(color);
                              std::cout << "The move was from " << x << ',' << y << std::endl;
                              std::cout << "The move was to " << xnext << ',' << ynext << std::endl;
                              #endif // DEBUG_MOVE
                              if(result > (start_dist[xnext][ynext]+goal_dist[xnext][ynext])) {
                                result = start_dist[xnext][ynext]+goal_dist[xnext][ynext];
                                reached_goal = true;
                                pathX = xnext;
                                pathY = ynext;
                              }
                          }
                    } while(true);
                }


                if(reached_goal) {
                    // now reconstruct path
                    size_t x = pathX,y = pathY;
                    color[startX][startY] |= FROM;
                    color[goalX][goalY] |= TO;
                    while( !(x == (size_t)goalX && y == (size_t)goalY) ) {
                        color[x][y] |= PATH;
                        std::tie(x,y) = goal_pred[x][y];
                    }
                    x = pathX;
                    y = pathY;
                    while( !(x == (size_t)startX && y == (size_t)startY) ) {
                        color[x][y] |= PATH;
                        std::tie(x,y) = start_pred[x][y];
                    }
                }

                return result;
            } // bidirectional_dijkstra
            enum {
                START_GROUP = 1<<1,
                GOAL_GROUP = 1<<2,
                BLOCKED = 1<<3,
                LINK = (START_GROUP | GOAL_GROUP),
                PATH = 1<<4,
                FROM = 1<<5,
                TO = 1<<6,
            };
        }; // class count_chess_move
    }
}

#endif // ALGO_GRAPH_BIDIRECTIONAL_CHESS_MOVE_H

