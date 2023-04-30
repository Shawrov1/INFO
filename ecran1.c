#include <ncurses.h>
#include <string.h>


int main(int argc, char argv)
{
  /* NCURSES START "/

  initscr();
  noecho();
  cbreak();

  // get screen size

  int yMax, xMax; getmaxyx(stdscr, yMax, xMax);

  // create a window for our input WINDOW * menuwin = newwin (6, xMax-12, yMax-8, 5); box (menuwin, 0, 0); wrefresh(menuwin);

  refresh();

  // makes it so we can use arrow keys

  keypad (menuwin, true);

  string choices[3] = {"Jouer", "Continuer", "Quitter"};

  int choice;

  int highlight = 8;

  while(1)
  {
    for (int i = 0; i < 3; i++){
      if(i == highlight)
        wattron (menuwin, A_REVERSE);          mvwprintw(menuwin, i+1, 1, choices[i].c_str());
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


  // make sure program waits before exiting...

  getch();
  endwin();

  /* NCURSES END */

  return 0;
}