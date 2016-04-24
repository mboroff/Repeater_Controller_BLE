/***********************************
 *  general functions 
***********************************/

/******************************
 * get_UV3buff
 */
byte get_UV3buff(){
  
//  for (int i= 0; i < 32; i++) {       // clear UV3buff
//       UV3buff[i] = txtNull;
 // }
  byte k = 0;
  long T = millis() + 100;
  char c = 0;
 if (currentDevice == 0) {  
  while ((millis() < T) && (c != '\r')){   // while data in the serial bufffer
    if(Serial3.available()){
      c = Serial3.read();                  // read a character
      UV3buff[k++] = c;
      if (c == '\r') UV3buff[--k] = 0;
    }
  }
 } else {
  while ((millis() < T) && (c != '\r')){   // while data in the serial buffer
    if(Serial2.available()){            
      c = Serial2.read();                 // read a character
      UV3buff[k++] = c;
      if (c == '\r') UV3buff[--k] = 0;
    }
  }
 }

  if (c == 13){
    return 1;
  }
  return 0;
}

/*************************
 * BEEP
 */

void beep()
{
     tone(BUZZER, 700, 100);
}



/*******************************************
 *      get config info from current device
********************************************/

void getConfiginfo()
{
#ifdef DEBUG
   Serial.println(F("Get config"));
#endif  
//                     getSquelchlevel();
  getCTCSS();
  getTonemode();
  getradioTemp();
  getVolume();
}

void getradioTemp()
{
#ifdef DEBUG
  Serial.println(F("Get radio temp"));
#endif  

 memcpy(UV3buff, txtSpace20, 20);
  sendReadcmd("TP?\r");
/*
 if (currentDevice == 0) {
     Serial3.write('\r');
     Serial3.print("TP\r");
     
 } else {
     Serial2.write('\r');
     Serial2.print("TP\r");
 
 }
  */
  delay200();
  get_UV3buff();
  memcpy(iPhoneBuffer, txtRadioTemp, 7);
  for (int i = 0; i < 3; i++) {
       if (UV3buff[i + 6] == 0x00) {
           UV3buff[i + 6] = '0';
       }
       radioTemp[i] = UV3buff[6 + i];
       iPhoneBuffer[i + 6] = UV3buff[6 + i]; 
       iPhoneBuffer[i + 7] = '\0';
       }  
  if (iPhoneBuffer[8] == '0') {
      iPhoneBuffer[8] = 'C';  
  }
    
  sendDataToIphone();

}

/********************************
 * Flush buffers
*********************************/

void flushBuffers()
{
  Serial3.flush();
  Serial2.flush();
  delay200();
}

/***************************
 *   Send a query to RS-UV3
 */
void sendReadcmd(char* cmd)
{
#ifdef DEBUG
Serial.print(F("sendReadcmd ")); Serial.println(cmd);
Serial.print(F("currentDevice = ")); Serial.println(currentDevice);  
#endif
  flushBuffers();
  if (currentDevice == 0) {
      Serial3.write('\r');
      Serial3.flush();
      Serial3.print(cmd);
      delay200();
#ifdef DEBUG      
Serial.print(F("sendReadcmd ")); Serial.println(cmd);
#endif
      } else {
              Serial2.write('\r');
              Serial2.flush();
              Serial2.print(cmd);
              delay200();
              }
}

/************************
 *  Send a data store to RS-UV3
 */

 void sendStorecmd(char* cmd, char* data)
{
#ifdef DEBUG  
  Serial.print(F("cmd = ")); Serial.println(cmd);
  Serial.print(F("data = ")); Serial.println(data);
#endif 
 flushBuffers();
 if (currentDevice == 0) {
     Serial3.write('\r');
     Serial3.flush();
     Serial3.print(cmd);
     Serial3.write(data);
     Serial3.write('\r');
     delay200();
     Serial3.print("ST0");
     Serial3.write('\r');
     delay200();
     } else { 
             Serial2.write('\r');
             Serial2.flush();
             Serial2.print(cmd);
             Serial2.write(data);
             Serial2.write('\r');
             delay200();
             Serial2.print("ST0");
             Serial2.write('\r');
             delay200();
             }
}


/************************
 *  Send a cmd to RS-UV3 with data
 */ 
 void sendDatacmd(char* cmd, char* data)
{
#ifdef DEBUG  
  Serial.println(F("sendDatacmd"));
  Serial.print(F("cmd = ")); Serial.println(cmd);
  Serial.print(F("data = ")); Serial.println(data);
#endif
 flushBuffers();
 if (currentDevice == 0) {
     Serial3.write('\r');
     Serial3.flush();
     Serial3.print(cmd);
     Serial3.print(data);
     Serial3.write('\r');
     delay200();
     } else { 
             Serial2.write('\r');
             Serial2.flush();
             Serial2.print(cmd);
             Serial2.print(data);
             Serial2.write('\r');
             delay200();
             }
}
/*********************
 * delay1K
*********************/
void delay1k()
{
  delay(1000);
}

/************************
 * delay2k
************************/

void delay2k()
{
  delay(2000);
}

/************************
 * delay200();
************************/

void delay200()
{
  delay(200);
}
/************************
 * delay500();
************************/

void delay500()
{
  delay(500);
}

/************************
 * delay4K();
************************/

void delay4k()
{
  delay(4000);
}

/***********************************
 * sendRecvStringToUV3
************************************/
 void sendRecvStringToUV3() 
 {
#ifdef DEBUG
   Serial.println("sendRecv");
#endif
    if (currentDevice == 0) {    // check device
         Serial3.write('\r');
         Serial3.print("FR");
         Serial3.write(UV3buff);
         Serial3.write("000");              // freq is stored in kHz
         Serial3.write('\r');
         delay200();
         Serial3.flush();
         Serial3.print("ST");
         Serial3.write(memoryChannel);
         Serial3.write('\r');
         } else {                     // device 2
                  Serial2.write('\r');
                  Serial2.print("FR");
                  Serial2.write(UV3buff);
                  Serial2.write("000");         // freq is stored in kHz
                  Serial2.write('\r');
                  delay200();
                  Serial2.flush();
                  Serial2.print("ST");
                  Serial2.write(memoryChannel);
                  Serial2.write('\r');
                }

  getConfiginfo();   // get infor from the rs-uv3
  getFreq();
  printFreq();
 }
/********************************
 * sendXmitStringToUV3
********************************/
 void sendXmitStringToUV3()
 {
#ifdef DEBUG
   Serial.println("sendXmit");
#endif   
    if (currentDevice == 0) {    // check device
         Serial3.write('\r');
         Serial3.print("FT");
         Serial3.write(UV3buff);
         Serial3.write("000");              // freq is stored in kHz
         Serial3.write('\r');
         delay200();
         Serial3.flush();
         Serial3.print("ST");
         Serial3.write(memoryChannel);
         Serial3.write('\r');
         } else {                     // device 2
                  Serial2.write('\r');
                  Serial2.print("FT");
                  Serial2.write(UV3buff);
                  Serial2.write("000");         // freq is stored in kHz
                  Serial2.write('\r');
                  delay200();
                  Serial2.flush();
                  Serial2.print("ST");
                  Serial2.write(memoryChannel);
                  Serial2.write('\r');
                }

  getConfiginfo();   // get infor from the rs-uv3
  getFreq();
  printFreq();
  
 }

