csv_iterator
============

A flexible iterator library written in C++ for traversing CSV files

Usage:
------

Just copy the the files under the folder include in your include files. In your
code include the `csv_iterator.hpp` header and using the boost tuples declare 
an iterator reading from an istream. The contructor without arguments is a synomim
for the end of the stream.

The minimal example would be:

    #include <fstream>
    #include <boost/tuple/tuple.hpp>
    
    using namespace boost::tuples;
    typedef tuple<int,std::string,double> record;
    
    void myFunc(const record& value){
        // Your code here
    }
    
    int main(int argc, const char *argv[])
    {
        // Example of csv_iterator usage
        std::ifstream in("myCsvFile.csv");
        csv::iterator<record> it(in);
    
        // Use the iterator in your algorithms.
        std::for_each(it, csv::iterator<record>(), myFunc);
    
        return 0;
    }
              



Testing
-------

In order to ensure that the libraries work for your platform type `make test`

Libraries:
----------

    sudo apt-get install cmake libboost-dev liboost-iostreams-dev
