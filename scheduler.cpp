#include <iostream>
#include <cstdio>
#include <ctime>
#include <conio.h>
#include <vector>

using namespace std;

class Process {
public:
    int id;
    float turnaround;
    float waiting;
    float arrival;
    float burst;
    int priority;
    int tq;
    int fbratio;

    Process() {
        waiting = 0;
        turnaround = 0;
        arrival = 0;
        burst = 0;
        id = 0;
        tq = 5;
        fbratio = 0;
        priority = 0;
    }

    void display(Process* arr, int n) {
        cout << "\n\nID" << '\t' << "Arrival" << '\t' << '\t' << "Burst" << '\t' << '\t'
             << "Priority" << '\t' << "Waiting" << '\t' << '\t' << "TurnAround" << '\t' << "FBR";
        for (int i = 0; i < n; i++) {
            cout << "\n" << arr[i].id << '\t';
            cout << arr[i].arrival << '\t' << '\t';
            cout << arr[i].burst << '\t' << '\t';
            cout << arr[i].priority << '\t' << '\t';
            cout << arr[i].waiting << '\t' << '\t';
            cout << arr[i].turnaround << '\t' << '\t';
            cout << arr[i].fbratio << '\t' << '\t';
        }
    }

    void setburst() {
        cin >> this->burst;
    }

    void setarrival() {
        cin >> this->arrival;
    }

    void setID() {
        cin >> this->id;
    }

    float getarrival() {
        return arrival;
    }

    float getburst() {
        return burst;
    }

    void setpriority() {
        cin >> this->priority;
    }

    int getID() {
        return id;
    }

    void sortarrivaltime(Process arr[], int n) {
        int max = 0;
        int flag = 0;
        for (int i = 0; i < n - 1; i++) {
            max = i;
            flag = 0;
            for (int j = i + 1; j < n; j++) {
                if (arr[j].arrival < arr[max].arrival)
                    max = j;
                else if (arr[j].arrival == arr[max].arrival) {
                    if (arr[j].burst < arr[max].burst) {
                        max = j;
                        flag = 1;
                    }
                }
            }
            if (max != i) {
                if (flag == 1) {
                    swap(arr[max].burst, arr[i].burst);
                    swap(arr[max].arrival, arr[i].arrival);
                    swap(arr[max].id, arr[i].id);
                } else {
                    swap(arr[max].arrival, arr[i].arrival);
                    swap(arr[max].id, arr[i].id);
                }
            }
        }
    }

    void MLQ(Process array[], int n) {
        cout << "\n\nWelcome to Multi-Level Queue Scheduling: \n";
        sortarrivaltime(array, n);
        display(array, n);
        vector<Process> arr;
        vector<Process>::iterator it;

        for (int i = 0; i < n; i++) {
            arr.push_back(array[i]);
        }

        for (auto it = arr.begin(); it != arr.end(); ++it) {
            it->arrival *= CLOCKS_PER_SEC;
            it->burst *= CLOCKS_PER_SEC;
        }

        clock_t now = clock();

        for (int i = 0; i < n;) {
            while (clock() - now <= arr[i].arrival) {
                ;
            }
            cout << "\n\nProcess " << arr[i].id << " has arrived.";
            cout << "\nIt's Priority is: " << arr[i].priority;
            cout << "\nIt's Burst Time is: " << array[i].burst;

            if (arr[i].priority <= 3 && arr[i].priority > 0) {
                cout << "\nWelcome to Priority Scheduling: ";
                cout << "\nProcess " << arr[i].id << " is running.";
                clock_t now1 = clock();
                while (clock() - now1 <= arr[i].burst) {
                    ;
                }
                cout << "\nProcess " << arr[i].id << " is terminating.";
                cout << "\n******************************************************************\n";
                i++;
            } else if (arr[i].priority <= 6 && arr[i].priority > 3) {
                cout << "\nWelcome to Round Robin Scheduling: ";
                cout << "\nProcess " << arr[i].id << " is running.";
                clock_t now1 = clock();
                while (clock() - now1 <= arr[i].burst) {
                    ;
                }
                cout << "\nProcess " << arr[i].id << " is terminating.";
                cout << "\n******************************************************************\n";
                i++;
            } else if (arr[i].priority <= 9 && arr[i].priority > 6) {
                cout << "\nWelcome to SRJF Scheduling: ";
                cout << "\nProcess " << arr[i].id << " is running.";
                clock_t now1 = clock();
                while (clock() - now1 <= arr[i].burst) {
                    ;
                }
                cout << "\nProcess " << arr[i].id << " is terminating.";
                cout << "\n******************************************************************\n";
                i++;
            }
        }
    }

    void LongestJobFirst(Process array[], int n) {
        array->sortLJF(array, n);
        display(array, n);
        cout << "\n\nWelcome to the Longest Job First Algorithm\n";

        vector<Process> arr;
        vector<Process> ljf;
        vector<Process>::iterator it;

        for (int i = 0; i < n; i++) {
            arr.push_back(array[i]);
        }

        for (auto it = arr.begin(); it != arr.end(); ++it) {
            it->arrival *= CLOCKS_PER_SEC;
            it->burst *= CLOCKS_PER_SEC;
        }

        int i = 0;
        clock_t now = clock();

        for (int i = 0; i < n;) {
            while (clock() - now < arr[i].arrival) {
                ;
            }
            cout << "\nProcess " << arr[i].id << " has arrived.";
            cout << "\nIt's Burst Time is: " << array[i].burst;

            cout << "\n\nProcess " << arr[i].id << " is running.";
            clock_t now1 = clock();
            while (clock() - now1 <= arr[i].burst) {
                ;
            }
            cout << "\nProcess " << arr[i].id << " is terminating.";
            cout << "\n******************************************************************\n";
            i++;
        }
    }

    void sortLJF(Process arr[], int n) {
        int max = 0;
        int flag = 0;
        for (int i = 0; i < n - 1; i++) {
            max = i;
            flag = 0;
            for (int j = i + 1; j < n; j++) {
                if (arr[j].arrival < arr[max].arrival)
                    max = j;
                else if (arr[j].arrival == arr[max].arrival) {
                    if (arr[j].burst > arr[max].burst) {
                        max = j;
                        flag = 1;
                    }
                }
            }
            if (max != i) {
                if (flag == 1) {
                    swap(arr[max].burst, arr[i].burst);
                    swap(arr[max].arrival, arr[i].arrival);
                    swap(arr[max].id, arr[i].id);
                } else {
                    swap(arr[max].arrival, arr[i].arrival);
                    swap(arr[max].id, arr[i].id);
                }
            }
        }
    }

    void calctimes(Process array[], int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                if (i == 0) {
                    array[i].turnaround = array[i].burst;
                } else {
                    array[i].turnaround += array[j].burst;
                }
            }
            array[i].waiting = array[i].turnaround;
            array[i].turnaround = array[i].turnaround - array[i].arrival;
            array[i].fbratio = (array[i].waiting + array[i].burst) / array[i].burst;
        }
    }

    void sortFBR(Process arr[], int n) {
        int max = 0;
        int flag = 0;
        for (int i = 0; i < n - 1; i++) {
            max = i;
            flag = 0;
            for (int j = i + 1; j < n; j++) {
                if (arr[j].arrival < arr[max].arrival)
                    max = j;
                else if (arr[j].arrival == arr[max].arrival) {
                    if (arr[j].fbratio < arr[max].fbratio) {
                        max = j;
                        flag = 1;
                    }
                }
            }
            if (max != i) {
                if (flag == 1) {
                    swap(arr[max].fbratio, arr[i].fbratio);
                    swap(arr[max].arrival, arr[i].arrival);
                    swap(arr[max].id, arr[i].id);
                } else {
                    swap(arr[max].arrival, arr[i].arrival);
                    swap(arr[max].id, arr[i].id);
                }
            }
        }
    }
};

int main() {
    Process obj;
    Process* arr;
    int num;
    cout << "How many processes you want to enter: ";
    cin >> num;
    arr = new Process[num];
    for (int i = 0; i < num; i++) {
        cout << "\nEnter Process ID: ";
        arr[i].setID();
        cout << "Enter Arrival Time: ";
        arr[i].setarrival();
        cout << "Enter Burst Time: ";
        arr[i].setburst();
        cout << "Enter Priority: ";
        arr[i].setpriority();
    }

    obj.MLQ(arr, num);
    // obj.LongestJobFirst(arr, num);

    cout << "\n\nDo you want to run another scheduling algorithm (y/n): ";
    char choice;
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        obj.LongestJobFirst(arr, num);
    }

    delete[] arr;

    return 0;
}
