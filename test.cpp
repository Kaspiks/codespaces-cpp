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

int main() {
  ifstream file("input.txt");
  string line;
  string start_line;
  vector<Officer> cit_officers;
  vector<Officer> non_cit_officers;
  int l, f_id, set_time;
  char type;
  // char delimiter = ' ';

  if (file.is_open()) {
    // Read each line from the file and store it in the
    // 'line' variable.
    
    getline(file, line);
    stringstream smth(line);
    int cit_off_count, non_cit_off_count, cit_def_time, non_cit_def_time;

    smth >> cit_off_count >> non_cit_off_count >> cit_def_time >> non_cit_def_time;

    // std::cout << "cit_off_count: " << cit_off_count << std::endl;
    // std::cout << "non_cit_off_count: " << non_cit_off_count << std::endl;
    // std::cout << "cit_def_time: " << cit_def_time << std::endl;
    // std::cout << "non_cit_def_time: " << non_cit_def_time << std::endl;

    for(int i = 1; i <= cit_off_count; i++) {
      Officer v;
      v.type = 'P';
      v.id = i;
      v.time = cit_def_time;
      v.time_of_availability_change = 0;

      cit_officers.push_back(v);
    }

    for(int i = 1; i <= non_cit_off_count; i++) {
      Officer v;
      v.type = 'N';
      v.id = i;
      v.time = non_cit_def_time;
      v.time_of_availability_change = 0;

      non_cit_officers.push_back(v);
    }

    while (getline(file, line)) {
      // cout << line << endl;

      stringstream ss(line);

      string t;
      // Make a while loop that iterates over the officer lines in input.txt and then check it against the vectors of struct depending on the type in the input.txt and update

      if (ss >> l >> type >> f_id >> set_time) {
        if (type == 'P') {
          for (auto &officer : cit_officers) {
            if (officer.type == type && officer.id == f_id) {
              officer.time = set_time;
            }
          }
        }

        if (type == 'N') {
          for (auto &officer : non_cit_officers) {
            if (officer.type == type && officer.id == f_id) {
              officer.time = set_time;
            }
          }
        }
      }

      // while(getline(ss, t, delimiter)) {
      //   cout << "\"" << t << "\"" << " "; 
      // }

    }

    // Close the file stream once all lines have been
    // read.
    file.close();
  } else {
    // Print an error message to the standard error
    // stream if the file cannot be opened.
    cerr << "Unable to open file!" << endl;
  }

  for (auto& a : cit_officers) {
    cout << "Type: " << a.type << " Cit Officer id " << a.id << " time:" << a.time << " time of availability: " << a.time_of_availability_change <<endl;
  }

  for (auto& a : non_cit_officers) {
    cout << "Type: " << a.type << " Cit Officer id " << a.id << " time:" << a.time << " time of availability: " << a.time_of_availability_change <<endl;
  }

return 0;
}
