#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void dump(int*mem, const int y_size, int j) {
    cout << j << " -------------------\n";
    for(int i = 0; i < y_size+1; i++) {
        cout << mem[i] << ',';
    }
    cout << '\n';
}

int lcs(const int x_size, const int y_size) {
    int x[x_size];
    int y[y_size];
    int mem[x_size+1][y_size+1];
    int i = 0,j = 0;
    for(i = 0 ; i < x_size; i++) {
        cin >> x[i];
        mem[i][0] = 0;
    }
    mem[i][0] = 0;
    for(i = 0 ; i < y_size; i++) {
        cin >> y[i];
        mem[0][i] = 0;
    }
    mem[0][i] = 0;

    // find longest common substring
    for(i = 0; i < x_size; i++) {
        for(j = 0; j < y_size; j++) {
            
            if(x[i] == y[j]) {
                mem[i+1][j+1] = mem[i][j]+1;
            } else {
                mem[i+1][j+1] = (mem[i+1][j] > mem[i][j+1])?mem[i+1][j]:mem[i][j+1];
            }
        }
        //dump(mem[i+1], y_size, i+1);
    }
    
    /**/
    
    // print longest common substring
    int lcs_len = mem[x_size][y_size];
    //vector<int> lcs(lcs_len);
    vector<int> lcs;
    //cout << lcs_len << '\n';
    j = y_size;
    i = x_size;
    while(lcs_len) {
        if(x[i-1] == y[j-1]) {
            //cout << x[i] << ' ';
            lcs.push_back(x[i-1]);
            lcs_len--;i--;j--;
        } else if(mem[i][j-1] > mem[i-1][j]){
            j--;
        } else {
            i--;
        }
    }
    //cout << '\n';
    vector<int>::reverse_iterator it = lcs.rbegin();
    for(;it != lcs.rend();it++) {
        cout << *it << ' ';
    }
    cout << '\n';
    return 0;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int m,n;
    cin >> m >> n;
    lcs(m,n);
    return 0;
}

