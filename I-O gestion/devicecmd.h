/* devicecmd.h
 *
 * A couple of macros definition
 * to communicate with a 
 * lights controller device
 *
 * message syntax : ANSWER_TYPE CONTENT ;
 * 
 * SCHAAF Hugo
 * 29/01/2019
 */

#ifndef DEVICECMD
#define DEVICECMD 1

// limits
#define CMDMAXSIZE 50
#define MSGMAXSIZE 50
#define MAXNAME 20
#define MAXPATH 20

// commands
#define DCERR	0x00
#define DCGETID 0x01 // get the device identifier
#define DCCNCT	0x02 // device connected
#define DCDSCT	0x03 // device disconnected

#endif