#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

enum Actions { TURN_LED_ON, TURN_LED_OFF, NOTHING };
enum Status { DARK, NOT_DARK };
enum Location { ROOM };

class Environment {
private:
    int envLocation[1];

public:
    Environment() {
        srand(time(0)); // Seed the random number generator
    }

    void setEnv() {
        cout << "--- Environment settings ---\n";
        int ran = rand() % 10; // Assuming the sensor perceived data in the range of 0-9
        if (ran < 5) {
            envLocation[ROOM] = DARK;
        } else {
            envLocation[ROOM] = NOT_DARK;
        }
    }

    int getStatusOfCurrentLoc(int location) {
        return envLocation[location];
    }

    void setStatusOfCurrentLoc(int location, int status) {
        envLocation[location] = status;
    }

    void printStatus(int agentLocation) {
        cout << "--- Environment status ---\n";
        if (getStatusOfCurrentLoc(ROOM) == DARK) {
            cout << "The room is dark.\n";
        } else {
            cout << "The room is not dark.\n";
        }
    }
};

class Agent {
public:
    int LEDAction(int location, int status) {
        if (status == DARK) {
            return TURN_LED_ON;
        } else if (status == NOT_DARK) {
            return TURN_LED_OFF;
        } else {
            return NOTHING;
        }
    }
};

int main() {
    Environment myRoom;
    int agentAction;
    int loc = ROOM;
    Agent agent;

    for (int i = 0; i < 10; i++) {
        myRoom.printStatus(loc);
        if (myRoom.getStatusOfCurrentLoc(loc) == NOT_DARK) {
            agentAction = NOTHING;
            cout << "Next action: " << agentAction << " (The room is already bright!)\n";
            myRoom.setEnv();
        } else {
            agentAction = agent.LEDAction(loc, myRoom.getStatusOfCurrentLoc(loc));
            if (agentAction == TURN_LED_ON) {
                cout << "Next action: TURN_LED_ON (Turning lights on)\n";
            } else if (agentAction == TURN_LED_OFF) {
                cout << "Next action: TURN_LED_OFF (Turning lights off)\n";
            }
            myRoom.setStatusOfCurrentLoc(loc, DARK);
        }
    }

    return 0;
}
