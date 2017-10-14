/*  
 *  BaseEngine.ino - responsible for running the actual GAME. When playing
 *  or playtesting the game, this OS State will be used.
*/

bool is_text = false;
int player_x = 159;
int player_y = 119;
bool is_running;
int target_x;
int target_y;
int TimeSinceLastMove = 0;
bool moving = false;
int txt_box_w = 320;
int txt_box_h = 59;


void drawEngine(void){
  tft.fillScreen(GREEN);
  drawMap(0, 0, 0, standardMapRes);
  position_player();
  draw_character(player_x, player_y);
  make_text_box("This is a text box!!");
  //drawSprite(50, 50, 0);

  
}


void runEngine(void){
  is_running = true;
    //delay(100);
  move_character();
  
}

void position_player(void)
{
  int blockx = player_x / (8 * standardMapRes);
  int blocky = player_y / (8 * standardMapRes);

  if (getFromMaps(blockx, blocky, currentMap) != 15) {
    find_space();
  }
}

void find_space(void) 
{
  int blockx = random(0,8);
  int blocky = random(0,6);

  while(check_collision(blockx, blocky)) {
    blockx = random(0,8);
    blocky = random(0,6);
  }
  player_x = blockx * (8 * standardMapRes);
  player_x = blockx * (8 * standardMapRes);
}

void move_character(void) 
{
  TimeSinceLastMove += delta;
  TSPoint p = getTouchPoint();
  if ( p.z == 500) {
    if (is_text) {
      Serial.print("REMOVE BOX");
      is_text = false;
      tft.fillRect(0, 240 - txt_box_h - 1, txt_box_w, txt_box_h + 1, GREEN);
      drawMap(0, 0, currentMap, standardMapRes);
      return;
    }
    Serial.print("FOUND NEW MOVE\n");
    moving = true;
    target_x = p.x;
    target_y = p.y;
    movement();
  }

}



bool is_move(int x, int y) 
{
  if (x == 0 && y == 0) {
    return false;
  }
  int blockx1 = (x / (8 * standardMapRes)) *(8 * standardMapRes);
  int blocky1 = (y / (8 * standardMapRes)) *(8 * standardMapRes);
  int blockx2 = (player_x / (8 * standardMapRes)) *(8 * standardMapRes);
  int blocky2 = (player_y / (8 * standardMapRes)) *(8 * standardMapRes);

  if ((blockx1 != blockx2) || (blocky1 != blocky2)) {
    return true;
  }
  return false;
}

void draw_character(int x, int y) 
{
  int corn_y = (y / (8 * standardMapRes)) *(8 * standardMapRes);
  int corn_x = (x / (8 * standardMapRes)) *(8 * standardMapRes);
  drawSpriteWithRes(corn_x, corn_y, 0, standardMapRes);
  player_x = corn_x;
  player_y = corn_y;
}




/*TSPoint match_grid(TSPoint ot){
  ot.x = (x / (standardMapRes * 8)) * (standardMapRes * 8);
  ot.y = (y / (standardMapRes * 8)) * (standardMapRES * 8);
>>>>>>> Stashed changes

  return ot;
}*/

  
  


 
/*void pointa_pointb(TSPoint b){
  int blockx1 = (b.x / (8 * standardMapRes));
  int blocky1 = (b.y / (8 * standardMapRes));
  int blockx2 = (player_x / (8 * standardMapRes));
  int blocky2 = (player_y / (8 * standardMapRes));
  while (blockx1 != blockx2){
      if (blockx1 < blockx2){
        blockx2 = blockx2 - 1;
        if(check_collision(blockx2, blocky2)) {
          blockx2++;
          tft.fillRect(player_x, player_y, 40, 40, GREEN);
          draw_character(blockx2 * (standardMapRes * 8), blocky2 * (standardMapRes * 8));
          return;
        }
      }
      else if (blockx1 > blockx2) {
        blockx2 = blockx2 + 1;
        if(check_collision(blockx2, blocky2)) {
          blockx2--;
          tft.fillRect(player_x, player_y, 40, 40, GREEN);
          draw_character(blockx2 * (standardMapRes * 8), blocky2 * (standardMapRes * 8));
          return;
        }
      }
      tft.fillRect(player_x, player_y, 40, 40, GREEN);
      draw_character(blockx2 * (standardMapRes * 8), blocky2 * (standardMapRes * 8));
      Serial.print("Changing X\n");
      delay(100);
  }

  while (blocky1 != blocky2){
      if (blocky1 < blocky2){
        blocky2 = blocky2 - 1;
        if(check_collision(blockx2, blocky2)) {
          blocky2++;
          tft.fillRect(player_x, player_y, 40, 40, GREEN);
          draw_character(blockx2 * (standardMapRes * 8), blocky2 * (standardMapRes * 8));
          return;
        }
      }
      else if (blocky1 > blocky2) {
        blocky2 = blocky2 + 1;
        if(check_collision(blockx2, blocky2)) {
          blocky2--;
          tft.fillRect(player_x, player_y, 40, 40, GREEN);
          draw_character(blockx2 * (standardMapRes * 8), blocky2 * (standardMapRes * 8));
          return;
        }
      }
      Serial.print("Changing Y\n");
      tft.fillRect(player_x, player_y, 40, 40, GREEN);
      draw_character(blockx2 * (standardMapRes * 8), blocky2 * (standardMapRes * 8));
      delay(100);
  }
}*/

bool check_collision(int blockx, int blocky) 
{
  Serial.print(getFromMaps(blockx, blocky, currentMap));
  if (getFromMaps(blockx, blocky, currentMap) != 15) {
    return true;
  }
  return false;
  
}


void movement(){
  if(moving){
    if(TimeSinceLastMove > 250){
       tft.fillRect(player_x, player_y, 40, 40, GREEN);
        int blockx1 = (target_x / (8 * standardMapRes));
        int blocky1 = (target_y / (8 * standardMapRes));
        int blockx2 = (player_x / (8 * standardMapRes));
        int blocky2 = (player_y / (8 * standardMapRes));
        TimeSinceLastMove = 0;
    if (blockx1 != blockx2){
      if (blockx1 < blockx2){
        blockx2 = blockx2 - 1;
        if(check_collision(blockx2, blocky2)) {
          blockx2++;
          tft.fillRect(player_x, player_y, 40, 40, GREEN);
          draw_character(blockx2 * (standardMapRes * 8), blocky2 * (standardMapRes * 8));
          return;
        }
      }
      else if (blockx1 > blockx2) {
        blockx2 = blockx2 + 1;
        if(check_collision(blockx2, blocky2)) {
          blockx2--;
          tft.fillRect(player_x, player_y, 40, 40, GREEN);
          draw_character(blockx2 * (standardMapRes * 8), blocky2 * (standardMapRes * 8));
          return;
        }
      }
      tft.fillRect(blockx2 * (standardMapRes * 8), blocky2 * (standardMapRes * 8), 40, 40, GREEN);
      draw_character(blockx2 * (standardMapRes * 8), blocky2 * (standardMapRes * 8));
    }

    else if (blocky1 != blocky2){
      if (blocky1 < blocky2){
        blocky2 = blocky2 - 1;
        if(check_collision(blockx2, blocky2)) {
          blocky2++;
          tft.fillRect(player_x, player_y, 40, 40, GREEN);
          draw_character(blockx2 * (standardMapRes * 8), blocky2 * (standardMapRes * 8));
          return;
        }
      }
      else if (blocky1 > blocky2) {
        blocky2 = blocky2 + 1;
        if(check_collision(blockx2, blocky2)) {
          blocky2--;
          tft.fillRect(player_x, player_y, 40, 40, GREEN);
          draw_character(blockx2 * (standardMapRes * 8), blocky2 * (standardMapRes * 8));
          return;
        }
      }
      tft.fillRect(player_x, player_y, 40, 40, GREEN);
      draw_character(blockx2 * (standardMapRes * 8), blocky2 * (standardMapRes * 8));
    }
    else {
      moving = false;
        draw_character(blockx2 * (standardMapRes * 8), blocky2 * (standardMapRes * 8));
    }
    
    }
  }
}

void make_text_box(char *text)
{
  is_text = true;
  tft.fillRect(0, 240 - txt_box_h, txt_box_w, txt_box_h, BLACK);
  tft.drawFastHLine(0, 240 - txt_box_h + 1, 320, LIGHTGRAY);
  drawText(10, 240 - txt_box_h + 25 , 2, text, WHITE);
  
}

