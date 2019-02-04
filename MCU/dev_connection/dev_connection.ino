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
    Serial.print(*tmp);
  }while(*tmp++ != ';' && tmp-buf < CMDMAXSIZE);

	scanf(buf,"CMD %d ;", &cmd);

	return cmd;
}

//---------------------------------------------------------------//
// main 
//

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	int8_t cmd = DCERR;

	if(Serial.available())
	{
    Serial.println(Serial.available());
		cmd = getCmd();

    Serial.println("\ncmd : "+String{cmd});
   
  	switch(cmd)
  	{
  		case DCGETID :
  
  			Serial.print("ID LC251hs ;");
  
  		default:
        Serial.println("DCERR");
  	}
	}
  Serial.flush();
}
