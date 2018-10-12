#include <iostream>
#include <vector>
#include <cassert>
#include <cstring>

using namespace std;

//#define DEBUG

#define BOARD_SIZE 9
#define SQUARE_SIZE 3
#define NUM_SQUARE 9
#define NUM_DIGITS 9

// There are total 9! = 362880 possible square formation in 3x3 square of 9 numbers.
// Considering the rotation and mirrors we can reduce the possible square to (9!/8) = 45360
// Now we have total 9! = 362880 possible square placement in 9x9 board of 9 squares.
// Now considering the squares that can be placed in the same row or in the same column we can reduce it further.

struct sudoku_square {
    //! Each digit 1-9 can be at one of 9 positions.
    uint8_t rotation[NUM_DIGITS];
    sudoku_square() : rotation{0},mask{0},digit_state{-1} {
        memset(rotation, 0, sizeof(rotation));
    }
    //! it builds the next possible sudoku square
    inline sudoku_square next(int digit_index, int digit_rotation) const { 
        assert(digit_index < NUM_DIGITS);
        assert(digit_index == (digit_state+1)); // push
        sudoku_square sqresult(*this);
        sqresult.rotation[digit_index] = digit_rotation;
        sqresult.digit_state = digit_index;
        sqresult.mask |= 0x100 >> digit_rotation;
        return sqresult;
    }
    inline void get_digit_mask_row_wise(uint16_t (&digit_mask)[SQUARE_SIZE]) const {
        assert(-1 != digit_state);
        memset(digit_mask, 0, sizeof(digit_mask));
        for(int i = 0; i < NUM_DIGITS && i <= digit_state; i++) {
            assert(rotation[i] < NUM_DIGITS);
            digit_mask[rotation[i]/SQUARE_SIZE] |= 1U<<i;
        }
    }
    inline void get_digit_mask_column_wise(uint16_t (&digit_mask)[SQUARE_SIZE]) const {
        assert(-1 != digit_state);
        memset(digit_mask, 0, sizeof(digit_mask));
        for(int i = 0; i < NUM_DIGITS && i <= digit_state; i++) {
            assert(rotation[i] < NUM_DIGITS);
            digit_mask[rotation[i]%SQUARE_SIZE] |= 1U<<i;
        }
    }
    inline int8_t get_next_digit_index() const {
        return digit_state+1;
    }
    inline uint16_t top_digit_mask() const {
        return 1U << digit_state;
    }
    inline int8_t top_digit() const {
        return digit_state+1;
    }
    inline void get_square_grid(int (&grid)[SQUARE_SIZE][SQUARE_SIZE]) const {
        for(int i = 0; i < NUM_DIGITS && i <= digit_state; i++) {
            grid[rotation[i]/3][rotation[i]%3] = i+1;
        }
    }
    inline uint16_t get_mask() const {
        return mask;
    }
    inline bool is_occupied(int digit_rotation) const {
        const uint16_t digit_mask = 0x100 >> digit_rotation;
        return digit_mask & get_mask();
    }
    inline bool is_complete() const {
        return NUM_DIGITS == (digit_state+1);
    }
private:
    uint16_t mask;
    int8_t digit_state; /* digit_value = digit_state+1 */
    
};

ostream& operator<<(ostream& ostrm, const sudoku_square& sqr) {
    int sqr_grid[SQUARE_SIZE][SQUARE_SIZE];
    memset(sqr_grid, 0, sizeof(sqr_grid));
    sqr.get_square_grid(sqr_grid);
    ostrm << "[square:";
    for(int i = 0; i < SQUARE_SIZE; i++) {
        for(int j = 0; j < SQUARE_SIZE; j++) {
            ostrm << sqr_grid[i][j] << ' ';
        }
        ostrm << ',';
    }
    ostrm << "]";
    return ostrm;
}

ostream& operator<<(ostream& ostrm, const int (&grid)[BOARD_SIZE][BOARD_SIZE]) {
    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < (BOARD_SIZE-1); j++) {
            ostrm << grid[i][j] << ' ';
        }
        ostrm << grid[i][BOARD_SIZE-1] << endl;
    }
    return ostrm;
}

class square_generator {
public:
    square_generator(int square_index, const int (&base_grid)[BOARD_SIZE][BOARD_SIZE])
        : square_index(square_index)
            , base_row((square_index/3)*3)
            , base_col((square_index%3)*3)
            , base_grid(base_grid) {
        // So the second position can be placed anywhere from 1-9, we can denote them as bitmask,
        // 0b000000000 = 9 bit bit-mask represents the problem
        // So the first digit can be placed in,
        // 0x100 = 0b100000000 = rotation[0] = 0
        //         0b010000000 = rotation[0] = 1
        //         0b000010000 = rotation[0] = 4
        // the positions above.

        // make sudoku stack for depth-first traversal

        // Add 3 root nodes of the transformation tree
        //sudoku_square rotationA,rotationB,rotationC;
        // 0x100 = 0b100000000 = rotation[0] = 0
        //rotationA = rotationA.next(0,0);
        //         0b010000000 = rotation[0] = 1
        //rotationB = rotationB.next(0,1);
        //         0b000010000 = rotation[0] = 4
        //rotationC = rotationC.next(0,4);
        //sudoku_stack.push_back(rotationA);
        //sudoku_stack.push_back(rotationB);
        //sudoku_stack.push_back(rotationC);

        
        // update composed grid
        memcpy(composed_grid, base_grid, sizeof(composed_grid));

        reset_composed_grid();
        for(int row=0;row < SQUARE_SIZE; row++) {
            const int board_row = base_row + row;
            uint16_t mask = 0;
            for(int board_col = 0; board_col < BOARD_SIZE; board_col++) {
                if(composed_grid[board_row][board_col] == 0) {
                    continue;
                }
                mask |= 1U << (composed_grid[board_row][board_col]-1);
            }
            row_wise_exclusive_mask[row] = mask;
        }
        for(int col=0;col < SQUARE_SIZE; col++) {
            const int board_col = base_col + col;
            uint16_t mask = 0;
            for(int board_row = 0; board_row < BOARD_SIZE; board_row++) {
                if(composed_grid[board_row][board_col] == 0) {
                    continue;
                }
                mask |= 1U << (composed_grid[board_row][board_col]-1);
            }
            col_wise_exclusive_mask[col] = mask;
        }

        // add all rotation of 1 in the solution square if acceptable
        sudoku_square dummy;
        for(int rotation = 0; rotation < NUM_DIGITS; rotation++) {
            const uint8_t base_value = get_base_board_at_rotation(rotation);
            if(base_value && base_value != 1) {
                continue;
            }
            if(!is_valid_rotation(1,rotation)) {
                continue;
            }
            sudoku_square xsqr = dummy.next(0,rotation);
            //if(!is_valid(xsqr)) {
            //    continue;
            //}
            sudoku_stack.push_back(xsqr);
        }

    }
    ~square_generator() {
        sudoku_stack.clear();
    }

    void self_test() {
        int test_grid[BOARD_SIZE][BOARD_SIZE] = {
            {1,0,0,   0,0,0,  0,0,0}
            ,{0,6,0,  0,2,1,  0,0,0}
            ,{0,8,0,  0,0,0,  0,0,0}

            ,{0,4,0,  0,0,0,  0,0,0}
            ,{0,0,0,  3,0,0,  0,0,2}
            ,{0,0,0,  0,5,0,  0,0,0}

            ,{0,0,0,  0,0,0,  6,0,0}
            ,{0,0,0,  0,0,0,  0,0,0}
            ,{0,0,0,  0,0,0,  0,0,0}
        };

        // select top,left square
        square_generator genA(0,test_grid);
        assert(genA.get_base_board_at_rotation(0) == 1);
        assert(genA.get_base_board_at_rotation(4) == 6);
        //assert(genE.sudoku_stack.back().get_mask() == 0b100010);

        // select middle 9x9 square
        //  x x x     0 0 0
        //  x x x     3 0 0
        //  x x x     0 5 0
        square_generator genE(4,test_grid);
        assert(genE.get_base_board_at_rotation(3) == 3);
        assert(genE.get_base_board_at_rotation(7) == 5);
        //assert(genE.sudoku_stack.back().get_mask() == 0b100010);
        cout << "Board read test successful" << endl;


        cout << "Testing 3x3 square permutations ....(next_square)" << endl;
        cout << genA.sudoku_stack.back() << endl;
        cout << genE.sudoku_stack.back() << endl;
        const sudoku_square xa = genA.next_square();
        const sudoku_square xe = genE.next_square();
        assert(9 == xa.get_next_digit_index());
        cout << "9 means all 9 numbers are chosen correctly:" << (int)xa.get_next_digit_index() << endl;
        cout << xa << endl;
        assert(9 == xe.get_next_digit_index());
        cout << xe << endl;
        cout << "Square creation successful" << endl;


        cout << "Testing 3x3 square permutations ....(digit-mask)" << endl;
        uint16_t digit_mask[SQUARE_SIZE];
        cout << "Digit mask at each row/column should have popcount=3 and (&)ing will result in 0" << endl;
        xa.get_digit_mask_row_wise(digit_mask);
        cout << "xa digit-mask(hex):";
        uint16_t test_mask = 0;
        for(int i = 0; i < SQUARE_SIZE; i++) {
            cout << "0x" << hex << digit_mask[i] << ' ';
            assert(__builtin_popcount(digit_mask[i]) == SQUARE_SIZE);
            test_mask |= digit_mask[i];
        }
        cout << "0x" << hex << test_mask << endl;
        assert(__builtin_popcount(test_mask) == NUM_DIGITS);
        cout << "xa Square digit-mask test successful" << endl;

        cout << "Checking the middle square to be complete" << endl;
        cout << (int)xe.get_next_digit_index() << endl;
        assert(xe.is_complete());
        if(xe.is_complete()) {
            memset(digit_mask,0,sizeof(digit_mask));
            xe.get_digit_mask_row_wise(digit_mask);
            cout << "digit-mask:" << endl;
            test_mask = 0;
            for(int i = 0; i < SQUARE_SIZE; i++) {
                cout << digit_mask[i] << ' ';
                assert(__builtin_popcount(digit_mask[i]) == SQUARE_SIZE);
                test_mask |= digit_mask[i];
            }
            cout << "0x" << hex << test_mask << endl;
            assert(__builtin_popcount(test_mask) == NUM_DIGITS);

            memset(digit_mask,0,sizeof(digit_mask));
            xe.get_digit_mask_column_wise(digit_mask);
            cout << "digit-mask:" << endl;
            test_mask = 0;
            for(int i = 0; i < SQUARE_SIZE; i++) {
                cout << digit_mask[i] << ' ';
                assert(__builtin_popcount(digit_mask[i]) == SQUARE_SIZE);
                test_mask |= digit_mask[i];
            }
            cout << "0x" << hex << test_mask << endl;
            assert(__builtin_popcount(test_mask) == NUM_DIGITS);
        }
        cout << "middle square test successful" << endl;


        cout << endl;
        cout << genA.composed_grid << endl;
        cout << genE.composed_grid << endl;

        const int ibase_row = (genE.square_index/3)*3;
        for(int row=0;row < SQUARE_SIZE; row++) {
            const int board_row = ibase_row + row;
            uint16_t mask = 0;
            for(int board_col = 0; board_col < BOARD_SIZE; board_col++) {
                if(genE.composed_grid[board_row][board_col] == 0) {
                    continue;
                }
                mask |= 1U << (genE.composed_grid[board_row][board_col]-1);
            }
            cout << "row=" << row << ", mask=" << mask << endl;
        }
 
        const int ibase_col = (genE.square_index%3)*3;
        for(int col=0;col < SQUARE_SIZE; col++) {
            const int board_col = ibase_col + col;
            uint16_t mask = 0;
            for(int board_row = 0; board_row < BOARD_SIZE; board_row++) {
                if(genE.composed_grid[board_row][board_col] == 0) {
                    continue;
                }
                // cout << "checking " << board_row << ',' << board_col << ":" << genE.composed_grid[board_row][board_col] << endl;
                // assert(0 != genE.composed_grid[board_row][board_col]);
                mask |= 1U << (genE.composed_grid[board_row][board_col]-1);
            }
            cout << "col=" << col << ", mask=" << mask << endl;
        }

        #ifdef DEBUG_FULL
        cout << "Checking all rotations of sudoku square" << endl;
        
        const sudoku_square x = sudoku_stack.back();
        for(int rotation = 0; rotation < NUM_DIGITS; rotation++) {
            if(x.is_occupied(rotation)) {
                // We already played with this digit in previous digit-index
                continue;
            }
            sudoku_square y = x.next(x.get_next_digit_index(),rotation);
            // this rotation works
            cout << "Expanding" << y << endl;
            for(int rotation2 = 0; rotation2 < NUM_DIGITS; rotation2++) {
                if(y.is_occupied(rotation2)) {
                    // We already played with this digit in previous digit-index
                    continue;
                }
                sudoku_square z = y.next(y.get_next_digit_index(),rotation2);
                // this rotation works
                cout << z << endl;
            }
        }
        cout << "Tried all rotations" << endl;
        #endif // DEBUG_FULL
    }
    
    // DFS Tree
    // 
    const sudoku_square next_square() {
        // do dfs
        while(!sudoku_stack.empty()) {
            const sudoku_square x = sudoku_stack.back();
            sudoku_stack.pop_back();

            if(x.get_next_digit_index() < NUM_DIGITS) {
                // we have more digits to consider
                // explore next digit positions
                // Below is the all rotation of 2 after 1 is set
                // [square:2 0 0 ,0 0 0 ,0 0 1 ,]
                // [square:0 2 0 ,0 0 0 ,0 0 1 ,]
                // [square:0 0 2 ,0 0 0 ,0 0 1 ,]
                // [square:0 0 0 ,2 0 0 ,0 0 1 ,]
                // [square:0 0 0 ,0 2 0 ,0 0 1 ,]
                // [square:0 0 0 ,0 0 2 ,0 0 1 ,]
                // [square:0 0 0 ,0 0 0 ,2 0 1 ,]
                // [square:0 0 0 ,0 0 0 ,0 2 1 ,]
                // [square:0 0 0 ,0 0 0 ,0 0 2 ,] discarded case
                // Below is the all rotation of 3 after 1,2 is set
                /* [square:3 0 0 ,0 0 0 ,0 0 1 ,] discarded case */
                /* [square:2 3 0 ,0 0 0 ,0 0 1 ,] */
                /* [square:2 0 3 ,0 0 0 ,0 0 1 ,] */
                /* [square:2 0 0 ,3 0 0 ,0 0 1 ,] */
                /* [square:2 0 0 ,0 3 0 ,0 0 1 ,] */
                /* [square:2 0 0 ,0 0 3 ,0 0 1 ,] */
                /* [square:2 0 0 ,0 0 0 ,3 0 1 ,] */
                /* [square:2 0 0 ,0 0 0 ,0 3 1 ,] */
                /* [square:2 0 0 ,0 0 0 ,0 0 3 ,] discarded case */
           
                for(int rotation = 0; rotation < NUM_DIGITS; rotation++) {

                    // if the base-board has any number assigned then the square has to match that
                    const uint8_t base_value = get_base_board_at_rotation(rotation);
                    if(base_value && base_value != (x.get_next_digit_index()+1)) {
                        // base-board has different non-zero value than our square
                        continue;
                    }

                    if(x.is_occupied(rotation)) {
                        // We already played with this digit in previous digit-index
                        continue;
                    }
                    if(!is_valid_rotation(1U<<x.get_next_digit_index(),rotation)) {
                        continue;
                    }
                    sudoku_square y = x.next(x.get_next_digit_index(),rotation);
                    //if(!is_valid(y)) {
                    //    continue;
                    //}
                    // this rotation works
                    sudoku_stack.push_back(y);
                }
            } else {
                // no more digits left
                #ifdef DEBUG
                current_square = x;
                #endif
                build_composed_grid(x);
                return x; // we have found a successful sudoku_square
            }
        }
        sudoku_square empty_square;
        #ifdef DEBUG
        current_square = empty_square;
        #endif
        return empty_square;
    }
    int get_square_index() const {
        return square_index;
    }
    const auto& get_composed_grid() const {
        return composed_grid;
    }
    #ifdef DEBUG
    const auto& get_current_square() const {
        return current_square;
    }
    #endif
    bool has_more() const {
        return !sudoku_stack.empty();
    }
private:
    #ifdef DEBUG
    sudoku_square current_square;
    #endif
    vector<sudoku_square> sudoku_stack;
    const int square_index;
    const int base_row;
    const int base_col;
    const int (&base_grid)[BOARD_SIZE][BOARD_SIZE];
    int composed_grid[BOARD_SIZE][BOARD_SIZE];
    int row_wise_exclusive_mask[SQUARE_SIZE];
    int col_wise_exclusive_mask[SQUARE_SIZE];
    void reset_composed_grid() {
        // Now cleanup the composed grid in the square position
        for(int row=0;row < SQUARE_SIZE; row++) {
            for(int col=0;col < SQUARE_SIZE; col++) {
                composed_grid[base_row+row][base_col+col] = 0;
            }
        }
    }

    void build_composed_grid(const sudoku_square& xsqr) {
        // Now cleanup the composed grid in the square position
        int sqr_grid[SQUARE_SIZE][SQUARE_SIZE];
        xsqr.get_square_grid(sqr_grid);
        for(int row=0;row < SQUARE_SIZE; row++) {
            for(int col=0;col < SQUARE_SIZE; col++) {
                composed_grid[base_row+row][base_col+col] = sqr_grid[row][col];
            }
        }
    }

    bool is_valid_rotation(uint16_t top_digit_mask, int rotation) {
        if(row_wise_exclusive_mask[rotation/SQUARE_SIZE] & top_digit_mask) {
            return false;
        }
        if(col_wise_exclusive_mask[rotation%SQUARE_SIZE] & top_digit_mask) {
            return false;
        }
        return true;
    }

    bool is_valid(const sudoku_square& sq) {
        // check if the sudoku square is valid in this position
        // build digit mask for square
        uint16_t digit_mask[SQUARE_SIZE]{0};
        sq.get_digit_mask_row_wise(digit_mask);
        #ifdef DEBUG_FULL
        cout << "square=" << sq << endl;
        #endif
        
        // go left and right of the board and find the digits
        // our board is like the following.
        // sq sq sq = base_row 0
        // sq sq sq = base_row 3
        // sq sq sq = base_row 6
        for(int row=0;row < SQUARE_SIZE; row++) {
            #ifdef DEBUG_FULL
            cout << "row=" << row << ", mask=" << row_wise_exclusive_mask[row] << ", digit_mask=" << digit_mask[row] << endl;
            #endif
            if(row_wise_exclusive_mask[row] & digit_mask[row]) {
                return false;
            }
        }
        
        // now check column-wise
        memset(digit_mask,0, sizeof(digit_mask));
        sq.get_digit_mask_column_wise(digit_mask);
        
        // go top to bottom of the board and find the digits
        // our board is like the following.
        // sq sq sq = base_col 0
        // sq sq sq = base_col 3
        // sq sq sq = base_col 6
        for(int col=0;col < SQUARE_SIZE; col++) {
            if(col_wise_exclusive_mask[col] & digit_mask[col]) {
                return false;
            }
        }
        
        return true;
    }
    int get_base_board_at_rotation(int rotation) const {
        return base_grid[base_row+(rotation/3)][base_col+(rotation%3)];
    }
};



void sudoku_solve(int (&grid)[BOARD_SIZE][BOARD_SIZE]) {
    //your logic here
    square_generator root_gen(0,grid);
#ifdef DEBUG
    root_gen.self_test();
#endif
    vector<square_generator> generator_stack;
    generator_stack.push_back(root_gen);
    
    while(!generator_stack.empty()) {
        square_generator& gen = generator_stack.back();
        sudoku_square sqr = gen.next_square();
        if(!sqr.is_complete()) {
            assert(!gen.has_more());
            // invalid backtrack
            generator_stack.pop_back();
            #ifdef DEBUG
            cout << "going for the next one" << endl;
            #endif
            continue;
        }
        // get next square generator
        if((gen.get_square_index()+1) < NUM_SQUARE) {
            square_generator ngen(gen.get_square_index()+1,gen.get_composed_grid());
            generator_stack.push_back(ngen);
            continue;
        } else {
            // we tried everything
            // display result
            cout << gen.get_composed_grid();
            #ifdef DEBUG
            cout << "Successful" << endl;
            #endif
            break; // we are done
        }
    }
    generator_stack.clear();
}

int main(void) {
    int n, board[BOARD_SIZE][BOARD_SIZE];
    cin >> n;
    for(int i=0;i<n;i++) {
        for(int j=0;j<BOARD_SIZE;j++) {
            for(int k=0;k<BOARD_SIZE;k++) {
                board[j][k] = 0;
                cin >> board[j][k];
            }
        }
        sudoku_solve(board);
    }
    return 0;
}

