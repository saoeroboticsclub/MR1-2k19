#include <PS2X_lib.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>

#define dir1 7      //1->clockwise,0->Anticlockwise
#define dir2 13
#define dir3 11

#define pwm1 6
#define pwm2 12
#define pwm3 10

#define throw_D1 23      //1->forward,0->backward 
#define throw_P1 4

#define piston_1a 33
#define piston_1b 31

#define piston_2a 29
#define piston_2b 27

#define ir1 39          //0->normally  1->detecting

#define PS2_DAT A0
#define PS2_CMD A1
#define PS2_SEL A2
#define PS2_CLK A3
#define pressures false
#define rumble  false

#define sqrt_var sqrt(3.0)/2.0

//void(*resetFunc)(void) = 0;

int x = 128, y = 127, px = 0, py = 0;
float angle, magnitude;
float vx, vy;
float w1, w2, w3;
int md1, md2, md3;
int spd = 180;
bool m1c = 1, m1ac = 0, m2c = 1, m2ac = 0, m3ac = 0, m3c = 1;
int error = 1, count, count1;
const int rs = 53, en = 51, d4 = 49, d5 = 47, d6 = 45, d7 = 43;
bool flag = 1, ir1_flag, l_flag, r_flag;
float i, j;
int check = 0;
unsigned long last;
int lcd_flag = 0;

PS2X ps2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {

  Serial.begin(57600);
  lcd.begin(20, 4);

  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(dir3, OUTPUT);

  pinMode(throw_D1, OUTPUT);

  pinMode(piston_1a, OUTPUT);
  pinMode(piston_1b, OUTPUT);
  pinMode(piston_2a, OUTPUT);
  pinMode(piston_2b, OUTPUT);
  pinMode(ir1, INPUT_PULLUP);

  /* A 0 on the 0th byte indicates that arduino was reset automatically and latest values of motor speed and throwing status
      is restored.  */
  /*if (EEPROM[0] == 0) {
    spd = EEPROM.read(4);
    count = EEPROM.read(8);
    }
    EEPROM.update(0, 0);
    delay(50);*/

  piston1close();
  piston2close();
  stop_motor();
  stop_();
  waiting();

}

void loop()
{
  lcd_func();
  ps2.read_gamepad();
  delay(30);
  Read_button();
}
