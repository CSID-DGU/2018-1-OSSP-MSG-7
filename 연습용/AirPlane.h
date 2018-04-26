#include "helpers.h"
#include <vector>

using namespace std;

class AirPlane
{
private:
  SDL_Surface *plane;
  SDL_Surface *bullet;
  int pos_x,pos_y;// 비행기 x,y 좌표;

public:
  vector<SDL_Rect> bullet_rect;

  AirPlane();
  ~AirPlane();
  //void Got_shot(발사체 좌표, 너비, 길이);
  void shooting();
  void bullet_apply_surface(SDL_Surface* destination, SDL_Rect* clip);
  void plane_apply_surface(SDL_Surface* destination, SDL_Rect* clip);
  void control_bullet();
  void control_plane(int x, int y);
  SDL_Surface *Get_plane();
  //vector<SDL_Surface*> Get_bullets();
};
