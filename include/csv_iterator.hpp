#ifndef _CSV_ITERATOR_HPP_
#define _CSV_ITERATOR_HPP_

#include <string>
#include <vector>
#include <boost/tuple/tuple.hpp>
#include <boost/lexical_cast.hpp>

namespace csv {
    template<class Tuple>
    class iterator {
        typedef std::vector<std::string>::iterator strIt;
        bool m_bad;

        strIt m_it, m_itEnd;

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
                while(m_it != m_itEnd){
                    boost::tuples::get<0>(result) = boost::lexical_cast<int>(*m_it);
                    ++m_it;
                    boost::tuples::get<1>(result) = boost::lexical_cast<int>(*m_it);
                    ++m_it;
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
