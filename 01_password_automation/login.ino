#include <SPI.h>
#include <MFRC522.h>
#include <Keyboard.h>

#define SS_PIN 10
#define RST_PIN 5

MFRC522 mfrc522(SS_PIN, RST_PIN);
char ctrlKey = KEY_RETURN;

void setup() {
  Serial.begin(9600);
  Keyboard.begin();
  SPI.begin();
  mfrc522.PCD_Init();
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));  //serial monitor

  Keyboard.press(ctrlKey);
  Keyboard.release(ctrlKey);
  delay(300);

  for (byte i = 0; i < 4; i++) {
    Keyboard.print(mfrc522.uid.uidByte[i], HEX);
  }

  Keyboard.releaseAll();
  delay(200);

  Keyboard.press(ctrlKey);
  Keyboard.releaseAll();
}
