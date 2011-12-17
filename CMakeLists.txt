project(csv_iterator)
cmake_minimum_required(VERSION 2.6.2)

set(CMAKE_CXX_FLAGS "--std=c++0x")          

include_directories(include)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake) 

find_package(Boost COMPONENTS iostreams REQUIRED)

add_executable(csvItExample src/main.cpp)

# Testing
find_package(CppUnit REQUIRED)
add_executable(UnitTester test/main.cpp
                    test/csv_iteratorTest.cpp
              )

target_link_libraries(UnitTester ${CPPUNIT_LIBRARIES}
                                 ${Boost_IOSTREAMS_LIBRARIES})


