/**************************************************
 *   get_repeater_info all information
 *   the name of each field read is listed 
 *   in the routine
**************************************************/

void get_repeater_info()
{
#ifdef DEBUG
Serial.println(functionLabels[menuSelect-1]);
#endif
  
  sendReadcmd("AF?\r");
  get_UV3buff();
#ifdef DEBUG
Serial.println("Getting sys info");
#endif
  int i;
  lcd.createChar(1, fullBar);

  if (getRepeaterInfoForiPhone == false) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(txtAudiolpf);
      lcd.setCursor(0, 1);
      lcd.print(UV3buff);
      delay2k();
  } 
#ifdef BLE
  else {  
          copyUV3buffToIphoneBuffer();
          sendDataToIphone();
          lcd.setCursor(13, 2);
          lcd.print("Sending");
          lcd.createChar(1, fullBar);
          lcd.setCursor(0,3); 
          lcd.write( 1 );
          }
#endif  
  sendReadcmd("AI?\r");
  get_UV3buff();
    if (getRepeaterInfoForiPhone == false) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Arduino In Pin"));
        lcd.setCursor(0, 1);
        lcd.print(txtFunction);               // "Function"
        lcd.setCursor(0, 2);
        lcd.print(UV3buff);
         delay2k();
  } 
#ifdef BLE  
  else {  
          copyUV3buffToIphoneBuffer();
          sendDataToIphone(); 
          lcd.setCursor(1,3); 
          lcd.write( 1 );
          }
#endif    
  sendReadcmd("AO?\r");
  get_UV3buff();
  if (getRepeaterInfoForiPhone == false) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("Arduino Output Pin"));
      lcd.setCursor(0, 1);
      lcd.print(txtFunction);
      lcd.setCursor(0, 2);
      lcd.print(UV3buff);
      delay2k();
  } 
#ifdef BLE 
  else {  
          copyUV3buffToIphoneBuffer();
          sendDataToIphone();
          for (int i = 0; i < 2; i++) {     
              lcd.setCursor(i,3); 
              lcd.write( 1 );
          }
  }
#endif  
  sendReadcmd("B1?\r");
  get_UV3buff();
    if (getRepeaterInfoForiPhone == false) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("Arduino USB Speed"));
        lcd.setCursor(0, 1);
        lcd.print(UV3buff);
        delay2k();
  } 
#ifdef BLE
  else {  
          copyUV3buffToIphoneBuffer();
          sendDataToIphone();
          for (i = 0; i < 3; i++) {     
              lcd.setCursor(i,3); 
              lcd.write( 1 );
          }
  }
#endif    
  sendReadcmd("B2?\r");
  get_UV3buff();
   if (getRepeaterInfoForiPhone == false) {
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print(F("I/O Connector Serial"));
       lcd.setCursor(0, 1);
       lcd.print(F("Baud Rate"));
       lcd.setCursor(0, 2);
       lcd.print(UV3buff);
       delay2k();
  } 
#ifdef BLE  
  else {  
          copyUV3buffToIphoneBuffer();
          sendDataToIphone();
          for (i = 0; i < 4; i++) {     
              lcd.setCursor(i,3); 
              lcd.write( 1 );
          }

  }
#endif   
  sendReadcmd("BM?\r");
  get_UV3buff();
   if (getRepeaterInfoForiPhone == false) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("Beacon Message"));
      lcd.setCursor(0, 1);
      lcd.print(UV3buff);
      delay2k();
  } 
#ifdef BLE
  else {  
          copyUV3buffToIphoneBuffer();
          sendDataToIphone();
          for (int i = 0; i < 5; i++) {     
              lcd.setCursor(i,3); 
              lcd.write( 1 );
          }
  }
#endif  
  sendReadcmd("BT?\r");
  get_UV3buff();
   if (getRepeaterInfoForiPhone == false) { 
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("Beacon Timer"));
      lcd.setCursor(0, 1);
      lcd.print(UV3buff);
      delay2k();
  }
#ifdef BLE
  else {  
          copyUV3buffToIphoneBuffer();
          sendDataToIphone();
          for (int i = 0; i < 5; i++) {     
                lcd.setCursor(i,3); 
                lcd.write( 1 );
                }

  }
#endif  
  sendReadcmd("CF?\r");
  get_UV3buff();
   if (getRepeaterInfoForiPhone == false) { 
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("CW Audio Freq"));
      lcd.setCursor(0, 1);
      lcd.print(UV3buff);
      delay2k();
  } 
#ifdef BLE
  else {  
          copyUV3buffToIphoneBuffer();
          sendDataToIphone();
           for (int i = 0; i < 6; i++) {     
              lcd.setCursor(i,3); 
              lcd.write( 1 );
          }
 }
#endif   
  sendReadcmd("CL?\r");
  get_UV3buff();
  if (getRepeaterInfoForiPhone == false) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("CW Call Sign"));
      lcd.setCursor(0, 1);
      lcd.print(UV3buff);
      delay2k();
  } 
#ifdef BLE  
    else {  
          copyUV3buffToIphoneBuffer();
          sendDataToIphone();
          for (int i = 0; i < 6; i++) {     
              lcd.setCursor(i,3); 
              lcd.write( 1 );
          }
  }
#endif  
  sendReadcmd("CS?\r");
  get_UV3buff();
  if (getRepeaterInfoForiPhone == false) {  
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("CW Speed"));
      lcd.setCursor(0, 1);
      lcd.print(UV3buff);
      delay2k();
  } 
#ifdef BLE
  else {  
          copyUV3buffToIphoneBuffer();
          sendDataToIphone();
          for (i = 0; i < 7; i++) {     
              lcd.setCursor(i,3); 
              lcd.write( 1 );
          }

  }
#endif 
  sendReadcmd("DD?\r");
  get_UV3buff();
  if (getRepeaterInfoForiPhone == false) {  
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("DTMF Tone Duration"));
      lcd.setCursor(0, 1);
      lcd.print(UV3buff);
      delay2k();
  } 
#ifdef BLE 
  else {  
          copyUV3buffToIphoneBuffer();
          sendDataToIphone();
            for (int i = 0; i < 7; i++) {     
              lcd.setCursor(i,3); 
              lcd.write( 1 );
          }
}
#endif  
  sendReadcmd("DP?\r");
  get_UV3buff();
   if (getRepeaterInfoForiPhone == false) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("Pre-emphasis State"));
      lcd.setCursor(0, 1);
      lcd.print(UV3buff);
      delay2k();
  } 
#ifdef BLE
  else {  
          copyUV3buffToIphoneBuffer();
          sendDataToIphone();
          for (int i = 0; i < 8; i++) {     
              lcd.setCursor(i,3); 
              lcd.write( 1 );
          }
  }
#endif  
  sendReadcmd("DR?\r");
  get_UV3buff();
   if (getRepeaterInfoForiPhone == false) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("DTMF Detector State"));
      lcd.setCursor(0, 1);
      lcd.print(UV3buff);
      delay2k();
  } 
#ifdef BLE  
  else {  
          copyUV3buffToIphoneBuffer();
          sendDataToIphone();
           for (int i = 0; i < 9; i++) {     
              lcd.setCursor(i,3); 
              lcd.write( 1 );
          }
 }
#endif 
  sendReadcmd("EX?\r");
  get_UV3buff();
   if (getRepeaterInfoForiPhone == false) { 
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("E-pin state "));
      lcd.setCursor(0, 1);
      lcd.print(UV3buff);
      delay2k();
   
      lcd.clear();
    } 
#ifdef BLE    
    else {  
          copyUV3buffToIphoneBuffer();
          sendDataToIphone();
           for (int i = 0; i < 9; i++) {     
              lcd.setCursor(i,3); 
              lcd.write( 1 );
          }
   }
#endif
  sendReadcmd("FW\r");
  get_UV3buff();
  
  if (getRepeaterInfoForiPhone == false) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("Firmware Version"));
      lcd.setCursor(0, 1);
      lcd.print(UV3buff);
      delay2k();
  }
#ifdef BLE   
    else {  
          copyUV3buffToIphoneBuffer();
          sendDataToIphone();
          for (i = 0; i < 9; i++) {     
              lcd.setCursor(i,3); 
            lcd.write( 1 );
          }
          
  }
#endif  
  sendReadcmd("GM?\r");
  get_UV3buff();
  if (getRepeaterInfoForiPhone == false) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("Mic Gain"));
      lcd.setCursor(0, 1);
      lcd.print(UV3buff);
       delay2k();
  } 
#ifdef BLE  
  else {  
          copyUV3buffToIphoneBuffer();
          sendDataToIphone();
            for (i = 0; i < 10; i++) {     
              lcd.setCursor(i,3); 
              lcd.write( 1 );
          }
  }
#endif  
  sendReadcmd("GT?\r");
  get_UV3buff();
    if (getRepeaterInfoForiPhone == false) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(F("CW/DTMF Tone Gain"));
        lcd.setCursor(0, 1);
        lcd.print(UV3buff);
        delay2k();
  } 
#ifdef BLE  
  else {  
          copyUV3buffToIphoneBuffer();
          sendDataToIphone();
          for (i = 0; i < 11; i++) {     
              lcd.setCursor(i,3); 
              lcd.write( 1 );
          }
}
#endif    
  sendReadcmd("HT?\r");
  get_UV3buff();
   if (getRepeaterInfoForiPhone == false) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("HangTime"));
      lcd.setCursor(0, 1);
      lcd.print(UV3buff);
      delay2k();
  } 
#ifdef BLE
     else {  
          char tempCmd[10] = "HT       ";
          for (int i = 0; i < 4; i++ ) {
               if (UV3buff[i + 1] == '\0' || UV3buff[i + 1] == ' ' ) {
                   tempCmd[i + 3] = '0';
                   } else {
                          tempCmd[i + 3] = UV3buff[i + 1];
                          }
               tempCmd[i + 4] = '\0';
              }
           memcpy(iPhoneBuffer, tempCmd, 9);
           sendDataToIphone();
            } 
#endif   
      getIDtimer();
      if (getRepeaterInfoForiPhone == false) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("CW ID Timer"));
      lcd.setCursor(0, 1);
      lcd.print(UV3buff);
       delay2k();
  } 
#ifdef BLE
     else {  
          sprintf(tempIDtimer, "%03.3i", idTimer);     // format the id time before sending to uv3
          tempIDtimer[4] = txtNull;
          char tempCmd[8] = "IT 000";
          for (int i = 0; i < 3; i ++) {
              if (tempIDtimer[i] == '\0' || tempIDtimer[i] == ' ') {
                   tempCmd[i + 3] = '0';
                   } else {
                           tempCmd[i + 3] = tempIDtimer[i];
                          }
                  tempCmd[i + 4] = '\0';
                  }
          memcpy(iPhoneBuffer, tempCmd, 8);
          sendDataToIphone();
          for (i = 0; i < 12; i++) {     
              lcd.setCursor(i,3); 
              lcd.write( 1 );
          }
  }
#endif  
  sendReadcmd("PD?\r");
  get_UV3buff();
  if (getRepeaterInfoForiPhone == false) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("Power Down State"));
      lcd.setCursor(0, 1);
      lcd.print(UV3buff);
      delay2k();
  } 
#ifdef BLE  
    else {  
          copyUV3buffToIphoneBuffer();
          sendDataToIphone();
          for (i = 0; i < 13; i++) {     
              lcd.setCursor(i,3); 
              lcd.write( 1 );
          }          
  }
#endif  
  sendReadcmd("PW?\r");
  get_UV3buff();   
  if (getRepeaterInfoForiPhone == false) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("TX Power Level"));
      lcd.setCursor(0, 1);
      lcd.print(UV3buff);
      delay2k();
  } 
#ifdef BLE  
     else {  
          copyUV3buffToIphoneBuffer();
          sendDataToIphone();
            for (i = 0; i < 14; i++) {     
              lcd.setCursor(i,3); 
              lcd.write( 1 );
          }
}
#endif  
  sendReadcmd("SD?\r");
  get_UV3buff();
  if (getRepeaterInfoForiPhone == false) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("Side Tone State"));
      lcd.setCursor(0, 1);
      lcd.print(UV3buff);
      delay2k();
  } 
#ifdef BLE  
      else {  
          copyUV3buffToIphoneBuffer();
          sendDataToIphone();
          for (i = 0; i < 15; i++) {     
              lcd.setCursor(i,3); 
              lcd.write( 1 );
          }
  }
#endif  
  sendReadcmd("SO?\r");
  get_UV3buff();
  if (getRepeaterInfoForiPhone == false) { 
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("Squelch State"));
      lcd.setCursor(0, 1);
      lcd.print(UV3buff);
      delay2k();
  } 
#ifdef BLE     
     else {  
          copyUV3buffToIphoneBuffer();
          sendDataToIphone();
          for (i = 0; i < 16; i++) {     
              lcd.setCursor(i,3); 
              lcd.write( 1 );
          }
  }
#endif
  sendReadcmd("SQ?\r");
  get_UV3buff();
  if (getRepeaterInfoForiPhone == false) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("Squelch Level"));
      lcd.setCursor(0, 1);
      lcd.print(UV3buff);
      delay2k();
  } 
#ifdef BLE
      else {  
          copyUV3buffToIphoneBuffer();
          sendDataToIphone();
          for (i = 0; i < 16; i++) {     
              lcd.setCursor(i,3); 
              lcd.write( 1 );
          }
  }
#endif
  sendReadcmd("TF?\r");
  get_UV3buff();
  if (getRepeaterInfoForiPhone == false) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("CTCSS Tone Freq"));
      lcd.setCursor(0, 1);
      lcd.print(UV3buff);
      delay2k();
  } 
  #ifdef BLE
     else {  
          getCTCSS();
         
          lcd.createChar(1, fullBar);
          for (i = 0; i < 17; i++) {     
              lcd.setCursor(i,3); 
              lcd.write( 1 );
              }          
          }
#endif  
  sendReadcmd("TG?\r");
  get_UV3buff();
  if (getRepeaterInfoForiPhone == false) { 
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("TX Time Out CW"));
      lcd.setCursor(0, 1);
      lcd.print(F("Message"));
      lcd.setCursor(0, 2);
      lcd.print(UV3buff);
      delay2k();
  } 
#ifdef BLE
     else {  
          copyUV3buffToIphoneBuffer();
          sendDataToIphone();
           for (i = 0; i < 17; i++) {     
              lcd.setCursor(i,3); 
              lcd.write( 1 );
          }
 }
#endif  
  sendReadcmd("TM?\r");
  get_UV3buff();
  if (getRepeaterInfoForiPhone == false) {  
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("Tone Squelch Mode"));
      lcd.setCursor(0, 1);
      lcd.print(UV3buff);
      delay2k();
  } 
#ifdef BLE  
      else {  
          copyUV3buffToIphoneBuffer();
          sendDataToIphone();
          for (i = 0; i < 18; i++) {     
              lcd.setCursor(i,3); 
              lcd.write( 1 );
          }
  }
#endif  
  sendReadcmd("TO?\r");
  get_UV3buff();
  if (getRepeaterInfoForiPhone == false) { 
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("TX Time Out Timer"));
      lcd.setCursor(0, 1);
      lcd.print(UV3buff);
      delay2k();
  } 
#ifdef BLE
      else {        
          char tempTOtimer[4] = "   ";          
          char tempCmd[8] = "TO     ";
          for (int i = 0; i < 3; i ++) {
              if (UV3buff[i + 2] == '\0' || UV3buff[i + 2] == ' ') {
                   tempCmd[i + 3] = '0';
                   } else {
                           tempCmd[i + 3] = UV3buff[i + 2];
                          }
                  tempCmd[i + 4] = '\0';
                  }
          memcpy(iPhoneBuffer, tempCmd, 8);
           sendDataToIphone();
  }
#endif  
  sendReadcmd("TP?\r");
  get_UV3buff();
  if (getRepeaterInfoForiPhone == false) {  
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("PCB Temperature"));
      lcd.setCursor(0, 1);
      lcd.print(UV3buff);
      delay2k();
  } 
#ifdef BLE  
     else {  
          copyUV3buffToIphoneBuffer();
          sendDataToIphone();
          for (i = 0; i < 18; i++) {     
              lcd.setCursor(i,3); 
              lcd.write( 1 );
          }
  }
#endif    
  sendReadcmd("VT\r");
  get_UV3buff();
  if (getRepeaterInfoForiPhone == false) {  
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("Operating Voltage"));
      lcd.setCursor(0, 1);
      lcd.print(UV3buff);
      delay2k();
  } 
#ifdef BLE  
     else {  
          copyUV3buffToIphoneBuffer();
          sendDataToIphone();
          for (i = 0; i < 19; i++) {     
              lcd.setCursor(i,3); 
              lcd.write( 1 );
          }
  }
#endif  
  sendReadcmd("VU?\r");
  get_UV3buff();
  if (getRepeaterInfoForiPhone == false) {  
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("Volume"));
      lcd.setCursor(0, 1);
      lcd.print(UV3buff);
      delay2k();
      lcd.clear();
  } 
  #ifdef BLE
     else {  
          for (int i = 0; i < 2; i++) {
               if (UV3buff[i + 4] == ' ' || UV3buff[i + 4] == '\0'){
                   UV3buff[i + 4] = '0';
               }
          }
          copyUV3buffToIphoneBuffer();
          sendDataToIphone();         
          for (i = 0; i < 19; i++) {     
              lcd.setCursor(i,3); 
              lcd.write( 1 );
          }
          delay1k();
          }
#endif
}

void copyUV3buffToIphoneBuffer()
{
 memcpy(iPhoneBuffer, UV3buff, 32);
}



