#define pinSensorA 12
int checkSensor;
bool autoWindow; //Verifica se função auto está ligada ou desligada

int touchOnOff = 15;
int touchAuto = 4;
int LedAuto = 14;

int ValOnOff,valAuto;
long lastmsOnOff,lastmsAuto;

int releJanela = 12;

void autoSensorWindow(){
  checkSensor = analogRead(pinSensorA);
  Serial.print("Sensor chuva:");
  Serial.print(checkSensor);
  Serial.print("  ");
  Serial.print("Atuador:");
  if(checkSensor > 700){
    Serial.println("Janela Aberta");
  }
  else Serial.print("Janela Fechada");
}

void listenPin(){ //ouve pinos touch fisicos
  ValOnOff = touchRead(touchOnOff);
  if(touchOnOff < 20){ //verifica se o valor lido é maior que 0    
      if (millis() - lastmsOnOff > 150) digitalWrite(releJanela,!digitalRead(releJanela));
   }
   
  valAuto = touchRead(touchAuto);
  if(valAuto < 20){ //verifica se o valor lido é maior que 0    
      if (millis() - lastmsAuto > 150){
        autoWindow = !autoWindow;  
        digitalWrite(LedAuto,!digitalRead(LedAuto));
      }
   }
  delay(100);
}

void setup() {
  Serial.begin(115200);
  autoWindow = true;
  pinMode(LedAuto,OUTPUT);
  digitalWrite(LedAuto,HIGH);
  
  pinMode(releJanela,OUTPUT);
  digitalWrite(releJanela,HIGH);
  
  pinMode(touchOnOff,INPUT);
  pinMode(touchAuto,INPUT);

  lastmsOnOff = 0;
  lastmsAuto = 0;
  
}

void loop() {
  listenPin();
  if(autoWindow == true) autoSensorWindow();
}
