/* dev_connection.ino
 *
 *
 * Test the device connection 
 * 
 * ***WARNING***  
 * changing the serial port settings from 
 * the computer side causes the arduino
 * to reset. Place a 10µF condo between
 * to avoid this.
 * *************
 *
 * SCHAAF Hugo 27/02/2019                 
 */
#include "devicecmd.h"

#define BLUELED   4
#define REDLED    5
#define GREENLED  6

static int8_t getCmd()
{	
	char buf[CMDMAXSIZE] = "";
  char* tmp = buf;
  
	int8_t cmd = DCERR;
	// retreive characters until ';' is encountered
  do
  {
    while(!Serial.available())
    {;;}
    *tmp = Serial.read();
  }while(*tmp++ != ';' && tmp-buf < CMDMAXSIZE);

	sscanf(buf,"CMD %d ;", &cmd);

	return cmd;
}

//---------------------------------------------------------------//
// main 
//

void setup()
{
  pinMode(BLUELED, OUTPUT);
  pinMode(REDLED, OUTPUT);
  pinMode(GREENLED, OUTPUT);

  digitalWrite(BLUELED, HIGH);
  delay(1000);
  digitalWrite(BLUELED, LOW);

  Serial.begin(9600);
}


void loop()
{
	int8_t cmd;

	if(Serial.available())
	{
		cmd = getCmd();
   
  	switch(cmd)
  	{
  		case DCGETID :

  			Serial.print("ID LC251hs ;");

        digitalWrite(BLUELED, HIGH);
        delay(500);
        digitalWrite(BLUELED, LOW);
        break;

      case DCCNCT :

        Serial.print(String{DCCNCT}+';'); 
        digitalWrite(REDLED, LOW);
        digitalWrite(GREENLED, HIGH);
        break;


      case DCDSCT :

        Serial.print(String{DCDSCT}+';'); 
        digitalWrite(REDLED, HIGH);
        digitalWrite(GREENLED, LOW);
        break;
  
  		default:
        Serial.print("DCERR;");
  	}

	}
  Serial.flush();
}
