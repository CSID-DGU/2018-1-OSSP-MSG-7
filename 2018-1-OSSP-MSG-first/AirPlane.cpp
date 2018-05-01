#include "AirPlane.h"

AirPlane::AirPlane()
{
  bullet = load_image("assets/bullet.gif");//총알 이미지
  plane = load_image("assets/p2.gif");// 비행기 이미지
  //Setcolorkey는 네모난 그림에서 비행기로 쓸 그림 빼고 나머지 흰 바탕들만 투명하게 바꾸는거
  SDL_SetColorKey(plane, SDL_SRCCOLORKEY,SDL_MapRGB(plane->format,255,255,255));
  SDL_SetColorKey(bullet, SDL_SRCCOLORKEY,SDL_MapRGB(bullet->format,255,255,255));
  pos_x = SCREEN_WIDTH / 2;//처음 시작 위치 지정
  pos_y = SCREEN_HEIGHT / 2;//처음 시작 위치 지정
  life = 1;
}
AirPlane::~AirPlane()
{
  SDL_FreeSurface(plane);//plane변수 없애는거
}

//맞는 판정
//void Got_shot(발사체 좌표, 너비, 길이);

void AirPlane::shooting()
{
  SDL_Rect temp;
  temp.x = pos_x + 1;
  temp.y = pos_y - 4;
  bullet_rect.push_back(temp);
}

void AirPlane::bullet_apply_surface(SDL_Surface* destination, SDL_Rect* clip)
{
  vector<SDL_Rect>::iterator iter;
  for(iter = bullet_rect.begin(); iter != bullet_rect.end(); iter++ )
  {
    SDL_BlitSurface( bullet, clip, destination, &(*iter));
  }
}
void AirPlane::plane_apply_surface(SDL_Surface* destination, SDL_Rect* clip )
{
  SDL_Rect offset;
  offset.x = pos_x;
  offset.y = pos_y;
  SDL_BlitSurface( plane, clip, destination, &offset );
}
void AirPlane::control_bullet()
{//vector
  vector<SDL_Rect>::iterator iter;
  vector<SDL_Rect> temp;
  SDL_Rect temp1;
  for(iter = bullet_rect.begin(); iter != bullet_rect.end(); iter++)
  {
    temp1.x = (*iter).x;
    temp1.y = (*iter).y - 15;
    temp.push_back(temp1);
  }

  bullet_rect = temp;
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

SDL_Surface *AirPlane::Get_plane()
{
  return this->plane;
}

vector<SDL_Rect> AirPlane::Get_bullets()
{
  return this->bullet_rect;
}

bool AirPlane::Got_shot(vector<SDL_Rect> enemy_bullets)
{
  vector<SDL_Rect>::iterator iter;
  bool flag = false;

  for(iter = enemy_bullets.begin(); iter != enemy_bullets.end(); iter++)
  {
    if((pos_x + 18 < (*iter).x + 9 || pos_y + 20 < (*iter).y + 5) ||
    ((*iter).x + 18 < pos_x + 9 || (*iter).y + 10 < pos_y + 10));//안 맞았을 때

    else//맞았을때
    {
      flag = true;
      break;
    }
  }
  return flag;
}



Enemy_standard::Enemy_standard()
{
  bullets = load_image("assets/bullet.gif");//총알 이미지
  enemy = load_image("assets/3.gif");// 비행기 이미지
  //Setcolorkey는 네모난 그림에서 비행기로 쓸 그림 빼고 나머지 흰 바탕들만 투명하게 바꾸는거
  SDL_SetColorKey(enemy, SDL_SRCCOLORKEY,SDL_MapRGB(enemy->format,255,255,255));
  SDL_SetColorKey(bullets, SDL_SRCCOLORKEY,SDL_MapRGB(bullets->format,255,255,255));
  pos_x = SCREEN_WIDTH / 2;//처음 시작 위치 지정
  pos_y = SCREEN_HEIGHT / 4;//처음 시작 위치 지정
  life = 1;
}
Enemy_standard::~Enemy_standard()
{
  SDL_FreeSurface(enemy);//enemy변수 없애는거
}

bool Enemy_standard::Got_shot(vector<SDL_Rect> bullets)
{
  vector<SDL_Rect>::iterator iter;
  bool flag = false;

  for(iter = bullets.begin(); iter != bullets.end(); iter++)
  {
    if((pos_x + 18 < (*iter).x + 9 || pos_y + 20 < (*iter).y + 5) ||
    ((*iter).x + 18 < pos_x + 9 || (*iter).y + 10 < pos_y + 10));//안 맞았을 때

    else//맞았을때
    {
      flag = true;
      break;
    }
  }
  return flag;
}

void Enemy_standard::shooting()
{
  SDL_Rect temp;
  temp.x = pos_x + 2;
  temp.y = pos_y + 4;
  bullet_rects.push_back(temp);
}

void Enemy_standard::bullet_apply_surface(SDL_Surface* destination, SDL_Rect* clip)
{
  vector<SDL_Rect>::iterator iter;
  for(iter = bullet_rects.begin(); iter != bullet_rects.end(); iter++ )
  {
    SDL_BlitSurface( bullets, clip, destination, &(*iter));
  }
}

void Enemy_standard::enemy_apply_surface(SDL_Surface* destination, SDL_Rect* clip )
{
  SDL_Rect offset;
  offset.x = pos_x;
  offset.y = pos_y;
  SDL_BlitSurface( enemy, clip, destination, &offset );
}

void Enemy_standard::control_bullet()
{//vector
  vector<SDL_Rect>::iterator iter;
  vector<SDL_Rect> temp;
  SDL_Rect temp1;
  for(iter = bullet_rects.begin(); iter != bullet_rects.end(); iter++)
  {
    temp1.x = (*iter).x;
    temp1.y = (*iter).y + 15;
    temp.push_back(temp1);
  }

  bullet_rects = temp;
}

void Enemy_standard::control_plane(int x, int y)
{
  pos_x += x;
  pos_y += y;
}

SDL_Surface *Enemy_standard::Get_plane()
{
  return this->enemy;
}

vector<SDL_Rect> Enemy_standard::Get_bullets()
{
  return this->bullet_rects;
}
