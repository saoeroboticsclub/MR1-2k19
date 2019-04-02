void kiwi() {
  x = ps2.Analog(PSS_RX);
  y = ps2.Analog(PSS_RY);

  (x == 128) ? (x = 0) : (x > 128) ? (x = map(x, 129, 255, 1, 255)) : (x = map(x, 127, 0, -1, -255));
  (y == 127) ? (y = 0) : (y < 127) ? (y = map(y, 126, 0, 1, 255)) : (y = map(y, 128, 255, -1, -255));

  if (y == -1)  y = 0;
  if (x == 0 && y == 0) return;

  if (x == 255 && y == -255 && px == 0 && py == 0) {
    x = px; y = py;
    return;
  }

  Serial.println(String(x) + " " + String(y));
  if ( y > 0 ) {

    while (y > 0) {
      kiwi_calculator();
      
      if (ps2.Button(PSB_L1)) {
        Serial.println("Steering Anti-Clockwise");
        run_motors(m1ac, spd, m2c, (spd * 0.4), m3ac, (spd * 0.7));
      }

      else if (ps2.Button(PSB_R1)) {
        Serial.println("Steering Clockwise");
        run_motors(m1ac, (spd * 0.5), m2c, spd, m3c, (spd * 0.7));
      }

      else {
        Serial.println("FORWARD");
        forward_12();
      }
    }
  }

  else if ( y < 0) {
    Serial.println("BACKWARD");
    backward_12();
  }

  else if ( x > 0) {
    Serial.println("RIGHT");
    right_12();
  }

  else {
    Serial.println("LEFT");
    left_12();
  }
  px = x;
  py = y;
  //  if (x == 0 && y == 0) return;
  //
  //  vx = cos(angle) * magnitude;
  //  vy = sin(angle) * magnitude;
  //
  //  //Set motor speeds
  //  w1 = 0.5 * vx + sqrt_var * vy;
  //  w2 = 0.5 * vx - sqrt_var * vy;
  //  w3 = -vx;
  //
  //  //Set motor directions
  //  md1 = w1 > 0 ? 0 : 1;
  //  md2 = w2 > 0 ? 0 : 1;
  //  md3 = w3 > 0 ? 0 : 1;
  //
  //  digitalWrite(dir1, md1);
  //  digitalWrite(dir2, md2);
  //  digitalWrite(dir3, md3);
  //
  //  w1 = constrain(map(abs(w1), 0, 255, 0, spd), 0, spd);
  //  w2 = constrain(map(abs(w2), 0, 255, 0, spd), 0, spd);
  //  w3 = constrain(map(abs(w3), 0, 255, 0, spd), 0, spd);
  //
  //  analogWrite(pwm1, w1);
  //  analogWrite(pwm2, w2);
  //  analogWrite(pwm3, w3);
  //
  //  if (w1 || w2 || w3) {
  //    Serial.print(" " + String(md1) + " " + String(md2) + " " + String(md3) + " ");
  //    Serial.println(String(w1) + " " + String(w2) + " " + String(w3));
  //  }
}


void kiwi_calculator() {
  ps2.read_gamepad();
  delay(30);

  x = ps2.Analog(PSS_RX);
  y = ps2.Analog(PSS_RY);

  (x == 128) ? (x = 0) : (x > 128) ? (x = map(x, 129, 255, 1, 255)) : (x = map(x, 127, 0, -1, -255));
  (y == 127) ? (y = 0) : (y < 127) ? (y = map(y, 126, 0, 1, 255)) : (y = map(y, 128, 255, -1, -255));

  if (y == -1)  y = 0;
  if (x == 0 && y == 0) return;

  if (x == 255 && y == -255 && px == 0 && py == 0) {
    x = px; y = py;
    return;
  }
}

