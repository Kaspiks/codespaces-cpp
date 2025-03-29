#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

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

    vector<Officer> cit_officers;
    vector<Officer> non_cit_officers;

    // Maps to hold overrides for officer times
    map<int, int> cit_officer_times;
    map<int, int> non_cit_officer_times;

    if (file.is_open()) {
        // First line: counts and default times
        getline(file, line);
        stringstream smth(line);
        int cit_off_count, non_cit_off_count, cit_def_time, non_cit_def_time;

        smth >> cit_off_count >> non_cit_off_count >> cit_def_time >> non_cit_def_time;

        // Pre-fill officers with default times
        for (int i = 1; i <= cit_off_count; i++) {
            Officer v = {'P', i, cit_def_time, 0};
            cit_officers.push_back(v);
        }

        for (int i = 1; i <= non_cit_off_count; i++) {
            Officer v = {'N', i, non_cit_def_time, 0};
            non_cit_officers.push_back(v);
        }

        while (getline(file, line)) {
            stringstream ss(line);
            string marker;
            char type;
            int f_id, set_time;

            if (ss >> marker >> type >> f_id >> set_time) {
                if (marker == "T") {
                    if (type == 'P') {
                        cit_officer_times[f_id] = set_time;
                    } else if (type == 'N') {
                        non_cit_officer_times[f_id] = set_time;
                    }
                }
            } else {
                break;
            }
        }

        file.close();
    } else {
        cerr << "Unable to open file!" << endl;
        return 1;
    }

    for (auto &officer : cit_officers) {
        if (cit_officer_times.count(officer.id)) {
            officer.time = cit_officer_times[officer.id];
        }
    }

    for (auto &officer : non_cit_officers) {
        if (non_cit_officer_times.count(officer.id)) {
            officer.time = non_cit_officer_times[officer.id];
        }
    }

    for (const auto& a : cit_officers) {
        cout << "Type: " << a.type
             << " Cit Officer id " << a.id
             << " time: " << a.time
             << " time of availability: " << a.time_of_availability_change
             << endl;
    }

    for (const auto& a : non_cit_officers) {
        cout << "Type: " << a.type
             << " Non-Cit Officer id " << a.id
             << " time: " << a.time
             << " time of availability: " << a.time_of_availability_change
             << endl;
    }

    return 0;
}
