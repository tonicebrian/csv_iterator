#ifndef _CSV_ITERATOR_HPP_
#define _CSV_ITERATOR_HPP_

#include <string>
#include <vector>

namespace csv {
    template<class Tuple>
    class iterator {
        typedef std::vector<std::string>::iterator strIt;
        public:
            /**
             * Constructor denoting end of range
             */
            iterator() {
            }

            Tuple operator*() {
                return Tuple();
            }
    };
};
#endif
