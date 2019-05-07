#include "pch.h"
#include "SerialThread.h"
#include "CSerialIO.h"

const unsigned short MAX_MESSAGE = 300;

SerialThread::SerialThread() :m_serialIO(NULL)
{

}
SerialThread::~SerialThread()
{
	m_serialIO = NULL;
}


BOOL SerialThread::InitInstance()
{
	return TRUE;
}

int SerialThread::Run()
{
	// Check signal controlling and status to open serial communication.
	while (1)
	{
		if (!m_serialIO)
			continue;

		while (m_serialIO->GetProcessActivateValue() == TRUE)
		{
			if ((serialCtrl().GetPortStatus() == FALSE) && m_serialIO->GetPortActivateValue() == TRUE)
			{
				if (serialCtrl().OpenPort(m_serialIO->m_DCB, (m_serialIO->m_strPortName).c_str()) == TRUE)
				{
					m_serialIO->OnEventOpen(TRUE);
				}
				else
				{
					m_serialIO->OnEventOpen(FALSE);
					m_serialIO->SetPortActivate(FALSE);
				}

			}
			else if (m_serialIO->GetPortActivateValue() == TRUE)
			{
				char message[MAX_MESSAGE] = { 0 };
				unsigned int lenBuff = MAX_MESSAGE;
				unsigned long lenMessage;
				if (serialCtrl().Read(message, lenBuff, lenMessage) == TRUE)
				{
					if (lenMessage > 0)
						m_serialIO->OnEventRead(message, lenMessage);
				}
				else
				{
					m_serialIO->SetProcessActivate(FALSE);
				}

			}

			if (m_serialIO->GetSendActivateValue() == TRUE)
			{
				unsigned long nWritten;
				if (serialCtrl().Write(m_serialIO->m_sendBuffer, m_serialIO->m_sendSize, nWritten) == TRUE)
				{
					m_serialIO->OnEventWrite(nWritten);
				}
				else
				{
					m_serialIO->OnEventWrite(-1);
				}
				m_serialIO->SetSendActivate(FALSE);
			}
			if (m_serialIO->m_bClosePort == TRUE)
			{
				if (serialCtrl().ClosePort() == TRUE)
				{
					m_serialIO->OnEventClose(TRUE);
				}
				else
				{
					m_serialIO->OnEventClose(FALSE);
				}
				m_serialIO->m_bClosePort = FALSE;

			}
		}

	}
	return 0;
}
void SerialThread::ClosePort()
{

	serialCtrl().ClosePort();

}