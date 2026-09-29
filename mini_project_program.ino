#define trigA 2
#define echoA 3

#define trigB 4
#define echoB 5

#define redA 6
#define yellowA 7
#define greenA 8

#define redB 9
#define yellowB 10
#define greenB 11

// LDR pins
#define ldrA A0
#define ldrB A1

// Street light LEDs
#define lightA 12
#define lightB 13

// LDR threshold
int threshold = 500;

long getDistance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  long duration = pulseIn(echo, HIGH);
  long distance = duration * 0.034 / 2;
  
  return distance;
}

void setup() {
  Serial.begin(9600);

  pinMode(trigA, OUTPUT); pinMode(echoA, INPUT);
  pinMode(trigB, OUTPUT); pinMode(echoB, INPUT);

  pinMode(redA, OUTPUT); pinMode(yellowA, OUTPUT); pinMode(greenA, OUTPUT);
  pinMode(redB, OUTPUT); pinMode(yellowB, OUTPUT); pinMode(greenB, OUTPUT);

  pinMode(lightA, OUTPUT);
  pinMode(lightB, OUTPUT);
}

void loop() {

  // -------- TRAFFIC SYSTEM --------
  long distA = getDistance(trigA, echoA);
  long distB = getDistance(trigB, echoB);

  Serial.print("Dist A: "); Serial.print(distA);
  Serial.print(" | Dist B: "); Serial.print(distB);

  // -------- STREET LIGHT SYSTEM --------
  int valA = analogRead(ldrA);
  int valB = analogRead(ldrB);

  Serial.print(" | LDR A: "); Serial.print(valA);
  Serial.print(" | LDR B: "); Serial.println(valB);

  // Street Light A
  if (valA < threshold) {
    digitalWrite(lightA, HIGH);
  } else {
    digitalWrite(lightA, LOW);
  }

  // Street Light B
  if (valB < threshold) {
    digitalWrite(lightB, HIGH);
  } else {
    digitalWrite(lightB, LOW);
  }

  // -------- TRAFFIC DECISION --------

  // Road A has more traffic
  if (distA < distB) {
    digitalWrite(greenA, HIGH);
    digitalWrite(redA, LOW);
    digitalWrite(redB, HIGH);
    digitalWrite(greenB, LOW);

    delay(5000);

    digitalWrite(greenA, LOW);
    digitalWrite(yellowA, HIGH);
    delay(2000);
    digitalWrite(yellowA, LOW);
  }

  // Road B has more traffic
  else {
    digitalWrite(greenB, HIGH);
    digitalWrite(redB, LOW);
    digitalWrite(redA, HIGH);
    digitalWrite(greenA, LOW);

    delay(5000);

    digitalWrite(greenB, LOW);
    digitalWrite(yellowB, HIGH);
    delay(2000);
    digitalWrite(yellowB, LOW);
  }
}