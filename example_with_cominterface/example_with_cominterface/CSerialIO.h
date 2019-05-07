#pragma once
#include "SerialThread.h"
#include <string>
#include <thread>

#define MAX_SEND_BUFFER 1024

class CSerialIO : public SerialThread
{

public:
	CSerialIO();
	virtual ~CSerialIO();

	BOOL Init();
	void OpenPort(std::string strPortName, std::string strBaudRate);//open serial port with parameter name and baud rate
	virtual void OnEventOpen(BOOL bSuccess);// handle the event whether the port is successfully opened 
	void ClosePort();//close serial port
	virtual void OnEventClose(BOOL bSuccess);//handle the event whether the port is successfully closed
	virtual void OnEventRead(char *inPacket, int inLength);// handle the received data from serial
	void Write(char *outPacket, int outLength);// write data directly 
	virtual void OnEventWrite(int nWritten); //return how many bytes has been written

	BOOL GetSendActivateValue(void);
	void SetSendActivate(BOOL bSendActivate);
	BOOL GetPortActivateValue(void);
	void SetPortActivate(BOOL bPortActivate);
	BOOL GetProcessActivateValue(void);
	void SetProcessActivate(BOOL bProcessActivate);

	DCB m_DCB;
	char m_sendBuffer[MAX_SEND_BUFFER];
	unsigned int m_sendSize;
	std::string	m_strPortName;
	BOOL m_bClosePort;
	std::thread thRun;

private:
	std::thread m_run_thread;
	void UnInit();
	SerialThread* m_serialProcess;
	BOOL m_bProccessActivate;
	BOOL m_bPortActivate;
	BOOL m_bSendActivate;
	std::string	m_strBaudRate;
};