#ifndef _CSV_HELPERS_HPP_
#define _CSV_HELPERS_HPP_

#include <vector>
#include <string>
#include <boost/tuple/tuple.hpp>
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
};

#endif


