#include "AirPlane.h"

SDL_Surface *screen;
SDL_Surface *background;
SDL_Surface *bullet;
SDL_Surface *item;

SDL_Event event;
Uint8 *keystates;

_bullets enemy_bullets;
_bullets player_bullets;
Item I;

bool init()
{//고칠 것: if문 추가해서 init했을 때 실패하면 false반환하게끔
  SDL_Init(SDL_INIT_EVERYTHING);
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_DOUBLEBUF );
  SDL_WM_SetCaption("MSG", NULL);
  return true;
}

bool load_files()
{//고칠 것: if문 추가해서 init했을 때 실패하면 false반환하게끔
  background = load_image("assets/background.png");
  bullet = load_image("assets/bullet.gif");
  item = load_image("assets/tem1.png");
  SDL_SetColorKey(bullet, SDL_SRCCOLORKEY,SDL_MapRGB(bullet->format,255,255,255));
  return true;
}

int main()
{
  init();//초기화 함수
  load_files();//이미지,폰트,bgm 로드하는 함수

  int start_time = 0;
  int delay = 0;
  int count = 0; int number = 1; //임시변수

  Enemy_standard E;
  AirPlane A;

  while(true){
    start_time = SDL_GetTicks();//나중에 프레임 계산할 변수

    if(player_bullets.blt.size() > 0 )
      player_bullets.control_bullet();//총알들 위치 위로 상승

    if(enemy_bullets.blt.size() > 0)//임시 코딩. 적들 총알 위치 아래로 이동
      enemy_bullets.control_bullet();

    if(A.Got_shot(enemy_bullets.blt))//임시 코딩. 사용자 맞으면 게임 끝
      break;

    if(number == 1 && E.Got_shot(player_bullets))//임시 코딩.적 맞으면 끝
      {
        I.add_itm(E.pos_x, E.pos_y, E.pos_x, E.pos_y - 15);
        E.~Enemy_standard();
        //I.control_item();       // why an umjihinya

        number = 0;
      }
    if(A.Got_item(I.itm))
    {
      A.increaseLife();
      SDL_FreeSurface(item);
    }
    if(SDL_PollEvent(&event)){
      if(event.type == SDL_QUIT)
			   break;
    }

    keystates = SDL_GetKeyState(NULL);

      if(count++ % 30 == 0 && number == 1 )//임시
        E.shooting(enemy_bullets);
      if(count % 5 == 0 && number == 1)//임시
        E.control_plane(0,5);

      if(keystates[SDLK_a])
      {
        A.shooting(player_bullets);
      }

      if(keystates[SDLK_UP])
        A.control_plane(0,-3);

      if(keystates[SDLK_DOWN])
        A.control_plane(0, 3);

      if(keystates[SDLK_LEFT])
        A.control_plane(-3, 0);

      if(keystates[SDLK_RIGHT])
        A.control_plane(3, 0);

    apply_surface(0, 0, background,screen,NULL);//백그라운드 그리는거
    enemy_bullets.bullet_apply_surface(bullet, screen,NULL);//적 총알들 그리는 것
    player_bullets.bullet_apply_surface(bullet, screen, NULL);
    I.item_apply_surface(item, screen, NULL);

    if( number == 1 )
      {
        E.enemy_apply_surface(screen,NULL);
      }
    A.plane_apply_surface(screen,NULL);//A비행기 그리는거
    delay = 1000/30 - (SDL_GetTicks() - start_time);
    if(delay > 0)
      SDL_Delay(delay);//이거 fps를 고려해서 Delay해야됨 프레임 설정안하면 cpu마다 게임 속도 다르대

      SDL_Flip(screen);
  }

  SDL_FreeSurface(bullet);
  SDL_FreeSurface(background);
  SDL_FreeSurface(screen);

  SDL_Quit();//init한 SDL 변수들 닫아주는겅 일걸,위의 freesurface랑 차이 모름

  return 0;
}
