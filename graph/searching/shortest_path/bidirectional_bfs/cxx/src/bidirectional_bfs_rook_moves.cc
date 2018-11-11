// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
bidirectional_bfs_rook_moves.cc file is part of Algosnippet.
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

#include <iostream>
#include "bidirectional_chess_moves.h"

using namespace std;
using namespace algo_snippet::chess_board;

int main()
{
    int n;
    cin >> n;

    vector<vector<char>> color(n);

    for (int i = 0; i < n; i++) {
        string row;
        cin >> row;
        for(auto x : row) {
            color[i].push_back((x=='X')?count_chess_move::BLOCKED:0);
        }
    }

    int startX = 0, startY = 0, goalX = 0, goalY = 0;
    cin >> startX >> startY >> goalX >> goalY;

    chess_piece piece(true,false,false,n);
    int result = count_chess_move::bidirectional_bfs_end_on_expand(
            color, piece, startX, startY, goalX, goalY, true);

    cout << result << "\n";

    for (int i = 0; i < n; i++) {
        for(auto x : color[i]) {
            if(x & count_chess_move::BLOCKED) {
                cout << 'X';
            } else if(x & count_chess_move::PATH){
                cout << 'P';
            } else if(x & count_chess_move::FROM) {
                cout << 'S';
            } else if(x & count_chess_move::TO) {
                cout << 'G';
            } else if(x & count_chess_move::START_GROUP) {
                cout << '~';
            } else if(x & count_chess_move::GOAL_GROUP) {
                cout << '~';
            } else {
                cout << '.';
            }
        }
        cout << endl;
    }

    return 0;
}

