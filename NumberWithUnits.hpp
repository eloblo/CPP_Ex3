#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

namespace ariel{

// graph data structure for dynamic storing of given measurments as nodes in a directed graph.
// in this case a node represent a measurment and the edges have the weight needed to convert one measurment to another
class Graph{
        private:
            // a private class. used only in the graph data structure.
            class Node{
                public:
                    std::string _id;   
                    std::vector<std::string> edges_id;  //neighboring nodes id
                    std::vector<double> edges_val;      //the weight of an edges. the index is the same as the neighbor id
                    Node(std::string id){
                        _id = id;
                    }
                    double tag = 0;   //the state of the node
                    void add_edge(std::string node, double value){     //add a new node to the neighbors' list without changing the indexes
                        edges_id.push_back(node);
                        edges_val.push_back(value);
                    }
            };
            std::map<std::string, Node> nodes;   //a hash map of all the nodes in the graph. key = node's id, value = node object
            void reset_tag();   //sets all nodes tag to 0
            
        public:
            bool is_empty();   
            void add_node(const std::string& id);   
            //conects 2 nodes from node1 to node2 with weight of 1/value and fron node2 to node1 with weight of value 
            void connect(const std::string& node1, const std::string& node2, double value);
            bool contains(const std::string& node);
            double get_path(const std::string& src, const std::string& dst);   //returns the weight of the path from src to dst using bfs
    };  

    //represent a value with a specific measurment 
    class NumberWithUnits{
        private:
            static Graph g; //a agraph to store all existing measurment. can be loaded dynamicly
            double amount;  //the value of the number
            std::string measure;   //measurment of the number
        public:
            NumberWithUnits(double amu, const std::string& mea);   
            
            //reads an existing file to upload its measurment and conversion rates to the graph for later use
            static void read_units(std::ifstream& file);
            
            //oparators for the number object, same as int
            NumberWithUnits operator+ () const;
            NumberWithUnits operator- () const;
            NumberWithUnits& operator++ ();
            NumberWithUnits operator++ (int dummy);
            NumberWithUnits& operator-- ();
            NumberWithUnits operator-- (int dummy);
            NumberWithUnits& operator+= (const NumberWithUnits& other);
            NumberWithUnits& operator-= (const NumberWithUnits& other);
            NumberWithUnits& operator*= (double a);  //multiplie by a double a and set the new value
            
            
            friend NumberWithUnits operator+ (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2);
            friend NumberWithUnits operator- (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2);
            friend bool operator== (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2);
            friend bool operator!= (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2);
            friend bool operator>= (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2);
            friend bool operator<= (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2);
            friend bool operator< (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2);
            friend bool operator> (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2);
            //returns an ostream of "value[measurment]"
            friend std::ostream& operator<< (std::ostream& os, const NumberWithUnits& nwu);
            //recive an input in the form of "value[measurment]" and return a new number with the given values
            friend std::istream& operator>> (std::istream& is, NumberWithUnits& nwu);
            //multiplie by a double a and return the new value
            friend NumberWithUnits operator* (double a, const NumberWithUnits& nwu);
            friend NumberWithUnits operator*(const NumberWithUnits& nwu, double a);
    };
}
