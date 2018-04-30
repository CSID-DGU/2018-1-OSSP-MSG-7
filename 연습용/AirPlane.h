#include "helpers.h"

class AirPlane
{
private:
  SDL_Surface *plane;
  SDL_Surface *bullet;
  int pos_x,pos_y;// 비행기 x,y 좌표;
  int life;
public:
  vector<SDL_Rect> bullet_rect;

  AirPlane();
  ~AirPlane();
  bool Got_shot(vector<SDL_Rect> enemy_bullets);
  void shooting();
  void bullet_apply_surface(SDL_Surface* destination, SDL_Rect* clip);
  void plane_apply_surface(SDL_Surface* destination, SDL_Rect* clip);
  void control_bullet();
  void control_plane(int x, int y);
  SDL_Surface *Get_plane();//plane 변수 getter
  vector<SDL_Rect> Get_bullets();//총알 변수 getter
};

class Enemy_standard
{
private:
  SDL_Surface *enemy;
  SDL_Surface *bullets;
  int pos_x,pos_y;// 비행기 x,y 좌표;
  int life;
public:
  vector<SDL_Rect> bullet_rects;

  Enemy_standard();
  ~Enemy_standard();
  bool Got_shot(vector<SDL_Rect> bullets);
  void shooting();
  void bullet_apply_surface(SDL_Surface* destination, SDL_Rect* clip);
  void enemy_apply_surface(SDL_Surface* destination, SDL_Rect* clip);
  void control_bullet();
  void control_plane(int x, int y);
  SDL_Surface *Get_plane();
  vector<SDL_Rect> Get_bullets();
};
