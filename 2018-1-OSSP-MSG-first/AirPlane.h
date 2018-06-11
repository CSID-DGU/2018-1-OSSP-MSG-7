#include "helpers.h"

class BOOM
{
private:
  typedef struct bomb
  {
    SDL_Rect SDL_b;
    int count = 0;
  }bomb;
public:
  bomb b;
  int three;    //boss 맞았을 때 위치 정할 변수
  BOOM(SDL_Rect offset)
  {
     b.SDL_b = offset;
  };
  void set_bomb(SDL_Rect boss)
  {
    b.SDL_b = boss;
  }
  void boom_apply_surface(SDL_Surface* boom[], SDL_Surface* destination, SDL_Rect* clip )
  {//적 비행기가 격추됬을 때의 좌표에 폭발 스프라이트 이미지 출력
    	SDL_BlitSurface( boom[b.count++], clip, destination, &(b.SDL_b));
  };
};

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
      if( -1 < tmp.bullet_pos.x && tmp.bullet_pos.x< SCREEN_WIDTH && 0 <= tmp.bullet_pos.y  && tmp.bullet_pos.y < SCREEN_HEIGHT)
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
  int pos_x,pos_y;// 비행기 x,y 좌표

public:
  AirPlane();
  ~AirPlane();
  bool Got_shot(_bullets &A,_bullets &B,_bullets &C);
  bool Got_item(vector<items> I);
  void shooting(_bullets &A);
  void increaseLife();
  void plane_apply_surface(SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
  void control_plane(int x, int y);
  void invisible(SDL_Surface *plane);
  SDL_Rect Get_plane();//plane 변수 getter

  int invisible_mode;
  int life;
};

class Enemy_standard_2
{
public:
  SDL_Surface *enemy;
  SDL_Rect offset;
  int pos_x, pos_y;
  int life;

  int mode;
  int count = 0;
  bool first_exe = true;   // to initialize count in control for only one time
  int pos;  // enemy's movement location

  Enemy_standard_2(int mode);
  ~Enemy_standard_2();
  bool Got_shot(_bullets &A);
  void shooting(_bullets &A);
  void enemy_apply_surface(SDL_Surface* destination, SDL_Rect* clip);
  void control_plane(_bullets &A);
  SDL_Rect Get_plane();
};

class Enemy_standard
{
public:
    SDL_Rect offset;
    int life;
    int count=0;//루프문 반복할 변수
    int mode;// 좌,우 나타날 장소를 정하는 변수
    bool first_exe = true;
    int pos;
    int pos_x,pos_y;// 비행기 x,y 좌표;
    Enemy_standard(int mode);
    ~Enemy_standard();
    bool Got_shot(_bullets &A);
    void shooting(_bullets &A);
    void enemy_apply_surface(SDL_Surface* source[], SDL_Surface* destination, SDL_Rect* clip);
    void control_plane(_bullets &enemey);
    SDL_Rect Get_plane();
};

class Mini_Boss
{
private:
  SDL_Surface *mini_boss;
  SDL_Rect offset;
  int pos_x, pos_y;
  int life;
  int count = 0;
  int direction = 0;
  int cont_shoot = 0;

public:
  Mini_Boss();
  ~Mini_Boss();
  bool Got_shot(_bullets &A, int &x);
  void shooting(_bullets &A);
  void enemy_apply_surface(SDL_Surface* destination, SDL_Rect* clip);
  void control_plane(_bullets &A);
  void loss_life(int& score);
  SDL_Rect Get_plane();

  int amount = 1;
};

class Boss
{
private:
  SDL_Surface *mini_boss;
  SDL_Rect offset;
  int pos_x, pos_y;
  int life;
  int count = 0;
  int direction = 0;
  int cont_shoot = 0;

public:
  Boss();
  ~Boss();
  bool Got_shot(_bullets &A,  int &x);
  void shooting(_bullets &A);
  void enemy_apply_surface(SDL_Surface* destination, SDL_Rect* clip);
  void control_plane(_bullets &A);
  void loss_life(int& score);
  SDL_Rect Get_plane();

  int amount = 1;
};

class Item
{
public:
  SDL_Surface *item;

  ~Item();
  void add_itm(int x, int y, int ply_x, int ply_y);                                      //x,y는 item 방향성, ply_x,y는 item의 현재 위치
  void item_apply_surface(SDL_Surface *item, SDL_Surface* destination, SDL_Rect* clip);  // item들 그리기
  void control_item();

  vector<items> itm;
};
