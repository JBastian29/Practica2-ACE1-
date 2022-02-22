#include <LiquidCrystal.h>
int rs = 10, rw=9, en=8, d4=7, d5=6,d6=5, d7=4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
char string1[] = "Canche1"; 
char string2[] = "Canche2"; 

void imprimirLCD(String texto, int linea){
  lcd.setCursor(0,linea);
  lcd.print(texto);
}

void setup() {
  // put your setup code here, to run once:
  for(int i=4; i<11; i++) pinMode(i,OUTPUT);
  lcd.begin(16,2);
  imprimirLCD("hola buenas",0);
  imprimirLCD("que tal",1);
}

void loop() {
  // put your main code here, to run repeatedly:

}
