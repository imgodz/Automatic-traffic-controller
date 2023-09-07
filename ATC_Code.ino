// PINS

// Trig Pins
const int Trig_North = 24;
const int Trig_East = 28;
const int Trig_South = 32;
const int Trig_West = 36;

// Echo Pins
const int Echo_North = 25;
const int Echo_East = 29;
const int Echo_South = 33;
const int Echo_West = 37;

// Red Lights
const int Red_N = 38;
const int Red_E = 41;
const int Red_S = 44;
const int Red_W = 47;

// Yellow Lights
const int Yellow_N = 39;
const int Yellow_E = 42;
const int Yellow_S = 45;
const int Yellow_W = 48;

// Green Lights
const int Green_N = 40;
const int Green_E = 43;
const int Green_S = 46;
const int Green_W = 49;

const int buzzer = 7;

const int led = 3;

const int sensorPin = A0;

// Other Variables
float duration, distance;
int current;
int count = 0;
bool traffic;
int prev = 4;
bool north, east, west, south;
int sensorValue = 0;

void setup() {
  Serial.begin(9600);
  pinMode(Trig_North, OUTPUT);
  pinMode(Trig_East, OUTPUT);
  pinMode(Trig_South, OUTPUT);
  pinMode(Trig_West, OUTPUT);
  pinMode(Echo_North, INPUT);
  pinMode(Echo_East, INPUT);
  pinMode(Echo_South, INPUT);
  pinMode(Echo_West, INPUT);
  pinMode(Red_N, OUTPUT);
  pinMode(Red_E, OUTPUT);
  pinMode(Red_S, OUTPUT);
  pinMode(Red_W, OUTPUT);
  pinMode(Yellow_N, OUTPUT);
  pinMode(Yellow_E, OUTPUT);
  pinMode(Yellow_S, OUTPUT);
  pinMode(Yellow_W, OUTPUT);
  pinMode(Green_N, OUTPUT);
  pinMode(Green_E, OUTPUT);
  pinMode(Green_S, OUTPUT);
  pinMode(Green_W, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {

  Serial.print("Begin\n");


  digitalWrite(Red_N, HIGH);
  digitalWrite(Red_E, HIGH);
  digitalWrite(Red_S, HIGH);
  digitalWrite(Red_W, HIGH);
  delay(20);

  sensorValue = analogRead(sensorPin);
  Serial.println("Sensor o/p: ");
  Serial.print(sensorValue);
  Serial.print("\n");

  if (sensorValue < 100) {
    digitalWrite(led, HIGH);
    delayMicroseconds(500);
  }
  else {
    digitalWrite(led, LOW);
  }

  current = Select_Road(prev);
  if (current == 1) {
    traffic = Check_Traffic(Trig_North, Echo_North);
    if (traffic) {
      Lights_North();
      count = count + 1;
    }
    prev = 1;
    return;
  } else if (current == 2) {
    if (Check_Traffic(Trig_East, Echo_East)) {
      Lights_East();
      count = count + 1;
    }
    prev = 2;
  } else if (current == 3) {
    if (Check_Traffic(Trig_South, Echo_South)) {
      Lights_South();
      count = count + 1;
    }
    prev = 3;
  } else if (current == 4) {
    if (Check_Traffic(Trig_West, Echo_West)) {
      Lights_West();
      count = count + 1;
    }
    prev = 4;
  } else {
    return;
  }
  if (count == 4) {
    peds_crossing();
    count = 0;
  }
}

float Check_Traffic(float Trig, float Echo) {
  delay(10);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  float duration_func = pulseIn(Echo, HIGH);
  float distance_func = 0.017 * duration_func;
  Serial.print("Distance\n");
  Serial.print(distance_func);
  Serial.print("\n");
  delay(10);
  if (distance_func <= 7 && distance_func >= 1) {
    return true;
  } else {
    return false;
  }
}

void peds_crossing() {
  for (int i = 0; i <= 10; i++) {
    tone(buzzer, 5000);  // Send 1KHz sound signal...
    delay(500);          // ...for 1 sec
    noTone(buzzer);      // Stop sound...
    delay(500);
  }
}



int Select_Road(int prev) {
  int Current_func;
  Serial.print("Selecting\n");
  if (prev == 4) {
    Current_func = 1;
  } else if (prev == 1) {
    Current_func = 2;
  } else if (prev == 2) {
    Current_func = 3;
  } else if (prev == 3) {
    Current_func = 4;
  }
  return Current_func;
}

void Lights_North() {
  digitalWrite(Red_N, LOW);
  digitalWrite(Yellow_N, HIGH);
  delay(1000);
  digitalWrite(Yellow_N, LOW);
  digitalWrite(Green_N, HIGH);
  for (int i = 2; i <= 10; i += 2) {
    bool now = Check_Traffic(Trig_North, Echo_North);
    delay(2000);
    if (now) {
      continue;
    } else {
      break;
    }
  }
  digitalWrite(Green_N, LOW);
  digitalWrite(Yellow_N, HIGH);
  delay(1000);
  digitalWrite(Red_N, HIGH);
  digitalWrite(Yellow_N, LOW);
}

void Lights_East() {
  digitalWrite(Red_E, LOW);
  digitalWrite(Yellow_E, HIGH);
  delay(1000);
  digitalWrite(Yellow_E, LOW);
  digitalWrite(Green_E, HIGH);
  for (int i = 2; i <= 10; i += 2) {
    bool now = Check_Traffic(Trig_East, Echo_East);
    delay(2000);
    if (now) {
      continue;
    } else {
      break;
    }
  }
  digitalWrite(Green_E, LOW);
  digitalWrite(Yellow_E, HIGH);
  delay(1000);
  digitalWrite(Red_E, HIGH);
  digitalWrite(Yellow_E, LOW);
}

void Lights_South() {
  digitalWrite(Red_S, LOW);
  digitalWrite(Yellow_S, HIGH);
  delay(1000);
  digitalWrite(Yellow_S, LOW);
  digitalWrite(Green_S, HIGH);
  for (int i = 2; i <= 10; i += 2) {
    bool now = Check_Traffic(Trig_South, Echo_South);
    delay(2000);
    if (now) {
      continue;
    } else {
      break;
    }
  }
  digitalWrite(Green_S, LOW);
  digitalWrite(Yellow_S, HIGH);
  delay(1000);
  digitalWrite(Red_S, HIGH);
  digitalWrite(Yellow_S, LOW);
}

void Lights_West() {
  digitalWrite(Red_W, LOW);
  digitalWrite(Yellow_W, HIGH);
  delay(1000);
  digitalWrite(Yellow_W, LOW);
  digitalWrite(Green_W, HIGH);
  for (int i = 2; i <= 10; i += 2) {
    bool now = Check_Traffic(Trig_West, Echo_West);
    delay(2000);
    if (now) {
      continue;
    } else {
      break;
    }
  }
  digitalWrite(Green_W, LOW);
  digitalWrite(Yellow_W, HIGH);
  delay(1000);
  digitalWrite(Red_W, HIGH);
  digitalWrite(Yellow_W, LOW);
}
