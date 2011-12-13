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
    CPPUNIT_TEST(testCheckEqualityInitializedIterators);
    CPPUNIT_TEST(testIteratorFeedWithValues);
    CPPUNIT_TEST(testIteratorFeedWithDoubles);
    CPPUNIT_TEST(testFillTuple);
    CPPUNIT_TEST_SUITE_END();

    typedef boost::tuple<int,int> TwoIntRecord;
    typedef boost::tuple<int,int,int> ThreeIntRecord;
    typedef boost::tuple<double,double> TwoDoubleRecord;

    public:

    void setUp(){
    }

    void tearDown(){
    }

    void testDereference(){
        csv::iterator<TwoIntRecord> it;
        TwoIntRecord expected;
        CPPUNIT_ASSERT_EQUAL(expected, *it);
    }

    void testCheckEqualityOfEmpties(){
        csv::iterator<TwoIntRecord> it, it2;
        CPPUNIT_ASSERT(it == it2);
    }

    void testCheckEqualityOfDifferentIterators() {
        std::vector<std::string> values;
        csv::iterator<TwoIntRecord> it, it2(values.begin(), values.end());
        CPPUNIT_ASSERT(it != it2);
    }

    void testCheckEqualityInitializedIterators() {
        std::vector<std::string> values;
        csv::iterator<TwoIntRecord> it(values.begin(),values.end()), it2(values.begin(),values.end());

        // No iterator equals the other
        CPPUNIT_ASSERT(it != it2);
    }

    void testIteratorFeedWithValues(){
        std::vector<std::string> values = {"1","2"};
        csv::iterator<TwoIntRecord> it(values.begin(), values.end());

        TwoIntRecord expected;
        boost::tuples::get<0>(expected) = 1;
        boost::tuples::get<1>(expected) = 2;

        CPPUNIT_ASSERT_EQUAL(expected,*it);
    }

    void testIteratorFeedWithDoubles(){
        std::vector<std::string> values = {"1.4","2.5"};
        csv::iterator<TwoDoubleRecord> it(values.begin(), values.end());

        TwoDoubleRecord expected;
        boost::tuples::get<0>(expected) = 1.4;
        boost::tuples::get<1>(expected) = 2.5;

        CPPUNIT_ASSERT_EQUAL(expected,*it);
    }

    void testFillTuple() {
       ThreeIntRecord expected, obtained;

       csv::helper<ThreeIntRecord,2>::fill(obtained);

       boost::tuples::get<0>(expected) = 0;
       boost::tuples::get<1>(expected) = 1;
       boost::tuples::get<2>(expected) = 2;
       CPPUNIT_ASSERT_EQUAL(expected,obtained);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(csv_iteratorTest);




