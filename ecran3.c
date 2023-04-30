#include <ncurses.h>
#include <string.h>


int main(int argc, char argv)
{
  /* NCURSES START */

  initscr();
  noecho();
  cbreak();

  // taille ecran

  int yMax, xMax; getmaxyx(stdscr, yMax, xMax);

  // creation fenetre
  
  *menuwin = newwin (6, xMax-12, yMax-8, 5);
  box (menuwin, 0, 0);
  wrefresh(menuwin);
  refresh();

  // définition des fleches

  keypad (menuwin, true);

  string choices[3] = {"2", "3"};

  int choice;

  int highlight = 8;

  while(1)
  {
    printw("Vous voulez jouer à 2 ou 3 ?");
    
    for (int i = 0; i < 2; i++){
      if(i == highlight)
        mvwprintw(menuwin, i+1, 1, choices[i].c_str());
        wattron (menuwin, A_REVERSE);
        wattroff (menuwin, A_REVERSE);
    }
  
    choice = wgetch(menuwin);

    switch(choice)
    {
      case KEY_UP:
        highlight--;
        if (highlight == -1)
          highlight= 0;
        break;

      case KEY_DOWN:
        highlight++;
        if(highlight == 3) 
          highlight= 2;
        break;
      default:
        break;
    }
    if (choice == 10)
      break;

  }


  // temps d'attente

  getch();
  endwin();

  / NCURSES END */

  return 0;
}