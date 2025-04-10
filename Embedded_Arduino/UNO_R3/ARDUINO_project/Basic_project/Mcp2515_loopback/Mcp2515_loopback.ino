/*******************************************************************************
* Include
*******************************************************************************/
#include <mcp_can.h>
#include <SPI.h>
/*******************************************************************************
* Define
*******************************************************************************/
unsigned long prevTX = 0;                                        /*Variable to store last execution time*/ 
const unsigned int invlTX = 1000;                                /*execute after 1 second*/

byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};  /*data to send*/

long unsigned int rxId;
unsigned char len;
unsigned char rxBuf[8];

// Serial Output String Buffer
char msgString[128];

// CAN0 INT and CS
MCP_CAN CAN0(10);                               // Set CS to pin 10

/*******************************************************************************
* Code
*******************************************************************************/
void setup()
{
  Serial.begin(9600);

  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK)
  {
    Serial.println("MCP2515 Initialized Successfully!");
  } else{
    Serial.println("Error Initializing MCP2515...");  
  }                 
}

void loop()
{
  CAN0.readMsgBuf(&rxId, &len, rxBuf);              
  if((rxId & 0x80000000) == 0x80000000)
  {
    sprintf(msgString, "Extended ID: 0x%.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
  } else{
    sprintf(msgString, "Standard ID: 0x%.3lX       DLC: %1d  Data:", rxId, len);
  }

  Serial.print(msgString);

  for(byte i = 0; i<len; i++)
  {
    sprintf(msgString, " 0x%.2X", rxBuf[i]);
    Serial.print(msgString);
  }
        
  Serial.println();
  
  if(millis() - prevTX >= invlTX)
  {
    prevTX = millis();
    byte status = CAN0.sendMsgBuf(0x118, 8, data);
    
    if(status == CAN_OK)
      Serial.println("Message Sent Successfully!");
    else
      Serial.println("Error Sending Message...");

  }
}

/*******************************************************************************
* EOF
*******************************************************************************/