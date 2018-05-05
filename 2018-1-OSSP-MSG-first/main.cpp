#include "AirPlane.h"

SDL_Surface *screen;
SDL_Surface *background;

SDL_Event event;
Uint8 *keystates;

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
  return true;
}


int main(){
  init();//초기화 함수
  load_files();//이미지,폰트,bgm 로드하는 함수


  AirPlane A;
  Enemy_standard E;
  int start_time = 0;
  int delay = 0;
  int count = 0;

  while(true){
    start_time = SDL_GetTicks();//나중에 프레임 계산할 변수

    if(A.bullet_rect.size() > 0 )
      A.control_bullet();//총알들 위치 위로 상승하게하는거임

    if(E.bullet_rects.size() > 0)//임시 코딩. 잠시 적 총알 쏘게
      E.control_bullet();
    if(A.Got_shot(E.Get_bullets()))//임시 코딩. 사용자 맞으면 게임 끝
      break;
    if(SDL_PollEvent(&event)){
      if(event.type == SDL_QUIT)
			   break;
    }

    keystates = SDL_GetKeyState(NULL);

      if(keystates[SDLK_a])
      {
        A.shooting();
      }

      if(keystates[SDLK_UP])
        A.control_plane(0,-3);

      if(keystates[SDLK_DOWN])
        A.control_plane(0, 3);

      if(keystates[SDLK_LEFT])
        A.control_plane(-3, 0);

      if(keystates[SDLK_RIGHT])
        A.control_plane(3, 0);

    if(count++ % 30 == 0)//임시 코딩. 30번 반복마다 한번씩 발사
    {
      E.shooting();
    }

    apply_surface(0, 0, background,screen,NULL);//백그라운드 그리는거
    E.enemy_apply_surface(screen,NULL);//적 비행기 그리기 <-얘네다 임시로
    E.bullet_apply_surface(screen,NULL);//적 총알 그리기 <- 얘네다 임시로
    A.plane_apply_surface(screen,NULL);//A비행기 그리는거
    A.bullet_apply_surface(screen,NULL);//A비행기가 쏜 총알들 그리는거

    delay = 1000/30 - (SDL_GetTicks() - start_time);
    if(delay > 0)
      SDL_Delay(delay);//이거 fps를 고려해서 Delay해야됨 프레임 설정안하면 cpu마다 게임 속도 다르대

      SDL_Flip(screen);
  }
  SDL_FreeSurface(screen);//이거 얘 하나만 한 이유 딴거 없음 그냥 했음
  SDL_Quit();//init한 SDL 변수들 닫아주는겅 일걸?

  return 0;
}
