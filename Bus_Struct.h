//
//  Bus_Struct.h
//




#ifndef Bus_Struct_h
#define Bus_Struct_h

#include <list>

using namespace std;
enum choice_bus_status { LEFT, BOARDING, UNKNOWN };


class Bus{
public:
    double time;
    int stop_num;
    enum choice_bus_status status;
    Bus(int time,int stop_num,enum choice_bus_status status){
        this->time = time;
        this->stop_num = stop_num;
        this->status = status;
    }
    ~Bus(){
    }
};

Bus get_bus_status(const vector<vector<Bus>>& bus_status, double time, int bus_num);


// intput the time and the bus number to get the location of bus and its status
Bus get_bus_status(const vector<vector<Bus>>& bus_status, double time, int bus_num)
{
    Bus tmp(-1,-1,UNKNOWN);
  
    //vector<bus>::const_iterator it = bus_status[bus_num].begin();
    for (int i=0; i < bus_status[bus_num].size(); i++) {
        if (bus_status[bus_num][i].time > time) {
            tmp = bus_status[bus_num][i-1];
            break;
        }
        else if (bus_status[bus_num][i].time == time) {
            tmp = bus_status[bus_num][i];
            break;
        }
    }
    return tmp;
}








#endif /* Bus_Struct_h */
