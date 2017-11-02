#include<Windows.h>
#include<iostream>
#include<fstream>
using namespace std;

DWORD WINAPI myFirstThreadStartFunction(__in LPVOID lpParameter);
DWORD WINAPI mySecondThreadStartFunction(void *);
unsigned int myTempConter = 0xFFFFFFFF;
fstream file;
int main()
{
	
	file.open("Temp2.txt", ios::app | ios::out);
	unsigned int counter = 0;
	DWORD myThreadID;
	HANDLE myThread = CreateThread(0, 0, myFirstThreadStartFunction, &counter, 0, &myThreadID);
	CreateThread(0, 0, mySecondThreadStartFunction, NULL, 0, &myThreadID);
	char myChar = ' ';
	while (myChar != 'q')
	{

		cout << counter <<endl;
		//file << counter << endl;
		myChar = getchar();
		//file << "Decrementing Counter is" << myTempConter<<endl; 
		cout << " Decrementing Counter is" << myTempConter << endl;
	}
	CloseHandle(myThread);
	file.close();
	return 0;
}

DWORD WINAPI myFirstThreadStartFunction(__in LPVOID lpParameter)
{
	unsigned int& myCounter = *((unsigned int*)lpParameter);
	CRITICAL_SECTION critical;
	while (myCounter < 0xFFFFFFFF)
	{
		if (myCounter % 1546607 == 0)
		{
			//InitializeCriticalSection(&critical);
			file <<" Incrementing Counter is"<< myCounter << endl;
			//LeaveCriticalSection(&critical);
		}
		myCounter++;
	}
	return 0;
}


DWORD WINAPI mySecondThreadStartFunction(void *)
{
	//unsigned int myTempConter = 0xFFFFFFFF;
	CRITICAL_SECTION critical;
	while (myTempConter > 1)
	{
		if (myTempConter % 1546607 == 0)
		{
			//InitializeCriticalSection(&critical);
			file << " Decrementing Counter is" << myTempConter << endl;
			//LeaveCriticalSection(&critical);
		}
		myTempConter--;
	}
	return 0;
}
