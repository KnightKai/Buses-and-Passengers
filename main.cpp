//
//  main.cpp
//  520BUSSimulation
//

// please add Initialization.h and Event_Struct.h Bus_Struct.h and Print_Result.h into the main.cpp
// and paste random.cpp into the same ducoments not into main.cpp
// If it shows "bus.txt not found" , please check the path of bus.txt


#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <list>
#include <vector>
#include "random.cpp"
#include "Event_Struct.h"
#include "Initialization.h"
#include "Bus_Struct.h"
#include "Print_Result.h"
using namespace std;




int main()
{
    // initialize the seed from package random
    urandini();
    // the result is for recording the number of passages at each stop changes with time
    vector< vector<int> > result;
    vector<int> queue;
    // bus_status is for recording all the buses status
    vector< vector<Bus> > bus_status;
    // initialize parameter
    parameter para;
    list<event_struct> event_list;
    double clock(0.0), stop_time(28800);
    event_struct event, event_tmp;
    
    //initialize function
    Initialization(para , queue, result, event_list, bus_status);
    int stop_amount = para.stop_amount;
    int bus_amount  = para.bus_amount;
    int driving_time   = para.driving_time;
    int boarding_time  = para.boarding_time;
    int mean_arrival_rate = para.mean_arrival_rate;
    while(clock <= stop_time) {
        //get the next event
        get_event(event, event_list);
        clock = event.event_time;
        
        // deal with different Event type
        if(event.event_type == PERSON){
            queue[event.stop_num]++;
            int cur_number = queue[event.stop_num];
            result[event.stop_num].push_back(cur_number);
            generate_event(event_tmp, clock + exprand(60.0 / mean_arrival_rate), PERSON, event.stop_num, -1);
            
        }
        else if(event.event_type == ARRIVAL){
            if (queue[event.stop_num] == 0) {
                generate_event(event_tmp, clock + driving_time * 60, ARRIVAL, (event.stop_num + 1) % stop_amount, event.bus_num);
                Bus bus_status_tmp(clock,event.stop_num,LEFT);
                bus_status[event_tmp.bus_num].push_back(bus_status_tmp);
            }
            // else generate board
            else {
                generate_event(event_tmp, clock, BOARDER, event.stop_num, event.bus_num);
                Bus bus_status_tmp(clock,event.stop_num,BOARDING);
                bus_status[event_tmp.bus_num].push_back(bus_status_tmp);
            }
            
        }
        else if(event.event_type == BOARDER){
            if (0 == queue[event.stop_num]) {
                generate_event(event_tmp, clock + driving_time * 60, ARRIVAL, (event.stop_num + 1) % stop_amount, event.bus_num);
                
                // statistic the status of bus
                Bus bus_status_tmp(clock,event.stop_num,LEFT);
                bus_status[event_tmp.bus_num].push_back(bus_status_tmp);
            }
            else {
                // update the queue
                queue[event.stop_num]--;
                result[event.stop_num].push_back(queue[event.stop_num]);
                
                generate_event(event_tmp, clock + boarding_time, BOARDER, event.stop_num, event.bus_num);
            }
           
        }

        add_event(event_tmp, event_list);
        event_list.sort(); // sort the event list
    }
    
    show_all_bus_status(bus_status, bus_amount);
    show_result(result);
    
}
