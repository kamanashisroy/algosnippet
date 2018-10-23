// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
kmp.h file is part of Algosnippet.
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


#include <cstdlib>
#include <cassert>
#include <vector>
#include <string>

#ifndef ALGO_SNIPPET_STRING_KMP
#define ALGO_SNIPPET_STRING_KMP

namespace algo_snippet {
    namespace string {
        class kmp {
        public:
            kmp(std::string &pat) : pat(pat) {
                make_lcp_table();
            }
            //! \brief Try to find the pattern in the text
            int search(std::string &txt) {
                // sanity check
                if(txt.size() < pat.size()) {
                    return -1;
                }

                if(pat.size() == 0) {
                    return 0;
                }

                for(unsigned int i = 0,match_len = 0; (i+pat.size()-match_len-1) < txt.size();) {

                    if(pat[match_len] == txt[i]) {

                        // case 1: char matched
                        // go for next character
                        match_len++;
                        i++;
                        if(pat.size() == match_len) {
                            return i-match_len; // return match position
                        }
                    } else {

                        // case 2: char-not matched, find lcp-len
                        if(0 == match_len) {
                            i++; // go for next character
                        } else {
                            // start from prev match
                            match_len = (unsigned int)lcp_len[match_len-1];
                        }
                    }
                }
                return -1; // not found
            }
        private:
            std::string &pat;
            //! \brief keep the length of longest common proper-prefix of each suffix of proper-prefix.
            std::vector<int> lcp_len; //!< possible values are [-1 to (pat.size()-1))

            //! \brief calculate lcp table for given pattern
            void make_lcp_table() {
                // sanity check
                if(pat.size() == 0) {
                    return;
                }
                // Suppose the pattern               = XXXXYXXZZZ
                // Now a proper prefix               = XXXXYXX
                // LCP of the suffixes of prefix     =      XX
                // length                            =       2

                // If we convert the string of alphabet A, to a graph, then LCP length is the length of the longest cycle.

                lcp_len.resize(pat.size(),0);
                for(unsigned int i = 1; i < pat.size(); i++) {
                    if(pat[i] == pat[lcp_len[i-1]]) {
                        // increase the pattern length by adding from previous
                        lcp_len[i] = lcp_len[i-1]+1;
                    } else {
                        lcp_len[i] = (pat[i] == pat[0])?1:0;
                    }
                    assert(lcp_len[i] >= 0 && lcp_len[i] < (int)(pat.size()));
                }
            }
        };
    }
}

#endif // ALGO_SNIPPET_STRING_KMP

