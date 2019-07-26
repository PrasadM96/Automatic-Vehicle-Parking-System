void rfid(){
   // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  lcd.clear();
  //Show UID on serial monitor
  Serial.println();
  Serial.print(" UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();
  if ((content.substring(1) == ("13 08 02 21"))||(content.substring(1) ==  ("39 B1 CC 6E"))
                || (content.substring(1) ==  ("D9 47 39 59"))) //change UID of the card that you want to give access
  {
    Serial.println(" Access Granted ");
    Serial.println(" Welcome Mr.Circuit ");
    delay(1000);
    Serial.println();
    lcd_d(1,1," Access Granted ");
    lcd_d(2,1," Welcome Mr.Hashan ");
    delay(2000);
    servo_m();
    statuss = 1;
    delay(3000);
    lcd.clear();
    lcd_d(1,1,"Use Your RFID Card");
  }
  
  else   {
    Serial.println(" Access Denied ");
    lcd_d(1,3," Access Denied ");
    delay(3000);
    lcd.clear();
    lcd_d(1,1,"Use Your RFID Card");
  }  
}
