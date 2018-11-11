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
#include <tuple>
//#include <array>

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
                 , board_size(board_size)
                 , xstart(0)
                 , ystart(0) {

                // cannot be rook and the pawn
                assert(!(is_rook && is_pawn));
            }
            void reset(size_t x, size_t y) {
                xstart = x;
                ystart = y;
            }
            void next_phase() {
                state++;
                dist=1;
            }
            auto next_move() {
               int x = (int)xstart;
               int y = (int)ystart;
               switch(state) {
                    if(is_pawn) {
                        assert(!is_rook);
                        case 0:
                            // try up
                            if( (x-dist) >= 0) {
                                x-=dist;
                                state++;
                                break;
                            }
                            dist = 1;
                        case 1:
                            // try left
                            state = 1;
                            if((y-dist) >= 0) {
                                y-=dist;
                                state++;
                                break;
                            }
                            dist = 1;
                        case 2:
                            // try down
                            state = 2;
                            if( (x+dist) < (int)X_BORDER ) {
                                x+=dist;
                                state++;
                                break;
                            }
                            dist = 1;
                        case 3:
                            // try right
                            state = 3;
                            if( (y+dist) < (int)Y_BORDER ) {
                                y+=dist;
                                state++;
                                break;
                            }
                            dist = 1;
                    }
                    if(is_rook) {
                        case 0:
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
                            if( (x+dist) < (int)X_BORDER ) {
                                x+=dist;
                                dist++;
                                break;
                            }
                            dist = 1;
                        case 3:
                            // try right
                            state = 3;
                            if( (y+dist) < (int)Y_BORDER ) {
                                y+=dist;
                                dist++;
                                break;
                            }
                            dist = 1;
                    }
                    if(is_bishop) {
                        case 4:
                            state = 4;
                            // go to right-bottom corner
                            if( (x+dist) < (int)X_BORDER && (y+dist) < (int)Y_BORDER ) {
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
                            if( (x-dist) >= 0 && (y+dist) < (int)Y_BORDER) {
                                x-=dist;
                                y+=dist;
                                dist++;
                                break;
                            }
                            dist = 1;
                        case 7:
                            state = 7;
                            // go to left-bottom corner
                            if( (x+dist) < (int)X_BORDER && (y-dist) >= 0) {
                                x+=dist;
                                y-=dist;
                                dist++;
                                break;
                            }
                            state = 8;
                            dist = 1;
                    } // is_bishop
                    default:
                        break;
                }
                //cout << x << ',' << y << endl;
                return make_pair(x,y);
            }
        private:
            bool is_rook;
            bool is_bishop;
            bool is_pawn;
            size_t board_size;
            size_t xstart;
            size_t ystart;
        };
        class count_chess_move {
        public:
            size_t bidirectional_bfs_end_on_explore(const vector<string> &input
                , int startX
                , int startY
                , int goalX
                , int goalY) {
                // convert string grid to distances
                vector<vector<int>> grid;
                vector<vector<int>> color;
                grid.reserve(input.size());
                for(auto input_line : input) {
                    grid.emplace_back(input_line.size(),INT_MAX);
                    color.emplace_back(input_line.size(),0);
                    for(unsigned int i = 0; i < input_line.size(); i++) {
                        color.back()[i] = (input_line[i] == 'X') ? BLOCKED : 0;
                    }
                }

                // do breadth-first traversal
                deque<pair<int,int>> fringe;
                
                // add start to the fringe
                color[startX][startY] |= START;
                grid[startX][startY] = 0;
                fringe.push_back(make_pair(startX,startY));
              
                // add goal
                color[goalX][goalY] |= GOAL;
                grid[goalX][goalY] = 0;
                fringe.push_back(make_pair(goalX,goalY));
              
                while(!fringe.empty()) {
                    int x = 0, y =0;
                    tie(x,y) = fringe.front();
                    fringe.pop_front();
                  
                    const int mydist = grid[x][y];
                    const int mycolor = (color[x][y] & LINK);
                    // mark expanded
                    assert(LINK != mycolor);
                  
                    // add neighbors to the fringe
                    iter_neighbor neighbor(x,y,grid[0].size(),grid.size());
                    do {
                          int xnext = 0,ynext = 0;
                          tie(xnext,ynext) = neighbor.next();
                          if(xnext == x && ynext == y) {
                               break;
                          }
                      
                          if((color[xnext][ynext] & BLOCKED)) {
                               continue;
                          }
                          
                          if((color[xnext][ynext] & mycolor)) {
                              continue;
                          }
                          fringe.push_back(make_pair(xnext,ynext));
                          color[xnext][ynext] |= mycolor;
                          if((color[xnext][ynext] & LINK) == LINK) {
                              // found
                              return grid[xnext][ynext] + mydist + 1;
                          }
                          grid[xnext][ynext] = mydist+1;
                    } while(true);
                }

                return INT_MAX;
            } // bidirectional_bfs
            size_t bidirectional_bfs_end_on_expand(const vector<string> &input
                    , chess_piece piece
                    , const size_t startX
                    , const size_t startY
                    , const size_t goalX
                    , const size_t goalY) {
                // convert string grid to distances
                vector<vector<size_t>> agrid;
                vector<vector<size_t>> bgrid;
                vector<vector<char>> color;
                agrid.reserve(input.size());
                bgrid.reserve(input.size());
                for(auto input_line : input) {
                    agrid.emplace_back(input_line.size(),INT_MAX);
                    bgrid.emplace_back(input_line.size(),INT_MAX);
                    color.emplace_back(input_line.size(),0);
                    for(size_t i = 0; i < input_line.size(); i++) {
                        color.back()[i] = (input_line[i] == 'X') ? BLOCKED : 0;
                    }
                }

                // do breadth-first traversal
                deque<pair<size_t,size_t>> fringe;
                
                // add start to the fringe
                color[startX][startY] |= START;
                agrid[startX][startY] = 0;
                fringe.push_back(make_pair(startX,startY));
              
                // add goal
                color[goalX][goalY] |= GOAL;
                bgrid[goalX][goalY] = 0;
                fringe.push_back(make_pair(goalX,goalY));
              
                size_t result = INT_MAX;
                while(!fringe.empty()) {
                    size_t x = 0, y =0;
                    tie(x,y) = fringe.front();
                    fringe.pop_front();
                  
                    const char mycolor = (color[x][y] & LINK);
                    assert(!(color[x][y] & BLOCKED));
                    if(LINK == mycolor) {
                        // reached goal
                        return result;
                    }
                    assert(LINK != mycolor);
                    #ifdef DEBUG_MOVE
                    cout << "Expanding " << x << ',' << y << endl;
                    #endif // DEBUG_MOVE
                    const size_t mydist = (mycolor&START) ? agrid[x][y] : bgrid[x][y];
                  
                    // add neighbors to the fringe
                    piece.place(x,y);
                    do {
                          size_t xnext = 0,ynext = 0;
                          tie(xnext,ynext) = piece.next_move();
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
                          cout << "Exploring " << xnext << ',' << ynext << endl;
                          #endif // DEBUG_MOVE
                          fringe.push_back(make_pair(xnext,ynext));
                          color[xnext][ynext] |= mycolor;
                          if(mycolor & START) {
                              // try to do relaxation
                              agrid[xnext][ynext] = min(agrid[xnext][ynext],mydist+1);
                          } else { // when exploring GOAL
                              bgrid[xnext][ynext] = min(bgrid[xnext][ynext],mydist+1);
                          }
                          if((color[xnext][ynext] & LINK) == LINK) {
                              // Relax the goal
                              #ifdef DEBUG_MOVE
                              draw_board(agrid);
                              draw_board(bgrid);
                              draw_board(color);
                              cout << "The move was from " << x << ',' << y << endl;
                              cout << "The move was to " << xnext << ',' << ynext << endl;
                              #endif // DEBUG_MOVE
                              result = min(result, agrid[xnext][ynext]+bgrid[xnext][ynext]);
                          }
                    } while(true);
                }
                return INT_MAX;
            } // bidirectional_dijkstra
        private:
            enum {
                START = 1<<1,
                GOAL = 1<<2,
                BLOCKED = 1<<3,
                LINK = (START | GOAL),
            };
        }; // class count_chess_move
    }
}

#endif // ALGO_GRAPH_BIDIRECTIONAL_CHESS_MOVE_H

