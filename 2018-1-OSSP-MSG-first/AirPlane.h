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

typedef struct items
{
public:
  items(int x, int y , int ply_x, int ply_y )
  {
    move_x = x;
    move_y = y;
    item_pos.x = ply_x;
    item_pos.y = ply_y;
  }
  int move_x, move_y;                     // item의 방향성
  SDL_Rect item_pos;                      // item의 위치
}items;

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
  SDL_Surface *plane;
  SDL_Rect offset;
  int pos_x,pos_y;// 비행기 x,y 좌표;
  int life;
public:
  AirPlane();
  ~AirPlane();
  bool Got_shot(vector<bullets> enemy_bullets);
  void shooting(_bullets &A);
  void plane_apply_surface(SDL_Surface* destination, SDL_Rect* clip);
  void control_plane(int x, int y);
  SDL_Rect Get_plane();//plane 변수 getter
};

class Enemy_standard
{
public:
  SDL_Surface *enemy;

  int pos_x,pos_y;// 비행기 x,y 좌표;
  int life;

  Enemy_standard();
  ~Enemy_standard();
  bool Got_shot(_bullets &A);
  void shooting(_bullets &A);
  void enemy_apply_surface(SDL_Surface* destination, SDL_Rect* clip);
  void control_plane(int x, int y);
  SDL_Surface *Get_plane();

};

class Item
{
public:
  void add_itm(int x, int y, int ply_x, int ply_y)    //x,y는 item 방향성, ply_x,y는 item의 현재 위치
  {
    items tmp(x,y,ply_x,ply_y);
    itm.push_back(tmp);
  }
  void item_apply_surface(SDL_Surface *item, SDL_Surface* destination, SDL_Rect* clip)  // item들 그리기
  {
    for(vector<items>::iterator iter = itm.begin(); iter!= itm.end(); iter++)
    {
      SDL_BlitSurface( item, clip, destination, &(*iter).item_pos);
    }
  }
  void control_item()
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

  vector<items> itm;
};
