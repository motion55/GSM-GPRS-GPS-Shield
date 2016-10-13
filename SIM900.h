#ifndef SIMCOM900_H
#define SIMCOM900_H

#include <SoftwareSerial.h>
#include "GSM.h"


class SIMCOM900 : public virtual GSM {

private:
	int configandwait(char* pin);
	int setPIN(char *pin);
	int changeNSIPmode(char);

public:
	SIMCOM900() {};
	~SIMCOM900() {};
	static SIMCOM900& GetInstance()
	{	
		static SIMCOM900* s_instance;
		if (!s_instance) s_instance = new SIMCOM900;
		return *s_instance;
	}
	SIMCOM900(SIMCOM900 const&) = delete;
	void operator = (SIMCOM900 const&) = delete;

	int getCCI(char* cci);
	int getIMEI(char* imei);
	int sendSMS(const char* to, const char* msg);
	boolean readSMS(char* msg, int msglength, char* number, int nlength);
	boolean readCall(char* number, int nlength);
	boolean call(char* number, unsigned int milliseconds);
	char forceON();
	virtual int read(char* result, int resultlength);
	int readCellData(int &mcc, int &mnc, long &lac, long &cellid);
};

#define _SINGLETON_

#ifdef  _SINGLETON_
#define gsm (SIMCOM900::GetInstance())
#else
extern SIMCOM900 gsm;
#endif


#endif

