// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/*
double_hashing.h file is part of Algosnippet.
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
        class hash_table_double_hashing {
        private:
            class hash_table_double_hashing_iterator {
            public:
                KT& operator*();
                hash_table_double_hashing_iterator& operator++();
                bool operator==(const hash_table_double_hashing_iterator& other);
                hash_t hval;
                hash_t hval2;
                std::size_t index;
            private:
                hash_table_double_hashing<KT>& container;
                hash_table_double_hashing_iterator(hash_table_double_hashing<KT>& container, hash_t hval, hash_t hval2, std::size_t index);
                friend hash_table_double_hashing;
            };
        public:
            //! \brief create hash-table by linear probing
            hash_table_double_hashing(
                std::size_t init_order     //!< table_size = (1<<init_order);
                , KT&& default_val          //!< default content value
            );
            bool insert(hash_t hval, hash_t hval2, KT& x);
            bool remove(hash_t hval, hash_t hval2, const KT& x);
            bool search(hash_t hval, hash_t hval2, KT& x);
            hash_table_double_hashing_iterator iter_range(hash_t hval, hash_t hval2);
            inline std::size_t get_table_size() const {
                return table_size;
            }
            inline std::size_t get_content_count() const {
                return content_count;
            }
            inline std::size_t get_empty_count() const {
                return table_size-fill_count;
            }
            inline const hash_table_double_hashing_iterator& end() const {
                return end_iter;
            }
        private:
            std::size_t table_order;
            std::size_t table_size;
            std::vector<hash_t> htable;
            std::vector<KT> content;
            KT default_val;
            std::size_t content_count;
            std::size_t fill_count;
            hash_table_double_hashing_iterator end_iter;
            inline std::size_t get_modulo_size(hash_t hval) const {
                // return hval%table_size;
                return hval & (table_size-1);
            }
            hash_table_double_hashing_iterator& next(hash_table_double_hashing_iterator& it) const;
            //! \brief it can access invalid memory
            const KT& get(hash_table_double_hashing_iterator& it) const {
                if(RESERVED_EMPTY == it.hval || table_size >= it.index) {
                    return default_val;
                }
                return content[get_modulo_size(it.hval+it.index)];
            }
        };
        
        template<typename KT>
        hash_table_double_hashing<KT>::hash_table_double_hashing(std::size_t table_order, KT&& default_val)
            :table_order(table_order)
            , table_size(1<<table_order)
            , htable(table_size, 0)
            , content(table_size, default_val)
            , default_val(default_val)
            , content_count(0)
            , fill_count(0)
            , end_iter(*this, 0, 0, std::numeric_limits<std::size_t>::max()) {
        }

        template<typename KT>
        bool hash_table_double_hashing<KT>::insert(hash_t hval, hash_t hval2, KT& x) {
            hval = hval + RESERVED_MAX;
            // sanity check
            if(hval < RESERVED_MAX) { // hval overflow
                return false; // failed
            }

            if(content_count >= table_size) {
                // no room
                return false;
            }

            for(size_t i = 0,inc = 0; i<table_size; i++, inc+=hval2) {
                const size_t hindex = get_modulo_size(hval+inc);
                if(RESERVED_EMPTY == htable[hindex] || RESERVED_DELETED == htable[hindex]) {
                    if(RESERVED_EMPTY == htable[hindex]) {
                        fill_count++;
                    }
                    htable[hindex] = hval;
                    content[hindex] = x;
                    content_count++;
                    return true;
                }
            }
            return false;
        }

        template<typename KT>
        bool hash_table_double_hashing<KT>::remove(hash_t hval, hash_t hval2, const KT& x) {
            hval = hval + RESERVED_MAX;
            // sanity check
            if(hval < RESERVED_MAX) { // hval overflow
                return false; // failed
            }

            for(size_t i = 0,inc = 0; i<table_size; i++, inc+=hval2) {
                const size_t hindex = get_modulo_size(hval+inc);
                if(hval == htable[hindex] && x == content[hindex]) {
                    htable[hindex] = RESERVED_DELETED;
                    content[hindex] = default_val;
                    content_count--;
                    return true;
                } else if(RESERVED_EMPTY == htable[hindex]) {
                    return false;
                }
            }
            return false;
        }

        template<typename KT>
        bool hash_table_double_hashing<KT>::search(hash_t hval, hash_t hval2, KT& xout) {
            hval = hval + RESERVED_MAX;
            // sanity check
            if(hval < RESERVED_MAX) { // hval overflow
                return false; // failed
            }

            for(size_t i = 0,inc = 0; i<table_size; i++, inc+=hval2) {
                const size_t hindex = get_modulo_size(hval+inc);
                if(hval == htable[hindex] && xout == content[hindex]) {
                    xout = content[hindex]; // set outval
                    return true;
                } else if(RESERVED_EMPTY == htable[hindex]) {
                    return false;
                }
            }
            return false;
        }

        template<typename KT>
        typename hash_table_double_hashing<KT>::hash_table_double_hashing_iterator
        hash_table_double_hashing<KT>::iter_range(hash_t hval, hash_t hval2) {
            hval = hval + RESERVED_MAX;
            // sanity check
            if(hval < RESERVED_MAX) { // hval overflow
                return end_iter; // failed
            }

            for(size_t i = 0,inc = 0; i<table_size; i++, inc+=hval2) {
                const size_t hindex = get_modulo_size(hval+inc);
                if(hval == htable[hindex]) {
                    // found
                    return hash_table_double_hashing_iterator(*this,hval,hval2,i);
                } else if(RESERVED_EMPTY == htable[hindex]) {
                    return end_iter; // failed
                }
            }
            return end_iter; // failed
        }

        template<typename KT>
        typename hash_table_double_hashing<KT>::hash_table_double_hashing_iterator&
        hash_table_double_hashing<KT>::next(hash_table_double_hashing_iterator& x) const {
            // sanity check
            if(RESERVED_EMPTY == x.hval) { // invalid
                return end_iter;
            }

            for(size_t i = x.index+1,inc = ((1+x.index)*x.hval2); i<table_size; i++, inc+=x.hval2) {
                const size_t hindex = get_modulo_size(x.hval+inc);
                if(x.hval == htable[hindex]) {
                    x.index = i;
                    return x;
                } else if(RESERVED_EMPTY == htable[hindex]) {
                    return end_iter; // failed
                }
            }
            return end_iter; // failed
        }

        template<typename KT>
        hash_table_double_hashing<KT>::hash_table_double_hashing_iterator::hash_table_double_hashing_iterator(hash_table_double_hashing& container, hash_t hval, hash_t hval2, std::size_t index)
            : hval(hval),hval2(hval2),index(index),container(container) {
        }

        template<typename KT>
        bool hash_table_double_hashing<KT>::hash_table_double_hashing_iterator::operator==(const hash_table_double_hashing_iterator& other) {
            return index == other.index;
        }

        template<typename KT>
        typename hash_table_double_hashing<KT>::hash_table_double_hashing_iterator&
        hash_table_double_hashing<KT>::hash_table_double_hashing_iterator::operator++() {
            return container.next(*this);
        }

        template<typename KT>
        KT& hash_table_double_hashing<KT>::hash_table_double_hashing_iterator::operator*() {
            return container.get(*this);
        }
    }
}

#endif // _DOUBLE_HASHING_HXX
 
