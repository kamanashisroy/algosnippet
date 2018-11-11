#include <bits/stdc++.h>

using namespace std;

enum {
    START = 1<<1,
    GOAL = 1<<2,
    BLOCKED = 1<<3,
    LINK = (START | GOAL),
};

struct iter_neighbor {
   iter_neighbor(size_t x, size_t y, size_t X_BORDER, size_t Y_BORDER)
     : x(x),y(y),state(0),dist(1),X_BORDER(X_BORDER),Y_BORDER(Y_BORDER) {
   }
   void next_phase() {
       state++;
       dist=1;
   }
   auto next() {
       int xnext = (int)x;
       int ynext = (int)y;
       switch(state) {
           case 0:
              // try up
              if( (xnext-dist) >= 0) {
                  xnext-=dist;
                  dist++;
                  break;
              }
              state = 1;
              dist = 1;
           case 1:
              // try left
              if((ynext-dist) >= 0) {
                  ynext-=dist;
                  dist++;
                  break;
              }
              state = 2;
              dist = 1;
           case 2:
              // try down
              if( (xnext+dist) < (int)X_BORDER ) {
                  xnext+=dist;
                  dist++;
                  break;
              }
              state = 3;
              dist = 1;
           case 3:
              // try right
              if( (ynext+dist) < (int)Y_BORDER ) {
                  ynext+=dist;
                  dist++;
                  break;
              }
              state = 4;
              dist = 1;
           #ifdef CORNER_MOVES
           case 4:
              // go to right-bottom corner
              if( (xnext+dist) < (int)X_BORDER && (ynext+dist) < (int)Y_BORDER ) {
                  xnext+=dist;
                  ynext+=dist;
                  dist++;
                  break;
              }
              state = 5;
              dist = 1;
           case 5:
              // go to left-top corner
              if( (xnext-dist) >= 0 && (ynext-dist) >= 0) {
                  xnext-=dist;
                  ynext-=dist;
                  dist++;
                  break;
              }
              state = 6;
              dist = 1;
           case 6:
              // go to right-top corner
              if( (xnext-dist) >= 0 && (ynext+dist) < (int)Y_BORDER) {
                  xnext-=dist;
                  ynext+=dist;
                  dist++;
                  break;
              }
              state = 7;
              dist = 1;
           case 7:
              // go to left-bottom corner
              if( (xnext+dist) < (int)X_BORDER && (ynext-dist) >= 0) {
                  xnext+=dist;
                  ynext-=dist;
                  dist++;
                  break;
              }
              state = 8;
              dist = 1;
           #endif
         default:
              break;
       }
       //cout << xnext << ',' << ynext << endl;
       return make_pair(xnext,ynext);
   }
private:
   size_t x;
   size_t y;
   size_t state;
   int dist;
   const size_t X_BORDER;
   const size_t Y_BORDER;
};

void draw_board(const vector<vector<size_t>> &board) {
    cout << "-----------------" << endl;
    for(auto row : board) {
        for(auto col : row) {
            cout << col << ',';
        }
        cout << endl;
    }
    cout << "-----------------" << endl;
}

// Complete the minimumMoves function below.
size_t minimumMoves(const vector<string> &input, const size_t startX, const size_t startY, const size_t goalX, const size_t goalY) {
  
    // convert string grid to distances
    vector<vector<size_t>> agrid;
    vector<vector<size_t>> bgrid;
    vector<vector<size_t>> color;
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
      
        const size_t mycolor = (color[x][y] & LINK);
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
        iter_neighbor neighbor(x,y,color[0].size(),color.size());
        do {
              size_t xnext = 0,ynext = 0;
              tie(xnext,ynext) = neighbor.next();
              if(xnext == x && ynext == y) {
                   break;
              }
              if((color[xnext][ynext] & BLOCKED)) {
                   neighbor.next_phase();
                   continue;
              }
              if((color[xnext][ynext] & mycolor)) {
                   // neighbor.next_phase();
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
}

int main()
{
    size_t n;
    cin >> n;

    vector<string> grid(n);

    for (size_t row = 0; row < n; row++) {
        string colstr;
        cin >> colstr;
        grid[row] = colstr;
    }

    size_t startX,startY,goalX,goalY;
    cin >> startX >> startY >> goalX >> goalY;

    size_t result = minimumMoves(grid, startX, startY, goalX, goalY);

    cout << result << "\n";

    return 0;
}

