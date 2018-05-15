#include "AirPlane.h"

AirPlane::AirPlane()
{
  pos_x = SCREEN_WIDTH / 2;//처음 시작 위치 지정
  pos_y = SCREEN_HEIGHT / 2;//처음 시작 위치 지정
  life = 1;
}
AirPlane::~AirPlane()
{

}

void AirPlane::shooting(_bullets &player_bullets)
{
  player_bullets.add_blt( 0, -10,pos_x,pos_y - 15);
}

void AirPlane::plane_apply_surface(SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )
{
  offset.x = pos_x;
  offset.y = pos_y;
  SDL_BlitSurface( source, clip, destination, &offset );
}
void AirPlane::control_plane(int x, int y)
{
  if( pos_x + x >= 0 && (pos_x + PLAYER_WIDTH + x) <= SCREEN_WIDTH &&
      pos_y + y >= 0 && (pos_y + PLAYER_HEIGHT + y) < SCREEN_HEIGHT-6)//화면 범위 안
  {
    pos_x += x;
    pos_y += y;
  }
}

SDL_Rect AirPlane::Get_plane()
{
  return offset;
}

bool AirPlane::Got_shot(vector<bullets> enemy_bullets)
{
  vector<bullets>::iterator iter;
  bool flag = false;

  for(iter = enemy_bullets.begin(); iter != enemy_bullets.end(); iter++)
  {
    if((pos_x + 18 < (*iter).bullet_pos.x + 9 || pos_y + 20 < (*iter).bullet_pos.y + 5) ||
    ((*iter).bullet_pos.x + 18 < pos_x + 9 || (*iter).bullet_pos.y + 10 < pos_y + 10));//안 맞았을 때

    else//맞았을때
    {
      flag = true;
      break;
    }
  }
  return flag;
}



Enemy_standard_2::Enemy_standard_2(int mode)
{
  enemy = load_image("assets/3.gif");// 비행기 이미지
  //Setcolorkey는 네모난 그림에서 비행기로 쓸 그림 빼고 나머지 흰 바탕들만 투명하게 바꾸는거
  SDL_SetColorKey(enemy, SDL_SRCCOLORKEY,SDL_MapRGB(enemy->format,255,255,255));

  this->mode = mode;
  int y = rand()%100 + 10;
  if(mode == 0) pos_x = -ENEMY_WIDTH;//처음 시작 위치 지정
  else pos_x = SCREEN_WIDTH+ENEMY_WIDTH;
  pos_y = y;//처음 시작 위치 지정
  life = 1;
  count = 0;
}

Enemy_standard_2::~Enemy_standard_2()
{
}

bool Enemy_standard_2::Got_shot(_bullets &A)
{

  vector<bullets>::iterator iter;
  vector<bullets> tmp;

  bool flag = false;

  for(iter = A.blt.begin(); iter != A.blt.end(); iter++)
  {
    if((pos_x + 18 < (*iter).bullet_pos.x + 9 || pos_y + 20 < (*iter).bullet_pos.y + 5) ||
    ((*iter).bullet_pos.x + 18 < pos_x + 9 || (*iter).bullet_pos.y + 10 < pos_y + 10))//안 맞았을 때
      tmp.push_back(*iter);
    else//맞았을때
    {
      flag = true;
    }
  }

  A.blt = tmp;

  return flag;
}

void Enemy_standard_2::shooting(_bullets &A)
{
  A.add_blt( 0, 5,pos_x + 2,pos_y + 15);
}

void Enemy_standard_2::enemy_apply_surface(SDL_Surface* destination, SDL_Rect* clip )
{
  int i = count % 4;
  SDL_Rect offset;
  offset.x = pos_x;
  offset.y = pos_y;
  SDL_BlitSurface(enemy, clip, destination, &offset );
}

void Enemy_standard_2::control_plane(_bullets &A)
{
  if(first_exe==true){
    pos = rand()%75+75;
    first_exe=false;
  }
  if(count % 30 == 0 ) this->shooting(A);
  if(count < pos){
      if(mode == 0) pos_x += 3;
      else pos_x -= 3;
  }
  else {
      if(mode == 0){
          pos_x -= 3;
          pos_y += 3;
      }
      else {
          pos_x += 3;
          pos_y += 3;
      }
  }
  count++;
}

SDL_Surface *Enemy_standard_2::Get_plane()
{
  return this->enemy;
}

Enemy_standard::Enemy_standard(int mode)
{
  this->mode = mode;// 이동경로 mode
  srand(time(NULL));
  if( mode == 0)
    pos_x = 160;// 처음 시작 위치 지정
  else if(mode == 1)
    pos_x = 480;
  pos_y = -ENEMY_HEIGHT;//처음 시작 위치 지정
  life = 1;
  count = 0;
}

Enemy_standard::~Enemy_standard()
{
}

bool Enemy_standard::Got_shot(_bullets &A)
{

  vector<bullets>::iterator iter;
  vector<bullets> tmp;

  bool flag = false;

  for(iter = A.blt.begin(); iter != A.blt.end(); iter++)
  {
    if((pos_x + 18 < (*iter).bullet_pos.x + 9 || pos_y + 20 < (*iter).bullet_pos.y + 5) ||
    ((*iter).bullet_pos.x + 18 < pos_x + 9 || (*iter).bullet_pos.y + 10 < pos_y + 10))//안 맞았을 때
      tmp.push_back(*iter);
    else//맞았을때
    {
      flag = true;
    }
  }

  A.blt = tmp;

  return flag;
}

void Enemy_standard::shooting(_bullets &A)
{
  A.add_blt( 0, 5,pos_x + 2,pos_y + 15);
}

void Enemy_standard::enemy_apply_surface(SDL_Surface* source[], SDL_Surface* destination, SDL_Rect* clip )
{
  int i = count % 4;
  SDL_Rect offset;
  offset.x = pos_x;
  offset.y = pos_y;
  SDL_BlitSurface(source[i], clip, destination, &offset );
}

void Enemy_standard::control_plane(_bullets &enemy)
{//y= 3일 때 속도가 적당.
  if( count % 30 == 0)
    this->shooting(enemy);
  if(this->mode == 0)
  {
    if( count < 50 )
      pos_y += 3;
    if(count > 50)
      {
        pos_x += 3;
        pos_y += 3;
      }
  }
  else if(this->mode == 1)
  {
    if( count < 50 )
      pos_y += 3;
    if(count > 50)
      {
        pos_x -= 3;
        pos_y += 3;
      }
  }
  ++count;
}
