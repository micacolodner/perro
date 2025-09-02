//GENERAL
#include <Wire.h>
//TELEGRAM
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
//EEPROM
#include <Preferences.h>

//WIFI
const char* ssid = "MECA-IoT"; 
const char* password = "IoT$2025"; 
//Token del bot
#define BOTtoken "8025037753:AAFpbCTQcwS2Zl1ebt8SktN_9j35VvIw4xY"
//ID del chat con el bot
#define CHAT_ID "6235002183"  
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

//EEPROM
Preferences umbral_eeprom;

//VARIABLES
int checkeo = 0;
unsigned long contando = 0;
unsigned long intervalo = 1000;

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

//LEDS
#define LED1 5
#define LED2 18
#define LED3 19

//SENSORES Y LDR
#define MQA1 32
#define MQA2 33
#define LDR 35

void setup() {
 
Serial.begin(115200);

  pinMode(BOT_PANTALLA, INPUT_PULLUP);
  pinMode(BOT_SELECT, INPUT_PULLUP);
  pinMode(BOT_SUMA, INPUT_PULLUP);
  pinMode(BOT_RESTA, INPUT_PULLUP);
  pinMode(BOT, INPUT_PULLUP);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  pinMode(LDR, INPUT);

  //WIFI
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print("-"); 
  }
  Serial.println("WiFi conectado"); 
  bot.sendMessage(CHAT_ID, "BOT iniciado", ""); 

  //EEPROM
  VU_eeprom.begin("valor-VU", true);
  VU = VU_eeprom.getFloat("umbral", 0);
  VU_eeprom.end();
} 

void loop() {

  unsigned long ahora = millis();

  if (temp > umbral && checkeo == 0) 
  { 
    checkeo = 1; 
    bot.sendMessage(CHAT_ID, "Se superó el umbral, TEMP ACTUAL: " + String(temp), ""); 
  }
  if (temp < umbral) 
  {
    checkeo = 0; 
  }
  if ((ahora - contando) >= intervalo) 
  { 
    contando = ahora;

    int no_leidos = bot.getUpdates(bot.last_message_received + 1); 
    if (no_leidos > 0) 
    {
      String recibido = bot.messages[0].text;

      if (recibido == "TEMP")
      {
        bot.sendMessage(CHAT_ID, "TEMP ACTUAL: " + String(temp), ""); 
      }
    }
  }
}
