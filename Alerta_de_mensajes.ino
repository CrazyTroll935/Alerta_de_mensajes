#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

int led =  2;
int buzzer = 8;
char a;

 LiquidCrystal_I2C lcd (0x27, 2, 1, 0, 4, 5, 6, 7);
SoftwareSerial BT(10,11);       //pines donde esta conectado el hc05

void setup() {
 Serial.begin(9600);
 Serial.println("Listo");
 BT.begin(38400);  
 pinMode(buzzer, OUTPUT);
 pinMode(led, OUTPUT);

 lcd.setBacklightPin(3, POSITIVE);
 lcd.begin(16, 2);
 lcd.print("Hola Matias!");
 delay(1000);
 lcd.clear();
}

void alertaConRuido(){
  digitalWrite(buzzer,HIGH);
  delay(250);
  digitalWrite(buzzer,LOW);
}

void ledParpadeando(){
  digitalWrite(led,HIGH);
  delay(250);
  digitalWrite(led,LOW);
}

void loop() {
   if(BT.available()){         //Si llega un dato por el puerto BT se envia al monitor serial
    Serial.write(BT.read());
  }
  if (BT.available()) { 
   a = BT.read();
   if( a == 'A') { 
    alertaConRuido();
    digitalWrite(led,HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Mensaje Recibido"); 
  }
  if( a == 'B'){
    digitalWrite(led,LOW);
    digitalWrite(buzzer,LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sin Mensajes...");
  }
 }
}
//Informacion sobre el LCD con I2C https://naylampmechatronics.com/blog/35_tutorial-lcd-con-i2c-controla-un-lcd-con-solo-dos-pines.html