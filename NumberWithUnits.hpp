#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
//#include "Graph.hpp"

namespace ariel{

class Graph{
        private:
            class Node{
                public:
                    std::string _id;
                    std::vector<std::string> edges_id;
                    std::vector<double> edges_val;
                    Node(std::string id){
                        _id = id;
                    }
                    double tag = 0;
                    void add_edge(std::string node, double value){
                        edges_id.push_back(node);
                        edges_val.push_back(value);
                    }
            };
            std::map<std::string, Node> nodes;
            void reset_tag();
            
        public:
            bool is_empty();
            void add_node(const std::string& id);
            void connect(const std::string& node1, const std::string& node2, double value);
            bool contains(const std::string& node);
            double get_path(const std::string& src, const std::string& dst);
    };  

    class NumberWithUnits{
        private:
            static Graph g;
            double amount;
            std::string measure;
        public:
            NumberWithUnits(double amu, const std::string& mea);
            
            static void read_units(std::ifstream& file);
            
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
