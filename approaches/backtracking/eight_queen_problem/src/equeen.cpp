
#include <string.h>
#include <queue>
#include <iostream>
#include <cstdio>

int debug = 0;
#define DIAG 32
typedef int8_t bl_t;
using namespace std;
static inline int skip_check(bl_t*skip_cols,bl_t*skip_rows, bl_t*skips, int row, int column) {
	return skip_cols[column] || skip_rows[row] || skips[8+row-column] || skips[16+row+column];
}

static inline void set_skips(bl_t*skip_cols, bl_t*skip_rows, bl_t*skips, int row, int column) {
	skip_cols[column] = skip_rows[row] = skips[8+row-column] = skips[16+row+column] = 1;
}


static int dump_allowed_moves(bl_t*skip_cols, bl_t*skip_rows, bl_t*skip_diags) {
	if(debug < 10)
		return 0;
	for(int i = 0; i < 8; i++) {
		cout << "\t";
		for(int j = 0; j < 8; j++) {
			cout << skip_check(skip_cols, skip_rows, skip_diags, i, j) << "\t";
		}
		cout << endl;
	}
	return 0;
}

static int test_diagonal(int row, int column) {
	if(debug < 10)
		return 0;
	cout << "Testing skip matrix for row = " << row << " column = " << column << endl;
	bl_t skip_cols[8];
	bl_t skip_rows[8];
	bl_t skip_diags[DIAG];
	memset(skip_cols, 0, sizeof(skip_cols));
	memset(skip_rows, 0, sizeof(skip_rows));
	memset(skip_diags, 0, sizeof(skip_diags));
	set_skips(skip_cols, skip_rows, skip_diags, row, column);
	dump_allowed_moves(skip_cols, skip_rows, skip_diags);
	return 0;
}


static int eight_queen_subproblem(bl_t*pos, bl_t*skip_cols, bl_t*skip_rows, bl_t*skip_diags, const int row, const int column) {
	if(skip_check(skip_cols, skip_rows, skip_diags, row, column)) { // we cannot position the queen at this column
		return 0;
	}
	if(row >= 7) { // successful base case
		return 1;
	}
	bl_t myskip_cols[8];
	bl_t myskip_rows[8];
	bl_t myskip_diags[DIAG];
	memcpy(myskip_cols, skip_cols, 8*sizeof(bl_t));
	memcpy(myskip_rows, skip_rows, 8*sizeof(bl_t));
	memcpy(myskip_diags, skip_diags, DIAG*sizeof(bl_t));
	set_skips(myskip_cols, myskip_rows, myskip_diags, row, column);
	if(debug > 5)
		cout << "We are at row = " << row << " column = " << column << endl;
	dump_allowed_moves(myskip_cols, myskip_rows, myskip_diags);
	for(int i = 0; i < 8; i++) {
		/* now go for next row and try it */
		if(eight_queen_subproblem(pos, myskip_cols, myskip_rows, myskip_diags, row+1, i) == 1) {
			pos[row*8+column] = 1;
			cout << "Successful" << endl;
			return 1;
		}
	}
	return 0;
}

int main(int argc, char*argv[]) {
	bl_t pos[8][8];
	bl_t skip_cols[8];
	bl_t skip_rows[8];
	bl_t skip_diags[DIAG];
	memset(pos, 0, sizeof(pos));
	memset(skip_cols, 0, sizeof(skip_cols));
	memset(skip_rows, 0, sizeof(skip_cols));
	memset(skip_diags, 0, sizeof(skip_diags));

	test_diagonal(0,0);
	test_diagonal(2,2);
	test_diagonal(0,4);
	test_diagonal(3,4);
	test_diagonal(2,4);
	
	int i = 0;
	for(i = 0; i < 8; i++) {
		if(eight_queen_subproblem((bl_t*)pos, skip_cols, skip_rows, skip_diags, 0, i) == 0)
			continue;
		break;
	}
	cout << "One possible solution\n";
	for(i = 0; i < 8; i++) {
		cout << "\t";
		for(int j = 0; j < 8; j++) {
			cout << ((int)pos[i][j]) << '\t';
		}
		cout << endl;
	}
	return 0;
}

