#include "SIM900.h"
#include <SoftwareSerial.h>
//If not used, is better to exclude the HTTP library,
//for RAM saving.
//If your sketch reboots itself proprably you have finished,
//your memory available.
//#include "inetGSM.h"

//If you want to use the Arduino functions to manage SMS, uncomment the lines below.
#include "sms.h"
SMSGSM sms;

//Simple sketch to send and receive SMS.

int numdata;
boolean started=false;
char smsbuffer[160];
char n[20] = "09297895641";	//Replace with your cell number.

const int RX_pin = 2;
const int TX_pin = 3;
const int GSM_ON_pin = 7;

void setup()
{
  //Serial connection.
  Serial.begin(9600);
  Serial.println("GSM Shield testing.");

  //Configure Comm Port to select Hardware or Software serial
#ifdef _COMPORT_
  //gsm.SelectHardwareSerial(&Serial, GSM_ON_pin);
  gsm.SelectSoftwareSerial(RX_pin, TX_pin, GSM_ON_pin);
#endif

  //Configure baudrate.
  if (gsm.begin(9600)) 
  {
    Serial.println("\nstatus=READY");
    started=true;
  } else Serial.println("\nstatus=IDLE");

  if(started) 
  {
    //Enable this two lines if you want to send an SMS.
    if (sms.SendSMS(n, "Arduino SMS"))
      Serial.println("\nSMS sent OK");
  }
};

void loop()
{
  if(started) 
  {
    //Read if there are messages on SIM card and print them.
    /**  deprecated method
    if(gsm.readSMS(smsbuffer, 160, n, 20)) {
       Serial.println(n);
       Serial.println(smsbuffer);
    }
    **/
    //get 1st sms
    if (sms.GetSMS(1, n, 20, smsbuffer, 160))
    {
      Serial.println(n);
      Serial.println(smsbuffer);
      sms.DeleteSMS(1);
	  sms.SendSMS(n, smsbuffer);
    }
    delay(1000);
  }
};
