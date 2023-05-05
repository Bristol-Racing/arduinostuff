int PWM_pin = 3;
int PWM_pct = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PWM_pin, OUTPUT);
}

void loop() {
  char buffer[] = {' ', ' ', ' ', ' ', ' ', ' ', ' '}; // Receive up to 7 bytes
  while (!Serial.available()); // Wait for characters
  Serial.readBytesUntil('\n', buffer, 7);
  int PWM_pct = atoi(buffer);

  if (PWM_pct > 255) PWM_pct = 255;
  if (PWM_pct <= 0) PWM_pct = 0;

  analogWrite(PWM_pin, PWM_pct);

}
