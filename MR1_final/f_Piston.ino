void piston1close() {
  digitalWrite(piston_1a, LOW);
  digitalWrite(piston_1b, HIGH);
  Serial.println("Piston 1 close");
}

void piston1open() {
  digitalWrite(piston_1a, HIGH);
  digitalWrite(piston_1b, LOW);
  Serial.println("Piston 1 open");
}

void piston2close() {
  digitalWrite(piston_2a, LOW);
  digitalWrite(piston_2b, HIGH);
  Serial.println("Piston 2 close");
}

void piston2open() {
  digitalWrite(piston_2a, HIGH);
  digitalWrite(piston_2b, LOW);
  Serial.println("Piston 2 open");
}
