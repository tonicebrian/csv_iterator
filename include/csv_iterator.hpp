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
            public:
                /**
                 * Constructor denoting end of range
                 */
                iterator() : m_bad(true) {
                }

                iterator(std::istream& in)
                    : m_bad(false), m_in(&in) 
                {
                    this->operator++(0);
                }

                Tuple operator*() {
                    Tuple result;
                    try {
                        using namespace boost;
                        typedef tokenizer<escaped_list_separator<char> > Tokens;
                        Tokens tokens(currentLine);
                        details::filler<Tuple>::fill(result,tokens.begin(),tokens.end());
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
                    if(m_in->good()){
                        std::getline(*m_in, currentLine);
                    } else {
                        m_bad = true;
                    }
                }
        };
};


#endif
