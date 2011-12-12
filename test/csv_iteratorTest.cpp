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
    CPPUNIT_TEST(testCheckEqualityOfEmpties);
    CPPUNIT_TEST(testCheckEqualityOfDifferentIterators);
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

    void testCheckEqualityOfEmpties(){
        csv::iterator<record> it, it2;
        CPPUNIT_ASSERT(it == it2);
    }

    void testCheckEqualityOfDifferentIterators() {
        std::vector<std::string> values;
        csv::iterator<record> it, it2(values.begin());
        CPPUNIT_ASSERT(it != it2);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(csv_iteratorTest);




