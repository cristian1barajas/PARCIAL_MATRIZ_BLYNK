#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_NeoPixel.h>

#define PIN 2
#define NUMPIXELS 16

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

char auth[] = "efe7f987c2534c0497aa09d2a65f1eec";
char ssid[] = "BotLAB";
char pass[] = "00003322";

int my_Array[4][4];
int Count = 0;

long randNumber;

void Matrix_Created() {
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      my_Array[i][j] = Count;
      Count++;
  }
}

  int Change = my_Array[1][0];
  my_Array[1][0] = my_Array[1][3];
  my_Array[1][3] = Change;

  Change = my_Array[1][1];
  my_Array[1][1] = my_Array[1][2];
  my_Array[1][2] = Change;

  Change = my_Array[3][0];
  my_Array[3][0] = my_Array[3][3];
  my_Array[3][3] = Change;

  Change = my_Array[3][1];
  my_Array[3][1] = my_Array[3][2];
  my_Array[3][2] = Change;

  Serial.print("\n");

  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      Serial.print(my_Array[i][j]);
      Serial.print(" ");
    }
    Serial.print("\n");
  }
}

char Move(int x, int y) {
 Serial.print("X = ");
 Serial.print(x);
 Serial.print("; Y = ");
 Serial.println(y);

 if (x > 1000) {
   return 'R';
 } else if (x < 24) {
   return 'L';
 } else if (y > 1000) {
   return 'U';
 } else if (y < 24) {
   return 'D';
 } else {
   return 'X';
 }
}

void Random_Position() {
  randomSeed(analogRead(A0));
  randNumber = random(0, 16);
  Serial.println(randNumber);

  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      if (randNumber == my_Array[i][j]) {
        pixels.setPixelColor(my_Array[i][j], pixels.Color(0, 150, 0));
        pixels.show();
      }
    }
  }
}

void Move_Right() {
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      if (randNumber == my_Array[i][j]) {
        if (i < 3) {
          pixels.setPixelColor(my_Array[i][j], pixels.Color(0, 0, 0));
          pixels.show();
          i++;
          pixels.setPixelColor(my_Array[i][j], pixels.Color(0, 150, 0));
          pixels.show();
          randNumber = my_Array[i][j];
          delay(700);
        }
      }
    }
  }
}

void Move_Left() {
 for(int i = 0; i < 4; i++) {
   for(int j = 0; j < 4; j++) {
     if (randNumber == my_Array[i][j]) {
       if (i > 0) {
         pixels.setPixelColor(my_Array[i][j], pixels.Color(0, 0, 0));
         pixels.show();
         i--;
         pixels.setPixelColor(my_Array[i][j], pixels.Color(0, 150, 0));
         pixels.show();
         randNumber = my_Array[i][j];
         delay(700);
       }
     }
   }
 }
}

void Move_Up() {
 for(int i = 0; i < 4; i++) {
   for(int j = 0; j < 4; j++) {
     if (randNumber == my_Array[i][j]) {
       if (j < 3) {
         pixels.setPixelColor(my_Array[i][j], pixels.Color(0, 0, 0));
         pixels.show();
         j++;
         pixels.setPixelColor(my_Array[i][j], pixels.Color(0, 150, 0));
         pixels.show();
         randNumber = my_Array[i][j];
         delay(700);
       }
     }
   }
 }
}

void Move_Down() {
 for(int i = 0; i < 4; i++) {
   for(int j = 0; j < 4; j++) {
     if (randNumber == my_Array[i][j]) {
       if (j > 0) {
         pixels.setPixelColor(my_Array[i][j], pixels.Color(0, 0, 0));
         pixels.show();
         j--;
         pixels.setPixelColor(my_Array[i][j], pixels.Color(0, 150, 0));
         pixels.show();
         randNumber = my_Array[i][j];
         delay(700);
       }
     }
   }
 }
}

BLYNK_WRITE(V1) {
 int x = param[0].asInt();
 int y = param[1].asInt();

 char Flag_move = Move(x, y);
 Serial.println(Flag_move);

 switch (Flag_move)
 {
   case 'R':
     Move_Right();
     break;
   case 'L':
     Move_Left();
     break;
   case 'U':
     Move_Up();
     break;
   case 'D':
     Move_Down();
     break;
 }
}

void setup() {
 Serial.begin(9600);
 pixels.begin();
 pixels.clear();
 pixels.show();

 Blynk.begin(auth, ssid, pass);

 Matrix_Created();
 Random_Position();
}

void loop() {
 Blynk.run();
}
