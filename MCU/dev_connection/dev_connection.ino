/* dev_connection.ino
 *
 *
 * Test the device connection 
 *
 *
 */
#include "devicecmd.h"

#define LED 13

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
	Serial.begin(9600);
  pinMode(LED, OUTPUT);

  // mark a pause before continuing
  Serial.flush();
  Serial.write("Init from LC251hs");
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
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

        digitalWrite(LED, HIGH);
        delay(1000);
  			Serial.print("ID LC251hs ;");
        break;

      case DCDSCT :

        digitalWrite(LED, HIGH);
        delay(1000);
        Serial.print(String{DCDSCT}+';'); 
        break;
  
  		default:
        Serial.print("DCERR;");
  	}

    digitalWrite(LED, LOW);

	}

  Serial.flush();
}
