#include "pch.h"
#include "CSerialIO.h"
#include "SerialThread.h"


CSerialIO::CSerialIO() : m_strPortName("COM1"), m_strBaudRate("115200"), m_sendSize(0)
{
	m_serialProcess = new SerialThread();
	m_bProccessActivate = FALSE;
	m_bPortActivate = FALSE;
	m_bSendActivate = FALSE;
	m_bClosePort = FALSE;
	Init();
}

CSerialIO::CSerialIO(std::string strPrtName, std::string strBaudRate) : m_strPortName(strPrtName), m_strBaudRate(strBaudRate), m_sendSize(0)
{
	m_serialProcess = new SerialThread();
	m_bProccessActivate = FALSE;
	m_bPortActivate = FALSE;
	m_bSendActivate = FALSE;
	m_bClosePort = FALSE;
	Init();
	this->OpenPort(strPrtName, strBaudRate);
}

CSerialIO:: ~CSerialIO()
{
	if (m_serialProcess)
		delete m_serialProcess;

	m_run_thread.join();
	UnInit();
}
BOOL CSerialIO::Init()
{
 	m_serialProcess->setOwner(this);	
	m_run_thread = std::thread(&SerialThread::Run, m_serialProcess);

	m_DCB.ByteSize = 8;
	m_DCB.StopBits = ONESTOPBIT;
	m_DCB.Parity = NOPARITY;
	switch (atoi(m_strBaudRate.c_str()))
	{
	case 110:
		m_DCB.BaudRate = CBR_110;
		break;
	case 300:
		m_DCB.BaudRate = CBR_300;
		break;
	case 600:
		m_DCB.BaudRate = CBR_600;
		break;
	case 1200:
		m_DCB.BaudRate = CBR_1200;
		break;
	case 2400:
		m_DCB.BaudRate = CBR_2400;
		break;
	case 4800:
		m_DCB.BaudRate = CBR_4800;
		break;
	case 9600:
		m_DCB.BaudRate = CBR_9600;
		break;
	case 14400:
		m_DCB.BaudRate = CBR_14400;
		break;
	case 19200:
		m_DCB.BaudRate = CBR_19200;
		break;
	case 38400:
		m_DCB.BaudRate = CBR_38400;
		break;
	case 56000:
		m_DCB.BaudRate = CBR_56000;
		break;
	case 57600:
		m_DCB.BaudRate = CBR_57600;
		break;
	case 115200:
		m_DCB.BaudRate = CBR_115200;
		break;
	case 128000:
		m_DCB.BaudRate = CBR_128000;
		break;
	case 256000:
		m_DCB.BaudRate = CBR_256000;
		break;
	default:
		break;
	}
	m_bProccessActivate = TRUE;	
	return TRUE;

}
void CSerialIO::UnInit()
{
	m_bPortActivate = FALSE;
	if (m_serialProcess)
	{
		m_serialProcess->ClosePort();
		m_run_thread.~thread;
	}
}
void CSerialIO::OpenPort(std::string strPortName, std::string strBaudRate)
{
	m_strBaudRate = strBaudRate;
	m_strPortName = strPortName;
	m_bPortActivate = TRUE;

}
void CSerialIO::OnEventOpen(BOOL bSuccess)
{
	if (bSuccess)
		printf("port open successfully\n");
	else
		printf("port open failed\n");
}

void CSerialIO::ClosePort()
{
	m_bClosePort = TRUE;
	SetPortActivate(FALSE);
}
void CSerialIO::OnEventClose(BOOL bSuccess)
{
	if (bSuccess)
		printf("port close successfully\n");
	else
		printf("port close failed\n");

}
void CSerialIO::OnEventRead(char *inPacket, int inLength)
{
	strcpy_s(m_readingdata, inPacket);
	std::cout << "Receiving data is :" << m_readingdata << std::endl;

	return;
}

void CSerialIO::Write(char *outPacket, int outLength)
{
	if (outLength <= MAX_SEND_BUFFER)
	{
		memcpy(m_sendBuffer, outPacket, outLength);
		m_sendSize = outLength;
		SetSendActivate(TRUE);

	}
	else
	{
		printf("buffer over flow");
		OnEventWrite(-1);
	}
	return;
}

void CSerialIO::OnEventWrite(int nWritten)
{
	if (nWritten < 0)
	{
		printf("write error\n");
	}
	else
	{
		printf("%d bytes send\n", nWritten);
	}
}

BOOL CSerialIO::GetSendActivateValue(void)
{
	return m_bSendActivate;
}

void CSerialIO::SetSendActivate(BOOL bSendActivate)
{
	m_bSendActivate = bSendActivate;
}

BOOL CSerialIO::GetPortActivateValue(void)
{
	return m_bPortActivate;
}

void CSerialIO::SetPortActivate(BOOL bPortActivate)
{
	m_bPortActivate = bPortActivate;
}

BOOL CSerialIO::GetProcessActivateValue(void)
{
	//TODO: bakilacak
	return m_bProccessActivate = TRUE;
}

void CSerialIO::SetProcessActivate(BOOL bProcessActivate)
{
	m_bProccessActivate = bProcessActivate;
}
