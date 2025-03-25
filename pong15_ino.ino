/*
    Pong Attack

    Jus Godden 2025
*/
#include <TFT_eSPI.h>
#include <RotaryEncoder.h>
#include "esp_random.h"
#define ENCODER_INA 4
#define ENCODER_INB 5
#define ENCODER_KEY 0
#define TOP_BUTTON 6

TFT_eSPI tft = TFT_eSPI();
RotaryEncoder encoder(ENCODER_INA, ENCODER_INB, RotaryEncoder::LatchMode::TWO03);

int screen_width = 320;
int screen_height = 170;

int paddle_length = 40;
int paddle_width = 10;
int player_x = 10;
int player_y = (screen_height / 2) - (paddle_length / 2);
int player_speed = 15;
int player1_lives = 11;
int player1_hitstotal = 4;  // hits before kill minus 1
int player1_hitsremain = 4;

int paddle2_length = 40;
int paddle2_width = 10;
int player2_x = screen_width - 20;
int player2_y = (screen_height / 2) - (paddle_length / 2);
int player2_speed = 2;
int player2_lives = 11;
int player2_hitstotal = 4;  // hits before kill minus 1
int player2_hitsremain = 4;

int ball_speed = 2;
int ball_x = screen_width / 2;
int ball_y = screen_height / 2;
int ball_x_dir = -1;
int ball_y_dir = 1;

int ball2_speed = 2;
int ball2_x = screen_width / 2;
int ball2_y = screen_height / 2;
int ball2_x_dir = -1;
int ball2_y_dir = 1;
int ball2_enabled = 0;

int ball3_speed = 2;
int ball3_x = screen_width / 2;
int ball3_y = screen_height / 2;
int ball3_x_dir = -1;
int ball3_y_dir = 1;
int ball3_enabled = 0;

int player_1_score = 0;
int player_2_score = 0;

int missile1 = 0;
int missile1_x = 0;
int missile1_y = 0;
int missile1_rotate = 1;
int missile1_exhaust = 1;
int missile_speed = 3;
int missile1_rotation_speed = 5;
int missile1_rotation_count = 0;

int missile1_tripplefire = 0;
int missile1_tripplefire_enabled = 0;
int missile1_tripplefire1 = 0;
int missile1_tripplefire2 = 0;
int missile1_tripplefire1_x = 0;
int missile1_tripplefire2_x = 0;
int missile1_tripplefire1_y = 0;
int missile1_tripplefire2_y = 0;
int missile1_tripplefire1_y_dir = -1;
int missile1_tripplefire2_y_dir = 1;

int missile1_grenade = 0;
int missile1_grenade_enabled = 0;
int missile1_grenade1 = 0;
int missile1_grenade2 = 0;
int missile1_grenade1_x = 0;
int missile1_grenade2_x = 0;
int missile1_grenade1_y = 0;
int missile1_grenade2_y = 0;
int missile1_grenade1_y_dir = -1;
int missile1_grenade2_y_dir = 1;
int missile1_grenade1_rotate = 1;
int missile1_grenade2_rotate = 1;
int missile1_grenade1_rotation_speed = 5;
int missile1_grenade1_rotation_count = 0;
int missile1_grenade2_rotation_speed = 5;
int missile1_grenade2_rotation_count = 0;

int missile2 = 0;
int missile2_x = 0;
int missile2_y = 0;
int missile2_rotate = 1;
int missile2_exhaust = 0;
int missile_speed2 = 3;
int missile2_rotation_speed = 5;
int missile2_rotation_count = 0;

int missile2_tripplefire = 0;
int missile2_tripplefire_enabled = 0;
int missile2_tripplefire1 = 0;
int missile2_tripplefire2 = 0;
int missile2_tripplefire1_x = 0;
int missile2_tripplefire2_x = 0;
int missile2_tripplefire1_y = 0;
int missile2_tripplefire2_y = 0;
int missile2_tripplefire1_y_dir = -1;
int missile2_tripplefire2_y_dir = 1;

int missile2_grenade = 0;
int missile2_grenade_enabled = 0;
int missile2_grenade1 = 0;
int missile2_grenade2 = 0;
int missile2_grenade1_x = 0;
int missile2_grenade2_x = 0;
int missile2_grenade1_y = 0;
int missile2_grenade2_y = 0;
int missile2_grenade1_y_dir = -1;
int missile2_grenade2_y_dir = 1;
int missile2_grenade1_rotate = 1;
int missile2_grenade2_rotate = 1;
int missile2_grenade1_rotation_speed = 5;
int missile2_grenade1_rotation_count = 0;
int missile2_grenade2_rotation_speed = 5;
int missile2_grenade2_rotation_count = 0;

int diamond1_x = 0;
int diamond1_y = 0;
int diamond1_rotate = 1;
int diamond1_speed = 1;
int diamond1_dir = -1;
int diamond1_y_dir = 0;
int diamond1_type=0;
int diamond1_colour = TFT_YELLOW;
int diamond1 = 0;
int diamond1_rotation_speed = 5;
int diamond1_rotation_count = 0;

int diamond2_x = 0;
int diamond2_y = 0;
int diamond2_rotate = 1;
int diamond2_speed = 1;
int diamond2_dir = 1;
int diamond2_y_dir = 0;
int diamond2_type = 0;
int diamond2_colour = TFT_BLUE;
int diamond2 = 0;
int diamond2_rotation_speed = 5;
int diamond2_rotation_count = 0;

void reset_defaults(){
    screen_width = 320;
    screen_height = 170;

    paddle_length = 40;
    paddle_width = 10;
    player_x = 10;
    player_y = (screen_height / 2) - (paddle_length / 2);
    player_speed = 15;
    player1_lives = 11;
    player1_hitstotal = 4; // hits before kill is this minus 1
    player1_hitsremain = 4;

    paddle2_length = 40;
    paddle2_width = 10;
    player2_x = screen_width - 20;
    player2_y = (screen_height / 2) - (paddle_length / 2);
    player2_speed = 2;
    player2_lives = 11;
    player2_hitstotal = 4; // hits before kill is this minus 1
    player2_hitsremain = 4;


    ball_speed = 2;
    ball_x = screen_width / 2;
    ball_y = screen_height / 2;
    ball_x_dir = -1;
    ball_y_dir = 1;

    ball2_speed = 2;
    ball2_x = screen_width / 2;
    ball2_y = screen_height / 2;
    ball2_x_dir = -1;
    ball2_y_dir = 1;
    ball2_enabled = 0;

    ball3_speed = 2;
    ball3_x = screen_width / 2;
    ball3_y = screen_height / 2;
    ball3_x_dir = -1;
    ball3_y_dir = 1;
    ball3_enabled = 0;

    player_1_score = 0;
    player_2_score = 0;

    missile1 = 0;
    missile1_x = 0;
    missile1_y = 0;
    missile1_rotate = 1;
    missile1_exhaust = 0;
    missile_speed = 3;
    
    missile1_tripplefire = 0;
    missile1_tripplefire_enabled = 0;
    missile1_tripplefire1 = 0;
    missile1_tripplefire2 = 0;
    missile1_tripplefire1_x = 0;
    missile1_tripplefire2_x = 0;
    missile1_tripplefire1_y = 0;
    missile1_tripplefire2_y = 0;
    missile1_tripplefire1_y_dir = -1;
    missile1_tripplefire2_y_dir = 1;

    missile1_grenade = 0;
    missile1_grenade_enabled = 0;
    missile1_grenade1 = 0;
    missile1_grenade2 = 0;
    missile1_grenade1_x = 0;
    missile1_grenade2_x = 0;
    missile1_grenade1_y = 0;
    missile1_grenade2_y = 0;
    missile1_grenade1_y_dir = -1;
    missile1_grenade2_y_dir = 1;

    missile2 = 0;
    missile2_x = 0;
    missile2_y = 0;
    missile2_rotate = 1;
    missile2_exhaust = 1;
    missile_speed2 = 3;

    missile2_tripplefire = 0;
    missile2_tripplefire_enabled = 0;
    missile2_tripplefire1 = 0;
    missile2_tripplefire2 = 0;
    missile2_tripplefire1_x = 0;
    missile2_tripplefire2_x = 0;
    missile2_tripplefire1_y = 0;
    missile2_tripplefire2_y = 0;
    missile2_tripplefire1_y_dir = -1;
    missile2_tripplefire2_y_dir = 1;

    missile2_grenade = 0;
    missile2_grenade_enabled = 0;
    missile2_grenade1 = 0;
    missile2_grenade2 = 0;
    missile2_grenade1_x = 0;
    missile2_grenade2_x = 0;
    missile2_grenade1_y = 0;
    missile2_grenade2_y = 0;
    missile2_grenade1_y_dir = -1;
    missile2_grenade2_y_dir = 1;

    diamond1_x = 0;
    diamond1_y = 0;
    diamond1_rotate = 1;
    diamond1_speed = 1;
    diamond1_dir = -1;
    diamond1_y_dir = 0;
    diamond1_type = 0;
    diamond1_colour = TFT_YELLOW;
    diamond1 = 0;

    diamond2_x = 0;
    diamond2_y = 0;
    diamond2_rotate = 1;
    diamond2_speed = 1;
    diamond2_dir = 1;
    diamond2_y_dir = 0;
    diamond2_type = 0;
    diamond1_colour = TFT_BLUE;
    diamond2 = 0;

    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_BLUE, TFT_BLACK);
    tft.setTextSize(3);
}

void setup() {
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);

    tft.setTextColor(TFT_BLUE, TFT_BLACK);
    tft.setTextSize(3);
    tft.setCursor(50, 20);
    tft.print("0");
    tft.setCursor(screen_width - 80, 20);
    tft.print("0");

    pinMode(ENCODER_KEY, INPUT);
    pinMode(6, INPUT_PULLUP);
}

void draw_net(){
  int net_position = screen_width / 2;
  int i = 0;
  //tft.drawLine(net_position , 0, net_position, screen_height, TFT_DARKGREY);

  i = 2;
  while (i < screen_height){
    tft.drawLine(net_position ,i , net_position, i+15, TFT_DARKGREY);
    i=i+25;
  }
}

void draw_player_1(){
    tft.drawLine(player_x, player_y, player_x, player_y + paddle_length, TFT_GREEN);
    tft.drawLine(player_x + paddle_width, player_y, player_x + paddle_width, player_y + paddle_length, TFT_GREEN);
    tft.drawLine(player_x, player_y, player_x + paddle_width, player_y, TFT_GREEN);
    tft.drawLine(player_x, player_y + paddle_length, player_x + paddle_width, player_y + paddle_length, TFT_GREEN);
    // tft.drawRect(player_x, player_y, player_x + paddle_width, player_y + paddle_length, TFT_GREEN);
}

void blank_player_1(){
    tft.drawLine(player_x, player_y, player_x, player_y + paddle_length, TFT_BLACK);
    tft.drawLine(player_x + paddle_width, player_y, player_x + paddle_width, player_y + paddle_length, TFT_BLACK);
    tft.drawLine(player_x, player_y, player_x + paddle_width, player_y, TFT_BLACK);
    tft.drawLine(player_x, player_y + paddle_length, player_x + paddle_width, player_y + paddle_length, TFT_BLACK);
    // tft.drawRect(player_x, player_y, player_x + paddle_width, player_y + paddle_length, TFT_BLACK);
}

void draw_player_2(){ 
    tft.drawLine(player2_x, player2_y, player2_x, player2_y + paddle2_length, TFT_RED);
    tft.drawLine(player2_x + paddle2_width, player2_y, player2_x + paddle2_width, player2_y + paddle2_length, TFT_RED);
    tft.drawLine(player2_x, player2_y, player2_x + paddle2_width, player2_y, TFT_RED);
    tft.drawLine(player2_x, player2_y + paddle2_length, player2_x + paddle2_width, player2_y + paddle2_length, TFT_RED);
    // tft.drawRect(player2_x, player2_y, player2_x + paddle2_width, player2_y + paddle2_length, TFT_GREEN);
}

void blank_player_2(){
    tft.drawLine(player2_x, player2_y, player2_x, player2_y + paddle2_length, TFT_BLACK);
    tft.drawLine(player2_x + paddle2_width, player2_y, player2_x + paddle2_width, player2_y + paddle2_length, TFT_BLACK);
    tft.drawLine(player2_x, player2_y, player2_x + paddle2_width, player2_y, TFT_BLACK);
    tft.drawLine(player2_x, player2_y + paddle2_length, player2_x + paddle2_width, player2_y + paddle2_length, TFT_BLACK);
    // tft.drawRect(player2_x, player2_y, player2_x + paddle2_width, player2_y + paddle2_length, TFT_BLACK);
}

void draw_ball(){
    tft.drawSmoothCircle(ball_x, ball_y, 10, TFT_WHITE, TFT_BLACK);
}

void blank_ball(){
    tft.drawSmoothCircle(ball_x, ball_y, 10, TFT_BLACK, TFT_BLACK);
}

void move_ball(){
    // Ball physics section - sort of!
    int speedx = 0;
    ball_x = ball_x + (ball_x_dir * ball_speed);
    ball_y = ball_y + (ball_y_dir * ball_speed);

    if ( ball_y <= 10 ) {
      ball_y_dir = 1;
    }
    if ( ball_y >= screen_height - 10 ) {
      ball_y_dir = -1;
    }


    if (ball_x_dir > -2 && ball_x_dir < 2) {
      speedx = 1;
    }

    if ( ball_x <= (player_x + 15) && ball_x >= player_x) {
      if (ball_y >= (player_y) - 5 && ball_y <= (player_y + paddle_length + 5)) {
        ball_x_dir = 1;
      }
      if (ball_y >= (player_y) + 5 && ball_y <= (player_y + paddle_length - 5)) {
        ball_x_dir = 2;
      }
      if (ball_y >= (player_y) + 5 && ball_y <= (player_y + paddle_length - 10)) {
        ball_x_dir = 3;
      }
      if (ball_y >= (player_y) + 15 && ball_y <= (player_y + paddle_length - 15)) {
        ball_x_dir = 4;
        if (speedx != 1) {
          ball_y_dir = 0;
        }
      } else {
        if ( ball_y_dir == 0) {
          if (ball_y < player_y + ( paddle_length / 2)) {
            ball_y_dir = -1;
          } else {
            ball_y_dir = 1;
          }
        }
      }
    }

    if ( ball_x >= (player2_x - 5) && ball_x <= (player2_x + 10)) {
      if (ball_y >= (player2_y - 5) && ball_y <= (player2_y + paddle2_length + 5)) {
        ball_x_dir = -1;
      }
      if (ball_y >= (player2_y) + 5 && ball_y <= (player2_y + paddle2_length - 5)) {
        ball_x_dir = -2;
      }
      if (ball_y >= (player2_y) + 5 && ball_y <= (player2_y + paddle2_length - 10)) {
        ball_x_dir = -3;
      }
      if (ball_y >= (player2_y) + 15 && ball_y <= (player2_y + paddle2_length - 15)) {
        ball_x_dir = -4;
        if (speedx != 1) {
          ball_y_dir = 0;
        }
        // ball_y_dir = 0;
      } else {
        if ( ball_y_dir == 0) {
          if (ball_y < player2_y + ( paddle2_length / 2)) {
            ball_y_dir = -1;
          } else {
            ball_y_dir = 1;
          }
        }
      }
    }
    speedx = 0;


    if ( ball_x < 10 ) {
      ball_x = (screen_width / 2);
      // ball_y = (screen_height / 2);
      ball_y = 1;
      player_2_score++;
      if ( player1_lives > 0) {
        player1_lives--;
      }
      ball_x_dir = 1;
    }

    if ( ball_x > (screen_width - 10) ) {
      ball_x = (screen_width / 2);
      // ball_y = (screen_height / 2);
      ball_y = screen_height - 1;
      player_1_score++;
      if ( player2_lives > 0) {
        player2_lives--;
      }
      ball_x_dir = -1;
    }

}

// -------------------- ball 2 -------------------------------------
void draw_ball2(){
    tft.drawSmoothCircle(ball2_x, ball2_y, 10, TFT_WHITE, TFT_BLACK);
}

void blank_ball2(){
    tft.drawSmoothCircle(ball2_x, ball2_y, 10, TFT_BLACK, TFT_BLACK);
}

void move_ball2(){
    // Ball physics section - sort of!
    int speedx = 0;
    ball2_x = ball2_x + (ball2_x_dir * ball2_speed);
    ball2_y = ball2_y + (ball2_y_dir * ball2_speed);

    if ( ball2_y <= 10 ) {
      ball2_y_dir = 1;
    }
    if ( ball2_y >= screen_height - 10 ) {
      ball2_y_dir = -1;
    }


    if (ball2_x_dir > -2 && ball2_x_dir < 2) {
      speedx = 1;
    }

    if ( ball2_x <= (player_x + 15) && ball2_x >= player_x) {
      if (ball2_y >= (player_y) - 5 && ball2_y <= (player_y + paddle_length + 5)) {
        ball2_x_dir = 1;
      }
      if (ball2_y >= (player_y) + 5 && ball2_y <= (player_y + paddle_length - 5)) {
        ball2_x_dir = 2;
      }
      if (ball2_y >= (player_y) + 15 && ball2_y <= (player_y + paddle_length - 15)) {
        ball2_x_dir = 3;
        if (speedx != 1) {
          ball2_y_dir = 0;
        }
      } else {
        if ( ball2_y_dir == 0) {
          if (ball2_y < player_y + ( paddle_length / 2)) {
            ball2_y_dir = -1;
          } else {
            ball2_y_dir = 1;
          }
        }
      }
    }

    if ( ball2_x >= (player2_x - 5) && ball2_x <= (player2_x + 10)) {
      if (ball2_y >= (player2_y - 5) && ball2_y <= (player2_y + paddle2_length + 5)) {
        ball2_x_dir = -1;
      }
      if (ball2_y >= (player2_y) + 5 && ball2_y <= (player2_y + paddle2_length - 5)) {
        ball2_x_dir = -2;
      }
      if (ball2_y >= (player2_y) + 15 && ball2_y <= (player2_y + paddle2_length - 15)) {
        ball2_x_dir = -3;
        if (speedx != 1) {
          ball2_y_dir = 0;
        }
        // ball_y_dir = 0;
      } else {
        if ( ball2_y_dir == 0) {
          if (ball2_y < player2_y + ( paddle2_length / 2)) {
            ball2_y_dir = -1;
          } else {
            ball2_y_dir = 1;
          }
        }
      }
    }
    speedx = 0;


    if ( ball2_x < 10 ) {
      ball2_x = (screen_width / 2);
      // ball2_y = (screen_height / 2);
      ball2_y = 1;
      player_2_score++;
      if ( player1_lives > 0) {
        player1_lives--;
      }
      ball2_x_dir = 1;
      ball2_enabled = 0;
    }

    if ( ball2_x > (screen_width - 10) ) {
      ball2_x = (screen_width / 2);
      // ball2_y = (screen_height / 2);
      ball2_y = screen_height - 1;
      player_1_score++;
      if ( player2_lives > 0) {
        player2_lives--;
      }
      ball2_x_dir = -1;
      ball2_enabled = 0;
    }

}
// ------ end ball 2 ---------------------------

// -------------ball 3 -------------------------
void draw_ball3(){
    tft.drawSmoothCircle(ball3_x, ball3_y, 10, TFT_WHITE, TFT_BLACK);
}

void blank_ball3(){
    tft.drawSmoothCircle(ball3_x, ball3_y, 10, TFT_BLACK, TFT_BLACK);
}

void move_ball3(){
    // Ball physics section - sort of!
    int speedx = 0;
    ball3_x = ball3_x + (ball3_x_dir * ball_speed);
    ball3_y = ball3_y + (ball3_y_dir * ball_speed);

    if ( ball3_y <= 10 ) {
      ball3_y_dir = 1;
    }
    if ( ball3_y >= screen_height - 10 ) {
      ball3_y_dir = -1;
    }


    if (ball3_x_dir > -2 && ball3_x_dir < 2) {
      speedx = 1;
    }

    if ( ball3_x <= (player_x + 15) && ball3_x >= player_x) {
      if (ball3_y >= (player_y) - 5 && ball3_y <= (player_y + paddle_length + 5)) {
        ball3_x_dir = 1;
      }
      if (ball3_y >= (player_y) + 5 && ball3_y <= (player_y + paddle_length - 5)) {
        ball3_x_dir = 2;
      }
      if (ball3_y >= (player_y) + 15 && ball3_y <= (player_y + paddle_length - 15)) {
        ball3_x_dir = 3;
        if (speedx != 1) {
          ball3_y_dir = 0;
        }
      } else {
        if ( ball3_y_dir == 0) {
          if (ball3_y < player_y + ( paddle_length / 2)) {
            ball3_y_dir = -1;
          } else {
            ball3_y_dir = 1;
          }
        }
      }
    }

    if ( ball3_x >= (player2_x - 5) && ball3_x <= (player2_x + 10)) {
      if (ball3_y >= (player2_y - 5) && ball3_y <= (player2_y + paddle2_length + 5)) {
        ball3_x_dir = -1;
      }
      if (ball3_y >= (player2_y) + 5 && ball3_y <= (player2_y + paddle2_length - 5)) {
        ball3_x_dir = -2;
      }
      if (ball3_y >= (player2_y) + 15 && ball3_y <= (player2_y + paddle2_length - 15)) {
        ball3_x_dir = -3;
        if (speedx != 1) {
          ball3_y_dir = 0;
        }
        // ball_y_dir = 0;
      } else {
        if ( ball3_y_dir == 0) {
          if (ball3_y < player2_y + ( paddle2_length / 2)) {
            ball3_y_dir = -1;
          } else {
            ball3_y_dir = 1;
          }
        }
      }
    }
    speedx = 0;


    if ( ball3_x < 10 ) {
      ball3_x = (screen_width / 2);
      // ball3_y = (screen_height / 2);
      ball3_y = 1;
      player_2_score++;
      if ( player1_lives > 0) {
        player1_lives--;
      }
      ball3_x_dir = 1;
      ball3_enabled = 0;
    }

    if ( ball3_x > (screen_width - 10) ) {
      ball3_x = (screen_width / 2);
      // ball3_y = (screen_height / 2);
      ball3_y = screen_height - 1;
      player_1_score++;
      if ( player2_lives > 0) {
        player2_lives--;
      }
      ball3_x_dir = -1;
      ball3_enabled = 0;
    }

}
// ------------------end ball 3 ------------------------------------


void draw_missile1() {
  if (missile1_rotate == 1){
    tft.drawLine(missile1_x , missile1_y, missile1_x + 25, missile1_y + 5, TFT_GREEN);
    tft.drawLine(missile1_x , missile1_y + 10, missile1_x + 25, missile1_y + 5, TFT_GREEN);
    tft.drawLine(missile1_x , missile1_y, missile1_x, missile1_y + 10, TFT_GREEN);
    tft.drawPixel(missile1_x - 1, missile1_y + 3, TFT_DARKGREY);
    tft.drawPixel(missile1_x - 1, missile1_y + 7, TFT_DARKGREY);
  }
  if (missile1_rotate == 2){
    tft.drawLine(missile1_x , missile1_y + 1, missile1_x + 25, missile1_y + 5, TFT_GREEN);
    tft.drawLine(missile1_x , missile1_y + 9, missile1_x + 25, missile1_y + 5, TFT_GREEN);
    tft.drawLine(missile1_x , missile1_y + 1, missile1_x, missile1_y + 9, TFT_GREEN);
    tft.drawLine(missile1_x , missile1_y + 3, missile1_x + 25, missile1_y + 5, TFT_GREEN);
    tft.drawPixel(missile1_x - 1, missile1_y + 4, TFT_DARKGREY);
\
  }
  if (missile1_rotate == 3){
    tft.drawLine(missile1_x , missile1_y + 1, missile1_x + 25, missile1_y + 5, TFT_GREEN);
    tft.drawLine(missile1_x , missile1_y + 9, missile1_x + 25, missile1_y + 5, TFT_GREEN);
    tft.drawLine(missile1_x , missile1_y + 1, missile1_x, missile1_y + 9, TFT_GREEN);
    tft.drawLine(missile1_x , missile1_y + 6, missile1_x + 25, missile1_y + 5, TFT_GREEN);

    tft.drawPixel(missile1_x - 1, missile1_y + 6, TFT_DARKGREY);
  }
}

void blank_missile1(){
  if (missile1_rotate == 1){
    tft.drawLine(missile1_x , missile1_y, missile1_x + 25, missile1_y + 5, TFT_BLACK);
    tft.drawLine(missile1_x , missile1_y + 10, missile1_x + 25, missile1_y + 5, TFT_BLACK);
    tft.drawLine(missile1_x , missile1_y, missile1_x, missile1_y + 10, TFT_BLACK);
    tft.drawPixel(missile1_x - 46, missile1_y + 3, TFT_BLACK);
    tft.drawPixel(missile1_x - 46, missile1_y + 7, TFT_BLACK);
  }
    if (missile1_rotate == 2){
    tft.drawLine(missile1_x , missile1_y + 1, missile1_x + 25, missile1_y + 5, TFT_BLACK);
    tft.drawLine(missile1_x , missile1_y + 9, missile1_x + 25, missile1_y + 5, TFT_BLACK);
    tft.drawLine(missile1_x , missile1_y + 1, missile1_x, missile1_y + 9, TFT_BLACK);
    tft.drawLine(missile1_x , missile1_y + 3, missile1_x + 25, missile1_y + 5, TFT_BLACK);
    tft.drawPixel(missile1_x - 46, missile1_y + 4, TFT_BLACK);
  }
  if (missile1_rotate == 3){
    tft.drawLine(missile1_x , missile1_y + 1, missile1_x + 25, missile1_y + 5, TFT_BLACK);
    tft.drawLine(missile1_x , missile1_y + 9, missile1_x + 25, missile1_y + 5, TFT_BLACK);
    tft.drawLine(missile1_x , missile1_y + 1, missile1_x, missile1_y + 9, TFT_BLACK);
    tft.drawLine(missile1_x , missile1_y + 6, missile1_x + 25, missile1_y + 5, TFT_BLACK);

    tft.drawPixel(missile1_x - 46, missile1_y + 6, TFT_BLACK);
  }

  missile1_exhaust++;
  if (missile1_exhaust > 10){
    tft.drawLine(missile1_x - 4 , missile1_y + 3, missile1_x - 56, missile1_y + 3, TFT_BLACK);
    tft.drawLine(missile1_x - 4 , missile1_y + 4, missile1_x - 56, missile1_y + 4, TFT_BLACK);
    tft.drawLine(missile1_x - 4 , missile1_y + 6, missile1_x - 56, missile1_y + 6, TFT_BLACK);
    tft.drawLine(missile1_x - 4 , missile1_y + 7, missile1_x - 56, missile1_y + 7, TFT_BLACK);
  missile1_exhaust = 0;
  }
}

void missile1_blank_exhaust(){
    tft.drawLine(missile1_x - 1 , missile1_y + 3, missile1_x - 56, missile1_y + 3, TFT_BLACK);
    tft.drawLine(missile1_x - 1 , missile1_y + 4, missile1_x - 56, missile1_y + 4, TFT_BLACK);
    tft.drawLine(missile1_x - 1 , missile1_y + 6, missile1_x - 56, missile1_y + 6, TFT_BLACK);
    tft.drawLine(missile1_x - 1 , missile1_y + 7, missile1_x - 56, missile1_y + 7, TFT_BLACK);
}

void draw_missile1_tripplefire1(){
  if (missile1_tripplefire1_y_dir == -1){
    tft.drawLine(missile1_tripplefire1_x - 10 , missile1_tripplefire1_y + 5, missile1_tripplefire1_x, missile1_tripplefire1_y, TFT_YELLOW);
  }
  if (missile1_tripplefire1_y_dir == 1){
    tft.drawLine(missile1_tripplefire1_x - 10 , missile1_tripplefire1_y - 5, missile1_tripplefire1_x, missile1_tripplefire1_y, TFT_YELLOW);
  }
}

void draw_missile1_tripplefire2(){
  if (missile1_tripplefire2_y_dir == -1){
    tft.drawLine(missile1_tripplefire2_x - 10 , missile1_tripplefire2_y + 5, missile1_tripplefire2_x, missile1_tripplefire2_y, TFT_YELLOW);
  }
  if (missile1_tripplefire2_y_dir == 1){
    tft.drawLine(missile1_tripplefire2_x - 10 , missile1_tripplefire2_y - 5, missile1_tripplefire2_x, missile1_tripplefire2_y, TFT_YELLOW);
  }
}

void blank_missile1_tripplefire1(){
  if (missile1_tripplefire1_y_dir == -1){
    tft.drawLine(missile1_tripplefire1_x - 10 , missile1_tripplefire1_y + 5, missile1_tripplefire1_x, missile1_tripplefire1_y, TFT_BLACK);
  }
  if (missile1_tripplefire1_y_dir == 1){
    tft.drawLine(missile1_tripplefire1_x - 10 , missile1_tripplefire1_y - 5, missile1_tripplefire1_x, missile1_tripplefire1_y, TFT_BLACK);
  }
}

void blank_missile1_tripplefire2(){
  if (missile1_tripplefire2_y_dir == -1){
    tft.drawLine(missile1_tripplefire2_x - 10 , missile1_tripplefire2_y + 5, missile1_tripplefire2_x, missile1_tripplefire2_y, TFT_BLACK);
  }
  if (missile1_tripplefire2_y_dir == 1){
    tft.drawLine(missile1_tripplefire2_x - 10 , missile1_tripplefire2_y - 5, missile1_tripplefire2_x, missile1_tripplefire2_y, TFT_BLACK);
  }
}


void draw_missile1_grenade1(){
  //
  if (missile1_grenade1_rotate == 1){
    tft.drawSmoothCircle(missile1_grenade1_x + 4 + 5, missile1_grenade1_y + 4 + 5, 5, TFT_DARKGREY, TFT_BLACK);
    tft.drawLine(missile1_grenade1_x + 4 + 5 , missile1_grenade1_y + 3, missile1_grenade1_x + 4 + 5, missile1_grenade1_y, TFT_DARKGREY);
    tft.drawLine(missile1_grenade1_x , missile1_grenade1_y + 4 + 5, missile1_grenade1_x + 3, missile1_grenade1_y + 4 + 5, TFT_DARKGREY);
    tft.drawLine(missile1_grenade1_x + 15 , missile1_grenade1_y + 4 + 5, missile1_grenade1_x + 15 + 3, missile1_grenade1_y + 4 + 5, TFT_DARKGREY);
    tft.drawLine(missile1_grenade1_x + 4 + 5 , missile1_grenade1_y + 15, missile1_grenade1_x + 4 + 5, missile1_grenade1_y + 15 + 3, TFT_DARKGREY);
  }
  if (missile1_grenade1_rotate == 2) {
    tft.drawSmoothCircle(missile1_grenade1_x + 4 + 5, missile1_grenade1_y + 4 + 5, 5, TFT_DARKGREY, TFT_BLACK);
    tft.drawLine(missile1_grenade1_x + 5 + 6 , missile1_grenade1_y + 3, missile1_grenade1_x + 5 + 7, missile1_grenade1_y, TFT_DARKGREY);
    tft.drawLine(missile1_grenade1_x , missile1_grenade1_y + 3 + 3, missile1_grenade1_x + 3, missile1_grenade1_y + 3 + 4, TFT_DARKGREY);
    tft.drawLine(missile1_grenade1_x + 15 , missile1_grenade1_y + 5 + 6, missile1_grenade1_x + 15 + 3, missile1_grenade1_y + 5 + 7, TFT_DARKGREY);
    tft.drawLine(missile1_grenade1_x + 3 + 4 , missile1_grenade1_y + 15, missile1_grenade1_x + 3 + 3, missile1_grenade1_y + 15 + 3, TFT_DARKGREY);
  }
  if (missile1_grenade1_rotate == 3) {
    tft.drawSmoothCircle(missile1_grenade1_x + 4 + 5, missile1_grenade1_y + 4 + 5, 5, TFT_DARKGREY, TFT_BLACK);
    tft.drawLine(missile1_grenade1_x + 3 + 4 , missile1_grenade1_y + 3, missile1_grenade1_x + 3 + 3, missile1_grenade1_y, TFT_DARKGREY);
    tft.drawLine(missile1_grenade1_x + 3, missile1_grenade1_y + 5 + 6, missile1_grenade1_x, missile1_grenade1_y + 5 + 7, TFT_DARKGREY);
    tft.drawLine(missile1_grenade1_x + 15 , missile1_grenade1_y + 3 + 4, missile1_grenade1_x + 15 + 3, missile1_grenade1_y + 3 + 3, TFT_DARKGREY);
    tft.drawLine(missile1_grenade1_x + 5 + 6 , missile1_grenade1_y + 15, missile1_grenade1_x + 5 + 7, missile1_grenade1_y + 15 + 3, TFT_DARKGREY);
  }
}

void draw_missile1_grenade2(){
  //
  if (missile1_grenade2_rotate == 1){
    tft.drawSmoothCircle(missile1_grenade2_x + 4 + 5, missile1_grenade2_y + 4 + 5, 5, TFT_DARKGREY, TFT_BLACK);
    tft.drawLine(missile1_grenade2_x + 4 + 5 , missile1_grenade2_y + 3, missile1_grenade2_x + 4 + 5, missile1_grenade2_y, TFT_DARKGREY);
    tft.drawLine(missile1_grenade2_x , missile1_grenade2_y + 4 + 5, missile1_grenade2_x + 3, missile1_grenade2_y + 4 + 5, TFT_DARKGREY);
    tft.drawLine(missile1_grenade2_x + 15 , missile1_grenade2_y + 4 + 5, missile1_grenade2_x + 15 + 3, missile1_grenade2_y + 4 + 5, TFT_DARKGREY);
    tft.drawLine(missile1_grenade2_x + 4 + 5 , missile1_grenade2_y + 15, missile1_grenade2_x + 4 + 5, missile1_grenade2_y + 15 + 3, TFT_DARKGREY);
  }
  if (missile1_grenade2_rotate == 2) {
    tft.drawSmoothCircle(missile1_grenade2_x + 4 + 5, missile1_grenade2_y + 4 + 5, 5, TFT_DARKGREY, TFT_BLACK);
    tft.drawLine(missile1_grenade2_x + 5 + 6 , missile1_grenade2_y + 3, missile1_grenade2_x + 5 + 7, missile1_grenade2_y, TFT_DARKGREY);
    tft.drawLine(missile1_grenade2_x , missile1_grenade2_y + 3 + 3, missile1_grenade2_x + 3, missile1_grenade2_y + 3 + 4, TFT_DARKGREY);
    tft.drawLine(missile1_grenade2_x + 15 , missile1_grenade2_y + 5 + 6, missile1_grenade2_x + 15 + 3, missile1_grenade2_y + 5 + 7, TFT_DARKGREY);
    tft.drawLine(missile1_grenade2_x + 3 + 4 , missile1_grenade2_y + 15, missile1_grenade2_x + 3 + 3, missile1_grenade2_y + 15 + 3, TFT_DARKGREY);
  }
  if (missile1_grenade2_rotate == 3) {
    tft.drawSmoothCircle(missile1_grenade2_x + 4 + 5, missile1_grenade2_y + 4 + 5, 5, TFT_DARKGREY, TFT_BLACK);
    tft.drawLine(missile1_grenade2_x + 3 + 4 , missile1_grenade2_y + 3, missile1_grenade2_x + 3 + 3, missile1_grenade2_y, TFT_DARKGREY);
    tft.drawLine(missile1_grenade2_x + 3, missile1_grenade2_y + 5 + 6, missile1_grenade2_x, missile1_grenade2_y + 5 + 7, TFT_DARKGREY);
    tft.drawLine(missile1_grenade2_x + 15 , missile1_grenade2_y + 3 + 4, missile1_grenade2_x + 15 + 3, missile1_grenade2_y + 3 + 3, TFT_DARKGREY);
    tft.drawLine(missile1_grenade1_x + 5 + 6 , missile1_grenade2_y + 15, missile1_grenade2_x + 5 + 7, missile1_grenade2_y + 15 + 3, TFT_DARKGREY);
  }
}

void blank_missile1_grenade1(){
  //
  if (missile1_grenade1_rotate == 1){
    tft.drawSmoothCircle(missile1_grenade1_x + 4 + 5, missile1_grenade1_y + 4 + 5, 5, TFT_BLACK, TFT_BLACK);
    tft.drawLine(missile1_grenade1_x + 4 + 5 , missile1_grenade1_y + 3, missile1_grenade1_x + 4 + 5, missile1_grenade1_y, TFT_BLACK);
    tft.drawLine(missile1_grenade1_x , missile1_grenade1_y + 4 + 5, missile1_grenade1_x + 3, missile1_grenade1_y + 4 + 5, TFT_BLACK);
    tft.drawLine(missile1_grenade1_x + 15 , missile1_grenade1_y + 4 + 5, missile1_grenade1_x + 15 + 3, missile1_grenade1_y + 4 + 5, TFT_BLACK);
    tft.drawLine(missile1_grenade1_x + 4 + 5 , missile1_grenade1_y + 15, missile1_grenade1_x + 4 + 5, missile1_grenade1_y + 15 + 3, TFT_BLACK);
  }
  if (missile1_grenade1_rotate == 2) {
    tft.drawSmoothCircle(missile1_grenade1_x + 4 + 5, missile1_grenade1_y + 4 + 5, 5, TFT_BLACK, TFT_BLACK);
    tft.drawLine(missile1_grenade1_x + 5 + 6 , missile1_grenade1_y + 3, missile1_grenade1_x + 5 + 7, missile1_grenade1_y, TFT_BLACK);
    tft.drawLine(missile1_grenade1_x , missile1_grenade1_y + 3 + 3, missile1_grenade1_x + 3, missile1_grenade1_y + 3 + 4, TFT_BLACK);
    tft.drawLine(missile1_grenade1_x + 15 , missile1_grenade1_y + 5 + 6, missile1_grenade1_x + 15 + 3, missile1_grenade1_y + 5 + 7, TFT_BLACK);
    tft.drawLine(missile1_grenade1_x + 3 + 4 , missile1_grenade1_y + 15, missile1_grenade1_x + 3 + 3, missile1_grenade1_y + 15 + 3, TFT_BLACK);
  }
  if (missile1_grenade1_rotate == 3) {
    tft.drawSmoothCircle(missile1_grenade1_x + 4 + 5, missile1_grenade1_y + 4 + 5, 5, TFT_BLACK, TFT_BLACK);
    tft.drawLine(missile1_grenade1_x + 3 + 4 , missile1_grenade1_y + 3, missile1_grenade1_x + 3 + 3, missile1_grenade1_y, TFT_BLACK);
    tft.drawLine(missile1_grenade1_x + 3, missile1_grenade1_y + 5 + 6, missile1_grenade1_x, missile1_grenade1_y + 5 + 7, TFT_BLACK);
    tft.drawLine(missile1_grenade1_x + 15 , missile1_grenade1_y + 3 + 4, missile1_grenade1_x + 15 + 3, missile1_grenade1_y + 3 + 3, TFT_BLACK);
    tft.drawLine(missile1_grenade1_x + 5 + 6 , missile1_grenade1_y + 15, missile1_grenade1_x + 5 + 7, missile1_grenade1_y + 15 + 3, TFT_BLACK);
  }
}

void blank_missile1_grenade2(){
  //
  if (missile1_grenade2_rotate == 1){
    tft.drawSmoothCircle(missile1_grenade2_x + 4 + 5, missile1_grenade2_y + 4 + 5, 5, TFT_BLACK, TFT_BLACK);
    tft.drawLine(missile1_grenade2_x + 4 + 5 , missile1_grenade2_y + 3, missile1_grenade2_x + 4 + 5, missile1_grenade2_y, TFT_BLACK);
    tft.drawLine(missile1_grenade2_x , missile1_grenade2_y + 4 + 5, missile1_grenade2_x + 3, missile1_grenade2_y + 4 + 5, TFT_BLACK);
    tft.drawLine(missile1_grenade2_x + 15 , missile1_grenade2_y + 4 + 5, missile1_grenade2_x + 15 + 3, missile1_grenade2_y + 4 + 5, TFT_BLACK);
    tft.drawLine(missile1_grenade2_x + 4 + 5 , missile1_grenade2_y + 15, missile1_grenade2_x + 4 + 5, missile1_grenade2_y + 15 + 3, TFT_BLACK);
  }
  if (missile1_grenade2_rotate == 2) {
    tft.drawSmoothCircle(missile1_grenade2_x + 4 + 5, missile1_grenade2_y + 4 + 5, 5, TFT_BLACK, TFT_BLACK);
    tft.drawLine(missile1_grenade2_x + 5 + 6 , missile1_grenade2_y + 3, missile1_grenade2_x + 5 + 7, missile1_grenade2_y, TFT_BLACK);
    tft.drawLine(missile1_grenade2_x , missile1_grenade2_y + 3 + 3, missile1_grenade2_x + 3, missile1_grenade2_y + 3 + 4, TFT_BLACK);
    tft.drawLine(missile1_grenade2_x + 15 , missile1_grenade2_y + 5 + 6, missile1_grenade2_x + 15 + 3, missile1_grenade2_y + 5 + 7, TFT_BLACK);
    tft.drawLine(missile1_grenade2_x + 3 + 4 , missile1_grenade2_y + 15, missile1_grenade2_x + 3 + 3, missile1_grenade2_y + 15 + 3, TFT_BLACK);
  }
  if (missile1_grenade2_rotate == 3) {
    tft.drawSmoothCircle(missile1_grenade2_x + 4 + 5, missile1_grenade2_y + 4 + 5, 5, TFT_BLACK, TFT_BLACK);
    tft.drawLine(missile1_grenade2_x + 3 + 4 , missile1_grenade2_y + 3, missile1_grenade2_x + 3 + 3, missile1_grenade2_y, TFT_BLACK);
    tft.drawLine(missile1_grenade2_x + 3, missile1_grenade2_y + 5 + 6, missile1_grenade2_x, missile1_grenade2_y + 5 + 7, TFT_BLACK);
    tft.drawLine(missile1_grenade2_x + 15 , missile1_grenade2_y + 3 + 4, missile1_grenade2_x + 15 + 3, missile1_grenade2_y + 3 + 3, TFT_BLACK);
    tft.drawLine(missile1_grenade1_x + 5 + 6 , missile1_grenade2_y + 15, missile1_grenade2_x + 5 + 7, missile1_grenade2_y + 15 + 3, TFT_BLACK);
  }
}


void do_missile1() {
    int val = -1;
    int random_number = 0;

    if (missile1 == 0 ) {
      val = digitalRead(ENCODER_KEY);
      if (val == 0) {
        // launch player 1 missile
        missile1_x = player_x + 10;
        missile1_y = player_y + (paddle_length / 2) - 5;
        random_number = random(3, 6);
        missile_speed = random_number;
        missile1_exhaust = 0;
        missile1 = 1;

        if (missile1_tripplefire_enabled == 1){
          if (missile1_tripplefire1 == 0){
            missile1_tripplefire1_x = player_x + 10;
            missile1_tripplefire1_y = player_y + (paddle_length / 2);
            missile1_tripplefire1_y_dir = -1;
            missile1_tripplefire1 = 1;
          }

         if (missile1_tripplefire2 == 0){
            missile1_tripplefire2_y = player_y + (paddle_length / 2);
            missile1_tripplefire2_x = player_x + 10;
            missile1_tripplefire2_y_dir = 1;
            missile1_tripplefire2 = 1;
          }
        }

        if (missile1_grenade_enabled == 1){
          if (missile1_grenade1 == 0){
            missile1_grenade1_x = player_x + 10;
            missile1_grenade1_y = player_y + (paddle_length / 2);
            missile1_grenade1_y_dir = -1;
            missile1_grenade1 = 1;
          }

          if (missile1_grenade2 == 0){
            missile1_grenade2_y = player_y + (paddle_length / 2);
            missile1_grenade2_x = player_x + 10;
            missile1_grenade2_y_dir = 1;
            missile1_grenade2 = 1;
          }
        }

      }
      val = -1;
    } else {
      blank_missile1();
      missile1_x = missile1_x + missile_speed;
      if ( missile1_x > (player2_x - 10) && missile1_x < (player2_x + 10)) {
        if (missile1_y > (player2_y - 1) && missile1_y < (player2_y + paddle2_length + 1)) {
          player2_hitsremain--;
          if (player2_hitsremain < 1){
            blank_player_2();
            missile1_blank_exhaust();
            player2_y = (screen_height / 2) - (paddle2_length / 2);
            player_1_score++;
            if (player2_lives > 0) {
              player2_lives--;
            }
            paddle_length = 40;
            missile1 = 0;
            missile2_tripplefire_enabled = 0;
            player2_hitsremain = player2_hitstotal;
          }
          missile1 = 0;
        }
      }
      if ( missile1_x > screen_width ) {
        missile1_blank_exhaust();
        missile1_x = 0;
        missile1_y = 0;
        missile1 = 0;
      }
    }
    /* if (missile1 == 1) {
      missile1_rotate++;
      if (missile1_rotate > 3){
        missile1_rotate = 1;
      }
      draw_missile1();
    } */

    if (missile1 == 1) {
      missile1_rotation_count++;
      if (missile1_rotation_count > missile1_rotation_speed){
        missile1_rotation_count = 0;
        missile1_rotate++;
        if (missile1_rotate > 3){
          missile1_rotate = 1;
        }
      }
      draw_missile1();
    }

    if (missile1_tripplefire1 == 1){
      blank_missile1_tripplefire1();
    }
    if (missile1_tripplefire2 == 1){
      blank_missile1_tripplefire2();
    }

    if (missile1_tripplefire1 == 1){
      missile1_tripplefire1_x = missile1_tripplefire1_x + 5;
      missile1_tripplefire1_y = missile1_tripplefire1_y + missile1_tripplefire1_y_dir;

      if (missile1_tripplefire1_y < 5){
        missile1_tripplefire1_y_dir = 1;
      }
      if (missile1_tripplefire1_y > (screen_height - 5)){
        missile1_tripplefire1_y_dir = -1;
      }

      if ( missile1_tripplefire1_x > (player2_x - 10) && missile1_tripplefire1_x < (player2_x + 10)) {
        if (missile1_tripplefire1_y > (player2_y - 1) && missile1_tripplefire1_y < (player2_y + paddle2_length + 1)) {
          player2_hitsremain--;
          if (player2_hitsremain < 1){
            blank_player_2();
            player2_y = (screen_height / 2) - (paddle2_length / 2);
            player_1_score++;
            if (player2_lives > 0) {
              player2_lives--;
            }
            paddle_length = 40;
            missile1_tripplefire1 = 0;
            missile2_tripplefire_enabled = 0;
            player2_hitsremain = player2_hitstotal;
          }
          missile1_tripplefire1 = 0;
        }
      }
    }

    if (missile1_tripplefire1_x > screen_width){
      missile1_tripplefire1 = 0;
      missile1_tripplefire1_x = 0;
    }

    if (missile1_tripplefire2 == 1){
      missile1_tripplefire2_x = missile1_tripplefire2_x + 5;
      missile1_tripplefire2_y = missile1_tripplefire2_y + missile1_tripplefire2_y_dir;

      if (missile1_tripplefire1_y < 5){
        missile1_tripplefire2_y_dir = 1;
      }
      if (missile1_tripplefire2_y > (screen_height - 5)){
        missile1_tripplefire2_y_dir = -1;
      }

      if ( missile1_tripplefire2_x > (player2_x - 10) && missile1_tripplefire2_x < (player2_x + 10)) {
        if (missile1_tripplefire2_y > (player2_y - 1) && missile1_tripplefire2_y < (player2_y + paddle2_length + 1)) {
          player2_hitsremain--;
          if (player2_hitsremain < 1){
            blank_player_2();
            player2_y = (screen_height / 2) - (paddle2_length / 2);
            player_1_score++;
            if (player2_lives > 0) {
              player2_lives--;
            }
            paddle_length = 40;
            missile1_tripplefire2 = 0;
            missile2_tripplefire_enabled = 0;
            player2_hitsremain = player2_hitstotal;
          }
          missile1_tripplefire2 = 0;
        }
      }
    }

    if (missile1_tripplefire2_x > screen_width){
      missile1_tripplefire2 = 0;
      missile1_tripplefire2_x = 0;
    }

    if (missile1_tripplefire1 == 1){
      draw_missile1_tripplefire1();
    }
    if (missile1_tripplefire2 == 1){
      draw_missile1_tripplefire2();
    }

    // --- Grenades 1 start ---

    if (missile1_grenade1 == 1){
      blank_missile1_grenade1();
    }
    if (missile1_grenade2 == 1){
      blank_missile1_grenade2();
    }

    if (missile1_grenade1 == 1){
      missile1_grenade1_x = missile1_grenade1_x + 3;
      missile1_grenade1_y = missile1_grenade1_y + missile1_grenade1_y_dir;

      if (missile1_grenade1_y < 5){
        missile1_grenade1_y_dir = 1;
      }
      if (missile1_grenade1_y > (screen_height - 5)){
        missile1_grenade1_y_dir = -1;
      }

      if ( missile1_grenade1_x > (player2_x - 10) && missile1_grenade1_x < (player2_x + 10)) {
        if (missile1_grenade1_y > (player2_y - 1) && missile1_grenade1_y < (player2_y + paddle2_length + 1)) {
          player2_hitsremain--;
          if (player2_hitsremain < 1){
            blank_player_2();
            player2_y = (screen_height / 2) - (paddle2_length / 2);
            player_1_score++;
            if (player2_lives > 0) {
              player2_lives--;
            }
            paddle_length = 40;
            missile1_grenade1 = 0;
            missile2_grenade_enabled = 0;
            player2_hitsremain = player2_hitstotal;
          }
          missile1_grenade1 = 0;
        }
      }
    }

    if (missile1_grenade1_x > screen_width){
      missile1_grenade1 = 0;
      missile1_grenade1_x = 0;
    }

    if (missile1_grenade2 == 1){
      missile1_grenade2_x = missile1_grenade2_x + 3;
      missile1_grenade2_y = missile1_grenade2_y + missile1_grenade2_y_dir;

      if (missile1_grenade1_y < 5){
        missile1_grenade2_y_dir = 1;
      }
      if (missile1_grenade2_y > (screen_height - 5)){
        missile1_grenade2_y_dir = -1;
      }

      if ( missile1_grenade2_x > (player2_x - 10) && missile1_grenade2_x < (player2_x + 10)) {
        if (missile1_grenade2_y > (player2_y - 1) && missile1_grenade2_y < (player2_y + paddle2_length + 1)) {
          player2_hitsremain--;
          if (player2_hitsremain < 1){
            blank_player_2();
            player2_y = (screen_height / 2) - (paddle2_length / 2);
            player_1_score++;
            if (player2_lives > 0) {
              player2_lives--;
            }
            paddle_length = 40;
            missile1_grenade2 = 0;
            missile2_grenade_enabled = 0;
            player2_hitsremain = player2_hitstotal;
          }
          missile1_grenade2 = 0;
        }
      }
    }

    if (missile1_grenade2_x > screen_width){
      missile1_grenade2 = 0;
      missile1_grenade2_x = 0;
    }

    if (missile1_grenade1 == 1){
      missile1_grenade1_rotation_count++;
      if (missile1_grenade1_rotation_count > missile1_grenade1_rotation_speed){
        missile1_grenade1_rotation_count = 0;
        missile1_grenade1_rotate++;
        if (missile1_grenade1_rotate > 3){
          missile1_grenade1_rotate = 1;
        }
      }
      draw_missile1_grenade1();
    }
    if (missile1_grenade2 == 1){
      missile1_grenade2_rotation_count++;
      if (missile1_grenade2_rotation_count > missile1_grenade2_rotation_speed){
        missile1_grenade2_rotation_count = 0;
        missile1_grenade2_rotate++;
        if (missile1_grenade2_rotate > 3){
          missile1_grenade2_rotate = 1;
        }
      }
      draw_missile1_grenade2();
    }

    // --- Grenades 1 end ---
}



void draw_missile2() {
  if (missile2_rotate == 1){
    tft.drawLine(missile2_x , missile2_y, missile2_x - 25, missile2_y + 5, TFT_RED);
    tft.drawLine(missile2_x , missile2_y + 10, missile2_x - 25, missile2_y + 5, TFT_RED);
    tft.drawLine(missile2_x , missile2_y, missile2_x, missile2_y + 10, TFT_RED);
    tft.drawPixel(missile2_x + 1, missile2_y + 3, TFT_DARKGREY);
    tft.drawPixel(missile2_x + 1, missile2_y + 7, TFT_DARKGREY);
  }
  if (missile2_rotate == 2){
    tft.drawLine(missile2_x , missile2_y + 1, missile2_x - 25, missile2_y + 5, TFT_RED);
    tft.drawLine(missile2_x , missile2_y + 9, missile2_x - 25, missile2_y + 5, TFT_RED);
    tft.drawLine(missile2_x , missile2_y + 1, missile2_x, missile2_y + 9, TFT_RED);
    tft.drawLine(missile2_x , missile2_y + 3, missile2_x - 25, missile2_y + 5, TFT_RED);
    tft.drawPixel(missile2_x + 1, missile2_y + 4, TFT_DARKGREY);

  }
  if (missile2_rotate == 3){
    tft.drawLine(missile2_x , missile2_y + 1, missile2_x - 25, missile2_y + 5, TFT_RED);
    tft.drawLine(missile2_x , missile2_y + 9, missile2_x - 25, missile2_y + 5, TFT_RED);
    tft.drawLine(missile2_x , missile2_y + 1, missile2_x, missile2_y + 9, TFT_RED);
    tft.drawLine(missile2_x , missile2_y + 6, missile2_x - 25, missile2_y + 5, TFT_RED);

    tft.drawPixel(missile2_x + 1, missile2_y + 6, TFT_DARKGREY);
  }
}

void blank_missile2() {
  if (missile2_rotate == 1){
    tft.drawLine(missile2_x , missile2_y, missile2_x - 25, missile2_y + 5, TFT_BLACK);
    tft.drawLine(missile2_x , missile2_y + 10, missile2_x - 25, missile2_y + 5, TFT_BLACK);
    tft.drawLine(missile2_x , missile2_y, missile2_x, missile2_y + 10, TFT_BLACK);
    tft.drawPixel(missile2_x + 46, missile2_y + 3, TFT_BLACK);
    tft.drawPixel(missile2_x + 46, missile2_y + 7, TFT_BLACK);
  }
    if (missile2_rotate == 2){
    tft.drawLine(missile2_x , missile2_y + 1, missile2_x - 25, missile2_y + 5, TFT_BLACK);
    tft.drawLine(missile2_x , missile2_y + 9, missile2_x - 25, missile2_y + 5, TFT_BLACK);
    tft.drawLine(missile2_x , missile2_y + 1, missile2_x, missile2_y + 9, TFT_BLACK);
    tft.drawLine(missile2_x , missile2_y + 3, missile2_x - 25, missile2_y + 5, TFT_BLACK);
    tft.drawPixel(missile2_x + 46, missile2_y + 4, TFT_BLACK);
  }
  if (missile2_rotate == 3){
    tft.drawLine(missile2_x , missile2_y + 1, missile2_x - 25, missile2_y + 5, TFT_BLACK);
    tft.drawLine(missile2_x , missile2_y + 9, missile2_x - 25, missile2_y + 5, TFT_BLACK);
    tft.drawLine(missile2_x , missile2_y +1, missile2_x, missile2_y + 9, TFT_BLACK);
    tft.drawLine(missile2_x , missile2_y + 6, missile2_x - 25, missile2_y + 5, TFT_BLACK);
    tft.drawPixel(missile2_x + 46, missile2_y + 6, TFT_BLACK);
  }

  missile2_exhaust++;
  if (missile2_exhaust > 10){
    tft.drawLine(missile2_x + 4 , missile2_y + 3, missile2_x + 56, missile2_y + 3, TFT_BLACK);
    tft.drawLine(missile2_x + 4 , missile2_y + 4, missile2_x + 56, missile2_y + 4, TFT_BLACK);
    tft.drawLine(missile2_x + 4 , missile2_y + 6, missile2_x + 56, missile2_y + 6, TFT_BLACK);
    tft.drawLine(missile2_x + 4 , missile2_y + 7, missile2_x + 56, missile2_y + 7, TFT_BLACK);
    missile2_exhaust = 0;
  }
}

void missile2_blank_exhaust(){
    tft.drawLine(missile2_x + 1 , missile2_y + 3, missile2_x + 56, missile2_y + 3, TFT_BLACK);
    tft.drawLine(missile2_x + 1 , missile2_y + 4, missile2_x + 56, missile2_y + 4, TFT_BLACK);
    tft.drawLine(missile2_x + 1 , missile2_y + 6, missile2_x + 56, missile2_y + 6, TFT_BLACK);
    tft.drawLine(missile2_x + 1 , missile2_y + 7, missile2_x + 56, missile2_y + 7, TFT_BLACK);
}

void draw_missile2_tripplefire1(){
  if (missile2_tripplefire1_y_dir == -1){
    tft.drawLine(missile2_tripplefire1_x + 10 , missile2_tripplefire1_y + 5, missile2_tripplefire1_x, missile2_tripplefire1_y, TFT_YELLOW);
  }
  if (missile2_tripplefire1_y_dir == 1){
    tft.drawLine(missile2_tripplefire1_x + 10 , missile2_tripplefire1_y - 5, missile2_tripplefire1_x, missile2_tripplefire1_y, TFT_YELLOW);
  }
}

void draw_missile2_tripplefire2(){
  if (missile2_tripplefire2_y_dir == -1){
    tft.drawLine(missile2_tripplefire2_x + 10 , missile2_tripplefire2_y + 5, missile2_tripplefire2_x, missile2_tripplefire2_y, TFT_YELLOW);
  }
  if (missile2_tripplefire2_y_dir == 1){
    tft.drawLine(missile2_tripplefire2_x + 10 , missile2_tripplefire2_y - 5, missile2_tripplefire2_x, missile2_tripplefire2_y, TFT_YELLOW);
  }
}

void blank_missile2_tripplefire1(){
  if (missile2_tripplefire1_y_dir == -1){
    tft.drawLine(missile2_tripplefire1_x + 10 , missile2_tripplefire1_y + 5, missile2_tripplefire1_x, missile2_tripplefire1_y, TFT_BLACK);
  }
  if (missile2_tripplefire1_y_dir == 1){
    tft.drawLine(missile2_tripplefire1_x + 10 , missile2_tripplefire1_y - 5, missile2_tripplefire1_x, missile2_tripplefire1_y, TFT_BLACK);
  }
}

void blank_missile2_tripplefire2(){
  if (missile2_tripplefire2_y_dir == -1){
    tft.drawLine(missile2_tripplefire2_x + 10 , missile2_tripplefire2_y + 5, missile2_tripplefire2_x, missile2_tripplefire2_y, TFT_BLACK);
  }
  if (missile2_tripplefire2_y_dir == 1){
    tft.drawLine(missile2_tripplefire2_x + 10 , missile2_tripplefire2_y - 5, missile2_tripplefire2_x, missile2_tripplefire2_y, TFT_BLACK);
  }
}

void draw_missile2_grenade1(){
  //
  if (missile2_grenade1_rotate == 1){
    tft.drawSmoothCircle(missile2_grenade1_x + 4 + 5, missile2_grenade1_y + 4 + 5, 5, TFT_DARKGREY, TFT_BLACK);
    tft.drawLine(missile2_grenade1_x + 4 + 5 , missile2_grenade1_y + 3, missile2_grenade1_x + 4 + 5, missile2_grenade1_y, TFT_DARKGREY);
    tft.drawLine(missile2_grenade1_x , missile2_grenade1_y + 4 + 5, missile2_grenade1_x + 3, missile2_grenade1_y + 4 + 5, TFT_DARKGREY);
    tft.drawLine(missile2_grenade1_x + 15 , missile2_grenade1_y + 4 + 5, missile2_grenade1_x + 15 + 3, missile2_grenade1_y + 4 + 5, TFT_DARKGREY);
    tft.drawLine(missile2_grenade1_x + 4 + 5 , missile2_grenade1_y + 15, missile2_grenade1_x + 4 + 5, missile2_grenade1_y + 15 + 3, TFT_DARKGREY);
  }
  if (missile2_grenade1_rotate == 2) {
    tft.drawSmoothCircle(missile2_grenade1_x + 4 + 5, missile2_grenade1_y + 4 + 5, 5, TFT_DARKGREY, TFT_BLACK);
    tft.drawLine(missile2_grenade1_x + 5 + 6 , missile2_grenade1_y + 3, missile2_grenade1_x + 5 + 7, missile2_grenade1_y, TFT_DARKGREY);
    tft.drawLine(missile2_grenade1_x , missile2_grenade1_y + 3 + 3, missile2_grenade1_x + 3, missile2_grenade1_y + 3 + 4, TFT_DARKGREY);
    tft.drawLine(missile2_grenade1_x + 15 , missile2_grenade1_y + 5 + 6, missile2_grenade1_x + 15 + 3, missile2_grenade1_y + 5 + 7, TFT_DARKGREY);
    tft.drawLine(missile2_grenade1_x + 3 + 4 , missile2_grenade1_y + 15, missile2_grenade1_x + 3 + 3, missile2_grenade1_y + 15 + 3, TFT_DARKGREY);
  }
  if (missile2_grenade1_rotate == 3) {
    tft.drawSmoothCircle(missile2_grenade1_x + 4 + 5, missile2_grenade1_y + 4 + 5, 5, TFT_DARKGREY, TFT_BLACK);
    tft.drawLine(missile2_grenade1_x + 3 + 4 , missile2_grenade1_y + 3, missile2_grenade1_x + 3 + 3, missile2_grenade1_y, TFT_DARKGREY);
    tft.drawLine(missile2_grenade1_x + 3, missile2_grenade1_y + 5 + 6, missile2_grenade1_x, missile2_grenade1_y + 5 + 7, TFT_DARKGREY);
    tft.drawLine(missile2_grenade1_x + 15 , missile2_grenade1_y + 3 + 4, missile2_grenade1_x + 15 + 3, missile2_grenade1_y + 3 + 3, TFT_DARKGREY);
    tft.drawLine(missile2_grenade1_x + 5 + 6 , missile2_grenade1_y + 15, missile2_grenade1_x + 5 + 7, missile2_grenade1_y + 15 + 3, TFT_DARKGREY);
  }
}

void draw_missile2_grenade2(){
  //
  if (missile2_grenade2_rotate == 1){
    tft.drawSmoothCircle(missile2_grenade2_x + 4 + 5, missile2_grenade2_y + 4 + 5, 5, TFT_DARKGREY, TFT_BLACK);
    tft.drawLine(missile2_grenade2_x + 4 + 5 , missile2_grenade2_y + 3, missile2_grenade2_x + 4 + 5, missile2_grenade2_y, TFT_DARKGREY);
    tft.drawLine(missile2_grenade2_x , missile2_grenade2_y + 4 + 5, missile2_grenade2_x + 3, missile2_grenade2_y + 4 + 5, TFT_DARKGREY);
    tft.drawLine(missile2_grenade2_x + 15 , missile2_grenade2_y + 4 + 5, missile2_grenade2_x + 15 + 3, missile2_grenade2_y + 4 + 5, TFT_DARKGREY);
    tft.drawLine(missile2_grenade2_x + 4 + 5 , missile2_grenade2_y + 15, missile2_grenade2_x + 4 + 5, missile2_grenade2_y + 15 + 3, TFT_DARKGREY);
  }
  if (missile2_grenade2_rotate == 2) {
    tft.drawSmoothCircle(missile2_grenade2_x + 4 + 5, missile2_grenade2_y + 4 + 5, 5, TFT_DARKGREY, TFT_BLACK);
    tft.drawLine(missile2_grenade2_x + 5 + 6 , missile2_grenade2_y + 3, missile2_grenade2_x + 5 + 7, missile2_grenade2_y, TFT_DARKGREY);
    tft.drawLine(missile2_grenade2_x , missile2_grenade2_y + 3 + 3, missile2_grenade2_x + 3, missile2_grenade2_y + 3 + 4, TFT_DARKGREY);
    tft.drawLine(missile2_grenade2_x + 15 , missile2_grenade2_y + 5 + 6, missile2_grenade2_x + 15 + 3, missile2_grenade2_y + 5 + 7, TFT_DARKGREY);
    tft.drawLine(missile2_grenade2_x + 3 + 4 , missile2_grenade2_y + 15, missile2_grenade2_x + 3 + 3, missile2_grenade2_y + 15 + 3, TFT_DARKGREY);
  }
  if (missile2_grenade2_rotate == 3) {
    tft.drawSmoothCircle(missile2_grenade2_x + 4 + 5, missile2_grenade2_y + 4 + 5, 5, TFT_DARKGREY, TFT_BLACK);
    tft.drawLine(missile2_grenade2_x + 3 + 4 , missile2_grenade2_y + 3, missile2_grenade2_x + 3 + 3, missile2_grenade2_y, TFT_DARKGREY);
    tft.drawLine(missile2_grenade2_x + 3, missile2_grenade2_y + 5 + 6, missile2_grenade2_x, missile2_grenade2_y + 5 + 7, TFT_DARKGREY);
    tft.drawLine(missile2_grenade2_x + 15 , missile2_grenade2_y + 3 + 4, missile2_grenade2_x + 15 + 3, missile2_grenade2_y + 3 + 3, TFT_DARKGREY);
    tft.drawLine(missile2_grenade1_x + 5 + 6 , missile2_grenade2_y + 15, missile2_grenade2_x + 5 + 7, missile2_grenade2_y + 15 + 3, TFT_DARKGREY);
  }
}

void blank_missile2_grenade1(){
  //
  if (missile2_grenade1_rotate == 1){
    tft.drawSmoothCircle(missile2_grenade1_x + 4 + 5, missile2_grenade1_y + 4 + 5, 5, TFT_BLACK, TFT_BLACK);
    tft.drawLine(missile2_grenade1_x + 4 + 5 , missile2_grenade1_y + 3, missile2_grenade1_x + 4 + 5, missile2_grenade1_y, TFT_BLACK);
    tft.drawLine(missile2_grenade1_x , missile2_grenade1_y + 4 + 5, missile2_grenade1_x + 3, missile2_grenade1_y + 4 + 5, TFT_BLACK);
    tft.drawLine(missile2_grenade1_x + 15 , missile2_grenade1_y + 4 + 5, missile2_grenade1_x + 15 + 3, missile2_grenade1_y + 4 + 5, TFT_BLACK);
    tft.drawLine(missile2_grenade1_x + 4 + 5 , missile2_grenade1_y + 15, missile2_grenade1_x + 4 + 5, missile2_grenade1_y + 15 + 3, TFT_BLACK);
  }
  if (missile2_grenade1_rotate == 2) {
    tft.drawSmoothCircle(missile2_grenade1_x + 4 + 5, missile2_grenade1_y + 4 + 5, 5, TFT_BLACK, TFT_BLACK);
    tft.drawLine(missile2_grenade1_x + 5 + 6 , missile2_grenade1_y + 3, missile2_grenade1_x + 5 + 7, missile2_grenade1_y, TFT_BLACK);
    tft.drawLine(missile2_grenade1_x , missile2_grenade1_y + 3 + 3, missile2_grenade1_x + 3, missile2_grenade1_y + 3 + 4, TFT_BLACK);
    tft.drawLine(missile2_grenade1_x + 15 , missile2_grenade1_y + 5 + 6, missile2_grenade1_x + 15 + 3, missile2_grenade1_y + 5 + 7, TFT_BLACK);
    tft.drawLine(missile2_grenade1_x + 3 + 4 , missile2_grenade1_y + 15, missile2_grenade1_x + 3 + 3, missile2_grenade1_y + 15 + 3, TFT_BLACK);
  }
  if (missile2_grenade1_rotate == 3) {
    tft.drawSmoothCircle(missile2_grenade1_x + 4 + 5, missile2_grenade1_y + 4 + 5, 5, TFT_BLACK, TFT_BLACK);
    tft.drawLine(missile2_grenade1_x + 3 + 4 , missile2_grenade1_y + 3, missile2_grenade1_x + 3 + 3, missile2_grenade1_y, TFT_BLACK);
    tft.drawLine(missile2_grenade1_x + 3, missile2_grenade1_y + 5 + 6, missile2_grenade1_x, missile2_grenade1_y + 5 + 7, TFT_BLACK);
    tft.drawLine(missile2_grenade1_x + 15 , missile2_grenade1_y + 3 + 4, missile2_grenade1_x + 15 + 3, missile2_grenade1_y + 3 + 3, TFT_BLACK);
    tft.drawLine(missile2_grenade1_x + 5 + 6 , missile2_grenade1_y + 15, missile2_grenade1_x + 5 + 7, missile2_grenade1_y + 15 + 3, TFT_BLACK);
  }
}

void blank_missile2_grenade2(){
  //
  if (missile2_grenade2_rotate == 1){
    tft.drawSmoothCircle(missile2_grenade2_x + 4 + 5, missile2_grenade2_y + 4 + 5, 5, TFT_BLACK, TFT_BLACK);
    tft.drawLine(missile2_grenade2_x + 4 + 5 , missile2_grenade2_y + 3, missile2_grenade2_x + 4 + 5, missile2_grenade2_y, TFT_BLACK);
    tft.drawLine(missile2_grenade2_x , missile2_grenade2_y + 4 + 5, missile2_grenade2_x + 3, missile2_grenade2_y + 4 + 5, TFT_BLACK);
    tft.drawLine(missile2_grenade2_x + 15 , missile2_grenade2_y + 4 + 5, missile2_grenade2_x + 15 + 3, missile2_grenade2_y + 4 + 5, TFT_BLACK);
    tft.drawLine(missile2_grenade2_x + 4 + 5 , missile2_grenade2_y + 15, missile2_grenade2_x + 4 + 5, missile2_grenade2_y + 15 + 3, TFT_BLACK);
  }
  if (missile2_grenade2_rotate == 2) {
    tft.drawSmoothCircle(missile2_grenade2_x + 4 + 5, missile2_grenade2_y + 4 + 5, 5, TFT_BLACK, TFT_BLACK);
    tft.drawLine(missile2_grenade2_x + 5 + 6 , missile2_grenade2_y + 3, missile2_grenade2_x + 5 + 7, missile2_grenade2_y, TFT_BLACK);
    tft.drawLine(missile2_grenade2_x , missile2_grenade2_y + 3 + 3, missile2_grenade2_x + 3, missile2_grenade2_y + 3 + 4, TFT_BLACK);
    tft.drawLine(missile2_grenade2_x + 15 , missile2_grenade2_y + 5 + 6, missile2_grenade2_x + 15 + 3, missile2_grenade2_y + 5 + 7, TFT_BLACK);
    tft.drawLine(missile2_grenade2_x + 3 + 4 , missile2_grenade2_y + 15, missile2_grenade2_x + 3 + 3, missile2_grenade2_y + 15 + 3, TFT_BLACK);
  }
  if (missile2_grenade2_rotate == 3) {
    tft.drawSmoothCircle(missile2_grenade2_x + 4 + 5, missile2_grenade2_y + 4 + 5, 5, TFT_BLACK, TFT_BLACK);
    tft.drawLine(missile2_grenade2_x + 3 + 4 , missile2_grenade2_y + 3, missile2_grenade2_x + 3 + 3, missile2_grenade2_y, TFT_BLACK);
    tft.drawLine(missile2_grenade2_x + 3, missile2_grenade2_y + 5 + 6, missile2_grenade2_x, missile2_grenade2_y + 5 + 7, TFT_BLACK);
    tft.drawLine(missile2_grenade2_x + 15 , missile2_grenade2_y + 3 + 4, missile2_grenade2_x + 15 + 3, missile2_grenade2_y + 3 + 3, TFT_BLACK);
    tft.drawLine(missile2_grenade1_x + 5 + 6 , missile2_grenade2_y + 15, missile2_grenade2_x + 5 + 7, missile2_grenade2_y + 15 + 3, TFT_BLACK);
  }
}


void do_missile2() {
    int val = -1;
    int random_number = 0;

    if (missile2 == 0 ) {
      // val = digitalRead(ENCODER_KEY);
      // random_number = rand() % 101;
      random_number = random(100);
      if (random_number > 98) {
        // launch player 1 missile
        missile2_x = player2_x + 35;
        missile2_y = player2_y + (paddle2_length / 2) - 5;
        random_number = random(3, 6);
        missile_speed2 = random_number;
        missile2_exhaust = 0;
        missile2 = 1;

        if (missile2_tripplefire_enabled == 1){
          if (missile2_tripplefire1 == 0){
            missile2_tripplefire1_x = player2_x + 10;
            missile2_tripplefire1_y = player2_y + (paddle2_length / 2);
            missile2_tripplefire1_y_dir = -1;
            missile2_tripplefire1 = 1;
          }

          if (missile2_tripplefire2 == 0){
            missile2_tripplefire2_y = player2_y + (paddle2_length / 2);
            missile2_tripplefire2_x = player2_x + 10;
            missile2_tripplefire2_y_dir = 1;
            missile2_tripplefire2 = 1;
          }
        }

        if (missile2_grenade_enabled == 1){
          if (missile2_grenade1 == 0){
            missile2_grenade1_x = player2_x + 10;
            missile2_grenade1_y = player2_y + (paddle2_length / 2);
            missile2_grenade1_y_dir = -1;
            missile2_grenade1 = 1;
          }

          if (missile2_grenade2 == 0){
            missile2_grenade2_y = player2_y + (paddle2_length / 2);
            missile2_grenade2_x = player2_x + 10;
            missile2_grenade2_y_dir = 1;
            missile2_grenade2 = 1;
          }
        }
      }
      random_number = 0;
    } else {
      blank_missile2();
      missile2_x = missile2_x - missile_speed2;
      if ( missile2_x > (player_x) && missile2_x < (player_x + 5)) {
        if (missile2_y > (player_y - 5) && (missile2_y+10) < (player_y + paddle_length + 5)) {
          player1_hitsremain--;
          if (player1_hitsremain < 1){
            blank_player_1();
            missile2_blank_exhaust();
            player_y = (screen_height / 2) - (paddle_length / 2);
            player_2_score++;
            if (player1_lives > 0) {
              player1_lives--;
            }
            paddle_length = 40;
            missile2 = 0;
            missile1_tripplefire_enabled = 0;
            player1_hitsremain = player1_hitstotal;
          }
          missile2 = 0;
        }
      }
      if ( missile2_x < -25 ) {
        missile2_blank_exhaust();
        missile2_x = 0;
        missile2_y = 0;
        missile2 = 0;
      }
    }
    if (missile2 == 1) {
      missile2_rotation_count++;
      if (missile2_rotation_count > missile2_rotation_speed){
        missile2_rotation_count = 0;
        missile2_rotate++;
        if (missile2_rotate > 3){
          missile2_rotate = 1;
        }
      }
      draw_missile2();
    }

    if (missile2_tripplefire1 == 1){
      blank_missile2_tripplefire1();
    }
    if (missile2_tripplefire2 == 1){
      blank_missile2_tripplefire2();
    }

    if (missile2_tripplefire1 == 1){
      missile2_tripplefire1_x = missile2_tripplefire1_x - 5;
      missile2_tripplefire1_y = missile2_tripplefire1_y + missile2_tripplefire1_y_dir;

      if (missile2_tripplefire1_y < 5){
        missile2_tripplefire1_y_dir = 1;
      }
      if (missile2_tripplefire1_y > (screen_height - 5)){
        missile2_tripplefire1_y_dir = -1;
      }

      if ( missile2_tripplefire1_x > (player_x) && missile2_tripplefire1_x < (player_x + 20)) {
        if (missile2_tripplefire1_y > (player_y - 5) && missile2_tripplefire1_y < (player_y + paddle_length + 3)) {
          player1_hitsremain--;
          if (player1_hitsremain < 1){
            blank_player_1();
            missile2_blank_exhaust();
            player_y = (screen_height / 2) - (paddle_length / 2);
            player_2_score++;
            if (player1_lives > 0) {
              player1_lives--;
            }
            paddle_length = 40;
            // missile2 = 0;
            missile1_tripplefire_enabled = 0;
            missile2_tripplefire1 = 0;
            player1_hitsremain = player1_hitstotal;
          }
          missile2_tripplefire1 = 0;
        }
      }
    }

    if (missile2_tripplefire1_x < 0){
      missile2_tripplefire1 = 0;
      missile2_tripplefire1_x = 0;
    }

    if (missile2_tripplefire2 == 1){
      missile2_tripplefire2_x = missile2_tripplefire2_x - 5;
      missile2_tripplefire2_y = missile2_tripplefire2_y + missile2_tripplefire2_y_dir;

      if (missile2_tripplefire2_y < 5){
        missile2_tripplefire2_y_dir = 1;
      }
      if (missile2_tripplefire2_y > (screen_height - 5)){
        missile2_tripplefire2_y_dir = -1;
      }

      if ( missile2_tripplefire2_x > (player_x) && missile2_tripplefire2_x < (player_x + 20)) {
        if (missile2_tripplefire2_y > (player_y - 5) && missile2_tripplefire2_y < (player2_y + paddle2_length + 3)) {
          player1_hitsremain--;
          if (player1_hitsremain < 1){
            blank_player_1();
            missile2_blank_exhaust();
            player_y = (screen_height / 2) - (paddle_length / 2);
            player_2_score++;
            if (player1_lives > 0) {
              player1_lives--;
            }
            paddle_length = 40;
            // missile2 = 0;
            missile1_tripplefire_enabled = 0;
            missile2_tripplefire2 = 0;
            player1_hitsremain = player1_hitstotal;
          }
          missile2_tripplefire2 = 0;
        }
      }
    }

    if (missile2_tripplefire2_x < 0){
      missile2_tripplefire2 = 0;
      missile2_tripplefire2_x = 0;
    }

    if (missile2_tripplefire1 == 1){
      draw_missile2_tripplefire1();
    }
    if (missile2_tripplefire2 == 1){
      draw_missile2_tripplefire2();
    }

    // --- Grenades 2 start ---

    if (missile2_grenade1 == 1){
      blank_missile2_grenade1();
    }
    if (missile2_grenade2 == 1){
      blank_missile2_grenade2();
    }

    if (missile2_grenade1 == 1){
      missile2_grenade1_x = missile2_grenade1_x - 3;
      missile2_grenade1_y = missile2_grenade1_y + missile2_grenade1_y_dir;

      if (missile2_grenade1_y < 5){
        missile2_grenade1_y_dir = 1;
      }
      if (missile2_grenade1_y > (screen_height - 5)){
        missile2_grenade1_y_dir = -1;
      }

      if ( missile2_grenade1_x > (player_x) && missile2_grenade1_x < (player_x + 20)) {
        if (missile2_grenade1_y > (player_y - 5) && missile2_grenade1_y < (player_y + paddle_length + 3)) {
          player1_hitsremain--;
          if (player1_hitsremain < 1){
            blank_player_1();
            missile2_blank_exhaust();
            player_y = (screen_height / 2) - (paddle_length / 2);
            player_2_score++;
            if (player1_lives > 0) {
              player1_lives--;
            }
            paddle_length = 40;
            // missile2 = 0;
            missile1_grenade_enabled = 0;
            missile2_grenade1 = 0;
            player1_hitsremain = player1_hitstotal;
          }
          missile2_grenade1 = 0;
        }
      }
    }

    if (missile2_grenade1_x < 0){
      missile2_grenade1 = 0;
      missile2_grenade1_x = 0;
    }

    if (missile2_grenade2 == 1){
      missile2_grenade2_x = missile2_grenade2_x - 3;
      missile2_grenade2_y = missile2_grenade2_y + missile2_grenade2_y_dir;

      if (missile2_grenade2_y < 5){
        missile2_grenade2_y_dir = 1;
      }
      if (missile2_grenade2_y > (screen_height - 5)){
        missile2_grenade2_y_dir = -1;
      }

      if ( missile2_grenade2_x > (player_x) && missile2_grenade2_x < (player_x + 20)) {
        if (missile2_grenade2_y > (player_y - 5) && missile2_grenade2_y < (player2_y + paddle2_length + 3)) {
          player1_hitsremain--;
          if (player1_hitsremain < 1){
            blank_player_1();
            missile2_blank_exhaust();
            player_y = (screen_height / 2) - (paddle_length / 2);
            player_2_score++;
            if (player1_lives > 0) {
              player1_lives--;
            }
            paddle_length = 40;
            // missile2 = 0;
            missile1_grenade_enabled = 0;
            missile2_grenade2 = 0;
            player1_hitsremain = player1_hitstotal;
          }
          missile2_grenade2 = 0;
        }
      }
    }

    if (missile2_grenade2_x < 0){
      missile2_grenade2 = 0;
      missile2_grenade2_x = 0;
    }

    if (missile2_grenade1 == 1){
      missile2_grenade1_rotation_count++;
      if (missile2_grenade1_rotation_count > missile2_grenade1_rotation_speed){
        missile2_grenade1_rotation_count = 0;
        missile2_grenade1_rotate++;
        if (missile2_grenade1_rotate > 3){
          missile2_grenade1_rotate = 1;
        }
      }
      draw_missile2_grenade1();
    }
    if (missile2_grenade2 == 1){
      missile2_grenade2_rotation_count++;
      if (missile2_grenade2_rotation_count > missile2_grenade2_rotation_speed){
        missile2_grenade2_rotation_count = 0;
        missile2_grenade2_rotate++;
        if (missile2_grenade2_rotate > 3){
          missile2_grenade2_rotate = 1;
        }
      }
      draw_missile2_grenade2();
    }

    // --- Grenade 2 end ---
}


void draw_diamond_1(){
  if (diamond1_rotate == 1){
    tft.drawLine(diamond1_x + 10 , diamond1_y, diamond1_x, diamond1_y + 10, diamond1_colour);
    tft.drawLine(diamond1_x , diamond1_y + 10, diamond1_x + 10, diamond1_y + 20, diamond1_colour);
    tft.drawLine(diamond1_x + 10 , diamond1_y + 20, diamond1_x + 20, diamond1_y + 10, diamond1_colour);
    tft.drawLine(diamond1_x + 20 , diamond1_y + 10, diamond1_x + 10 , diamond1_y, diamond1_colour);
    tft.drawLine(diamond1_x, diamond1_y + 10, diamond1_x + 20 , diamond1_y + 10, diamond1_colour);
    tft.drawLine(diamond1_x + 10, diamond1_y, diamond1_x + 10 , diamond1_y + 20, diamond1_colour);
  }

  if (diamond1_rotate == 2){
    tft.drawLine(diamond1_x + 10 , diamond1_y, diamond1_x+3, diamond1_y + 10, diamond1_colour);
    tft.drawLine(diamond1_x + 3 , diamond1_y + 10, diamond1_x + 10, diamond1_y + 20, diamond1_colour);
    tft.drawLine(diamond1_x + 10 , diamond1_y + 20, diamond1_x + 17, diamond1_y + 10, diamond1_colour);
    tft.drawLine(diamond1_x + 17 , diamond1_y + 10, diamond1_x + 10 , diamond1_y, diamond1_colour);
    tft.drawLine(diamond1_x + 3, diamond1_y + 10, diamond1_x + 17 , diamond1_y + 10, diamond1_colour);

    tft.drawLine(diamond1_x + 10, diamond1_y, diamond1_x + 6 , diamond1_y + 10, diamond1_colour);
    tft.drawLine(diamond1_x + 6, diamond1_y + 10, diamond1_x + 10 , diamond1_y + 20, diamond1_colour);
    tft.drawLine(diamond1_x + 10, diamond1_y, diamond1_x + 13 , diamond1_y + 10, diamond1_colour);
    tft.drawLine(diamond1_x + 13, diamond1_y + 10, diamond1_x + 10 , diamond1_y + 20, diamond1_colour);
  }

  if (diamond1_rotate == 3){
    tft.drawLine(diamond1_x + 10 , diamond1_y, diamond1_x+3, diamond1_y + 10, diamond1_colour);
    tft.drawLine(diamond1_x + 3 , diamond1_y + 10, diamond1_x + 10, diamond1_y + 20, diamond1_colour);
    tft.drawLine(diamond1_x + 10 , diamond1_y + 20, diamond1_x + 17, diamond1_y + 10, diamond1_colour);
    tft.drawLine(diamond1_x + 17 , diamond1_y + 10, diamond1_x + 10 , diamond1_y, diamond1_colour);
    tft.drawLine(diamond1_x + 3, diamond1_y + 10, diamond1_x + 17 , diamond1_y + 10, diamond1_colour);

    tft.drawLine(diamond1_x + 10, diamond1_y, diamond1_x + 8 , diamond1_y + 10, diamond1_colour);
    tft.drawLine(diamond1_x + 8, diamond1_y + 10, diamond1_x + 10 , diamond1_y + 20, diamond1_colour);
    tft.drawLine(diamond1_x + 10, diamond1_y, diamond1_x + 15 , diamond1_y + 10, diamond1_colour);
    tft.drawLine(diamond1_x + 15, diamond1_y + 10, diamond1_x + 10 , diamond1_y + 20, diamond1_colour);
  }
}

void blank_diamond_1(){
  if (diamond1_rotate == 1){
    tft.drawLine(diamond1_x + 10 , diamond1_y, diamond1_x, diamond1_y + 10, TFT_BLACK);
    tft.drawLine(diamond1_x , diamond1_y + 10, diamond1_x + 10, diamond1_y + 20, TFT_BLACK);
    tft.drawLine(diamond1_x + 10 , diamond1_y + 20, diamond1_x + 20, diamond1_y + 10, TFT_BLACK);
    tft.drawLine(diamond1_x + 20 , diamond1_y + 10, diamond1_x + 10 , diamond1_y, TFT_BLACK);
    tft.drawLine(diamond1_x, diamond1_y + 10, diamond1_x + 20 , diamond1_y + 10, TFT_BLACK);
    tft.drawLine(diamond1_x + 10, diamond1_y, diamond1_x + 10 , diamond1_y + 20, TFT_BLACK);
  }

  if (diamond1_rotate == 2){
    tft.drawLine(diamond1_x + 10 , diamond1_y, diamond1_x+3, diamond1_y + 10, TFT_BLACK);
    tft.drawLine(diamond1_x + 3 , diamond1_y + 10, diamond1_x + 10, diamond1_y + 20, TFT_BLACK);
    tft.drawLine(diamond1_x + 10 , diamond1_y + 20, diamond1_x + 17, diamond1_y + 10, TFT_BLACK);
    tft.drawLine(diamond1_x + 17 , diamond1_y + 10, diamond1_x + 10 , diamond1_y, TFT_BLACK);
    tft.drawLine(diamond1_x + 3, diamond1_y + 10, diamond1_x + 17 , diamond1_y + 10, TFT_BLACK);

    tft.drawLine(diamond1_x + 10, diamond1_y, diamond1_x + 6 , diamond1_y + 10, TFT_BLACK);
    tft.drawLine(diamond1_x + 6, diamond1_y + 10, diamond1_x + 10 , diamond1_y + 20, TFT_BLACK);
    tft.drawLine(diamond1_x + 10, diamond1_y, diamond1_x + 13 , diamond1_y + 10, TFT_BLACK);
    tft.drawLine(diamond1_x + 13, diamond1_y + 10, diamond1_x + 10 , diamond1_y + 20, TFT_BLACK);
  }

  if (diamond1_rotate == 3){
    tft.drawLine(diamond1_x + 10 , diamond1_y, diamond1_x+3, diamond1_y + 10, TFT_BLACK);
    tft.drawLine(diamond1_x + 3 , diamond1_y + 10, diamond1_x + 10, diamond1_y + 20, TFT_BLACK);
    tft.drawLine(diamond1_x + 10 , diamond1_y + 20, diamond1_x + 17, diamond1_y + 10, TFT_BLACK);
    tft.drawLine(diamond1_x + 17 , diamond1_y + 10, diamond1_x + 10 , diamond1_y, TFT_BLACK);
    tft.drawLine(diamond1_x + 3, diamond1_y + 10, diamond1_x + 17 , diamond1_y + 10, TFT_BLACK);

    tft.drawLine(diamond1_x + 10, diamond1_y, diamond1_x + 8 , diamond1_y + 10, TFT_BLACK);
    tft.drawLine(diamond1_x + 8, diamond1_y + 10, diamond1_x + 10 , diamond1_y + 20, TFT_BLACK);
    tft.drawLine(diamond1_x + 10, diamond1_y, diamond1_x + 15 , diamond1_y + 10, TFT_BLACK);
    tft.drawLine(diamond1_x + 15, diamond1_y + 10, diamond1_x + 10 , diamond1_y + 20, TFT_BLACK);
  }
}


void do_diamond_1(){
  int val = 0;
  int val2 = 0;

  if (diamond1 == 0){
    val = random(200);
    if (val > 198){
      val = random(screen_height - 20);
      diamond1_x = screen_width;
      diamond1_y = val;
      diamond1 = 1;

      val = random(3) - 1;
      diamond1_y_dir = val;

      val2 = random(1,6);
      diamond1_type = val2;

      if (val2 == 1){
        diamond1_colour = TFT_YELLOW;
      }
      if (val2 == 2){
        diamond1_colour = TFT_PURPLE;
      }
      if (val2 == 3){
        diamond1_colour = TFT_BLUE;
      }
      if (val2 == 4){
        diamond1_colour = TFT_CYAN;
      }
      if (val2 == 5){
        diamond1_colour = TFT_ORANGE;
      }
      if (val2 == 6){
        diamond1_colour = TFT_DARKGREY;
      }
    }
  } else {
    blank_diamond_1();

    diamond1_rotation_count++;
    if (diamond1_rotation_count > diamond1_rotation_speed){
      diamond1_rotation_count = 0;
      diamond1_rotate++;
      if (diamond1_rotate > 3){
        diamond1_rotate = 1;
      }
    } 

    // diamond1_rotate++;
    // if (diamond1_rotate > 3){
    //   diamond1_rotate = 1;
    // }
    diamond1_x = diamond1_x + (diamond1_dir * diamond1_speed);
    diamond1_y = diamond1_y + diamond1_y_dir;
    if ( diamond1_y < 0){
      diamond1_y_dir = 1;
    }
    if ( diamond1_y > screen_height-20){
      diamond1_y_dir = -1;
    }

    if ( diamond1_x > (player_x) && diamond1_x < (player_x+10)) {
      if (diamond1_y > (player_y - 20) && (diamond1_y+20) < (player_y + paddle_length + 20)) {
        diamond1 = 0;
        if (diamond1_type == 1){
          blank_player_1();
          if (paddle_length == 40){
            paddle_length = 20;
          } else if (paddle_length == 20){
            paddle_length = 40;
          } else if (paddle_length = 80){
            paddle_length = 40;
          }
        }
        if (diamond1_type == 2){
          blank_player_1();
          if (paddle_length == 20){
            paddle_length = 40;
          } else if (paddle_length == 40){
            paddle_length = 80;
          } else if (paddle_length = 80){
            paddle_length = 40;
          }
        }
        if (diamond1_type == 3){
          if (missile1_tripplefire_enabled == 0){
            missile1_tripplefire_enabled = 1;
            missile1_tripplefire1 = 0;
            missile1_tripplefire2 = 0;
          } else if (missile1_tripplefire_enabled == 1){
            missile1_tripplefire_enabled = 0;
            missile1_tripplefire1 = 0;
            missile1_tripplefire2 = 0;
          }
        }
        if (diamond1_type == 4){
          if (ball2_enabled == 0){
            ball2_enabled = 1;
            ball2_x = (screen_width / 2);
            // ball2_y = (screen_height / 2);
            ball2_y = 1;
            ball2_y_dir = -1;
            ball2_x_dir = 1;
          } else if (ball3_enabled == 0) {
            ball3_enabled = 1;
            ball3_x = (screen_width / 2);
            // ball3_y = (screen_height / 2);
            ball3_y = 1;
            ball3_y_dir = 1;
            ball3_x_dir = -1;
          }
        }
        if (diamond1_type == 5){
          if (missile1_grenade_enabled == 0){
            missile1_grenade_enabled = 1;
            missile1_grenade1 = 0;
            missile1_grenade2 = 0;
          } else if (missile1_grenade_enabled == 1){
            missile1_grenade_enabled = 0;
            missile1_grenade1 = 0;
            missile1_grenade2 = 0;
          }
        }
      }
    }
    if (diamond1_x < -20){
      diamond1 = 0;
    }
    if (diamond1 == 1) {           
      draw_diamond_1();
    }
  }
}



void draw_diamond_2(){


  if (diamond2_rotate == 1){
    tft.drawLine(diamond2_x + 10 , diamond2_y, diamond2_x, diamond2_y + 10, diamond2_colour);
    tft.drawLine(diamond2_x , diamond2_y + 10, diamond2_x + 10, diamond2_y + 20, diamond2_colour);
    tft.drawLine(diamond2_x + 10 , diamond2_y + 20, diamond2_x + 20, diamond2_y + 10, diamond2_colour);
    tft.drawLine(diamond2_x + 20 , diamond2_y + 10, diamond2_x + 10 , diamond2_y, diamond2_colour);
    tft.drawLine(diamond2_x, diamond2_y + 10, diamond2_x + 20 , diamond2_y + 10, diamond2_colour);
    tft.drawLine(diamond2_x + 10, diamond2_y, diamond2_x + 10 , diamond2_y + 20, diamond2_colour);
  }

    if (diamond2_rotate == 2){
    tft.drawLine(diamond2_x + 10 , diamond2_y, diamond2_x+3, diamond2_y + 10, diamond2_colour);
    tft.drawLine(diamond2_x + 3 , diamond2_y + 10, diamond2_x + 10, diamond2_y + 20, diamond2_colour);
    tft.drawLine(diamond2_x + 10 , diamond2_y + 20, diamond2_x + 17, diamond2_y + 10, diamond2_colour);
    tft.drawLine(diamond2_x + 17 , diamond2_y + 10, diamond2_x + 10 , diamond2_y, diamond2_colour);
    tft.drawLine(diamond2_x + 3, diamond2_y + 10, diamond2_x + 17 , diamond2_y + 10, diamond2_colour);

    tft.drawLine(diamond2_x + 10, diamond2_y, diamond2_x + 6 , diamond2_y + 10, diamond2_colour);
    tft.drawLine(diamond2_x + 6, diamond2_y + 10, diamond2_x + 10 , diamond2_y + 20, diamond2_colour);
    tft.drawLine(diamond2_x + 10, diamond2_y, diamond2_x + 13 , diamond2_y + 10, diamond2_colour);
    tft.drawLine(diamond2_x + 13, diamond2_y + 10, diamond2_x + 10 , diamond2_y + 20, diamond2_colour);
  }

      if (diamond2_rotate == 3){
    tft.drawLine(diamond2_x + 10 , diamond2_y, diamond2_x+3, diamond2_y + 10, diamond2_colour);
    tft.drawLine(diamond2_x + 3 , diamond2_y + 10, diamond2_x + 10, diamond2_y + 20, diamond2_colour);
    tft.drawLine(diamond2_x + 10 , diamond2_y + 20, diamond2_x + 17, diamond2_y + 10, diamond2_colour);
    tft.drawLine(diamond2_x + 17 , diamond2_y + 10, diamond2_x + 10 , diamond2_y, diamond2_colour);
    tft.drawLine(diamond2_x + 3, diamond2_y + 10, diamond2_x + 17 , diamond2_y + 10, diamond2_colour);

    tft.drawLine(diamond2_x + 10, diamond2_y, diamond2_x + 8 , diamond2_y + 10, diamond2_colour);
    tft.drawLine(diamond2_x + 8, diamond2_y + 10, diamond2_x + 10 , diamond2_y + 20, diamond2_colour);
    tft.drawLine(diamond2_x + 10, diamond2_y, diamond2_x + 15 , diamond2_y + 10, diamond2_colour);
    tft.drawLine(diamond2_x + 15, diamond2_y + 10, diamond2_x + 10 , diamond2_y + 20, diamond2_colour);
  }
}

void blank_diamond_2(){
  if (diamond2_rotate == 1){
    tft.drawLine(diamond2_x + 10 , diamond2_y, diamond2_x, diamond2_y + 10, TFT_BLACK);
    tft.drawLine(diamond2_x , diamond2_y + 10, diamond2_x + 10, diamond2_y + 20, TFT_BLACK);
    tft.drawLine(diamond2_x + 10 , diamond2_y + 20, diamond2_x + 20, diamond2_y + 10, TFT_BLACK);
    tft.drawLine(diamond2_x + 20 , diamond2_y + 10, diamond2_x + 10 , diamond2_y, TFT_BLACK);
    tft.drawLine(diamond2_x, diamond2_y + 10, diamond2_x + 20 , diamond2_y + 10, TFT_BLACK);
    tft.drawLine(diamond2_x + 10, diamond2_y, diamond2_x + 10 , diamond2_y + 20, TFT_BLACK);
  }

  if (diamond2_rotate == 2){
    tft.drawLine(diamond2_x + 10 , diamond2_y, diamond2_x + 3, diamond2_y + 10, TFT_BLACK);
    tft.drawLine(diamond2_x + 3 , diamond2_y + 10, diamond2_x + 10, diamond2_y + 20, TFT_BLACK);
    tft.drawLine(diamond2_x + 10 , diamond2_y + 20, diamond2_x + 17, diamond2_y + 10, TFT_BLACK);
    tft.drawLine(diamond2_x + 17 , diamond2_y + 10, diamond2_x + 10 , diamond2_y, TFT_BLACK);
    tft.drawLine(diamond2_x + 3, diamond2_y + 10, diamond2_x + 17 , diamond2_y + 10, TFT_BLACK);

    tft.drawLine(diamond2_x + 10, diamond2_y, diamond2_x + 6 , diamond2_y + 10, TFT_BLACK);
    tft.drawLine(diamond2_x + 6, diamond2_y + 10, diamond2_x + 10 , diamond2_y + 20, TFT_BLACK);
    tft.drawLine(diamond2_x + 10, diamond2_y, diamond2_x + 13 , diamond2_y + 10, TFT_BLACK);
    tft.drawLine(diamond2_x + 13, diamond2_y + 10, diamond2_x + 10 , diamond2_y + 20, TFT_BLACK);
  }

  if (diamond2_rotate == 3){
    tft.drawLine(diamond2_x + 10 , diamond2_y, diamond2_x+3, diamond2_y + 10, TFT_BLACK);
    tft.drawLine(diamond2_x + 3 , diamond2_y + 10, diamond2_x + 10, diamond2_y + 20, TFT_BLACK);
    tft.drawLine(diamond2_x + 10 , diamond2_y + 20, diamond2_x + 17, diamond2_y + 10, TFT_BLACK);
    tft.drawLine(diamond2_x + 17 , diamond2_y + 10, diamond2_x + 10 , diamond2_y, TFT_BLACK);
    tft.drawLine(diamond2_x + 3, diamond2_y + 10, diamond2_x + 17 , diamond2_y + 10, TFT_BLACK);

    tft.drawLine(diamond2_x + 10, diamond2_y, diamond2_x + 8 , diamond2_y + 10, TFT_BLACK);
    tft.drawLine(diamond2_x + 8, diamond2_y + 10, diamond2_x + 10 , diamond2_y + 20, TFT_BLACK);
    tft.drawLine(diamond2_x + 10, diamond2_y, diamond2_x + 15 , diamond2_y + 10, TFT_BLACK);
    tft.drawLine(diamond2_x + 15, diamond2_y + 10, diamond2_x + 10 , diamond2_y + 20, TFT_BLACK);
  }
}



void do_diamond_2(){
  int val = 0;
  int val2 = 0;

  if (diamond2 == 0){
    val = random(200);
    if (val > 198){
      val = random(screen_height - 20);
      diamond2_x = -20;
      diamond2_y = val;
      diamond2 = 1;

      val = random(3) - 1;
      diamond2_y_dir = val;

      val2 = random(1,6);
      diamond2_type = val2;

      if (val2 == 1){
        diamond2_colour = TFT_YELLOW;
      }
      if (val2 == 2){
        diamond2_colour = TFT_PURPLE;
      }
      if (val2 == 3){
        diamond2_colour = TFT_BLUE;
      }
      if (val2 == 4){
        diamond2_colour = TFT_CYAN;
      }
      if (val2 == 5){
        diamond2_colour = TFT_ORANGE;
      }
      if (val2 == 6){
        diamond2_colour = TFT_DARKGREY;
      }
    }
  } else {
    blank_diamond_2();

    diamond2_rotation_count++;
    if (diamond2_rotation_count > diamond2_rotation_speed){
      diamond2_rotation_count = 0;
      diamond2_rotate++;
      if (diamond2_rotate > 3){
        diamond2_rotate = 1;
      }
    } 

    // diamond2_rotate++;
    // if (diamond2_rotate > 3){
    //   diamond2_rotate = 1;
    // }
    diamond2_x = diamond2_x + (diamond2_dir * diamond2_speed);
    diamond2_y = diamond2_y + diamond2_y_dir;
    if ( diamond2_y < 0){
      diamond2_y_dir = 1;
    }
    if ( diamond2_y > screen_height-20){
      diamond2_y_dir = -1;
    }

    if ( diamond2_x > (player2_x - 20) && diamond2_x < (player2_x +10)) {
      if (diamond2_y - 20 > (player2_y - 20) && (diamond2_y+20) < (player2_y + paddle2_length + 20)) {
        diamond2 = 0;
        if (diamond2_type == 1){
          blank_player_2();
          if (paddle2_length == 40){
            paddle2_length = 20;
          } else if (paddle2_length == 20){
            paddle2_length = 40;
          } else if (paddle2_length = 80){
            paddle2_length = 40;
          }
        }
        if (diamond2_type == 2){
          blank_player_2();
          if (paddle2_length == 20){
            paddle2_length = 40;
          } else if (paddle2_length == 40){
            paddle2_length = 80;
          } else if (paddle2_length = 80){
            paddle2_length = 40;
          }
        }
        if (diamond2_type == 3){
          if (missile2_tripplefire_enabled == 0){
            missile2_tripplefire_enabled = 1;
            missile2_tripplefire1 = 0;
            missile2_tripplefire2 = 0;
          } else if (missile2_tripplefire_enabled == 1){
            missile2_tripplefire_enabled = 0;
            missile2_tripplefire1 = 0;
            missile2_tripplefire2 = 0;
          }
        }
        if (diamond2_type == 4){
          if (ball2_enabled == 0){
            ball2_enabled = 1;
            ball2_x = (screen_width / 2);
            // ball2_y = (screen_height / 2);
            ball2_y = screen_height - 1;
            ball2_y_dir = 1;
            ball2_x_dir = 1;
          } else if (ball3_enabled == 0) {
            ball3_enabled = 1;
            ball3_x = (screen_width / 2);
            // ball3_y = (screen_height / 2);
            ball3_y = screen_height - 1;
            ball3_y_dir = -1;
            ball3_x_dir = -1;
          }
        }
        if (diamond2_type == 3){
          if (missile2_grenade_enabled == 0){
            missile2_grenade_enabled = 1;
            missile2_grenade1 = 0;
            missile2_grenade2 = 0;
          } else if (missile2_grenade_enabled == 1){
            missile2_grenade_enabled = 0;
            missile2_grenade1 = 0;
            missile2_grenade2 = 0;
          }
        }
      }
    }
    if (diamond2_x > screen_width){
      diamond2 = 0;
    }
    if (diamond2 == 1) {
      draw_diamond_2();
    }
  }
}



void draw_lives(){
  int i;
  int j = 1;

  j = 10;
  for (i=1; i <= player1_lives; i++){
    tft.drawLine(j , 5, j, 10, TFT_YELLOW);
    j=j+3;
  }
  tft.drawLine(j , 5, j, 10, TFT_BLACK);  //extra line drawn black to rmove any exta lines after player is shot.

  j = screen_width - 10;
  for (i=1; i <= player2_lives; i++){
    tft.drawLine(j , 5, j, 10, TFT_YELLOW);
    j=j-3;
  }
  tft.drawLine(j , 5, j, 10, TFT_BLACK);  //extra line drawn black to rmove any exta lines after player is shot.
}

void pause_game(){
    int val1 = -1;
    int val2 = -1;

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setTextSize(5);
    tft.setCursor(60, 60);
    tft.print("PAUSED");
    delay(1000);

    val1 = -1;
    val2 = -1;
    while (val1 != 0 && val2 !=0){
      val1 = digitalRead(ENCODER_KEY);
      val2 = digitalRead(6);
    }

    val2 = digitalRead(6);
    if (val2 == 0){
      esp_restart();
    }

    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_BLUE, TFT_BLACK);
    tft.setTextSize(3);
}

void game_over(){
    int val = -1;

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setTextSize(5);
    
    if (player_1_score > player_2_score){
      tft.setCursor(35, 60);
      tft.print("YOU WIN!");
    } else {
      tft.setCursor(25, 60);
      tft.print("GAME OVER");
    }
    delay(1000);

    val = digitalRead(ENCODER_KEY);
    while (val != 0) {
      val = digitalRead(ENCODER_KEY);
    }

    reset_defaults();
}


void loop() {
    static int pos = 0;
    encoder.tick();
    int val = -1;
    int random_number = 0;
    // Draw a line from (10, 20) to (80, 150) with green color
    // tft.drawLine(10, 20, 80, 150, TFT_GREEN);

    int newPos = encoder.getPosition();
    // val = digitalRead(TOP_BUTTON);
    if (pos != newPos) {
        tft.fillScreen(TFT_BLACK);
        if (newPos < pos && player_y > (0 - paddle_length)) {
            blank_player_1();
            player_y = player_y - player_speed;
        }
        
        if (newPos > pos && player_y < (screen_height + paddle_length)) {
            blank_player_1();
            player_y = player_y + player_speed;
        }
        pos = newPos;
    }

    if ( ball_x_dir >= 1 ) {
        if ( ball_y + 5 > player2_y + (paddle2_length /2 )) {
          random_number = random(100);
          if (random_number < 85){
            blank_player_2();
            player2_y = player2_y + player2_speed;
            if (paddle2_length < 40){
              player2_y = player2_y + player2_speed;
            }
          }
        }
        if (ball_y + 5 < player2_y + (paddle2_length /2 )) {
        random_number = random(100);
          if (random_number < 85){
            blank_player_2();
            player2_y = player2_y - player2_speed;
            if (paddle2_length < 40){
              player2_y = player2_y - player2_speed;
            }
          }
       }
    }
    random_number = random(100);
    if (random_number > 97){
      blank_player_2();
      player2_y = player2_y + player2_speed;
    }
    if (random_number < 98 && random_number > 95){
      blank_player_2();
      player2_y = player2_y - player2_speed;
    }

    draw_net();

    // draw scores
    tft.setCursor(50, 20);
    tft.print(player_1_score);
    tft.print(" ");
    tft.setCursor(screen_width - 80, 20);
    tft.print(player_2_score);
    tft.print(" ");

    draw_lives();

    /* To win game, it is first to reach 11 points.
    However there must be at least 2 points difference between opponents scores.
    Otherwise the game will comtinue beyond 11 points until there is a two point difference in score. */
    if (player1_lives <=0 || player2_lives <= 0){
      if ( (player_1_score - player_2_score) > 1 || (player_2_score - player_1_score) > 1 ){
        game_over();
      }
    }

    val = -1;
    val = digitalRead(6);
    if (val == 0) {
      pause_game();
    }

    do_diamond_1();
    do_diamond_2();

    do_missile1();
    do_missile2();

    blank_ball();
    move_ball();

    if (ball2_enabled == 1){
      blank_ball2();
      move_ball2();
    }

    if (ball3_enabled == 1){
      blank_ball3();
      move_ball3();
    }

    // tft.fillScreen(TFT_BLACK);
    draw_player_1();
    draw_player_2();
    draw_ball();

    if (ball2_enabled == 1){
      draw_ball2();
    }

    if (ball3_enabled == 1){
      draw_ball3();
    }


    delay(10);
}
