#include <iostream>
#include <cstdlib>
using namespace std;

bool *p; // Contains status (alive or dead of all processes, index is ID)
int initiatorID = -1;
int coordinatorID = -1;
int number;

void buildRing() {
    //Finds alive processes;
    int alive_processes[number], alive_count = 0;

    for(int i = 0; i < number; i++){
        if(p[i] == true){
            alive_processes[alive_count] = i;
            alive_count++;
        }
    }

    if ( alive_count == 0){
        cout << "No Processes Alive";
        coordinatorID = -1;
        initiatorID = -1;
    }

    else {

        //Randomly pick initiator from alive processes
        int initiator_index = rand()%alive_count;
        initiatorID = alive_processes[ initiator_index ];

        cout << "Initiator ID: " << initiatorID << endl;

        int i = 0;

        int current = initiator_index;

        // Prints the messages passed in the ring
        do {
        int next = (current + 1) % alive_count;
        cout << "Message from " << alive_processes[current] << " -> " << alive_processes[next] << endl;
        current = next;
        } while (alive_processes[current] != initiatorID);

        // Largest ID is coordinator
        coordinatorID = alive_processes[alive_count - 1];
        cout << "Coordinator ID: " << coordinatorID << endl;
    }
}

// Prints status of every process
void status() {
    cout << "\nNumber Of Processes: " << number << endl;
    for (int i = 0; i < number; i++) {
        cout << i << "->";
        if (p[i] == true)
            cout << "Alive";
        else
            cout << "Dead";
        if (i == initiatorID)
            cout << "  -> INITIATOR";
        if (i == coordinatorID)
            cout << "  -> COORDINATOR";
        cout << endl;
    }
}

void recoverProcess() {
    int ID;
    cout << "Enter ID of the process to recover\n";
    cin >> ID;
    if( p[ID] == false ){
        p[ID] = true;
        buildRing();
        status();
    }
    else 
        cout << "\nProcess Already Active\n";
  }

void crashProcess() {
    int ID;
    cout << "Enter ID of the process to crash\n";
    cin >> ID;
    if( p[ID] == true ){
        p[ID] = false;
        buildRing();
        status();
    }
    else 
        cout << "\nProcess Already Dead\n";
}


int main() {

    cout << "Enter the number of processes\n";
    cin >> number;
    p = new bool[number];

    for (int i = 0; i < number; i++) {
        p[i] = true;
    }

    buildRing();
    status();

    int choice, ID;
    while (true) {
        cout << "\nEnter Choice\n";
        cout << "1. Crash Process\n2. Recover Process\n3. Exit\n";
        cin >> choice;
        switch (choice) {
            case 1:
                crashProcess();
                break;
            case 2:
                recoverProcess();
                break;
            case 3:
                return 0;
            default:
                cout << "Wrong Choice";
        }
    }

    return 0;
}
