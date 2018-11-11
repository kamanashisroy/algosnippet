#include <bits/stdc++.h>

using namespace std;

enum {
    START = 1<<1,
    GOAL = 1<<2,
    BLOCKED = 1<<3,
    LINK = (START | GOAL),
};

struct iter_neighbor {
   iter_neighbor(int x, int y, int X_BOUNDARY, int Y_BOUNDARY)
     : x(x),y(y),state(0),X_BOUNDARY(X_BOUNDARY),Y_BOUNDARY(Y_BOUNDARY) {
   }
   auto next() {
       int xnext = x;
       int ynext = y;
       switch(state) {
           case 0:
              // try left
              if(xnext > 0) {
                  xnext--;
                  state = 1;
                  break;
              }
           case 1:
              // try top
              if(ynext < 0) {
                  ynext--;
                  state = 2;
                  break;
              }
           case 2:
              // try right
              if( xnext < (X_BOUNDARY-1) ) {
                  xnext++;
                  state = 3;
                  break;
              }
           case 3:
              // try down
              if( ynext < (Y_BOUNDARY-1) ) {
                  ynext++;
                  state = 4;
                  break;
              }
         default:
              break;
       }
       return make_pair(xnext,ynext);
   }
private:
   int x;
   int y;
   int state;
   const int X_BOUNDARY;
   const int Y_BOUNDARY;
};

// Complete the minimumMoves function below.
int minimumMoves(const vector<string> &input, int startX, int startY, int goalX, int goalY) {
  
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
}

int main()
{
    int n;
    cin >> n;

    vector<string> grid(n);

    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    int startX = 0, startY = 0, goalX = 0, goalY = 0;
    cin >> startX >> startY >> goalX >> goalY;

    int result = minimumMoves(grid, startX, startY, goalX, goalY);

    cout << result << "\n";

    return 0;
}

