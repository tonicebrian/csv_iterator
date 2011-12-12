#ifndef _CSV_ITERATOR_HPP_
#define _CSV_ITERATOR_HPP_

#include <string>
#include <vector>

namespace csv {
    template<class Tuple>
    class iterator {
        typedef std::vector<std::string>::iterator strIt;
        bool m_bad;

        public:
            /**
             * Constructor denoting end of range
             */
            iterator() : m_bad(true) {
            }

            iterator(strIt it) : m_bad(false){
            }

            Tuple operator*() {
                return Tuple();
            }

            bool operator==(const iterator& other) {
                return m_bad == other.m_bad;
            }

            bool operator!=(const iterator& other) {
                return !(*this == other);
            }
    };
};
#endif
