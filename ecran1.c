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

  // creer une fenetre en terminale

  WINDOW * menuwin = newwin (6, xMax-12, yMax-9, 5);
  box (menuwin, 0, 0);
  refresh();
  wrefresh(menuwin);
  refresh();

  // fleche fonctionnel

  keypad (menuwin, true);

  char choices[][20] = {"Jouer", "Continuer", "Quitter"};

  int choice;

  int highlight = 8;

  while(1)
  {
    for (int i = 0; i < 3; i++){
        mvwprintw(menuwin, i+1, 10, "%s", choices[i]);
        if(i == highlight)
            wattron (menuwin, A_REVERSE);
            wattroff (menuwin, A_REVERSE);
        wrefresh(menuwin);
       
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


  getch();
  endwin();

  /* NCURSES END */

  return 0;
}
