//
//  Initialization.h
//


#ifndef Initialization_h
#define Initialization_h



#include <string>
#include <list>
#include "Event_Struct.h"
#include "Bus_Struct.h"
using namespace std;


// the struct of single bus status


// the struct contains all the parameters stored in the configure file
struct parameter{
    int stop_amount;
    int bus_amount;
    int driving_time;
    int boarding_time;
    int mean_arrival_rate;
} ;

int strtoint(string str);
void Initialization(parameter &p, vector<int>&queue, vector< vector<int> > &result, list<event_struct> &event_list,  vector< vector<Bus> > &bus_status);


// convert string to int
int strtoint(string str)
{
    stringstream ss;
    int val;
    ss << str;
    ss >> val;
    return val;
}


void Initialization(parameter &p, vector<int>& queue, vector< vector<int> > &result, list<event_struct> &event_list,  vector< vector<Bus> > &bus_status)
{
    //open file bus.txt
    ifstream file("/Users/kaikang/Desktop/bus.txt");
    if (!file) {
        cout<<"bus.txt not found" <<endl;
        return;
    }
    
    // read parameter from the bus.txt file
    string line, temp, value;
    while (getline(file, line)) {
        auto pos = line.find("=");
        if (pos != string::npos) {
            temp = line.substr(0, pos);
            value = line.substr(pos + 1, line.length());
            if ("stop_amount" == temp)
                p.stop_amount = strtoint(value);
            else if ("bus_amount" == temp)
                p.bus_amount = strtoint(value);
            else if ("driving_time" == temp)
                p.driving_time = strtoint(value);
            else if ("boarding_time" == temp)
                p.boarding_time = strtoint(value);
            else if ("mean_arrival_rate" == temp)
                p.mean_arrival_rate = strtoint(value);
        }
    }
    
    // initialize the queue and result
    queue.resize(p.stop_amount);
    for (int i = 0; i < p.stop_amount; ++i) {
        queue[i]=0;
        vector<int> tmp(1,0);
        //tmp.clear();
        //tmp.push_back(0);
        result.push_back(tmp);
        
    }
    
    // generate the initial bus events and statistic
    event_struct event;
    vector<Bus> bus_tmp;
    
    for (int i = 0; i < p.bus_amount; ++i) {
        event.event_time = 0;
        event.event_type = ARRIVAL;
        event.stop_num = i * (p.stop_amount / p.bus_amount);
        event.bus_num = i;
        add_event(event, event_list);
        
        // initialize the statistic
        Bus bus_stat_tmp(0,event.stop_num,BOARDING);
        bus_tmp.clear();                          // every car get one vector
        bus_tmp.push_back(bus_stat_tmp);
        bus_status.push_back(bus_tmp);
    }
    
    // generate the initial person events
    for (int i = 0; i < p.stop_amount; ++i) {
        event.event_time = 0;
        event.event_type = PERSON;
        event.stop_num = i;
        event.bus_num = -1;
        add_event(event, event_list);
    }
    
}








#endif /* Initialization_h */
