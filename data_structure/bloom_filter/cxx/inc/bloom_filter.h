// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
bloom_filter.h file is part of Algosnippet.
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

#ifndef _ALGO_BLOOM_FILTER_HXX
#define _ALGO_BLOOM_FILTER_HXX

typedef unsigned long long hash_t;

namespace algo_snippet {
    namespace dict {
        //! \tparam   ORDER   Indicate the size(=1<<ORDER) of bloom filter
        template<typename HT, int ORDER>
        class bloom_filter {
        public:
            bloom_filter() : space{0} {}
            ~bloom_filter() {}
            void insert(HT hval) {
                std::size_t hindex = get_modulo_size(hval);
                space[hindex>>3] |= 1<<(hindex&3);
            }
            bool contains(HT hval) {
                std::size_t hindex = get_modulo_size(hval);
                return (space[hindex>>3] & (1<<(hindex&3)));
            }
            //! \return size in bytes
            std::size_t size() const {
                return (1<<ORDER);
            }
        private:
            inline std::size_t get_modulo_size(HT hval) const {
                // return hval%table_size;
                return hval & (size()-1);
            }
            std::array<uint8_t,(1<<ORDER)> space;
        };
    }
}

#endif // _ALGO_BLOOM_FILTER_HXX
 
