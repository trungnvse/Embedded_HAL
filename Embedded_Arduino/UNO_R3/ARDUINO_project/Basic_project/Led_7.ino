/*
 * ================================================================================*
 * tiktok : trungnvse
 * ================================================================================*                           
 */

const int Leds[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
const int numof_Leds = sizeof(Leds) / sizeof(Leds[0]);

void run_leds_1()
{
  for (int i = 0; i < numof_Leds; i++) {
  digitalWrite(Leds[i], HIGH);
  delay(500);
  digitalWrite(Leds[i], LOW);
  }
}

void setup() {
  for (int i = 0; i < numof_Leds; i++) {
  pinMode(Leds[i], OUTPUT);    
  }
}

void loop() {
  run_leds_1();
  delay(1000);
}
 