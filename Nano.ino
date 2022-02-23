#include <Wire.h>

String message;
bool S =false;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(8);
  Wire.onRequest(eventoSolicitud);
  Wire.onReceive(eventoRecepcion);
}


void eventoRecepcion(){
  if(Wire.read() == 'S'){
    S=true;
    message=String(millis())+ '\n';
  }
}

void eventoSolicitud(){
  Wire.write("hello ");
}
void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
}
