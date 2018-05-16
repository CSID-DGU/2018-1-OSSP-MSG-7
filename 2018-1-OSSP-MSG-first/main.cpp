#include "AirPlane.h"

SDL_Surface *screen;//화면
SDL_Surface *background;//배경화면
SDL_Surface *bullet;//총알 이미지
SDL_Surface *plane;// 사용자 비행기 이미지
SDL_Surface *enemy[4];//회전하는 비행기 이미지
SDL_Surface *boom[11];// 폭발 이미지

SDL_Surface *enemy2;

SDL_Event event;
Uint8 *keystates;

_bullets enemy_bullets;//적 총알 배열
_bullets player_bullets;//사용자 총알 배열


bool init();//변수들 초기화 함수
bool load_files();//이미지, 폰트 초기화 함수
bool SDL_free();// sdl 변수들 free 함수

int main(){
  init();//초기화 함수
  load_files();//이미지,폰트,bgm 로드하는 함수
  srand(time(NULL));

  int start_time = 0;
  int delay = 0;
  int count = 0;
  int shootcnt = 0;

  vector<Enemy_standard_2>::iterator it2;
  vector<Enemy_standard>::iterator it;
  vector<BOOM>::iterator B_it;

  vector<BOOM> B;//폭발
  vector<Enemy_standard> E;//기본1형 비행기
  vector<Enemy_standard_2> E2;// 2nd standard enemy
  AirPlane A;//사용자 비행기

  while(true){
    if(count % 5 == 0) shootcnt = 0;
    if(count % 50 == 0)//100count마다 1기씩 생성
    {
      int i = rand()%2;
      int j = rand()%2;
      Enemy_standard tmp(i);
      Enemy_standard_2 tmp2(j);
      E.push_back(tmp);
      E2.push_back(tmp2);
    }

    start_time = SDL_GetTicks();//나중에 프레임 계산할 변수

    if(player_bullets.blt.size() > 0 )//총알들 위치 이동
      player_bullets.control_bullet();

    if(enemy_bullets.blt.size() > 0)//적 총알들 위치 이동
      enemy_bullets.control_bullet();

    if(A.Got_shot(enemy_bullets.blt))//사용자 피격 판정
      break;

    if(E.size() > 0)
    {
      vector<Enemy_standard> v_tmp;

      for(it = E.begin(); it != E.end(); it++)//적 비행기들 피격 판정
      {
        Enemy_standard tmp(0);
        if((*it).Got_shot(player_bullets))//비행기가 격추 당하면
        {
          BOOM B_tmp((*it).Get_plane());
          B.push_back(B_tmp);
          (*it).~Enemy_standard();
        }
        else
        {
          tmp = *it;
          v_tmp.push_back(tmp);
        }
      }

      E = v_tmp;

    }
    if(E2.size()>0)
    {
        vector<Enemy_standard_2> v_tmp;
        for(it2 = E2.begin(); it2 != E2.end(); it2++)//적 비행기들 피격 판정
        {
          Enemy_standard_2 tmp(0);
          if((*it2).Got_shot(player_bullets))
          {
            BOOM B_tmp((*it2).Get_plane());
            B.push_back(B_tmp);
            (*it2).~Enemy_standard_2();
        }
          else
          {
            tmp = *it2;
            v_tmp.push_back(tmp);
          }
        }

        E2=v_tmp;
    }

    //키보드 이벤트 처리하는 부분
    if(SDL_PollEvent(&event)){
      if(event.type == SDL_QUIT)//버튼 누르면 꺼저야 되는데 안 꺼짐 수정 사항
			   break;
    }

    keystates = SDL_GetKeyState(NULL);

      if(E.size() > 0)//적 비행기 이동 및 발사
      {
        for(it = E.begin(); it != E.end(); it++)
        {
          (*it).control_plane(enemy_bullets);
        }
        for(it2 = E2.begin(); it2 != E2.end(); it2++)
        {
          (*it2).control_plane(enemy_bullets);
        }
      }



      if(keystates[SDLK_a])
      {
        if(shootcnt == 0) {
            A.shooting(player_bullets);
            shootcnt = 1;
        }
      }

      if(keystates[SDLK_UP])
        A.control_plane(0,-4);

      if(keystates[SDLK_DOWN])
        A.control_plane(0, 4);

      if(keystates[SDLK_LEFT])
        A.control_plane(-4, 0);

      if(keystates[SDLK_RIGHT])
        A.control_plane(4, 0);

    //이미지 그리는 부분
    apply_surface(0, 0, background,screen,NULL);//백그라운드 그리는거
    enemy_bullets.bullet_apply_surface(bullet, screen,NULL);//적 총알들
    player_bullets.bullet_apply_surface(bullet, screen, NULL);//사용자 총알들
    A.plane_apply_surface(plane, screen,NULL);//사용자 비행기
    if( E.size() > 0)//적 비행기
    {
      for( it = E.begin(); it != E.end(); it++)
      {
        (*it).enemy_apply_surface(enemy, screen, NULL);
      }
    }
    if( E2.size() > 0)
    {
      for( it2 = E2.begin(); it2 != E2.end(); it2++)
      {
        (*it2).enemy_apply_surface(screen, NULL);
      }
    }

    if( B.size() > 0)//폭발
    {
      vector<BOOM> B_tmp;

      for(B_it = B.begin(); B_it != B.end(); B_it++)
      {
        if((*B_it).b.count <  11)
        {
          (*B_it).boom_apply_surface(boom,screen,NULL);
          B_tmp.push_back(*B_it);
        }
        else
        {
          (*B_it).~BOOM();
        }
      }
      B = B_tmp;
    }
    //fps 계산
    delay = 1000/40 - (SDL_GetTicks() - start_time);
    if(delay > 0)
      SDL_Delay(delay);

      SDL_Flip(screen);
      count ++;
  }
  SDL_free();
  return 0;
}








bool init()
{//고칠 것: if문 추가해서 init했을 때 실패하면 false반환하게끔
  SDL_Init(SDL_INIT_EVERYTHING);
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_DOUBLEBUF );
  SDL_WM_SetCaption("MSG", NULL);
  return true;
}
//return true;

bool load_files()
{//고칠 것: if문 추가해서 init했을 때 실패하면 false반환하게끔
  background = load_image("assets/background.png");//배경화면
  bullet = load_image("assets/bullet.gif");// 총알 이미지
  plane = load_image("assets/p2.gif");// 사용자 비행기 이미지
  for(int i = 0 ; i < 4; i++)
  {
    string str = "assets/E_";
    string str1 = to_string(i + 1);
    string str2 = ".gif";
    string str3 = str + str1 + str2;
    enemy[i] = load_image(str3);
    SDL_SetColorKey(enemy[i], SDL_SRCCOLORKEY,SDL_MapRGB(enemy[i]->format,255,255,255));
  }
  for(int i = 0 ; i < 11; i++)//폭발 이미지
  {
    string str = "assets/explosion/";
    string str1 = to_string(i);
    string str2 = ".gif";
    string str3 = str + str1 + str2;
    boom[i] =load_image(str3);
    SDL_SetColorKey(boom[i], SDL_SRCCOLORKEY,SDL_MapRGB(boom[i]->format,255,255,255));
  }
  SDL_SetColorKey(plane, SDL_SRCCOLORKEY,SDL_MapRGB(plane->format,255,255,255));
  SDL_SetColorKey(bullet, SDL_SRCCOLORKEY,SDL_MapRGB(bullet->format,255,255,255));
  return true;
}

bool SDL_free()
{//올바르게 free하면 true 반환하게 수정
  SDL_FreeSurface(plane);
  SDL_FreeSurface(bullet);
  SDL_FreeSurface(background);
  SDL_FreeSurface(screen);
  for(int i =0 ; i < 4; i++)
    SDL_FreeSurface(enemy[i]);
  for(int i = 0; i < 11; i++)
    SDL_FreeSurface(boom[i]);

  SDL_Quit();//init한 SDL 변수들 닫아주는겅 일걸,위의 freesurface랑 차이 모름

  return true;
}
