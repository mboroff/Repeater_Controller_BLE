/******************************
 * pollBLE
 *****************************/
void pollBLE(){
  #ifdef BLEMONIOR
  pollBLEcurrentFreeMem = freeRam();
  currentFunction = "pollBLE()";
  Serial.print(currentFunction); Serial.print(" ");
  if (localHour < 10) Serial.print("0");
  Serial.print(localHour); Serial.print(":"); 
  if (myMinute < 10) Serial.print("0");
  Serial.print(myMinute); Serial.print(":");
  if (mySecond < 10) Serial.print("0");
  Serial.print(mySecond);
  Serial.print(" freeRam = "); Serial.println(pollBLEcurrentFreeMem);
#endif

#ifdef BLE
  // Echo received data from bluetooth
  // Clear the input buffer 
  bufferData = "";
   while ( ble.available() )
  {
    char c = ble.read();
    bufferData += c;
     }

  // Get the lentgth of the input buffer
  int x = bufferData.length();

  // Check if buffer is greater than 1
  if (x > 1) {
#ifdef BLEMONIOR
  gotDataCurrentFreeMem = freeRam();
  if (previousGotDataFreeMem != gotDataCurrentFreeMem) {
      previousFreeMem = gotDataCurrentFreeMem;
     currentFunction = "Got data";
     Serial.print(currentFunction); Serial.print(" "); 
     Serial.print(localHour); Serial.print(":"); Serial.print(myMinute); Serial.print(":"); Serial.print(mySecond);
     Serial.print(" freeRam = "); Serial.println(gotDataCurrentFreeMem);
    }
#endif
    
#ifdef DEBUG
    Serial.println(); Serial.print("bufferData = "); Serial.println(bufferData); Serial.print("size of bufferData = "); Serial.println(bufferData.length());
#endif

/****************************************************************
 *   Stwart checking for strings of keywords and data
****************************************************************/ 
    // Check for unitA
    if (bufferData == "unitA ") {
        
        // Set the currentDevice
        currentDevice = 0;

        // Write the device number to eeprom
        EEPROM.write(deviceAddr, currentDevice);

#ifdef DEBUG
Serial.print(F("currentDevice = ")); Serial.println(currentDevice);Serial.print(F("repeaterEnabled = ")); Serial.println(repeaterEnabled);        
#endif 
     
        // We switch devices so refresh info to the bluetooth
        processHelloUV3();
        for (int i = 0; i < 20; i++) {  
             lcd.setCursor(i,3); 
             lcd.print(" ");
             }
          lcd.setCursor(13, 2);
          lcd.print("       ");
          previousLoopFreeMem = 0;

        //  Check for unitB
    } else  if (bufferData == "unitB ") {  
              
              // Set the currentDevice
              currentDevice = 1;

              // write the device number to eeprom
              EEPROM.write(deviceAddr, currentDevice);
#ifdef DEBUG
Serial.print(F("currentDevice = ")); Serial.println(currentDevice);Serial.print(F("repeaterEnabled = ")); Serial.println(repeaterEnabled);        
#endif  
              // We switch devices so refresh info to the bluetooth
              processHelloUV3();
              for (int i = 0; i < 20; i++) {  
                   lcd.setCursor(i,3); 
                   lcd.print(" ");
               }
               lcd.setCursor(13, 2);
               lcd.print("       ");
               previousLoopFreeMem = 0;
               } 
  
              else if (bufferData.substring(0, 3) == "Rx:") {  // Check if iPhone set new receive freq
                       // Creaate a temporary string
                       String tempString;

                       // move ghe first three characters to the temp string
                       tempString = bufferData.substring(4, 7);
                       
                        // move the last three characters bypassing a period
                       tempString += bufferData.substring(8, 11);

                       // copy the string to a character array
                       tempString.toCharArray(UV3buff, 7);
#ifdef DEBUG
Serial.print("tempString = "); Serial.println(tempString); Serial.print("UV3buff = "); Serial.println(UV3buff);
#endif

                         // Send the new receive set command to the UV3
                         sendRecvStringToUV3();
                          }
     else if (bufferData.substring(0, 3) == "Tx:") {  // Check for a new transmit frequency

              // Create a temporary string
              String tempString;

              // Move the first three characters
              tempString = bufferData.substring(4, 7);

              // move the last three characters bypassing the period
              tempString += bufferData.substring(8, 11);

              // convert the temp string to a char array
              tempString.toCharArray(UV3buff, 7);
#ifdef DEBUG              
Serial.print("tempString = "); Serial.println(tempString); Serial.print("UV3buff = "); Serial.println(UV3buff);
#endif             
              // send the string to the UV3
              sendXmitStringToUV3();
               }

       else if (bufferData.substring(0, 12) == "Repeater: ON") {      // Check for turn repeater power on    
 #ifdef DEBUG
 Serial.println("Processing repeater on");
#endif
               // set the repeaterEnabled switch to ON
               repeaterEnabled = relayOn;

               // write the new setting to eeprom
               EEPROM.write(repeaterAddr, repeaterEnabled);

               // turn the relay on
               digitalWrite(REPEATERPIN, LOW);      
               }
      else if (bufferData.substring(0, 13) == "Repeater: OFF") {   // check for repeater off
 #ifdef DEBUG
 Serial.println("Processing repeater off");
#endif
               // set the repeaterEnabled to Off
               repeaterEnabled = relayOff;

               // write the status to eeprom
               EEPROM.write(repeaterAddr, repeaterEnabled);

               // // turn the relay off   
               digitalWrite(REPEATERPIN, HIGH);   
               }

       else if (bufferData.substring(0, 7) == "Fan: ON") {     // Check for Fan On     
#ifdef DEBUG
Serial.println("Processing Fan on");
 #endif
               // set the enabled fan switch to On
               fanEnabled = relayOn;

               // write the status to eeprom
               EEPROM.write(fanAddr, fanEnabled);

               // turn the relay on   
               digitalWrite(FANPIN, LOW);   
               }
      else if (bufferData.substring(0, 8) == "Fan: OFF") {        // check for Fan OFF
#ifdef DEBUG
 Serial.println("Processing Fan off");
 #endif
               // set the fanEnabled to On
               fanEnabled = relayOff;

               // write the fanEnabled to eeprom
               EEPROM.write(fanAddr, fanEnabled);

               // turn the relay off   
               digitalWrite(FANPIN, HIGH);   
               }
      else if (bufferData.substring(0, 8) == "Beep: ON") {       // check for beep on
#ifdef DEBUG        
 Serial.println("Processing Beep On");
 #endif
               // set the buzzer Enable
               buzzerEnabled = true;

               // write the buzzard enabled to eeprom
               EEPROM.write(buzzerAddr, buzzerEnabled);     // save the status in EEPROM
               }
      else if (bufferData.substring(0, 9) == "Beep: OFF") {  // check for buzzer off
#ifdef DEBUG 
 Serial.println("Processing Beep Off");
#endif
               // turn the buzzwer off
               buzzerEnabled = false;

               // write the status to eeprom
               EEPROM.write(buzzerAddr, buzzerEnabled);     // save the status in EEPROM
               }
               
      else if (bufferData.substring(0, 2) == "T:") {  // check for time
#ifdef BLEMONIOR
 Serial.println("Processing Time:");
 Serial.println(bufferData);
#endif
              String tempString;
              char tempChar[3];
              
              // Move the hour characters
              tempString = bufferData.substring(2, 4);
              tempString.toCharArray(tempChar, 3);
              myHour = atoi(tempChar);
#ifdef BLEMONIOR             
      Serial.print("tempString = "); Serial.println(tempString);
      Serial.print("tempChar = "); Serial.println(tempChar);
      Serial.print("myHour = "); Serial.println(myHour);        
#endif
              // Move the minute characgters
              tempString = bufferData.substring(5, 7);
              tempString.toCharArray(tempChar, 3);
              myMinute = atoi(tempChar);
#ifdef BLEMONIOR              
      Serial.print("tempString = "); Serial.println(tempString);
      Serial.print("tempChar = "); Serial.println(tempChar);
      Serial.print("myMinute = "); Serial.println(myMinute);
#endif
              // Move the second characters
              tempString = bufferData.substring(8, 10);
              tempString.toCharArray(tempChar, 3);
              tempChar[2], '\0';
              mySecond = atoi(tempChar);
#ifdef BLEMONIOR
      Serial.print("tempString = "); Serial.println(tempString);
      Serial.print("tempChar = "); Serial.println(tempChar);
      Serial.print("mySecond = "); Serial.println(mySecond);        
#endif              
              rtc.setTime(myHour, myMinute, mySecond); 
               
#ifdef BLEMONIOR
 Serial.println("Processing Date:");
#endif
              tempString = "";                                       
              // Move the Month characters
              tempString = bufferData.substring(10, 12);
              tempString.toCharArray(tempChar, 3);
              myMonth = atoi(tempChar);
 #ifdef BLEMONIOR            
      Serial.print("tempString = "); Serial.println(tempString);
      Serial.print("tempChar = "); Serial.println(tempChar);
      Serial.print("myMonth = "); Serial.println(myMonth);  
#endif
              // Move the Day characters
              tempString = bufferData.substring(13, 15);
              tempString.toCharArray(tempChar, 3);
              myMonthDay = atoi(tempChar);
#ifdef BLEMONIOR
      Serial.print("tempString = "); Serial.println(tempString);
      Serial.print("tempChar = "); Serial.println(tempChar);
      Serial.print("myMonthDay = "); Serial.println(myMonthDay);
#endif
              // Move the Year characters
              tempString = bufferData.substring(16, 18);
              tempString.toCharArray(tempChar, 3);
              myYear = atoi(tempChar);
              myYear = myYear + 2000;
#ifdef BLEMONIOR
      Serial.print("tempString = "); Serial.println(tempString);
      Serial.print("tempChar = "); Serial.println(tempChar);
      Serial.print("myYear = "); Serial.println(myYear);        
#endif             
               rtc.setDate(myMonthDay, myMonth, myYear);
#ifdef BLEMONIOR 
                Serial.println("Processing Timezone:");
#endif
                tempChar[0] = bufferData[19];
                tempChar[1] = '\0';
                localOffset = atoi(tempChar);
#ifdef BLEMONIOR                
                Serial.print("localOffset = "); Serial.println(localOffset);
#endif
                }

      else if (bufferData.substring(0, 2) == "VU") {  // check for volume
#ifdef DEBUG        
                Serial.println("Processing Volume:");
#endif

                char tempChar[3];
                for (int i = 0; i < 2; i++) {
                    tempChar[i] = bufferData[i + 2];
                    tempChar[i + 1] = '\0';
                }
#ifdef DEBUG
                Serial.print("tempChar = "); Serial.println(tempChar);
#endif
                sendStorecmd("VU", tempChar);
                }

      else if (bufferData.substring(0, 3) == "AD1") {  // check for reset
#ifdef DEBUG
                Serial.println("Processing Reset:");
#endif
                sendReadcmd("FD1\r");
                delay1k();
                processHelloUV3();
                return;
                }

      else if (bufferData.substring(0, 2) == "CT") {
#ifdef DEBUG
                Serial.println("Processing xmit call sign");
#endif

                xmitCallsign();
                getradioTemp();
                printFreq();
                }

      else if (bufferData.substring(0, 8) == "HelloUV3") {  // Good morning from the iPhone
                 processHelloUV3();
                 for (int i = 0; i < 20; i++) {  
                      lcd.setCursor(i,3); 
                      lcd.print(" ");
                      }
                  lcd.setCursor(13, 2);
                  lcd.print("       ");
                  previousLoopFreeMem = 0;
                  return;
                  }

      else  {
               // Not a recognized command - just break it in two and send to UV3
 
              // Get the length of the buffer
              int buffLength = bufferData.length();
              
              // find out where the first blank character is located
              int spaceIndex = bufferData.indexOf(" ");

              // copy over the caommand part of the buffer
              char tempCmd[spaceIndex + 1];

              // copy the command to a char array
               bufferData.toCharArray(tempCmd, spaceIndex + 1);

               // make sure the string is terminated with a nuull
               tempCmd[spaceIndex+ 1] = '\0';

               // Create a temp char array the size of the data portion
               char tempData[buffLength + 1 - spaceIndex];

               // create a temporary string
               String tempString;

               // copy the data to a string
               tempString = bufferData.substring(spaceIndex +1, buffLength);

               // copy the string into a char array
               tempString.toCharArray(tempData, buffLength - spaceIndex);
#ifdef DEBUG               
Serial.println("********* Received buffer from iPhone ***********");
Serial.print("buffLength = "); Serial.println(buffLength);        
Serial.print("spaceIndex = "); Serial.println(spaceIndex);        
Serial.print("tempCmd = "); Serial.println(tempCmd);        
Serial.print("tempString = "); Serial.println(tempString);
Serial.print("tempData = "); Serial.println(tempData);    
#endif
               // send the command and data to the UV3
               sendStorecmd(tempCmd, tempData );
               }
      }
#endif      
}

/**************************
 * sendDataToIphone
***************************/

void sendDataToIphone() 
{
  if (firstTime == true) {
      return;
  }
#ifdef BLEMONIOR
  sendDataCurrentFreeMem = freeRam();
  if (previousSendDataFreeMem != sendDataCurrentFreeMem) {
      previousSendDataFreeMem = sendDataCurrentFreeMem;
      currentFunction = "sendDataToIphone()";
      Serial.print(currentFunction); Serial.print(" "); 
      Serial.print(localHour); Serial.print(":"); Serial.print(myMinute); Serial.print(":"); Serial.print(mySecond);
      Serial.print("freeRam = "); Serial.println(sendDataCurrentFreeMem);
      }
#endif
  
#ifdef DEBUG
  Serial.println("Enter sendDataToIphone"); 
#endif
#ifdef BLE
    // write the caommand and data to the iPhone
   if (iPhoneBuffer[0] != '\0') {
    ble.print(iPhoneBuffer);
#endif
#ifdef DEBUG    
    Serial.print("iPhoneBuffer = "); Serial.println(iPhoneBuffer);
#endif
#ifdef BLE
   }
  // Wait 1/4 second
  delay(250);
#endif
}


void processHelloUV3()
{
#ifdef BLEMONIOR
  currentFreeMem = freeRam();
  if (previousFreeMem != currentFreeMem) {
      previousFreeMem = currentFreeMem;
     currentFunction = "processHelloUV3()";
     Serial.print(currentFunction); Serial.print(" ");
     Serial.print(localHour); Serial.print(":"); Serial.print(myMinute); Serial.print(":"); Serial.print(mySecond);
     Serial.print(" freeRam = "); Serial.println(currentFreeMem);
    }
#endif
  
#ifdef BLE  
  if (currentDevice == 0) {
       memcpy (iPhoneBuffer, unitA, 6);
        } else {
                 memcpy (iPhoneBuffer, unitB, 6); 
                 }
   sendDataToIphone();             
     // send buzzer status to the iPhone
   if (buzzerEnabled == true) {
       memcpy(iPhoneBuffer, txtBeepSwitchTrue, 11); 
       } else {
               memcpy(iPhoneBuffer, txtBeepSwitchFalse, 12); 
               }
   sendDataToIphone();

   // check the status of the repeater and send current to the iPhone
   if (repeaterEnabled == relayOn) {

        // Copy the repeater on message to the buffer
        memcpy(iPhoneBuffer, txtRepeaterSwitchTrue, 15);
        }  else {  // If the repater is enabled sent it to the iPhone

                 // copy the the repeater off status to the iPhone
                 memcpy(iPhoneBuffer, txtRepeaterSwitchFalse, 16);
                 }

    // Send the data to the iPhone
    sendDataToIphone();
               
    if (fanEnabled == relayOn) {             // check if the fan is enabled

         // copy the fan on to the buffr
         memcpy(iPhoneBuffer, txtFanSwitchTrue, 10);
         } else {       // check if repeater is enabled

                 // copy the status to the ibuffer
                 memcpy(iPhoneBuffer, txtFanSwitchFalse, 11);
                 }
      // send the status to the iPhone             
      sendDataToIphone();          
      getradioTemp();
      getFreq();
      printFreq();
      sendDataToIphone();
      getRepeaterInfoForiPhone = true;
      get_repeater_info();
      getRepeaterInfoForiPhone = false;
      memcpy(iPhoneBuffer, txtDone, 5);
      sendDataToIphone();
      if (fanEnabled == relayOn){
          memcpy(iPhoneBuffer, txtFanSwitchTrue, 10);        
          } else {
                  memcpy(iPhoneBuffer, txtFanSwitchFalse, 11);           
                  }
       sendDataToIphone();
#endif
}

     

