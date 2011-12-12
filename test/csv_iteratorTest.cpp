#include <cppunit/extensions/HelperMacros.h>
#include "csv_iterator.hpp"

#include <vector>
#include <string>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/tuple/tuple_io.hpp>

class csv_iteratorTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(csv_iteratorTest);
    CPPUNIT_TEST(testDereference);
    CPPUNIT_TEST_SUITE_END();

    typedef boost::tuple<int,int> record;

    public:

    void setUp(){
    }

    void tearDown(){
    }

    void testDereference(){
        csv::iterator<record> it;
        record expected;
        CPPUNIT_ASSERT_EQUAL(expected, *it);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(csv_iteratorTest);




