//Only write PWM which is changed ? -- To be done
void run_motors(bool d1, int p1, bool d2, int p2, bool d3, int p3) {
  digitalWrite(dir1, d1);
  digitalWrite(dir2, d2);
  digitalWrite(dir3, d3);

  analogWrite(pwm1, p1);
  analogWrite(pwm2, p2);
  analogWrite(pwm3, p3);
}

//Wheelbase Motor Stop
void stop_motors() {
  analogWrite(pwm1, 0);
  analogWrite(pwm2, 0);
  analogWrite(pwm3, 0);
}

//Arm motor stopped
void stop_arm() {
  analogWrite(throw_P, 0);
}
