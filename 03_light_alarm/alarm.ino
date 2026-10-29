int photoPin = 0;
int buzzer = 4;
int buttonPin = 12;
int photoVal = 0;  //photocell value
int buttonVal = 0;
int cnt = 0;  //to stop looping

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(photoPin, INPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (cnt < 1) {
    photoVal = analogRead(photoPin);
    Serial.println(photoVal);
    delay(1000);

    if (photoVal < 600) {  //set a proper value you want
      digitalWrite(buzzer, HIGH);
    } else {
      digitalWrite(buzzer, LOW);
    }

    buttonVal = digitalRead(buttonPin);

    if (buttonVal == HIGH) {
      digitalWrite(buzzer, LOW);
      cnt = 1;
    }
  }
}
