#pragma once

#include <string>
#include <iostream>
#include <fstream>

namespace ariel{
    class NumberWithUnits{
        private:
            double amount;
            std::string measure;
        public:
            NumberWithUnits(double amu, std::string mea);
            
            static void read_units(std::ifstream& file){
                return;
            }
            
            NumberWithUnits operator+ () const;
            NumberWithUnits operator- () const;
            NumberWithUnits& operator++ ();
            NumberWithUnits operator++ (int dummy);
            NumberWithUnits& operator-- ();
            NumberWithUnits operator-- (int dummy);
            NumberWithUnits& operator+= (const NumberWithUnits& other);
            NumberWithUnits& operator-= (const NumberWithUnits& other);
            NumberWithUnits& operator*= (double a);
            
            friend NumberWithUnits operator+ (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2);
            friend NumberWithUnits operator- (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2);
            friend bool operator== (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2);
            friend bool operator!= (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2);
            friend bool operator>= (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2);
            friend bool operator<= (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2);
            friend bool operator< (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2);
            friend bool operator> (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2);
            friend std::ostream& operator<< (std::ostream& os, const NumberWithUnits& nwu);
            friend std::istream& operator>> (std::istream& is, NumberWithUnits& nwu);
            friend NumberWithUnits operator* (double a, const NumberWithUnits& nwu);
            friend NumberWithUnits operator*(const NumberWithUnits& nwu, double a);
    };
}
