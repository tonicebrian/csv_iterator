#include <cppunit/extensions/HelperMacros.h>
#include "csv_iterator.hpp"

#include <vector>
#include <string>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/tuple/tuple_io.hpp>

class csv_iteratorTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(csv_iteratorTest);
    CPPUNIT_TEST(testSimpleInts);
    CPPUNIT_TEST_SUITE_END();

    public:

    void setUp(){
    }

    void tearDown(){
    }

    void testSimpleInts(){
        typedef boost::tuple<int,int> record;
        std::vector<std::string> values = {"1","2"};
        csv::iterator<record> it;
        record obtained = it.getTuple(values.begin());
        record expected;


        CPPUNIT_ASSERT_EQUAL(expected, obtained);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(csv_iteratorTest);




