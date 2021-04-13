#include "doctest.h"
#include "NumberWithUnits.hpp"
using namespace ariel;

#include <string>
#include <iostream>
#include <sstream>
using namespace std;

TEST_CASE("Read text file"){
    ifstream units_file{"units.txt"};
    CHECK_NOTHROW(NumberWithUnits::read_units(units_file));
}

TEST_CASE("Bool operator") {
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a{2, "km"};
    NumberWithUnits b{2000, "m"};
    NumberWithUnits c{100, "m"};
    NumberWithUnits d{1, "ton"};
    CHECK_EQ(a,b);
    CHECK_NE(a,c);
    CHECK_NE(b,d);
    CHECK_GT(b,c);
    CHECK_LT(c,a);
    CHECK_GE(a,b);
    CHECK_LE(a,b);
}

TEST_CASE("Unary operator"){
    ifstream units_file{"units.txt"};
    NumberWithUnits a{3, "km"};
    NumberWithUnits b{100, "m"};
    CHECK_EQ(+a,a);
    CHECK_EQ(-b,NumberWithUnits(-100, "m"));
    CHECK_EQ(++b,NumberWithUnits(101, "m"));
    CHECK_EQ(b++,NumberWithUnits(0.101, "Km"));
    CHECK_EQ(b,NumberWithUnits(10200, "cm"));
    CHECK_EQ(--a,NumberWithUnits(2, "km"));
    CHECK_EQ(a--,NumberWithUnits(2, "km"));
    CHECK_EQ(a,NumberWithUnits(1, "km"));
}

TEST_CASE("Binary operators"){
    ifstream units_file{"units.txt"};
    NumberWithUnits a{3, "km"};
    NumberWithUnits b{100, "m"};
    a *= 3;
    CHECK_EQ(a,NumberWithUnits(9000, "m"));
    CHECK_EQ(a-b,NumberWithUnits(8.9, "km"));
    CHECK_EQ(a+b,NumberWithUnits(9100, "m"));
    CHECK_EQ(3*b,NumberWithUnits(300, "m"));
    CHECK_EQ(b*3,NumberWithUnits(30000, "cm"));
    a -= b;
    b += a;
    CHECK_EQ(a,NumberWithUnits(8900, "m"));
    CHECK_EQ(b,NumberWithUnits(9.1, "km"));
}

TEST_CASE("IO operators"){
    ifstream units_file{"units.txt"};
    NumberWithUnits a{3, "km"};
    istringstream sample_input{"700 [ kg ]"};
    sample_input >> a;
    CHECK_EQ(a,NumberWithUnits(700, "kg"));
    ostringstream stream;
    stream << a;
    string str =  stream.str();
    CHECK_EQ(str,"700[kg]");
}

TEST_CASE("Exceptions"){
    ifstream units_file{"units.txt"};
    NumberWithUnits a{3, "km"};
    NumberWithUnits b{100, "kg"};
    CHECK_THROWS(a+b);
    CHECK_THROWS(a-b);
    CHECK_THROWS(a+=b);
    CHECK_THROWS(a-=b);
}
