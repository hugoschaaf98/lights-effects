/* dev_connection.ino
 *
 *
 * Test the device connection 
 *
 *
 */
#include "devicecmd.h"

int8_t getCmd()
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
	Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop()
{
	int8_t cmd;

  digitalWrite(13, LOW);

	if(Serial.available())
	{
		cmd = getCmd();
   
  	switch(cmd)
  	{
  		case DCGETID :

        digitalWrite(13, HIGH);
        delay(500);
  			Serial.print("ID LC251hs ;");
        break;

      case DCDSCT :

        digitalWrite(13, HIGH);
        delay(500);
        Serial.print(String{DCDSCT}+';'); 
        break;
  
  		default:
        Serial.print("DCERR;");
  	}
	}

  Serial.flush();
}
