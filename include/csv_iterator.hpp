#ifndef _CSV_ITERATOR_HPP_
#define _CSV_ITERATOR_HPP_

#include <string>
#include <vector>
#include <boost/tuple/tuple.hpp>
#include <boost/lexical_cast.hpp>

namespace csv {
    namespace details {
        // This namespace is private and subject to change
        // Do not use
        template<class Tuple, int N >
            struct helper {
                static void fill(Tuple& tuple){
                    boost::tuples::get<N>(tuple) = N;
                    helper<Tuple,N-1>::fill(tuple);
                }
            };

        template<class Tuple>
            struct helper<Tuple, 0> {
                static void fill(Tuple& tuple){
                    boost::tuples::get<0>(tuple) = 0;
                };
            };
    }

    template<class Tuple>
        class iterator {
            typedef std::vector<std::string>::iterator strIt;
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
                    while(m_it != m_itEnd){
                        boost::tuples::get<0>(result) = boost::lexical_cast<typename boost::tuples::element<0,Tuple>::type >(*m_it);
                        ++m_it;
                        boost::tuples::get<1>(result) = boost::lexical_cast<typename boost::tuples::element<1,Tuple>::type >(*m_it);
                        ++m_it;
                    }
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
