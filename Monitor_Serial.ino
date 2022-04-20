int Rele = 7;
String Instruccion;

void setup() {
  pinMode(Rele,OUTPUT);
  Serial.begin(9600);
}

void loop(){
  if(Serial.available() > 0){
    Instruccion = Serial.readString();
    Serial.println(Instruccion);
    }
  if((Instruccion == "apagar") || (Instruccion == "apagado") || (Instruccion == "desactivado")){
      digitalWrite(Rele,HIGH);
  }
  if((Instruccion == "encender") || (Instruccion == "encendido") || (Instruccion == "activado")){
    digitalWrite(Rele,LOW); //Desactiva rele
   }
}
