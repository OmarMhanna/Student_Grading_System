#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <utility>
using namespace std;

vector<pair<string, double>> Data;

string Name;
int Grade;

ifstream Input("Input.txt");

bool N_S_Sort(pair<string, double> P1, pair<string, double> P2) {

    if (P1.second == P2.second) {

        return P1.first < P2.first;
    }

    return P1.second > P2.second;
}

bool Found(pair<string, double> P1) {

    return P1.first == Name;
}

void P1() {

    cout << "\n How many students would you like to add?\n Number of students: \n ";

    int N = 0;

    Input >> N;

    if (!N) {

        cout << "\n No students were added to the system\n ";

        return;
    }

    for (int i = 1; i <= N; i++) {

        cout << "\n Please enter the full name of student " << i << "\n ";

        Input.ignore();
        getline(Input, Name);

        auto it = find_if(Data.begin(), Data.end(), Found);

        if (it != Data.end()) {

            cout << "\n Student " << i << " is already assigned! Did you mean to modify this student's grade?\n ";

            Data.shrink_to_fit();

            return;
        }
        else {

            cout << "\n Please enter a valid grade from 0 to 1500 for student " << i << "\n ";

            Input >> Grade;

            if (Grade >= 0 && Grade <= 1500) {

                Data.push_back({ Name, Grade });

                cout << "\n Student " << i << " was successfully added to the system\n ";
            }
            else {

                for (int j = 1; j <= 3; j++) {

                    cout << "\n Invalid range! Try again (" << 4 - j << " tries left)\n ";
                    cout << "Please re-enter a valid grade from 0 to 1500\n ";
                    
                    Input >> Grade;

                    if (Grade >= 0 && Grade <= 1500) {

                        Data.push_back({ Name, Grade });

                        cout << "\n Student " << i << " was successfully added to the system\n ";

                        break;
                    }

                    if (j == 3) {

                        cout << "\n Invalid range!\n Student " << i << " was not added to the system\n ";

                        Data.shrink_to_fit();

                        return;
                    }
                }
            }
        }
    }

    cout << "\n All " << N << " students were successfully added to the system\n ";

    Data.shrink_to_fit();

    return;
}

void P2() {

    cout << "\n Please enter the full name of the student\n ";

    Input.ignore();
    getline(Input, Name);

    auto it = find_if(Data.begin(), Data.end(), Found);

    if (it != Data.end()) {

        int X = 0;

        cout << "\n 1. Modify name\n 2. Modify grade\n\n Please enter your choice: \n ";

        Input >> X;

        if (X == 1) {

            for (auto &itr : Data) {

                if (itr.first == Name) {

                    cout << "\n Please enter the new full name of the student\n ";

                    Input.ignore();
                    getline(Input, Name);

                    auto it = find_if(Data.begin(), Data.end(), Found);

                    if (it != Data.end()) {

                        cout << "\n This name already exists in the system! Did you mean to modify this student's grade?\n ";

                        return;
                    }
                    else {

                        itr.first = Name;

                        cout << "\n The name of the student was successfully modified\n ";

                        return;
                    }
                }
            }
        }
        else if (X == 2) {

            for (auto& itr : Data) {

                if (itr.first == Name) {

                    cout << "\n Please enter a new valid grade from 0 to 1500 for the student\n ";

                    Input >> Grade;

                    if (Grade >= 0 && Grade <= 1500) {

                        itr.second = Grade;

                        cout << "\n The grade of the student was successfully modified\n ";

                        return;
                    }
                    else {

                        for (int j = 1; j <= 3; j++) {

                            cout << "\n Invalid range! Try again (" << 4 - j << " tries left)\n ";
                            cout << "Please re-enter a valid grade from 0 to 1500\n ";

                            Input >> Grade;

                            if (Grade >= 0 && Grade <= 1500) {

                                itr.second = Grade;

                                cout << "\n The grade of the student was successfully modified\n ";

                                return;
                            }

                            if (j == 3) {

                                cout << "\n Invalid range!\n The grade of the student was not modified\n ";

                                return;
                            }
                        }
                    }
                }
            }
        }
        else {

            cout << "\n Invalid input!\n Please choose \'1\' or \'2\'\n ";
        }
    }
    else {

        cout << "\n Student is not assigned! Did you mean to add this student?\n ";
    }
}

void P3() {

    cout << "\n Please enter the full name of the student\n ";

    Input.ignore();
    getline(Input, Name);

    auto it = find_if(Data.begin(), Data.end(), Found);

    if (it != Data.end()) {

        for (auto& itr : Data) {

            if (itr.first == Name) {

                itr.second = 0;

                cout << "\n The grade of the student was successfully reset to 0\n ";

                return;
            }
        }
    }
    else {

        cout << "\n Student is not assigned! Did you mean to add this student?\n ";
    }
}

void P4() {

    cout << "\n Please enter the full name of the student\n ";

    Input.ignore();
    getline(Input, Name);

    auto it = find_if(Data.begin(), Data.end(), Found);

    if (it != Data.end()) {

        for (auto& itr : Data) {

            if (itr.first == Name) {

                cout << "\n The grade of " << itr.first <<" : " << itr.second << "\n ";

                return;
            }
        }
    }
    else {

        cout << "\n Student is not assigned! Did you mean to add this student?\n ";
    }
}

void P5() {

    if (Data.empty()) {

        cout << "\n No data to show!\n ";
    }
    else {

        sort(Data.begin(), Data.end(), N_S_Sort);

        cout << "\n Names and grades of all students:- \n ";

        for (auto it : Data) {

            cout << "\n " << it.first << " : " << it.second;
        }

        cout << "\n ";
    }
}

int main()
{

    while (1) {

        int Process = 6;

        cout << "\n 1. Add students to the system\n 2. Modify a name or a grade\n 3. Reset a grade\n 4. Get a student's grade\n 5. Get all grades\n 6. Close\n\n Please enter your choice: \n ";

        Input >> Process;

        if (Process == 1) {
            
            P1();
        }
        else if (Process == 2) {

            P2();
        }
        else if (Process == 3) {

            P3();
        }
        else if (Process == 4) {

            P4();
        }
        else if (Process == 5) {

            P5();
        }
        else if (Process == 6) {

            cout << "\n Thank you for using the program!\n ";

            return 0;
        }
        else {

            cout << "\n Invalid input!\n Please choose a number from \'1\' to \'6\'\n ";
        }
    }
}