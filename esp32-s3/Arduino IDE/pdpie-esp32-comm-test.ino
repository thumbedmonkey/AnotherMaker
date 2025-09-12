//the laziest automated chat test 

void setup() {
  Serial.begin(9600);
}

void loop() {
  String message = "Hello from Arduino 1. Random number: ";
  long randomNumber = random(0, 101);
  message += String(randomNumber);
  
  Serial.print(message);
  Serial.println();
  
  delay(30000);
}


/*
//arduino 2
void setup() {
  Serial.begin(9600);
}

void loop() {
  String message = "Hello from Arduino 2. Random number: ";
  long randomNumber = random(100, 201);
  message += String(randomNumber);
  
  Serial.print(message);
  Serial.println();
  
  delay(30000);
}
*/