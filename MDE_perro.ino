//LIBRERIAS
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_AHT10.h>
//CONFIGURA LIQUID
LiquidCrystal_I2C lcd(0x27, 16, 2);
//CONFIGURA AHT10
Adafruit_AHT10 aht;
//ESTADOS
#define PANTALLA1 1
#define CONFIRM_BOT_PANTALLA2 2
#define PANTALLA2 3
#define CONFIRM_BOT_SELECT 4
#define UMBRAL 5
#define SUMA 6
#define RESTA 7
#define RELE 8
#define RELE_ESPERA 9
#define RELE_CAMBIO 10
#define CONFIRM_BOT_PANTALLA1 11
#define GUARDAR 12
#define CONFIRM_BOT_PANTALLA12 13
#define PANTALLA12 14
#define CONFIRM_BOT_PANTALLA212 15
#define CONFIRM_12 16
#define CONFIRM_ATRAS 17

int ESTADO = PANTALLA1;
int contando_select = 0;

//PINES
//BOTONES
#define BOT_PANTALLA 15
int botpantalla;
#define BOT_SELECT 23
int botselect;
#define BOT_SUMA 4
int botsuma;
#define BOT_RESTA 16
int botresta;
#define BOT_SAVE 17
int botsave;

unsigned long contando = 0;
//RELE
#define PIN_RELE 25

//UMBRALES
float umbral_gas1 = 0.0;
float umbral_gas2 = 0.0;
float umbral_tempyhum = 0.0;
float umbral_ldr = 0.0;

//SENSORES y LDR
#define MQA1 32
float GAS1 = 0.0;
#define MQA2 33
float GAS2 = 0.0;
#define LDR 35
float LDR = 0.0;
#define TEMYHUM
float TYH = 0.0;

void setup() {
  Serial.print("PROGRAMA INICIADO");
  Serial.begin(115200);
  pinMode(BOT_PANTALLA, INPUT_PULLUP);
  pinMode(BOT_SELECT, INPUT_PULLUP);
  pinMode(BOT_SUMA, INPUT_PULLUP);
  pinMode(BOT_RESTA, INPUT_PULLUP);
  pinMode(BOT_SAVE, INPUT_PULLUP);

  pinMode(PIN_RELE, OUTPUT);
  digitalWrite(PIN_RELE, LOW);

  lcd.init();  //inicializa el lcd
  aht.begin();
}

void MDE() {

  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);

  botpantalla = digitalRead(BOT_PANTALLA);
  botselect = digitalRead(BOT_SELECT);
  botsuma = digitalRead(BOT_SUMA);
  botresta = digitalRead(BOT_RESTA);
  botsave = digitalRead(BOT_SAVE);
  ldr = analogRead(LDR);
  GAS1 = analogRead(GAS1);
  GAS2 = analogRead(GAS2);
  TYH = analogRead()

  switch (ESTADO) {
    case
  }
    /*switch (ESTADO) {

    case PANTALLA1:
      Serial.println("PANTALLA1");
      lcd.backlight();
      lcd.setCursor(0, 0);
      lcd.print("M1: 0.0 M2:0.0");
      lcd.setCursor(0, 1);
      lcd.print("A:0.0 L:0.0");
      if (botpantalla == LOW) {
        contando = millis();
        ESTADO = CONFIRM_BOT_PANTALLA2;
      }
      if (botsave == LOW) {
        contando = millis();
        ESTADO = CONFIRM_BOT_PANTALLA12;
      }
      break;

    case CONFIRM_BOT_PANTALLA12:
      Serial.println("CONFIRM_BOT_PANTALLA12");
      if (botsave == HIGH) {
        ESTADO = PANTALLA12;
        lcd.clear();
        lcd.backlight();
        lcd.setCursor(0, 0);
        lcd.print("RELE: OFF");
        lcd.setCursor(0, 1);
        lcd.print("GMT:0");
      }
      break;

    case PANTALLA12:
      Serial.println("PANTALLA12");
      if ((millis() - contando) >= 1000 && botsave == LOW) {
        contando = 0;
        ESTADO = CONFIRM_BOT_PANTALLA212;
        lcd.clear();
        lcd.backlight();
        lcd.setCursor(0, 0);
        lcd.print("RELE: OFF");
        lcd.setCursor(0, 1);
        lcd.print("GMT:0");
      }
      if (botpantalla == LOW) {
        ESTADO = CONFIRM_ATRAS;
        lcd.clear();
        lcd.backlight();
        lcd.setCursor(0, 0);
        lcd.print("RELE: OFF");
        lcd.setCursor(0, 1);
        lcd.print("GMT:0");
      }
      break;

    case CONFIRM_ATRAS:
      Serial.println("CONFIRM ATRAS");
      if (botpantalla == HIGH) {
        ESTADO = PANTALLA2;
      }
      break;

    case CONFIRM_BOT_PANTALLA212:
      Serial.println("CONFIRM_BOT_PANTALLA212");
      if (botsave == HIGH) {
        ESTADO = PANTALLA1;
      }
      if (botpantalla == LOW) {
        ESTADO = CONFIRM_ATRAS;
      }
      break;

    case CONFIRM_BOT_PANTALLA2:
      Serial.println("PANTALLA CONFIRM PANTALLA 2");
      if (botpantalla == HIGH) {
        ESTADO = PANTALLA2;
      }
      break;

    case PANTALLA2:
      Serial.println("PANTALLA2");
      if ((millis() - contando) >= 1000 && botselect == LOW) {
        contando = 0;
        lcd.backlight();
        lcd.setCursor(0, 0);
        lcd.print("M1: 0.0 M2:0.0");
        lcd.setCursor(0, 1);
        lcd.print("AT: " "L:0.0");
        ESTADO = CONFIRM_BOT_SELECT;
      }
      if (botpantalla == LOW) {
        ESTADO = CONFIRM_12;
      }
      break;

    case CONFIRM_12:
      Serial.print("CONFIRM 12");
      if (botpantalla == HIGH) {
        ESTADO = PANTALLA1;
      }
      break;

    case CONFIRM_BOT_SELECT:
      Serial.println("CONFIRM BOT SELECT");
      if (botselect == HIGH) {
        contando_select++;
        if (contando_select >= 5) {
          contando_select = 0;
        }
        if (contando_select == 4) {
          ESTADO = RELE;
        } else {
          ESTADO = UMBRAL;
        }
      }
      break;

    case UMBRAL:
      Serial.println("UMBRAL");
      if (botselect == LOW) {
        ESTADO = CONFIRM_BOT_SELECT;
      }
      if (botsuma == LOW) {
        ESTADO = SUMA;
      }
      if (botresta == LOW) {
        ESTADO = RESTA;
      }
      if (botsave == LOW) {
        ESTADO = GUARDAR;
      }
      break;

    case SUMA:
      Serial.println("SUMA");
      if (botsuma == HIGH) {
        if (contando_select == 0) {
          umbral_gas1 += 1;
        }
        if (contando_select == 1) {
          umbral_gas2 += 1;
        }
        if (contando_select == 2) {
          umbral_tempyhum += 1;
        }
        if (contando_select == 3) {
          umbral_ldr += 1;
        }
        ESTADO = UMBRAL;
      }
      break;

    case RESTA:
      Serial.println("RESTA");
      if (botresta == HIGH) {
        if (contando_select == 0) {
          umbral_gas1 -= 1;
        }
        if (contando_select == 1) {
          umbral_gas2 -= 1;
        }
        if (contando_select == 2) {
          umbral_tempyhum -= 1;
        }
        if (contando_select == 3) {
          umbral_ldr -= 1;
        }
        ESTADO = UMBRAL;
      }
      break;

    case RELE:
      Serial.println("RELE");
      if (botsuma == LOW || botresta == LOW) {
        ESTADO = RELE_ESPERA;
      }
      if (botsave == LOW) {
        ESTADO = GUARDAR;
      }
      break;

    case RELE_ESPERA:
      Serial.println("RELE ESPERA");
      if (botsuma == HIGH || botresta == HIGH) {
        ESTADO = RELE_CAMBIO;
      }
      break;

    case RELE_CAMBIO:
      Serial.println("RELE CAMBIO");
      digitalWrite(PIN_RELE, !digitalRead(PIN_RELE));
      ESTADO = RELE;
      break;

    case GUARDAR:
      Serial.println("GUARDAR");
      if (botsave == HIGH) {
        //printear el "guardado" y guardar en el eeprom
        ESTADO = PANTALLA1;
      }
      break;
  }*/
}

void loop() {
  // put your main code here, to run repeatedly:
  MDE();
}
