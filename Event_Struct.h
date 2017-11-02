//  Event_Struct.h
//

#ifndef Event_Struct_h
#define Event_Struct_h


#include <list>
using namespace std;
enum choice_event_type { PERSON, ARRIVAL, BOARDER };

class event_struct{
public:
    double event_time;
    enum choice_event_type event_type;
    int stop_num;
    int bus_num;
    event_struct(){}
    ~event_struct(){}
    // override operator < for sort function
    bool operator < (const event_struct& event) const{
        
        return event_time < event.event_time
        || (event_time == event.event_time && stop_num < event.stop_num)
        || (event_time == event.event_time && stop_num == event.stop_num && bus_num < event.bus_num)
        || (event_time == event.event_time && stop_num == event.stop_num && bus_num == event.bus_num && event_type < event.event_time);
    }
};

// get the event from the event list
void get_event(event_struct& event, list<event_struct>& event_list){
        event= *(event_list.begin());
        event_list.pop_front();
}

// generate a new event
void generate_event(event_struct& event, double event_time, choice_event_type event_type, int stop_num, int bus_num){
    
        event.event_time = (event_time);
        event.event_type = (event_type);
        event.stop_num = stop_num;
        event.bus_num = bus_num;
}

// add a new event to the event list
void add_event(event_struct& event , list<event_struct>& event_list ){
    
        event_list.push_back(event);
}





#endif /* Event_Struct_h */
