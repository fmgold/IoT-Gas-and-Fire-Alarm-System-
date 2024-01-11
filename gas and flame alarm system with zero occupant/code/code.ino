#include <LiquidCrystal.h>

int flame_sensor_pin = A2;
int flame_pin = HIGH;
int gas = A4;
int buzz = 7;
int led = 6;
int g;
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(gas, INPUT);
  pinMode ( flame_sensor_pin , INPUT );
  pinMode(buzz, OUTPUT);
  pinMode(led, OUTPUT);
  lcd.setCursor(2, 0);
  lcd.print("GAS AND FIRE ");
  lcd.setCursor(2, 1);
  lcd.print("ALARM SYSTEM");
  delay(2000);
  lcd.clear();
  Serial.begin(9600);
  delay(1000);

  //Set SMS format to ASCII
  Serial.write("AT+CMGF=1\r\n");
  delay(1000);

  //Send new SMS command and message number
  Serial.write("AT+CMGS=\"+2348144836070\"\r\n");
  delay(1000);

  //Send SMS content
  Serial.write("You are welcome");
  delay(1000);

  //Send Ctrl+Z / ESC to denote SMS message is complete
  Serial.write((char)26);
}

void loop() {
  flame_pin = digitalRead(flame_sensor_pin );
  g = digitalRead(gas);
  Serial.println(g);
  

  flame_pin = digitalRead( flame_sensor_pin) ; // reading from the sensor



  if (flame_pin == LOW && g == LOW) // applying condition
  {
    Serial.println ( "ALERT: SMOKE AND FLAME DETECTED" ) ;
    digitalWrite ( buzz , HIGH ) ;// if state is high, then turn high the BUZZER
    digitalWrite ( led , HIGH );
    lcd.setCursor(0, 0);
    lcd.print("FLAME AND SMOKE");
    lcd.setCursor(4, 1);
    lcd.print("DETECTED");
    delay(2000);
    Send_Sms();
    digitalWrite ( buzz , LOW ) ;// if state is high, then turn high the BUZZER
    digitalWrite ( led , LOW );
    lcd.clear();
  }
  else if (flame_pin == LOW && g == HIGH) {
    Serial.println ( "ALERT: FLAME DETECTED" ) ;
    lcd.setCursor(0, 0);
    lcd.print("FLAME DETECTED");
    digitalWrite ( buzz , HIGH ) ;// if state is high, then turn high the BUZZER
    digitalWrite ( led , HIGH );
    delay(2000);
    Send_fire();
    lcd.clear();
    digitalWrite ( buzz , LOW) ;// if state is high, then turn high the BUZZER
    digitalWrite ( led , LOW );
  }
  else if (flame_pin == HIGH && g == LOW) {
    Serial.println ( "ALERT: SMOKE DETECTED" ) ;
    lcd.setCursor(0, 0);
    lcd.print("SMOKE DETECTED");
    digitalWrite ( buzz , HIGH ) ;// if state is high, then turn high the BUZZER
    digitalWrite ( led , HIGH );
    Send_Smoke();
    delay(2000);
    lcd.clear();
    digitalWrite ( buzz , LOW ) ;// if state is high, then turn high the BUZZER
    digitalWrite ( led , LOW );
  }
  else
  {
    Serial.println ( " NO FLAME AND SMOKE DETECTED " ) ;
    digitalWrite ( buzz , LOW ) ; // otherwise turn it low
    digitalWrite ( led , LOW );
    lcd.setCursor(0, 0);
    lcd.print("NO FLAME AND");
    lcd.setCursor(0, 1);
    lcd.print("SMOKE DETECTED");
    delay(500);
    lcd.clear();
  }
  delay(1000);

}


void Send_Sms(){
   //Being serial communication witj Arduino and SIM800
  Serial.begin(9600);
  delay(1000);

  //Set SMS format to ASCII
  Serial.write("AT+CMGF=1\r\n");
  delay(1000);

  //Send new SMS command and message number
  Serial.write("AT+CMGS=\"phone number\"\r\n");
  delay(1000);

  //Send SMS content
  Serial.write("There is a fire and smoke, THERE COULD BE FIRE OUTBREAK");
  delay(1000);

  //Send Ctrl+Z / ESC to denote SMS message is complete
  Serial.write((char)26);
  delay(1000);

}

void Send_fire(){
   //Being serial communication witj Arduino and SIM800
  Serial.begin(9600);
  delay(1000);

  //Set SMS format to ASCII
  Serial.write("AT+CMGF=1\r\n");
  delay(1000);

  //Send new SMS command and message number
  Serial.write("AT+CMGS=\"phone number\"\r\n");
  delay(1000);

  //Send SMS content
  Serial.write("There is a fire, THERE COULD BE FIRE OUTBREAK");
  delay(1000);

  //Send Ctrl+Z / ESC to denote SMS message is complete
  Serial.write((char)26);
  delay(1000);

}

void Send_Smoke(){
   //Being serial communication witj Arduino and SIM800
  Serial.begin(9600);
  delay(1000);

  //Set SMS format to ASCII
  Serial.write("AT+CMGF=1\r\n");
  delay(1000);

  //Send new SMS command and message number
  Serial.write("AT+CMGS=\"phone number\"\r\n");
  delay(1000);

  //Send SMS content
  Serial.write("There is a smoke, ");
  delay(1000);

  //Send Ctrl+Z / ESC to denote SMS message is complete
  Serial.write((char)26);
  delay(1000);

}
