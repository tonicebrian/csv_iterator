#ifndef _CSV_ITERATOR_HPP_
#define _CSV_ITERATOR_HPP_

#include <string>
#include <vector>
#include <boost/tuple/tuple.hpp>
#include <boost/lexical_cast.hpp>
#include "details/csv_helpers.hpp"

namespace csv {
    template<class Tuple>
        class iterator {
            bool m_bad;

            strIt m_it, m_itEnd;

            /**
             * Metaprogramming function for filling the tuple
             */
            public:
            /**
             * Constructor denoting end of range
             */
            iterator() : m_bad(true) {
            }

            iterator(strIt beg, strIt end) 
                : m_bad(false), m_it(beg), m_itEnd(end)
            {
            }

            Tuple operator*() {
                Tuple result;
                try {
                    details::filler<Tuple>::fill(result,m_it,m_itEnd);
                } catch (boost::bad_lexical_cast& ex){
                    std::cout << ex.what() << std::endl;
                    m_bad = true;
                }
                return result;
            }

            bool operator==(const iterator& other) {
                return (m_bad == true) &&  (other.m_bad == true);
            }

            bool operator!=(const iterator& other) {
                return !(*this == other);
            }

            void operator++(int x = 0) {
            }
        };
};


#endif
