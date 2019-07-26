void GSM(){
  if (Serial.available()>0)
  switch(Serial.read()){
    case 's':
      sendMessage();
      break;
  }

  if(myserial.available()>0)
    Serial.write(myserial.read());
}


void sendMessage(){
  myserial.println("AT+CMGF=1");
  delay(1000);
  myserial.println("AT+CMGS=\"+94714737583\"\r");
  delay(1000);
  myserial.println("HIIII");
  delay(1000);
  myserial.println((char)26);
  delay(1000);
}
