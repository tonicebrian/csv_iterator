#ifndef _CSV_ITERATOR_HPP_
#define _CSV_ITERATOR_HPP_

#include <string>
#include <vector>

namespace csv {
    template<class Tuple>
    class iterator {
        typedef std::vector<std::string>::iterator strIt;
        public:
            Tuple getTuple(std::vector<std::string>::iterator it){
                return Tuple();
            }

            Tuple operator*() {
                return Tuple();
            }
    };
};
#endif
