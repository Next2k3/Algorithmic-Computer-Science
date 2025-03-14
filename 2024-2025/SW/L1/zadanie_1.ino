#define LED 13

volatile char serialInput;
int unitTime = 250; 

const char* morseTable[26] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", 
  "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", 
  "..-", "...-", ".--", "-..-", "-.--", "--.."
};

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    serialInput = Serial.read();
    
    if (serialInput >= 'a' && serialInput <= 'z') {
      blinkMorse(serialInput);
    }
  }
}

void blinkMorse(char letter) {
  int index = letter - 'a'; 
  Serial.print(letter);
  Serial.print(": ");
  Serial.println(morseTable[index]);

  for (const char* p = morseTable[index]; *p; p++) {
    digitalWrite(LED, HIGH);
    delay(*p == '.' ? unitTime : unitTime * 3); 
    digitalWrite(LED, LOW);
    delay(unitTime);
  }
  
  delay(unitTime * 3); 
}
