#include <stdexcept>
#include <queue>
#include <iterator>
#include <map>
#include <iostream>
using namespace std;
#include "NumberWithUnits.hpp"

// graph data structure for dynamic storing of given measurments as nodes in a directed graph.
// in this case a node represent a measurment and the edges have the weight needed to convert one measurment to another
namespace ariel{

    //sets all nodes tag to 0
    void Graph::reset_tag(){
        for (pair<string, Node> it : nodes){
            nodes.at(it.first).tag = 0;
        }      
    }
    bool Graph::is_empty(){
        return nodes.empty();
    }
    void Graph::add_node(const string& id){
        nodes.insert(pair<string,Node>(id,Node(id)));
    }
    //conects 2 nodes from node1 to node2 with weight of 1/value and fron node2 to node1 with weight of value 
    void Graph::connect(const string& node1, const string& node2, double value){
        nodes.at(node1).add_edge(node2, 1/value);
        nodes.at(node2).add_edge(node1, value);
    }
    bool Graph::contains(const string& node){
        return (nodes.count(node) != 0);
    }
    //returns the weight of the path from src to dst using bfs
    //calculate conversion rate from src to dst, 0 if none existing
    double Graph::get_path(const string& src, const string& dst){
        if(!(this->contains(src)) || !(this->contains(dst))){ return 0;}  //check if measure exist
        if(src == dst){ return 1;}   //check if the same measurment
        reset_tag();    //create a clean state
        queue<Node> q;  //a queue of connected nodes
        nodes.at(src).tag = 1;   //node src visited set tag as conversion value to src
        q.push(nodes.at(src));
        Node tmp("-");    //tmp node holder
        while(!q.empty()){
            tmp = q.front();   //poop checked node
            q.pop();
            //for every neighbor of node check if visited if not set its tag as the conversion value to src
            for (size_t i = 0; i < tmp.edges_id.size(); i++){
                string nei = tmp.edges_id.at(i);
                double nei_val = tmp.edges_val.at(i);
                //if found dst return the conversion value from src to tmp to dst
                if(nei == dst){
                   return (tmp.tag)*(nei_val);  
                }
                if(nodes.at(nei).tag == 0){  //check if visited
                    nodes.at(nei).tag = tmp.tag * nei_val;
                    q.push(nodes.at(nei));   //push fo later checking
                }
            }  
        }
        return 0;
    }

Graph NumberWithUnits::g;  // initialize the graph

NumberWithUnits::NumberWithUnits(double amu, const string& mea){
    if(g.contains(mea)){  //if measurment exist create new number
        amount = amu;
        measure = mea;
    }
    else{
        throw invalid_argument("Invalid measurment\n");
    }
}

void NumberWithUnits::read_units(ifstream& file){  //read a given txt file and add it's value to the graph
    int one = 0;
    char equ = 0;
    string mea1;
    string mea2;
    double amu = 0;
    while(file >> one >> mea1 >> equ >> amu >> mea2){  //reads 1 measurment1 = conversion-value measurment2
        if(!g.contains(mea1)){ g.add_node(mea1);} //if measurment dosnt exist add it
        if(!g.contains(mea2)){ g.add_node(mea2);}
        g.connect(mea1, mea2, amu);
    }
}
//return the same value
NumberWithUnits NumberWithUnits::operator+ () const{
    return NumberWithUnits(amount, measure);
}
//return negetive value
NumberWithUnits NumberWithUnits::operator- () const{
    return NumberWithUnits(-amount, measure);
}
//increment
NumberWithUnits& NumberWithUnits::operator++ (){
    amount++;
    return *this;
}
//pre-increment
NumberWithUnits NumberWithUnits::operator++ (int dummy){
    NumberWithUnits temp(amount, measure);
    amount++;
    return temp;
}
//decremnet
NumberWithUnits& NumberWithUnits::operator-- (){
    amount--;
    return *this;
}
//pre-decremnet
NumberWithUnits NumberWithUnits::operator-- (int dummy){
    NumberWithUnits temp(amount, measure);
    amount--;
    return temp;
}
//adds the other number value to this number
NumberWithUnits& NumberWithUnits::operator+= (const NumberWithUnits& other){
    double convert = g.get_path(measure, other.measure);   
    if(convert == 0){
        string error = "Units do not match - [" +measure+"] cannot be converted to ["+other.measure+"]\n";
        throw logic_error(error);
        }
    amount += other.amount * convert;
    return *this;
}
//redices the other number value to this number
NumberWithUnits& NumberWithUnits::operator-= (const NumberWithUnits& other){
    double convert = g.get_path(measure, other.measure);   
    if(convert == 0){
        string error = "Units do not match - [" +measure+"] cannot be converted to ["+other.measure+"]\n";
        throw logic_error(error);
        }
    amount -= other.amount * convert;
    return *this;
}
//multiplie this number value by a
NumberWithUnits& NumberWithUnits::operator*= (double a){
    amount *= a;
    return *this;
}
//return the sum of the two numbers
NumberWithUnits operator+ (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2){
    double convert = NumberWithUnits::g.get_path(nwu1.measure, nwu2.measure);  
    if(convert == 0){
        string error = "Units do not match - [" +nwu2.measure+"] cannot be converted to ["+nwu1.measure+"]\n";
        throw logic_error(error);
        }
    return NumberWithUnits(nwu1.amount + nwu2.amount * convert, nwu1.measure);
}
//return the subtraction of the two numbers
NumberWithUnits operator- (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2){
    double convert = NumberWithUnits::g.get_path(nwu1.measure, nwu2.measure);
    if(convert == 0){
        string error = "Units do not match - [" +nwu2.measure+"] cannot be converted to ["+nwu1.measure+"]\n";
        throw logic_error(error);
        }
    return NumberWithUnits(nwu1.amount - nwu2.amount * convert, nwu1.measure);
}
//return if equal by a threshold of 0.0001
bool operator== (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2){
    double convert = NumberWithUnits::g.get_path(nwu1.measure, nwu2.measure);
    if(convert == 0){
        string error = "Units do not match - [" +nwu2.measure+"] cannot be converted to ["+nwu1.measure+"]\n";
        throw logic_error(error);
        }
     const double threshold = 0.0001;
     double res = nwu1.amount - nwu2.amount * convert;
     return (-threshold <= res && res <= threshold);
}
bool operator!= (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2){
    return !(nwu1 == nwu2);
}
//returns if bigger or equal
bool operator>= (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2){
    double convert = NumberWithUnits::g.get_path(nwu1.measure, nwu2.measure);
    if(convert == 0){
        string error = "Units do not match - [" +nwu2.measure+"] cannot be converted to ["+nwu1.measure+"]\n";
        throw logic_error(error);
        }
    return(nwu1.amount > nwu2.amount * convert || nwu1 == nwu2);
}
//returns if lesser or equal
bool operator<= (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2){
    double convert = NumberWithUnits::g.get_path(nwu1.measure, nwu2.measure);
    if(convert == 0){
        string error = "Units do not match - [" +nwu2.measure+"] cannot be converted to ["+nwu1.measure+"]\n";
        throw logic_error(error);
        }
    return(nwu1.amount < nwu2.amount * convert || nwu1 == nwu2);
}
bool operator< (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2){
    return !(nwu1 >= nwu2);
}
bool operator> (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2){
    return !(nwu1 <= nwu2);
}
//returns an ostream of "value[measurment]"
ostream& operator<< (std::ostream& os, const NumberWithUnits& nwu){
    return (os << nwu.amount << '[' << nwu.measure << ']');
}
//recive an input in the form of "value[measurment]" and return a new number with the given values
istream& operator>>( std::istream& is, NumberWithUnits& nwu){
    double new_amu = 0;
    string new_mea;
    char c = 0;
    //cheack the beginig format "value ["
    if(!(is >> new_amu) || !(is >> c) || c != '['){  
        throw invalid_argument("Invalid measurment\n");
    }
    //reades the rest of the format "amount]"
    while(is >> c){
        if(c == ']'){ break;}
        new_mea += c;
    }
    if(new_mea.empty() || !NumberWithUnits::g.contains(new_mea)){ throw invalid_argument("Invalid measurment\n");}
    //if there were no errors set the new attributes
    nwu.measure = new_mea;
    nwu.amount = new_amu;
    return is;
}
 //multiplie by a double a and return the new value
NumberWithUnits operator* (double a, const NumberWithUnits& nwu){
    return NumberWithUnits(a*nwu.amount, nwu.measure);
}
NumberWithUnits operator* (const NumberWithUnits& nwu, double a){
    return NumberWithUnits(a*nwu.amount, nwu.measure);
}

}

