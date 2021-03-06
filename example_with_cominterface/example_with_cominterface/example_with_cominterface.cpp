// example_with_cominterface.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "SerialCtrl.h"
#include "CSerialIO.h"
#include "SerialThread.h"

#include <iostream>

int main()
{

	std::string comname, baudrate;
	std::string send_message;

	std::cout << "Please enter SerialPort Name : !\n";
	std::cin >> comname;

	std::cout << "Please enter BaudRate : !\n";
	std::cin >> baudrate;

	std::cout << "Please enter Message: !\n";
	std::cin >> send_message;

	unsigned long length;

	length = send_message.size();
	
	CSerialIO *serialIO = new CSerialIO();
	serialIO->OpenPort(comname, baudrate);

	while (1) 
	{
	serialIO->Write(const_cast<char*>(send_message.c_str()), send_message.size());
	}

	serialIO->ClosePort();

	getchar();

}


