
#include "../headers/mainHeader.h"
#include <sys/wait.h>
/*------------------------------------------------------------------------------------------------------------------
 --       FUNCTION:                  main
 --
 --       DATE:                      April 16, 2009
 --
 --       REVISIONS:
 --
 --       DESIGNER:                  Alin Albu
 --
 --       PROGRAMMER:                Alin Albu
 --
 --       INTERFACE:                 main(int argc, char* args[])
 --
 --       RETURNS:                   0 on success
 --
 --       NOTES:
 --
     This function is the main entry point for the "TuxBomber" application. It starts by loading
     the paths for the menus background and player models form the config.txb file. It then
     will initialize all the SDL modules needed for the game. If all is succesfult it creates the
     menu objects and loads the main menu.If the user select Player Options it loads the options menu
     If game options is selected a text box appears and the user can input the server IP address.
     Start game will call the start() function that will connect to the server and start the game.
 ---------------------------------------------------------------------------------------------------------------------*/
int
main(int argc, char* args[])
{
  int xMenuH; //exit menu height
  char *arg[2]; // arguments to be passed to start()
   int mmresult, ocresult; //MainMenu result and OkCancel menu result
  bool fulls = false, exitGame = false;  //full screen and exit selected flags
  std::string ip; //server ip
  Uint32 countStart, fps, frame; // time when load menu started, num of frames per sec, current frame
  FILE * fp; // config.txb file pointer
  SDL_Event event;
  SDL_Surface *screen;
  std::string mainOpts[MainMenu2::num_options_];  //main menu backgrounds paths
  std::string models[POptMenu::num_models_]; //models paths
  std::string game_models[POptMenu::num_models_]; //game models paths
  std::string playaOpts[POptMenu::num_options_]; // player options backgrounds paths
  std::string exitOpts[3]; //exit dialog backgrounds paths
  int stat;
  arg[0] = (char *) malloc(17);
  arg[1] = (char *) malloc(17);

  fp = fopen(CONFIG);
  if(fp == NULL){
    perror("Make sure that config.txb is in the root folder.");
    exit(1);
  }
  //get paths from file
  getMenuItems(models, fp, "menu_models\n", POptMenu::num_models_);
  getMenuItems(game_models, fp, "game_models\n", POptMenu::num_models_);
  getMenuItems(mainOpts, fp, "main_menu\n", MainMenu2::num_options_);
  getMenuItems(exitOpts, fp, "exit_menu\n", 3);
  getMenuItems(playaOpts, fp, "options_menu\n", POptMenu::num_options_);

  //init SDL

  if (!init_everything(&screen))
    {
      return 1;
    }
  //done SDL_init

  printf("Done init all Loading main...\n");

  //create main menu and exit dialog
  MainMenu2 main(mainOpts, ASOUND, BSOUND, screen);
  OkCancel exitMenu(exitOpts, BSOUND, screen);
  InputOkCancel *ip_dialog = new InputOkCancel(exitOpts, BSOUND, screen, 20);
  POptMenu pMenu(models, playaOpts, ASOUND, BSOUND, screen);

  mmresult = 0;
  ocresult = 0;
  exitGame = false;
  //start main loop
  while (!exitGame)
    {
      mmresult = main.start(event);
      switch (mmresult)
        {
      case 0: //error
        exitGame = true;
        break;
      case 1:    //load EXIT  ok_cancel dialog
        fps = 50;
        xMenuH = exitMenu.getBackground(0)->h;
        for (frame = 0; frame < fps; frame++)
          {
            countStart = SDL_GetTicks();
            if (SDL_GetTicks() - countStart < 1000 / fps)
              SDL_Delay((1000 / fps) - (SDL_GetTicks() - countStart));
            main.move(0, 0);
            exitMenu.move(0, ((250 + xMenuH) * frame / (int) fps) - xMenuH);
            SDL_Flip(screen);
            countStart = SDL_GetTicks();
          }
        main.move(0, 0);
        ocresult = exitMenu.start(event);
        switch (ocresult)
          {
        case 1: //exit game selected
          exitGame = true;
          break;
        case 2: //cancel exit selected
          for (frame = 0; frame < fps; frame++)
            {
              countStart = SDL_GetTicks();
              if (SDL_GetTicks() - countStart < 1000 / fps)
                SDL_Delay((1000 / fps) - (SDL_GetTicks() - countStart));
              main.move(0, 0);
              exitMenu.move(0, ((250 + xMenuH) * (fps - frame) / (int) fps)
                  - xMenuH);
              SDL_Flip(screen);
              countStart = SDL_GetTicks();
            }
          exitGame = false;
          break;
        default:
          break;
          }
        break;
      case 2:   //load player options
        main.setLoaded(0);
        main.showLoaded();
        pMenu.setLoaded(0);
        fps = 60;
        for (frame = 0; frame < fps; frame++)
          {
            countStart = SDL_GetTicks();
            if (SDL_GetTicks() - countStart < 1000 / fps)
              SDL_Delay((1000 / fps) - (SDL_GetTicks() - countStart));
            main.move(0 - (frame * 10), 0);
             pMenu.move(600 - (frame * 10), 0);
            SDL_Flip(screen);
            countStart = SDL_GetTicks();
          }

        pMenu.start();

        main.setLoaded(0);
        fps = 60;
        for (frame = 0; frame < fps; frame++)
          {
            countStart = SDL_GetTicks();
            if (SDL_GetTicks() - countStart < 1000 / fps)
              SDL_Delay((1000 / fps) - (SDL_GetTicks() - countStart));
            pMenu.move(0 + (frame * 10), 0);
            main.move(-600 + (frame * 10), 0);
            SDL_Flip(screen);
            countStart = SDL_GetTicks();
          }
        break;
      case 3: //load start game
        memcpy(arg[0], "gameStart", 10);
        memcpy(arg[1], ip.c_str(), 17);

        if (fulls)
          {
            start(3, arg, screen, &exitMenu); //start full screen
          }
        else
          {
            start(2, arg, screen, &exitMenu);//start in window
          }
	exitGame = true;
        /*screen = fulls ? SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32,
            SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN) : SDL_SetVideoMode(
            SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);*/
        SDL_Flip(screen);
        break;
      case 4: //load game options
        ip = ip_dialog->start(event);
        break;
      case 'f': //full screen
        fulls = !fulls;
        screen = fulls ? SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32,
            SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN) : SDL_SetVideoMode(
            SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
        break;
        }
    }

  SDL_FreeSurface(screen);
  TTF_Quit();
  fclose(fp);
  free(arg[0]);
  free(arg[1]);
  //SDL_Quit();      ***** CAUSES AN ERROR?! **** WORKS FINE WITHOUT CALLING THIS

  printf("Done\n");
  return 0;
}
