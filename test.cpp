#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct Officer {
  char type;
  int id;
  int time;
  int time_of_availability_change;
};

int findMin(const std::vector<int>& vec) {
    if (vec.empty()) throw std::runtime_error("Vector is empty!");

    int minVal = vec[0];  // Assume first element is minimum
    for (int num : vec) {
        if (num < minVal) {
            minVal = num;
        }
    }
    return minVal;
}

int main() {
  ifstream file("customs.txt");
  string line;
  string start_line;
  vector<Officer> cit_officers;
  vector<Officer> non_cit_officers;
  char delimiter = ' ';

  if (file.is_open()) {
    // Read each line from the file and store it in the
    // 'line' variable.

    getline(file, line);
    stringstream smth(line);
    int cit_off_count, non_cit_off_count, cit_def_time, non_cit_def_time;

    smth >> cit_off_count >> non_cit_off_count >> cit_def_time >> non_cit_def_time;

     std::cout << "cit_off_count: " << cit_off_count << std::endl;
     std::cout << "non_cit_off_count: " << non_cit_off_count << std::endl;
     std::cout << "cit_def_time: " << cit_def_time << std::endl;
     std::cout << "non_cit_def_time: " << non_cit_def_time << std::endl;
    int times=-1;
    for(int i = 1; i <= cit_off_count; i++) {
      Officer v;
      v.type = 'P';
      v.id = i;
      v.time = cit_def_time;
      v.time_of_availability_change = ++times;

      cit_officers.push_back(v);
    }
    times =-1;
    for(int i = 1; i <= non_cit_off_count; i++) {
      Officer v;
      v.type = 'N';
      v.id = i;
      v.time = non_cit_def_time;
      v.time_of_availability_change = ++times;
    cout<<"Times: "<<times<<' ';
      non_cit_officers.push_back(v);
    }
    vector <int> P_off_avail_times;
    for(auto& a : cit_officers){
        P_off_avail_times.push_back(a.time_of_availability);
    }
    vector <int> N_off_avail_times;
    for(auto& a : non_cit_officers){
        N_off_avail_times.push_back(a.time_of_availability);
    }

    //Check output
    cout<<"Before the change:"<<endl;
    for (auto& a : cit_officers) {
      cout << "Type: " << a.type << " Cit Officer id " << a.id << " time:" << a.time << " time of availability: " << a.time_of_availability_change <<endl;
    }

    for (auto& a : non_cit_officers) {
      cout << "Type: " << a.type << " Cit Officer id " << a.id << " time:" << a.time << " time of availability: " << a.time_of_availability_change <<endl;
    }
    //Check output


    vector<pair<int,int>> output;
    while (getline(file, line)) {
        stringstream ss(line);

    if(line[0]=='T'){  //works successfully
        char type;
        int id, time;
        ss.seekg(1,ss.beg);
        ss>>type;
        ss>>id>>time;
        if(type='P'){
            for(auto& a: cit_officers){
                if (a.id==id){
                    a.time=time;
                }
            }
        }
        else{
            for(auto& b:non_cit_officers){
                if (b.id==id){
                    b.time=time;
                }
            }
        }
    }else{
        char arr_type;
        int arr_time;
        ss>>arr_type;
        ss>>arr_time;
        if(arr_type=='P'){
            //Make a loop over officers to check time availability, how to check if all officers are unavailable and find minimum?
        }
    }
//    cout<<type<<' '<<id<< ' '<<time<<endl;

    }
    cout<<"After the change:"<<endl;
        for (auto& a : cit_officers) {
      cout << "Type: " << a.type << " Cit Officer id " << a.id << " time:" << a.time << " time of availability: " << a.time_of_availability_change <<endl;
    }

    for (auto& a : non_cit_officers) {
      cout << "Type: " << a.type << " Cit Officer id " << a.id << " time:" << a.time << " time of availability: " << a.time_of_availability_change <<endl;
    }
    // Close the file stream once all lines have been
    // read.
    file.close();
  } else {
    // Print an error message to the standard error
    // stream if the file cannot be opened.
    cerr << "Unable to open file!" << endl;
  }

return 0;
}
