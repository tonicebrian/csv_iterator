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
    CPPUNIT_TEST(testFillTupleWithMixedRecords);
    CPPUNIT_TEST(testReadIstream);
    CPPUNIT_TEST_SUITE_END();

    typedef boost::tuple<int,int> TwoIntRecord;
    typedef boost::tuple<int,int,int> ThreeIntRecord;

    typedef boost::tuple<double,double> TwoDoubleRecord;

    typedef boost::tuple<int,std::string,double> ThreeMixedRecord;
    typedef boost::tokenizer<boost::escaped_list_separator<char> > Tokens;

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
        std::stringstream ss;
        csv::iterator<TwoIntRecord> it, it2(ss);
        CPPUNIT_ASSERT(it != it2);
    }

    void testCheckEqualityInitializedIterators() {
        std::vector<std::string> values;
        std::stringstream ss1, ss2;
        csv::iterator<TwoIntRecord> it(ss1), it2(ss2);

        // No iterator equals the other
        CPPUNIT_ASSERT(it != it2);
    }

    void testIteratorFeedWithValues(){
        std::stringstream ss("1,2");
        csv::iterator<TwoIntRecord> it(ss);

        TwoIntRecord expected;
        boost::tuples::get<0>(expected) = 1;
        boost::tuples::get<1>(expected) = 2;

        CPPUNIT_ASSERT_EQUAL(expected,*it);
    }

    void testIteratorFeedWithDoubles(){
        std::stringstream ss("1.4,2.5");
        csv::iterator<TwoDoubleRecord> it(ss);

        TwoDoubleRecord expected;
        boost::tuples::get<0>(expected) = 1.4;
        boost::tuples::get<1>(expected) = 2.5;

        CPPUNIT_ASSERT_EQUAL(expected,*it);
    }

    void testFillTuple() {
        ThreeIntRecord expected, obtained;
        std::string line = "1,2,3";
        Tokens tokens(line);

        csv::details::helper<ThreeIntRecord,2>::fill(obtained, tokens.begin(), tokens.end());

        boost::tuples::get<0>(expected) = 1;
        boost::tuples::get<1>(expected) = 2;
        boost::tuples::get<2>(expected) = 3;
        CPPUNIT_ASSERT_EQUAL(expected,obtained);
    }

    void testFillTupleWithMixedRecords(){
        ThreeMixedRecord expected, obtained;
        std::string line = "1,hola,2.4";
        Tokens tokens(line);
        csv::details::helper<ThreeMixedRecord,2>::fill(obtained, tokens.begin(), tokens.end());

        boost::tuples::get<0>(expected) = 1;
        boost::tuples::get<1>(expected) = "hola";
        boost::tuples::get<2>(expected) = 2.4;
        CPPUNIT_ASSERT_EQUAL(expected,obtained);

        // Test the function that hides the manipulation of the number of elements
        csv::details::filler<ThreeMixedRecord>::fill(obtained, tokens.begin(), tokens.end());
        CPPUNIT_ASSERT_EQUAL(expected,obtained);
    }

    void testReadIstream(){
        std::stringstream ss("1,hola,2.4");
        csv::iterator<ThreeMixedRecord> it(ss);

        ThreeMixedRecord expected;
        boost::tuples::get<0>(expected) = 1;
        boost::tuples::get<1>(expected) = "hola";
        boost::tuples::get<2>(expected) = 2.4;
        CPPUNIT_ASSERT_EQUAL(expected,*it);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(csv_iteratorTest);




