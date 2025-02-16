#include <iostream>
#include <math.h>
#include <chrono>
#include <thread>
#include <memory>
#include <vector>

using namespace std;

// Интерфейс команды
class Command {
public:
    virtual void execute() = 0;
};

// Команда для открытия двери
class OpenDoorCommand : public Command {
private:
    Door& door;

public:
    OpenDoorCommand(Door& d) : door(d) {}

    void execute() override {
        door.move();
    }
};

// Команда для закрытия двери
class CloseDoorCommand : public Command {
private:
    Door& door;

public:
    CloseDoorCommand(Door& d) : door(d) {}

    void execute() override {
        door.move();
    }
};

// Команда для перемещения лифта
class MoveElevatorCommand : public Command {
private:
    Elevator& elevator;
    int targetFloor;

public:
    MoveElevatorCommand(Elevator& e, int floor) : elevator(e), targetFloor(floor) {}

    void execute() override {
        elevator.move(targetFloor);
    }
};

class Door {
private:
    bool isOpen;

public:
    Door() : isOpen(false) {}

    void move() {
        int doorPosition = isOpen ? 100 : 0;
        int step = isOpen ? -1 : 1;

        while ((isOpen && doorPosition > 0) || (!isOpen && doorPosition < 100)) {
            doorPosition += step;
            this_thread::sleep_for(chrono::milliseconds(40));
        }

        isOpen = !isOpen;
        cout << (isOpen ? "Двери лифта открылись" : "Двери лифта закрылись") << endl;
    }

    bool isDoorOpen() const {
        return isOpen;
    }
};

class Elevator {
private:
    double diameterOfTheWhinchDrum;
    double floorHeight;
    int currentFloor;
    int totalFloors;

public:
    Elevator(double diameter, double height, int floors, int startFloor)
        : diameterOfTheWhinchDrum(diameter), floorHeight(height), totalFloors(floors), currentFloor(startFloor) {}

    int move(int targetFloor) {
        double degreeNeedFor1Floor = (floorHeight / (M_PI * diameterOfTheWhinchDrum)) * 360;
        double degreeNeed = degreeNeedFor1Floor * (targetFloor - currentFloor);
        double curDeg = 0;
        int timeood = 1160000;

        if (targetFloor > currentFloor) {
            for (int i = currentFloor; i < targetFloor; i++) {
                curDeg += degreeNeedFor1Floor;
                this_thread::sleep_for(chrono::nanoseconds(timeood));
                cout << "Лифт сейчас на " << ++currentFloor << " этаже." << endl;
            }
        } else {
            for (int i = currentFloor; i > targetFloor; i--) {
                curDeg -= degreeNeedFor1Floor;
                this_thread::sleep_for(chrono::nanoseconds(timeood));
                cout << "Лифт сейчас на " << --currentFloor << " этаже." << endl;
            }
        }
        return currentFloor;
    }

    int getCurrentFloor() const {
        return currentFloor;
    }

    void setTotalFloors(int floors) {
        totalFloors = floors;
    }

    void setDiameter(double diameter) {
        diameterOfTheWhinchDrum = diameter;
    }

    void setFloorHeight(double height) {
        floorHeight = height;
    }
};

class ElevatorSettings {
private:
    int totalFloors;
    int currentFloor;
    int elevatorFloor;
    double diameterOfTheWhinchDrum;
    double floorHeight;

public:
    ElevatorSettings() : totalFloors(15), currentFloor(1), elevatorFloor(1), diameterOfTheWhinchDrum(0.2), floorHeight(3.0) {}

    void configureSettings() {
        char wcs = 'o';
        cout << "Хотите ли вы внести изменения в настройки?" << endl;
        while (wcs != 'N' && wcs != 'n' && wcs != 'Y' && wcs != 'y') {
            cout << "(Y или y - Да, N или n - Нет)" << endl;
            cin >> wcs;
        }
        if (wcs == 'Y' || wcs == 'y') {
            cout << "Сколько этажей в доме? (15 по стандарту)" << endl;
            while (
