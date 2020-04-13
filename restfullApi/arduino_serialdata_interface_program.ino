int x=0;
void setup() {
  
  Serial.begin(9600);
}

void loop() {
 
  Serial.println("transmitter: "+(String)x+" reciever.");
  delay(1000);                  
                          
}
