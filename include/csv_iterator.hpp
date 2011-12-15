#ifndef _CSV_ITERATOR_HPP_
#define _CSV_ITERATOR_HPP_

#include <string>
#include <istream>
#include <boost/tuple/tuple.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include "details/csv_helpers.hpp"

namespace csv {
    template<class Tuple>
        class iterator {
            private:
                bool m_bad;
                std::istream* m_in;
                std::string currentLine;
                Tuple currentResult; // Useful for passing pointers around
            public:
                /**
                 * Constructor denoting end of range
                 */
                iterator() : m_bad(true) {
                }

                iterator(std::istream& in)
                    : m_bad(false), m_in(&in) 
                {
                    this->operator++();
                }

                Tuple const* operator->(){
                    return &currentResult;
                }

                Tuple operator*() {
                    try {
                        using namespace boost;
                        typedef tokenizer<escaped_list_separator<char> > Tokens;
                        Tokens tokens(currentLine);
                        details::filler<Tuple>::fill(currentResult,tokens.begin(),tokens.end());
                    } catch (boost::bad_lexical_cast& ex){
                        std::cout << ex.what() << std::endl;
                        m_bad = true;
                    }
                    return currentResult;
                }

                bool operator==(const iterator& other) {
                    return (m_bad == true) &&  (other.m_bad == true);
                }

                bool operator!=(const iterator& other) {
                    return !(*this == other);
                }

                
                iterator& operator++() {
                    bool res = std::getline(*m_in, currentLine);
                    m_bad = !res;
                    return *this;
                }
        };
};


#endif
