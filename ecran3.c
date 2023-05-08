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

  char choices[][20] = {"2", "3"};

  int choice;

  int highlight = 0;

  

  while(1)
  {
    for (int i = 0; i < 2; i++){
      if(i == highlight){
        wattron (menuwin, A_REVERSE);
        mvwprintw(menuwin, i+1, 10, "%s", choices[i]);
        wattroff (menuwin, A_REVERSE);
        
      }
      
      else {
      mvwprintw(menuwin, 0, 30, "Voulez vous jouer à 2 ou 3 ?");
      mvwprintw(menuwin, i+1, 10, "%s", choices[i]);
      }

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
        if(highlight == 2) 
          highlight= 1;
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
