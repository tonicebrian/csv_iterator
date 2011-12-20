#include <csv_iterator.hpp>
#include <iostream>
#include <fstream>
#include <boost/tuple/tuple.hpp>

// Compressed streams
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/bzip2.hpp>

int main(int argc, const char *argv[])
{
    // Example of csv_iterator usage
    using namespace boost::tuples;
    typedef tuple<int,std::string,double> record;

    std::ifstream in;
    boost::iostreams::filtering_istream bzs;
    csv::iterator<record> it;

    if (argc == 2){
        in.open(argv[1],std::ifstream::in);
        it=csv::iterator<record>(in);
    } else if (argc == 3) {
        in.open(argv[2], std::ios_base::in | std::ios_base::binary);
        bzs.push(boost::iostreams::bzip2_decompressor());
        bzs.push(in);
        it=csv::iterator<record>(bzs);
    }
    else{
        std::cerr << "Usage ./csvItExample [-BZIP] <file.csv>" << std::endl;
        return 1;
    }

    unsigned long long acc = 0;
    std::for_each(it,csv::iterator<record>(), 
            [&acc](const record& rec){
            acc += rec.get<0>();
            });

    std::cout << acc << std::endl;

    return 0;
}
