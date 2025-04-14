int little_fin = 2;
int ring_fin   = 4;
int middle_fin = 7;
int index_fin  = 8;
int thumb      = 12;


void setup() {
  Serial.begin(9600);
  pinMode(little_fin, OUTPUT);
  pinMode(ring_fin, OUTPUT);
  pinMode(middle_fin, OUTPUT);
  pinMode(index_fin, OUTPUT);
  pinMode(thumb, OUTPUT);

}

void loop() {
  if (Serial.available() >= 5)
  {
    digitalWrite(thumb,      Serial.read() == 1 ? HIGH : LOW);
    digitalWrite(index_fin,  Serial.read() == 1 ? HIGH : LOW);
    digitalWrite(middle_fin, Serial.read() == 1 ? HIGH : LOW);
    digitalWrite(ring_fin,   Serial.read() == 1 ? HIGH : LOW);
    digitalWrite(little_fin, Serial.read() == 1 ? HIGH : LOW);
  }

}
