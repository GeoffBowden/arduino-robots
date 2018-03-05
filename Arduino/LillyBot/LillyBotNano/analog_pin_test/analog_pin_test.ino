void setup() {
  // put your setup code here, to run once:
  pinMode ( A1, OUTPUT );
  Serial.begin( 9600 );
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite( A1, HIGH );
  Serial.println("on");
  delay(1000);
  digitalWrite( A1, LOW) ;
  Serial.println("off");
  delay( 1000 ) ;
}
