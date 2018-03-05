
const int pingPin = 3;
const int readPin = 4;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  pinMode(pingPin, OUTPUT);
  pinMode(readPin, INPUT);
}

void loop() {
  long mm;
  mm = readDistance();
  // convert the time into a distance
  Serial.print(mm);
  Serial.print("mm");
  Serial.println();

  delay(500);
}


long readDistance()
{
  long duration = 0;
  primeSensor();
  duration = pulseIn(readPin, HIGH);
  return microsecondsToTenthsOfMillimetres( duration /10 );
}

void primeSensor()
{
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
}

long microsecondsToTenthsOfMillimetres(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  //return (( microseconds * 100 ) / 29 / 2) ;
  return ( ( microseconds * 100 ) / 58 ) ;
}
