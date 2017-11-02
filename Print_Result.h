//
//  Print_Result.h
//
//

#ifndef Print_Result_h
#define Print_Result_h

void show_all_bus_status(const vector< vector<Bus> > &bus_status, int bus_amount);
void show_result(const vector< vector<int> > &result);

// output the status of each bus into the file
void show_all_bus_status(const vector< vector<Bus> > &bus_status, int bus_amount)
{
    ofstream out;
    string bus_num;
    string t[] = { "LEFT", "BOARDING", "UNKNOWN" };
    //vector<bus>::const_iterator it;
    for (int i = 0; i < bus_amount; ++i) {
        bus_num = "bus" + to_string(i) + ".txt";
        out.open(bus_num);
        //it = bus_status[i].begin();
        for (int j =0 ;  j < bus_status[i].size(); j++) {
            if (bus_status[i][j].status == LEFT)
            out << "clock: " << bus_status[i][j].time << " stop_num: " << bus_status[i][j].stop_num << " status: " << t[bus_status[i][j].status] << " take_time: " << bus_status[i][j].time - bus_status[i][j-1].time << endl;
            else
            out << "clock: " << bus_status[i][j].time << " stop_num: " << bus_status[i][j].stop_num << " status: " << t[bus_status[i][j].status] << endl;
        }
        out.close();
    }
}

// get the average, max and min queue size and output on the screen
void show_result(const vector< vector<int> > &result)
{
    double sum = 0;
    int max = 0;
    int min = INT_MAX;
    int stop_number = 0;
    int i=0;
    for(;i<result.size();i++){
        sum = 0,max = 0,min = INT_MAX;
        for(int j=0;j<result[i].size();j++){
            sum +=result[i][j];
            if(max < result[i][j])
            max = result[i][j];
            if(min > result[i][j])
            min = result[i][j];
        }
        cout<< "Stop "<<stop_number++<<":Average size of waiting queue : "<<sum / result[i].size()<<endl;
        cout<<"         Maximum size of waiting queue : "<<max<<endl;
        cout<<"         Minimum size of waiting queue : "<<min<<endl;
    }
}


#endif /* Print_Result_h */
