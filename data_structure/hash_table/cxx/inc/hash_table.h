// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
hash_table.h file is part of Algosnippet.
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

#ifndef _ALGO_HASH_TABLE_HXX
#define _ALGO_HASH_TABLE_HXX

typedef unsigned long long hash_t;

namespace algo_snippet {
    namespace dict {
        enum reserved_hash_values {
            RESERVED_EMPTY = 0,
            RESERVED_DELETED = 1,
            RESERVED_MAX = 2,
        };

        template<typename KT>
        class hash_table {
        public:
            virtual ~hash_table() {};
            virtual bool insert(hash_t hval, KT& x) = 0;
            virtual bool remove(hash_t hval, const KT& x) = 0;
            virtual bool search(hash_t hval, KT& x) = 0;
        };
    }
}

#endif // _ALGO_HASH_TABLE_HXX
 
