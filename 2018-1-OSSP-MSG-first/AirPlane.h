#include "helpers.h"

typedef struct bullets
{
public:
  bullets(int x, int y , int ply_x, int ply_y )
  {
    move_x = x;
    move_y = y;
    bullet_pos.x = ply_x;
    bullet_pos.y = ply_y;
  }
  int move_x, move_y;//총알들의 방향성
  SDL_Rect bullet_pos;//총알들의 위치
}bullets;


class _bullets
{
public:
  void add_blt(int x, int y, int ply_x, int ply_y)//x,y는 총알 방향성, ply_x,y는 총알의 현재 위치
  {
    bullets tmp(x,y,ply_x,ply_y);
    blt.push_back(tmp);
  }

  void bullet_apply_surface(SDL_Surface *bullet,SDL_Surface* destination, SDL_Rect* clip)//총알들 그리기
  {
    for(vector<bullets>::iterator iter = blt.begin(); iter!= blt.end(); iter++)
    {
      SDL_BlitSurface( bullet, clip, destination, &(*iter).bullet_pos);
    }
  }

  void control_bullet()
  {
    vector<bullets> temp;
    for(vector<bullets>::iterator iter = blt.begin(); iter != blt.end(); iter++)
    {
      bullets tmp((*iter).move_x,(*iter).move_y,(*iter).bullet_pos.x + (*iter).move_x,(*iter).bullet_pos.y + (*iter).move_y);
      if( 0 < tmp.bullet_pos.x + 9 && tmp.bullet_pos.x< SCREEN_WIDTH && -5 <= tmp.bullet_pos.y  && tmp.bullet_pos.y < SCREEN_HEIGHT)
        temp.push_back(tmp);
    }

    blt = temp;
  }

  vector<bullets> blt;
};



class AirPlane
{
private:
  SDL_Rect offset;
  int pos_x,pos_y;// 비행기 x,y 좌표;
  int life;
public:
  AirPlane();
  ~AirPlane();
  bool Got_shot(vector<bullets> enemy_bullets);
  void shooting(_bullets &A);
  void plane_apply_surface(SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
  void control_plane(int x, int y);
  SDL_Rect Get_plane();//plane 변수 getter
};

class Enemy_standard
{
private:
  int life;
  int count;//루프문 반복할 변수
  int mode;// 좌,우 나타날 장소를 정하는 변수
public:
  int pos_x,pos_y;// 비행기 x,y 좌표;
  Enemy_standard(int mode);
  ~Enemy_standard();
  bool Got_shot(_bullets &A);
  void shooting(_bullets &A);
  void enemy_apply_surface(SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
  void control_plane(_bullets &enemey);
};
