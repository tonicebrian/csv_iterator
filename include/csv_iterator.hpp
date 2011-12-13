#ifndef _CSV_ITERATOR_HPP_
#define _CSV_ITERATOR_HPP_

#include <string>
#include <vector>
#include <boost/tuple/tuple.hpp>
#include <boost/lexical_cast.hpp>

namespace csv {
    // String iterator
    typedef std::vector<std::string>::iterator strIt;

    namespace details {
        // This namespace is private and subject to change
        // Do not use
        template<class Tuple, int N >
            struct helper {
                static void fill(Tuple& tuple, strIt it, strIt end){
                    using namespace boost::tuples;
                    typedef typename element<length<Tuple>::value-N-1,Tuple>::type value_type;
                    get<length<Tuple>::value-N-1>(tuple) = boost::lexical_cast<value_type>(*it);
                    ++it;
                    if(it != end){
                        helper<Tuple,N-1>::fill(tuple,it,end);
                    }
                }
            };

        template<class Tuple>
            struct helper<Tuple, 0> {
                static void fill(Tuple& tuple, strIt it, strIt end){
                    using namespace boost::tuples;
                    typedef typename boost::tuples::element<length<Tuple>::value-1,Tuple>::type value_type;
                    boost::tuples::get<length<Tuple>::value-1>(tuple) = boost::lexical_cast<value_type>(*it);
                    ++it;
                };
            };

        template<class Tuple>
            struct filler {
                static void fill(Tuple& tuple, strIt it,strIt end){
                    if(it != end){
                        helper<Tuple, boost::tuples::length<Tuple>::value-1>::fill(tuple,it,end);
                    }
                }
            };
    }

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
