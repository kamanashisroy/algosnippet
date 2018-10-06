// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
cuckoo_hashing.h file is part of Algosnippet.
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

#ifndef _DOUBLE_HASHING_HXX
#define _DOUBLE_HASHING_HXX

#include <vector>
#include <limits>
#include "hash_table.h"

namespace algo_snippet {
    namespace dict {
        template<typename KT>
        class hash_table_cuckoo_hashing {
        public:
            //! \brief create hash-table by linear probing
            hash_table_cuckoo_hashing(
                std::size_t init_order     //!< table_size = (1<<init_order);
                , KT&& default_val          //!< default content value
            );
            //! \WARNING x is passed by value
            bool insert(hash_t hval, hash_t hval2, KT x);
            bool remove(hash_t hval, hash_t hval2, const KT& x);
            bool search(hash_t hval, hash_t hval2, KT& x);
            inline std::size_t get_table_size() const {
                return table_size<<1;
            }
            inline std::size_t get_content_count() const {
                return content_count[0]+content_count[1];
            }
            inline std::size_t get_empty_count() const {
                return (table_size<<1)-fill_count[0]-fill_count[1];
            }
        private:
            std::size_t table_order;
            std::size_t table_size;
            std::vector<hash_t> htable[2];
            std::vector<hash_t> htable_secondary[2];
            std::vector<KT> content[2];
            KT default_val;
            std::size_t content_count[2];
            std::size_t fill_count[2];
            constexpr static int CUCKOO_RESERVE_MAX = RESERVED_DELETED;
            inline std::size_t get_modulo_size(hash_t hval) const {
                // return hval%table_size;
                return hval & (table_size-1);
            }
            //! \brief check if a spot is available for insertion
            inline bool is_available(int table_index, size_t hindex) const;
            //! \brief insert data without replacing other
            inline void insert_no_replace(int table_index, size_t hindex, hash_t hval, hash_t hval2, KT& x);
            //! \brief insert data by swapping with the older(for replacement)
            inline void insert_and_swap(int table_index, size_t hindex, hash_t hval, hash_t hval2, KT& x);
        };
        
        template<typename KT>
        hash_table_cuckoo_hashing<KT>::hash_table_cuckoo_hashing(std::size_t table_order, KT&& default_val)
            :table_order(table_order)
            , table_size(1<<table_order)
            , htable{
                std::vector<hash_t>(table_size, RESERVED_EMPTY)
                , std::vector<hash_t>(table_size, RESERVED_EMPTY)
            }
            , htable_secondary{
                std::vector<hash_t>(table_size, RESERVED_EMPTY)
                , std::vector<hash_t>(table_size, RESERVED_EMPTY)
            }
            , content{
                std::vector<KT>(table_size, default_val)
                , std::vector<KT>(table_size, default_val)
            }
            , default_val(default_val)
            , content_count{0,0}
            , fill_count{0,0} {
        }

        template<typename KT>
        inline bool hash_table_cuckoo_hashing<KT>::is_available(int table_index, size_t hindex) const {
            return (RESERVED_EMPTY == htable[table_index][hindex]);
        }

        template<typename KT>
        inline void hash_table_cuckoo_hashing<KT>::insert_no_replace(int table_index, size_t hindex, hash_t hval, hash_t hval2, KT& x) {
            if(RESERVED_EMPTY == htable[table_index][hindex]) {
                fill_count[table_index]++;
            }
            htable[table_index][hindex] = hval;
            htable_secondary[table_index][hindex] = hval2;
            content[table_index][hindex] = x;
            content_count[table_index]++;
        }

        template<typename KT>
        inline void hash_table_cuckoo_hashing<KT>::insert_and_swap(int table_index, size_t hindex, hash_t hval, hash_t hval2, KT& x) {
            std::swap(htable[table_index][hindex],hval);
            std::swap(htable_secondary[table_index][hindex],hval2);
            std::swap(content[table_index][hindex],x);
        }

        template<typename KT>
        bool hash_table_cuckoo_hashing<KT>::insert(hash_t hval, hash_t hval2, KT x) {
            hval = hval + CUCKOO_RESERVE_MAX;
            hval2 = hval2 + CUCKOO_RESERVE_MAX;
            // sanity check
            if(hval < CUCKOO_RESERVE_MAX || hval2 < CUCKOO_RESERVE_MAX) { // hval overflow
                return false; // failed
            }

            if(get_content_count() >= table_size) {
                // no room
                return false;
            }

            for(size_t i = 0; i<table_size; i++) {

                // calculate table index
                const size_t hindex = get_modulo_size(hval);
                const size_t hindex2 = get_modulo_size(hval2);

                if(is_available(0,hindex)) { // when table-1 has no conflict
                    insert_no_replace(0,hindex,hval,hval2,x);
                    return true;
                } else if(is_available(1,hindex2)) { // when table-2 has no conflict
                    insert_no_replace(1,hindex2,hval2,hval,x);
                    return true;
                } else { // conflict in both table-1 and table-2
                    if((i&1) == 0) { // when even
                        // insert in htable
                        insert_and_swap(0,hindex,hval,hval2,x);
                    } else { // go for table-2
                        insert_and_swap(1,hindex2,hval2,hval,x);
                    }
                }
            }
            // TODO efficient cycle detection
            // table is full or there is cycle
            return false;
        }

        //! remove is Theta(1) operation
        template<typename KT>
        bool hash_table_cuckoo_hashing<KT>::remove(hash_t hval, hash_t hval2, const KT& x) {
            hval = hval + CUCKOO_RESERVE_MAX;
            hval2 = hval2 + CUCKOO_RESERVE_MAX;
            // sanity check
            if(hval < CUCKOO_RESERVE_MAX || hval2 < CUCKOO_RESERVE_MAX) { // hval overflow
                return false; // failed
            }

            // calculate table index
            const size_t hindex = get_modulo_size(hval);
            const size_t hindex2 = get_modulo_size(hval2);

            if(hval == htable[0][hindex] && x == content[0][hindex]) {
                htable[0][hindex] = RESERVED_EMPTY;
                content[0][hindex] = default_val;
                content_count[0]--;
                return true;
            } else if(hval2 == htable[1][hindex2] && x == content[1][hindex2]) {
                htable[1][hindex2] = RESERVED_EMPTY;
                content[1][hindex2] = default_val;
                content_count[1]--;
                return true;
            }
            // not found
            return false;
        }

        //! search is Theta(1) operation
        template<typename KT>
        bool hash_table_cuckoo_hashing<KT>::search(hash_t hval, hash_t hval2, KT& xout) {
            hval = hval + CUCKOO_RESERVE_MAX;
            hval2 = hval2 + CUCKOO_RESERVE_MAX;
            // sanity check
            if(hval < CUCKOO_RESERVE_MAX || hval2 < CUCKOO_RESERVE_MAX) { // hval overflow
                return false; // failed
            }

            // calculate table index
            const size_t hindex = get_modulo_size(hval);
            const size_t hindex2 = get_modulo_size(hval2);

            if(hval == htable[0][hindex] && xout == content[0][hindex]) {
                xout = content[0][hindex];
                return true;
            } else if(hval2 == htable[1][hindex2] && xout == content[1][hindex2]) {
                xout = content[1][hindex2];
                return true;
            }
            return false;
        }
    }
}

#endif // _DOUBLE_HASHING_HXX
 
