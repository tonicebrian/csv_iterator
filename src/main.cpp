#include <csv_iterator.hpp>
#include <fstream>
#include <boost/tuple/tuple.hpp>

int main(int argc, const char *argv[])
{
    // Example of csv_iterator usage
    if(argc != 2){
        std::cerr << "Usage ./csvItExample <file.csv>" << std::endl;
        return 1;
    }

    std::ifstream in(argv[1]);
    using namespace boost::tuples;
    typedef tuple<int,std::string,double> record;
    csv::iterator<record> it(in);

    double acc = 0.0;
    std::for_each(it,csv::iterator<record>(), 
                  [&acc](const record& rec){
                    acc += rec.get<0>();
                    });

    std::cout << acc << std::endl;
    
    return 0;
}
