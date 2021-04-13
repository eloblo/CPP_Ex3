#include <stdexcept>
using namespace std;
#include "NumberWithUnits.hpp"

namespace ariel{

NumberWithUnits::NumberWithUnits(double amu, string mea){
    amount = amu;
    measure = move(mea);
}

NumberWithUnits NumberWithUnits::operator+ () const{
            	return NumberWithUnits(amount, measure);
            }
NumberWithUnits NumberWithUnits::operator- () const{
            	return NumberWithUnits(-amount, measure);
}

NumberWithUnits& NumberWithUnits::operator++ (){
    amount++;
    return *this;
}
NumberWithUnits NumberWithUnits::operator++ (int dummy){
    NumberWithUnits temp(amount, measure);
    amount++;
    return temp;
}
NumberWithUnits& NumberWithUnits::operator-- (){
    amount--;
    return *this;
}
NumberWithUnits NumberWithUnits::operator-- (int dummy){
    NumberWithUnits temp(amount, measure);
    amount--;
    return temp;
}
NumberWithUnits& NumberWithUnits::operator+= (const NumberWithUnits& other){
    return *this;
}
NumberWithUnits& NumberWithUnits::operator-= (const NumberWithUnits& other){
    return *this;
}

NumberWithUnits& NumberWithUnits::operator*= (double a){
    amount *= a;
    return *this;
}
            
NumberWithUnits operator+ (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2){
    return nwu1;
}
NumberWithUnits operator- (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2){
    return nwu1;
}

bool operator== (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2){
    return true;
}
bool operator!= (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2){
    return true;
}
bool operator>= (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2){
    return true;
}
bool operator<= (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2){
    return true;
}
bool operator< (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2){
    return true;
}
bool operator> (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2){
    return true;
}
ostream& operator<< (std::ostream& os, const NumberWithUnits& nwu){
    return (os << nwu.amount << '[' << nwu.measure << ']');
}
istream& operator>>( std::istream& is, NumberWithUnits& nwu){
    return is;
}
NumberWithUnits operator* (double a, const NumberWithUnits& nwu){
    return NumberWithUnits(a*nwu.amount, nwu.measure);
}
NumberWithUnits operator* (const NumberWithUnits& nwu, double a){
    return NumberWithUnits(a*nwu.amount, nwu.measure);
}

}

