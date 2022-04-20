int Rele = 7;
int cant;
void setup() {
  pinMode(Rele,OUTPUT);
  Serial.begin(9600);
}
void loop(){
  cant = analogRead (A0) / 4;
  Serial.println(cant);
  if(cant >= 200){ //Pote de 1Kohm
    digitalWrite(Rele,LOW);
  }else{
    digitalWrite(Rele,HIGH);
  }
}
