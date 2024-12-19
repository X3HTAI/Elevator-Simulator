#include <iostream>
#include <math.h>
#include <chrono>
#include <thread>

using namespace std;

double diameterOfTheWhinchDrum = 0.2, floorHeight = 3.0;

bool door_move(bool isDoorOpen)
{
	int doorPosition;
	if(isDoorOpen == false)
	{
		doorPosition = 100;
		while(doorPosition > 0)
		{
			doorPosition -= 1;
			this_thread::sleep_for(chrono::milliseconds(40));
		}
		cout << "Двери лифта открылись" << endl;
		isDoorOpen = true;
	}
	else
	{
		doorPosition = 0;
		while(doorPosition < 100)
		{
			doorPosition += 1;
			this_thread::sleep_for(chrono::milliseconds(40));
		}
		cout << "Двери лифта закрылись" << endl;
		isDoorOpen = false;
	}
	return isDoorOpen;
}

//int winch_drum(int timeood, int eof)
//{
	
	//return eof;
//}

int elevator_move(int eof, int nofb)
{
	double degreeNeedFor1Floor = (floorHeight / (M_PI * diameterOfTheWhinchDrum)) * 360;
	double degreeNeed = degreeNeedFor1Floor * nofb;
	double curDeg = 0;
	int idnf1f = degreeNeedFor1Floor;
	
	double dtnf = degreeNeedFor1Floor;
	
	int timeood = 1160000;
	
	if(nofb > 0)
	{
		if(idnf1f != degreeNeedFor1Floor)
		{
			double fod = degreeNeedFor1Floor - idnf1f;
			timeood *= fod;
			for(int i = 0; i < nofb; i ++)
			{
				curDeg += fod;
				if(curDeg >= dtnf)
				{
					eof += 1;
					cout << "Лифт сейчас на " << eof << " этаже." << endl;
					dtnf += degreeNeedFor1Floor;
				}
				this_thread::sleep_for(chrono::nanoseconds(timeood));
			}
		}
		timeood = 1160000;
		while(curDeg != degreeNeed)
		{
			curDeg += 1;
			if(curDeg >= dtnf)
			{
				eof += 1;
				cout << "Лифт сейчас на " << eof << " этаже." << endl;
				dtnf += degreeNeedFor1Floor;
			}
			this_thread::sleep_for(chrono::nanoseconds(timeood));
		}
	}
	else
	{
		if(idnf1f != degreeNeedFor1Floor)
		{
			double fod = degreeNeedFor1Floor - idnf1f;
			timeood *= fod;
			for(int i = 0; i > nofb; i --)
			{
				curDeg -= fod;
				if(abs(curDeg) >= dtnf)
				{
					eof -= 1;
					cout << "Лифт сейчас на " << eof << " этаже." << endl;
					dtnf += degreeNeedFor1Floor;
				}
				this_thread::sleep_for(chrono::nanoseconds(timeood));
			}
		}
		timeood = 1160000;
		while(curDeg != degreeNeed)
		{
			curDeg -= 1;
			if(abs(curDeg) >= dtnf)
			{
				eof -= 1;
				cout << "Лифт сейчас на " << eof << " этаже." << endl;
				dtnf += degreeNeedFor1Floor;
			}
			this_thread::sleep_for(chrono::nanoseconds(timeood));
		}
	}
	return eof;
}

int elevator_interface(int nof, int eof)
{
	int selectedFloor = 0;
	cout << "В доме " << nof << " этажей. На какой этаж вы хотите попасть?" << endl;
	while(selectedFloor < 1 || selectedFloor > nof)
	{
		cin >> selectedFloor;
		if (selectedFloor < 1 || selectedFloor > nof) cout << "В этом доме нет такого этажа." << endl;
	}
	
	if(selectedFloor == eof)
	{
		cout << "Удевительно, но вы уже на этом этаже!" << endl;
		return eof;
	}
	
	eof = elevator_move(eof, selectedFloor - eof);
	
	return eof;
}

int main()
{
    cout << "Симулятор лифта" << endl;
    
    bool isDoorOpen = false;
    char wue = 'y';
    int cf = 1, nof = 15, eof = 1;
	char wcs = 'o';
    
    cout << "Хотите ли вы внести изменения в настройки?" << endl;
    while(wcs != 'N' && wcs != 'n' && wcs != 'Y' && wcs != 'y')
    {
		cout << "(Y или y - Да, N или n - Нет)" << endl;
		cin >> wcs;
	}
    if (wcs == 'Y' || wcs == 'y')
    {
		char wces = 'o';
		nof = 0;
		cf = 0;
		eof = 0;
		cout << "Сколько этажей в доме? (15 по стандарту)" << endl;
		while(nof < 2)
		{
			cout << "(Не меньше 2)" << endl << "Этажей: ";
			cin >> nof;
		}
		cout << "На каком этаже вы сейчас? (1 по стандарту)" << endl;
		while(cf < 1 || cf > nof)
		{
			cout << "(Не меньше 1 и не больше кол-ва этажей)" << endl << "Этаж: ";
			cin >> cf;
		}
		cout << "На каком этаже лифт сейчас? (1 по стандарту)" << endl;
		while(eof < 1 || cf > eof)
		{
			cout << "(Не меньше 1 и не больше кол-ва этажей)" << endl << "Этаж: ";
			cin >> eof;
		}
		cout << "Хотите ли вы внести изменения в настройки лифта?" << endl;
		while(wces != 'N' && wces != 'n' && wces != 'Y' && wces != 'y')
		{
			cout << "(Y или y - Да, N или n - Нет)" << endl;
			cin >> wces;
		}
		if (wces == 'Y' || wces == 'y')
		{
			diameterOfTheWhinchDrum = 0;
			floorHeight = 0;
			cout << "Какой диаметр у барабана лебедки лифта в метрах? (0.2 метра по стандарту)" << endl;
			while(diameterOfTheWhinchDrum <= 0)
			{
				cout << "(Не меньше или равно 0)" << endl << "Диаметр в метрах: ";
				cin >> diameterOfTheWhinchDrum;
			}
			cout << "Какая высота у этажей в метрах? (3 метра по стандарту)" << endl;
			while(floorHeight < 2.5)
			{
				cout << "(Не меньше 2.5)" << endl << "Выстоа в метрах: ";
				cin >> floorHeight;
			}
		}
	}
	
	cout << "Вы на " << cf << " этаже;" << endl << "Лифт на " << eof << " этаже" << endl;
	cout << "Нажмите Enter, чтобы вызвать лифт." << endl;
	getchar();
	
	if(cf != eof) eof = elevator_move(nof, cf - eof);
	
	isDoorOpen = door_move(isDoorOpen);
	
	cout << "Вы вошли в лифт." << endl;
	
	while(wue == 'y' || wue == 'Y')
	{
		isDoorOpen = door_move(isDoorOpen);
		
		cf = elevator_interface(nof, eof);
		eof = cf;
		
		isDoorOpen = door_move(isDoorOpen);
		
		wue = 'o';
		cout << "Хотите использовать лифт снова?" << endl;
		while(wue != 'N' && wue != 'n' && wue != 'Y' && wue != 'y')
		{
			cout << "(Y или y - Да, N или n - Нет)" << endl;
			cin >> wue;
		}
	}
	
	cout << "Вы вышли из лифта." << endl;
	
	return 0;
}
