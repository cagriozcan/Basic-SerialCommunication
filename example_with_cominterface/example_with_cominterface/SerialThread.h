#pragma once

#include "pch.h"
#include "SerialCtrl.h"

class CSerialIO;

 class SerialThread 
{
public:			//bence Encapsulation gerekli

	SerialThread();               // Constructor.
	virtual ~SerialThread();       // Destructor.

	void ClosePort();
	virtual BOOL InitInstance();   // virtual function that derive from base-class.
	virtual int Run();             // virtual function that derive from base-class.  
	void setOwner(CSerialIO* serialIO)
	{
		m_serialIO = serialIO;
	}

	static SerialCtrl& serialCtrl() // Implement as the singleton funciton.
	{
		static SerialCtrl serial;
		return serial;
	}
private:
	CSerialIO*  m_serialIO;         // The pointer that pointer to object user data, such dialog,window

};