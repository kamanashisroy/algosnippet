// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
edit_distance_backtracking.h file is part of Algosnippet.
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

#ifndef ALGO_BACK_TRACKING_EDIT_DISTANCE_H
#define ALGO_BACK_TRACKING_EDIT_DISTANCE_H

#include <algorithm>

namespace algo_snippet {
    namespace backtracking {
        class edit_distance {
        public:
            static std::size_t calc(const char*x, std::size_t xlen, const char*y, std::size_t ylen) {
                if(!x || !y || 0 == xlen || 0 == ylen) {
                    return xlen+ylen;
                }
                // INITIALIZATION LOGIC
                return calc_helper(x,0,xlen,y,0,ylen);
            }
        private:
            static std::size_t calc_helper(const char*x, const std::size_t xpos, const std::size_t xlen, const char*y, const std::size_t ypos, const std::size_t ylen) {
                // TERMINATION LOGIC
                if(xlen == xpos) {
                    return ylen-ypos;
                } else if(ylen == ypos) {
                    return xlen-xpos;
                }
                std::size_t result = xlen+ylen;

                // INDUCTION LOGIC
                if(x[xpos] == y[ypos]) {
                    // try case 1: Character matched
                    result = calc_helper(x,xpos+1,xlen,y,ypos+1,ylen);
                } else {
                    // try case 2: Skip x-character mismatch(by deleting)
                    result = std::min(result
                        ,1 + // 1 edit(delete x)
                        calc_helper(
                            x
                            ,xpos+1 // skip/delete 1 character from xpos
                            ,xlen
                            ,y
                            ,ypos
                            ,ylen
                        )
                    );
                    // try case 3: Skip y-charater mismatch(by deleting)
                    result = std::min(result
                        ,1 + // 1 edit(delete y)
                        calc_helper(
                            x
                            ,xpos
                            ,xlen
                            ,y
                            ,ypos+1 // skip/delete 1 character from ypos
                            ,ylen
                        )
                    );
                    // try case 4: Change one character
                    result = std::min(result
                        ,1 + // 1 edit(change x/y)
                        calc_helper(
                            x
                            ,xpos+1
                            ,xlen
                            ,y
                            ,ypos+1
                            ,ylen
                        )
                    );
                }
                return result;
            }
        };
    }
}

#endif // ALGO_BACK_TRACKING_EDIT_DISTANCE_H

