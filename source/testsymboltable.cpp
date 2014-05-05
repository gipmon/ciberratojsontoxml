#include <iostream>
#include <string>
#include <map>
#include "symboltable.h"

using namespace std;
extern map<string, parameter>::iterator it;
extern map<string, parameter> symbol_table;

void construct(map<string, parameter> symboltable);

int main (){
    parameter one;
    parameter two;
    string key1 = "key time";
    string key2 = "beacon sensor aperture";

    one.comment = "Time to finish an intermmediate goal";
    one.class_name = "scoring parameters";
    one.value_type = "uint";
    one.xml_name = "KeyTime";

    two.comment = "Aperture of the beacon sensor";
    two.class_name = "robot modelling parameters";
    two.value_type = "double";
    two.default_value = "PI";
    two.xml_name = "BeaconAperture";

    add_parameter(key1, one);
    add_parameter(key2, two);
    construct(symbol_table);
}

void construct(map<string, parameter> symboltable){
    cout << "{\n" << endl;
    for(it = symboltable.begin(); it != symboltable.end(); it++) {
        // itator->first = key
        // itator->second = value
        string key = it->first;
        cout << "\""<< key << "\" : { \n " << "\t\"comment\" : \""<< find_parameter(key).comment << "\" \n" << "\t\"class\" : \""<< find_parameter(key).class_name << "\" \n" << "\t\"value type\" : \""<< find_parameter(key).value_type << "\" \n" << "\t\"default value\" : \""<< find_parameter(key).default_value << "\" \n"  << "\t\"XML name\" : \""<< find_parameter(key).xml_name << "\" \n" << "},"<< endl;
    }
    cout << "\n}" << endl;
}
