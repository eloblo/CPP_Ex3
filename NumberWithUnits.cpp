#include <stdexcept>
#include <queue>
#include <iterator>
#include <map>
#include <iostream>
using namespace std;
#include "NumberWithUnits.hpp"

namespace ariel{

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
    void Graph::connect(const string& node1, const string& node2, double value){
        nodes.at(node1).add_edge(node2, 1/value);
        nodes.at(node2).add_edge(node1, value);
    }
    bool Graph::contains(const string& node){
        return (nodes.count(node) != 0);
    }
    double Graph::get_path(const string& src, const string& dst){
        if(!(this->contains(src)) || !(this->contains(dst))){ return 0;}
        if(src == dst){ return 1;}
        reset_tag();
        queue<Node> q;
        nodes.at(src).tag = 1;
        q.push(nodes.at(src));
        Node tmp("-");
        while(!q.empty()){
            tmp = q.front();
            q.pop();
            for (size_t i = 0; i < tmp.edges_id.size(); i++){
                string nei = tmp.edges_id.at(i);
                double nei_val = tmp.edges_val.at(i);
                if(nei == dst){
                   return (tmp.tag)*(nei_val);
                }
                if(nodes.at(nei).tag == 0){
                    nodes.at(nei).tag = tmp.tag * nei_val;
                    q.push(nodes.at(nei));
                }
            }  
        }
        return 0;
    }

Graph NumberWithUnits::g;

NumberWithUnits::NumberWithUnits(double amu, const string& mea){
    if(g.contains(mea)){
        amount = amu;
        measure = mea;
    }
    else{
        throw invalid_argument("Invalid measurment\n");
    }
}

void NumberWithUnits::read_units(ifstream& file){
    int one = 0;
    char equ = 0;
    string mea1;
    string mea2;
    double amu = 0;
    while(file >> one >> mea1 >> equ >> amu >> mea2){
        if(!g.contains(mea1)){ g.add_node(mea1);}
        if(!g.contains(mea2)){ g.add_node(mea2);}
        g.connect(mea1, mea2, amu);
    }
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
    double convert = g.get_path(measure, other.measure);
    if(convert == 0){
        string error = "Units do not match - [" +measure+"] cannot be converted to ["+other.measure+"]\n";
        throw logic_error(error);
        }
    amount += other.amount * convert;
    return *this;
}
NumberWithUnits& NumberWithUnits::operator-= (const NumberWithUnits& other){
    double convert = g.get_path(measure, other.measure);
    if(convert == 0){
        string error = "Units do not match - [" +measure+"] cannot be converted to ["+other.measure+"]\n";
        throw logic_error(error);
        }
    amount -= other.amount * convert;
    return *this;
}

NumberWithUnits& NumberWithUnits::operator*= (double a){
    amount *= a;
    return *this;
}
            
NumberWithUnits operator+ (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2){
    double convert = NumberWithUnits::g.get_path(nwu1.measure, nwu2.measure);
    if(convert == 0){
        string error = "Units do not match - [" +nwu2.measure+"] cannot be converted to ["+nwu1.measure+"]\n";
        throw logic_error(error);
        }
    return NumberWithUnits(nwu1.amount + nwu2.amount * convert, nwu1.measure);
}
NumberWithUnits operator- (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2){
    double convert = NumberWithUnits::g.get_path(nwu1.measure, nwu2.measure);
    if(convert == 0){
        string error = "Units do not match - [" +nwu2.measure+"] cannot be converted to ["+nwu1.measure+"]\n";
        throw logic_error(error);
        }
    return NumberWithUnits(nwu1.amount - nwu2.amount * convert, nwu1.measure);
}

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
bool operator>= (const NumberWithUnits& nwu1, const NumberWithUnits& nwu2){
    double convert = NumberWithUnits::g.get_path(nwu1.measure, nwu2.measure);
    if(convert == 0){
        string error = "Units do not match - [" +nwu2.measure+"] cannot be converted to ["+nwu1.measure+"]\n";
        throw logic_error(error);
        }
    return(nwu1.amount > nwu2.amount * convert || nwu1 == nwu2);
}
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
ostream& operator<< (std::ostream& os, const NumberWithUnits& nwu){
    return (os << nwu.amount << '[' << nwu.measure << ']');
}
istream& operator>>( std::istream& is, NumberWithUnits& nwu){
    double new_amu = 0;
    string new_mea;
    char c = 0;
    if(!(is >> new_amu) || !(is >> c) || c != '['){
        throw invalid_argument("Invalid measurment\n");
    }
    while(is >> c){
        if(c == ']'){ break;}
        new_mea += c;
    }
    if(new_mea.empty() || !NumberWithUnits::g.contains(new_mea)){ throw invalid_argument("Invalid measurment\n");}
    nwu.measure = new_mea;
    nwu.amount = new_amu;
    return is;
}
NumberWithUnits operator* (double a, const NumberWithUnits& nwu){
    return NumberWithUnits(a*nwu.amount, nwu.measure);
}
NumberWithUnits operator* (const NumberWithUnits& nwu, double a){
    return NumberWithUnits(a*nwu.amount, nwu.measure);
}

}

