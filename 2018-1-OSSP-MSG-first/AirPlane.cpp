#include "AirPlane.h"

AirPlane::AirPlane()
{
  plane = load_image("assets/p2.gif");// 비행기 이미지
  //Setcolorkey는 네모난 그림에서 비행기로 쓸 그림 빼고 나머지 흰 바탕들만 투명하게 바꾸는거
  SDL_SetColorKey(plane, SDL_SRCCOLORKEY,SDL_MapRGB(plane->format,255,255,255));
  pos_x = SCREEN_WIDTH / 2;//처음 시작 위치 지정
  pos_y = SCREEN_HEIGHT / 2;//처음 시작 위치 지정
  life = 1;
}
AirPlane::~AirPlane()
{
  SDL_FreeSurface(plane);
}

void AirPlane::shooting(_bullets &player_bullets)
{
  player_bullets.add_blt( 0, -10,pos_x,pos_y - 15);
}

void AirPlane::plane_apply_surface(SDL_Surface* destination, SDL_Rect* clip )
{
  offset.x = pos_x;
  offset.y = pos_y;
  SDL_BlitSurface( plane, clip, destination, &offset );
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

bool AirPlane::Got_item(vector<items> I)
{
  vector<items>::iterator iter;
  bool flag = false;

  for(iter = I.begin(); iter != I.end(); iter++)
  {
    if((pos_x + 18 < (*iter).item_pos.x + 9 || pos_y + 20 < (*iter).item_pos.y + 5) ||
    ((*iter).item_pos.x + 18 < pos_x + 9 || (*iter).item_pos.y + 10 < pos_y + 10));//안 맞았을 때
    else                                                                           //맞았을때
    {
      flag = true;
      break;
    }
  }

  return flag;
}

void AirPlane::increaseLife()
{
  life++;
}

Enemy_standard::Enemy_standard()
{
  enemy = load_image("assets/3.gif");// 비행기 이미지
  //Setcolorkey는 네모난 그림에서 비행기로 쓸 그림 빼고 나머지 흰 바탕들만 투명하게 바꾸는거
  SDL_SetColorKey(enemy, SDL_SRCCOLORKEY,SDL_MapRGB(enemy->format,255,255,255));
  srand(time(NULL));
  int x = rand()%200 + 100;
  pos_x = x;//처음 시작 위치 지정
  pos_y = -ENEMY_HEIGHT;//처음 시작 위치 지정
  life = 1;
}

Enemy_standard::~Enemy_standard()
{
  SDL_FreeSurface(enemy);//enemy변수 없애는거
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

void Enemy_standard::enemy_apply_surface(SDL_Surface* destination, SDL_Rect* clip )
{
  SDL_Rect offset;
  offset.x = pos_x;
  offset.y = pos_y;
  SDL_BlitSurface( enemy, clip, destination, &offset );
}

void Enemy_standard::control_plane(int x, int y)
{
  pos_x += x;
  pos_y += y;
}

void Item::add_itm(int x, int y, int ply_x, int ply_y)
{
  items tmp(x,y,ply_x,ply_y);
  itm.push_back(tmp);
}

void Item::item_apply_surface(SDL_Surface *item, SDL_Surface* destination, SDL_Rect* clip)  // item들 그리기
{
  for(vector<items>::iterator iter = itm.begin(); iter!= itm.end(); iter++)
  {
    SDL_BlitSurface( item, clip, destination, &(*iter).item_pos);
  }
}

void Item::control_item()
{
  vector<items> temp;
  for(vector<items>::iterator iter = itm.begin(); iter != itm.end(); iter++)
  {
    items tmp((*iter).move_x,(*iter).move_y,(*iter).item_pos.x + (*iter).move_x,(*iter).item_pos.y + (*iter).move_y);
    if( 0 < tmp.item_pos.x + 9 && tmp.item_pos.x< SCREEN_WIDTH && -5 <= tmp.item_pos.y  && tmp.item_pos.y < SCREEN_HEIGHT)
      temp.push_back(tmp);
  }

  itm = temp;
}

SDL_Surface *Enemy_standard::Get_plane()
{
  return this->enemy;
}
