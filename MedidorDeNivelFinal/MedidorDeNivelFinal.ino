#include <Ultrasonic.h> // Biblioteca do ultrasonico
#include <LiquidCrystal.h> // biblioteca do visor LCD

/*
  defines te ajudam a configurar seu projeto
  PROF_RES = profundidade do reservatório (CM)
  VOL_RES = volume do reservatório (m³)
*/

#define PROF_RES 11,5  // mude o número e recompile na placa
#define VOL_RES 0,002   // mude o número e recompile na placa


// Pinagem do ULTRASONIC -- ATENÇÃO --
Ultrasonic ultrasonic(9, 8); // inicialização do objeto ultrasonic

// Pinagem do LCD 16x2 -- ATENÇÃO PARA ESSA PINAGEM --
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // inicialização do objeto lcd

float leituraUltra = 0; // para armazenar leitura

void setup (){
  lcd.begin(16, 2); // INICIALIZANDO VISOR DE 16x2
  Serial.begin(9600);

  apresentacao(); // mensagem de inicialização
  delay(2000); // 2s para começar
}

//laço principal (executado indefinidamente)
void loop(){
  leituraUltra = ultrasonic.distanceRead();
  mostraResultado();
  delay(1000);
}

void mostraResultado() {
  static float nivelCm = 0; // nivel em cm do reservatorio
  static float nivelPorc = 0; // nivel em porcentagem do reservatório
  static float nivelVol = 0; // nivel em volume cúbico do reservatório
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Distancia (cm)");
  lcd.setCursor(0,1);
  lcd.print(leituraUltra);
  lcd.print(" cm");
  Serial.print("Distancia em CM: ");
  Serial.println(leituraUltra);
  
  delay(1500); // DELAY PARA MUDAR AS INFORMAÇÕES DO LEITOR

  // condições de acordo com o range do ULTRASONIC
  if (leituraUltra < 3 && leituraUltra >  2) {
    leituraUltra = 0; // reservatorio cheio
  } else if(leituraUltra < 400 && leituraUltra > 397) {
    leituraUltra = PROF_RES; // reservatório vazio
  } else {
    leituraUltra = leituraUltra - 2; // tirando marca de posição do sensor
  }
   
  if (leituraUltra <= PROF_RES) { // O calculo so acontece se esse IF der verdadeiro
    nivelCm = PROF_RES - leituraUltra; // calculo do nivel
    nivelPorc = ((nivelCm*100)/PROF_RES); // (nivelCm * 100) / profundidade total do reservatório
    //nivelVol = ((nivelPorc*VOL_RES)/100); // DESCOMENTE PARA USAR
  }
  
  Serial.println();
  Serial.print("Profundidade Total: ");
  Serial.print(PROF_RES);
  Serial.print(" cm");
  Serial.println();
  Serial.print("Profundidade Atual: ");
  Serial.print(nivelCm);
  Serial.print(" cm\t");
  Serial.print(nivelPorc);
  Serial.print(" %");
  Serial.println();
  // parte do volume, descomente para usar
 /*Serial.print("Volume Total: ");
  Serial.print(VOL_RES);
  Serial.print(" m³");
  Serial.println();
  Serial.print("Volume Atual: ");
  Serial.print(nivelVol);
  Serial.println();*/
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" cm - Nivel - %");
  lcd.setCursor(0,1);
  lcd.print(nivelCm);
  lcd.print(" - ");
  lcd.print(nivelPorc);

// parte do volume, descomente para usar
  /*delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tot - Vol - At");
  lcd.setCursor(0,1);
  lcd.print(VOL_RES);
  lcd.print(" - ");
  lcd.print(nivelVol);*/
}

void apresentacao(){
  Serial.println("-- Medidor de nível de água para reservatórios --");
  Serial.println();
  Serial.println("Inicializando...");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Medidor para");
  lcd.setCursor(0,1);
  lcd.print("Reservatorios");
}

