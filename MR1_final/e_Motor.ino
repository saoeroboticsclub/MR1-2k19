void run_motor(bool d1, int p1, bool d2, int p2, bool d3, int p3) {
  digitalWrite(dir1, d1);
  digitalWrite(dir2, d2);
  digitalWrite(dir3, d3);

  analogWrite(pwm1, p1);
  analogWrite(pwm2, p2);
  analogWrite(pwm3, p3);
}

//Wheelbase Motor Stop
void stop_motor() {
  analogWrite(pwm1, 0);
  analogWrite(pwm2, 0);
  analogWrite(pwm3, 0);
  // Serial.println("Motor stop");
}

//Arm motor stopped
void stop_() {
  //   Serial.println("Motor stop");
  analogWrite(throw_P1, 0);
}
