#include <Servo.h>
#include <LiquidCrystal.h>
int usout = 2, usin = 3, ussrv = 4, encontrados=0,recurrencia = -1;
int rs= 5,en=6,d4=7,d5=8,d6=9,d7=10;
unsigned long tiempo;
long int objetivos[30][2];
Servo srv;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

unsigned long segundo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //------------------------Empieza el ultrasónico
  srv.attach(ussrv);
  srv.write(90);
  pinMode(usout, OUTPUT); pinMode(usin, INPUT);
  //-----------------------Pantalla LCD
  for (int i = rs; i < 8; i++) pinMode(i,OUTPUT);
  lcd.begin(0,0);

}
//------Imprime en la LCD
void imprimirLCD(String texto, int columna, int linea){
  lcd.setCursor(columna,linea);
  lcd.print(texto);
}

//-------------Ordena los objetivos con forme la distancia
void ordenarObjetivos(){
  int i, j, t1,t2;
   
   for (i = encontrados-1 ; i > 0; i--)
      for (j = 0; j < i; j++)
         if (objetivos[j][0] > objetivos[j + 1][0]) {
            t1 = objetivos[j][0];
            t2 = objetivos[j][1];
            objetivos[j][0] = objetivos[j + 1][0];
            objetivos[j][1] = objetivos[j + 1][1];
            objetivos[j + 1][0] = t1;
            objetivos[j + 1][1] = t2;
         }
}
//---------Como no hay librerias dínamicas nativas en arduino usé un matriz para guardar la distancia y los grados que pase el servo
void guardarObjetivos(long int d, long int p) {
  for(int i=0; i <30;i++){
    if(objetivos[i][0]==0){
      objetivos[i][0]=d;
      objetivos[i][1]=p;
      encontrados++;
      break;
    }
  }
}

//------------------Esta función sólo es para ver si sí me imprimió todo como debe de ser.

void imprimirObjetivos(){
   for(int i=0; i <30;i++){
      if(objetivos[i][0]==0)break;
      Serial.print("Distancia: ");
      Serial.println(objetivos[i][0]);
      Serial.print("Grados: ");
      Serial.println(objetivos[i][1]);
   }
}

void leerUS(unsigned long s) {
  digitalWrite(usout, HIGH);
  //delay(s);
  segundo = millis();
  //-----------------------Este while es para darle tiempo al servo de girar x cantidad de grados para
  // no leer el mismo obstáculo dos veces
  while (millis() - segundo < s) {
  }
  digitalWrite(usout, LOW);
  long value = pulseIn(usin, HIGH);
  value = (value * 343) / 20000;
  //-----------------if para no guardar lecturas a 0 cuando no hay nada y random que se puede sustitur con lectura de grados de servo.
  if(value!=0){
   guardarObjetivos(value,random(0,361));

  }
  
}
//--------------------------Funciones iniciales
void mensajeInicio(){
  byte customChar[] = {
 B00111, B01010, B10101, B10000, B10100, B01011, B00111, B00000
  };
  tiempo=millis();
  lcd.createChar(0, customChar);
  lcd.setCursor(0,0);
  lcd.write(byte(0));
  byte customChar1[] = {
  B11100, B01010, B10101, B00001, B00101, B11010, B11100, B00000
  };
  lcd.createChar(1, customChar1);
  lcd.setCursor(1,0);
  lcd.write(byte(1));
  imprimirLCD("GRUPO 06 ACE1",2,0);
  byte customChar2[] = {
  B00001, B00001, B00011, B00010, B10110, B01100, B00100, B00000
  };
  lcd.createChar(2, customChar2);
  lcd.setCursor(15,0);
  lcd.write(byte(2));
  while(millis()-tiempo<100){
      //Código para ver si está bien el esclavo
  }
  lcd.clear();
}

void reincios(){
  recurrencia++;
  lcd.home();
  lcd.print(String(recurrencia));
  lcd.setCursor(1,0);
  lcd.print(" veces iniciado"); 
  tiempo=millis();
  while(millis()-tiempo < 1000){
    
  }
  lcd.clear();
}

void principal(){
  if(millis()< 1000) mensajeInicio();
  reincios();
}

void loop() {
  // Puse 8 por qué tengo 8 obstáculos, pero pienso que podría ponerse por ejemplo cuando el servo haya girado 360 como condicional
  principal();
  /*while(encontrados < 8){
   leerUS(100); 
  }
  ordenarObjetivos();
  imprimirObjetivos();
  //-------Sólo para que haga otra búsqueda, sólo que se cambie al llegar el servo a 360
  encontrados =0;
  delay(10000);*/
}

/*
 * Mensaje
 Recurrencia: 0
  A la espera
  Escaneo 1 
    (pausa)
  Escaneo 2
  Son iguales? no ir a espera.
  Si seguir
  Atacar? no ir a espera
  Si seguir
  Atacar
  Final del ataque
  Regresar a Espera recurrencia 1
 */
