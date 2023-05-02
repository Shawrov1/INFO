#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>

void animation(WINDOW *win,int y,int x,int *i){

    mvwprintw(win, 6, 1, "appuyez sur q pour arrêter l'animation");

    if(!(*i)){
        mvwprintw(win, y, x, "Zzzzzzzz...");

    wrefresh(win);
    sleep(2);
    (*i)++;
    }
    
    mvwprintw(win, y, x, "\\(^v^)/  Salut !");
    wrefresh(win);
    usleep(500000);
    mvwprintw(win, y, x, "\\(^_^)\\  Salut !");
    wrefresh(win);
    usleep(500000);mvwprintw(win, y, x, "/(^_^)/  Salut !");
    wrefresh(win);
    usleep(500000);
}

int main()
{
    // Initialisation de Ncurses
    initscr();

    // Création de la première boîte
    int height1 = 15;
    int width1 = 40;
    int starty1 = (LINES - height1) / 2;
    int startx1 = (COLS - width1) / 2;
    WINDOW* win1 = newwin(height1, width1, starty1, startx1);
    box(win1, 0, 0);

    // Création de la deuxième boîte à l'intérieur de la première
    int height2 = 6;
    int width2 = 26;
    //int starty2 = (height1 - height2) / 2 + starty1;
    //int startx2 = (width1 - width2) / 2 + startx1+3;

    int startx2 = startx1+2;

    WINDOW* win2 = newwin(3, width1-4, starty1+height1-7, startx2);
    box(win2, 0, 0);

    mvwprintw(win2,1,10,"je mange du pain");

    WINDOW* win3 = newwin(3, width1-4, starty1+height1-4, startx2);
    box(win3, 0, 0);

    mvwprintw(win3,1,10,"je mange du miel");

    // Affichage des deux boîtes
    refresh();
    wrefresh(win1);
    wrefresh(win2);
    wrefresh(win3);

    nodelay(win1,1);
    int i=0;
    int arret =0;
    while(!arret){
        animation(win1,2,10,&i);
        //wrefresh(win1);
        wrefresh(win2);
        wrefresh(win3);
        int k=wgetch(win1);
        if(k=='q'){
            arret++;
        }

    }

    mvwprintw(win1, 2, 10, "l'animation a été arrêté");
    mvwprintw(win1, 6, 1, "appuyez sur q pour quitter le programme");
    wrefresh(win1);


    // Attente de l'utilisateur
    printw("\n\n\n\n\n\n\n\n");

    while(1){
        int k=getch();
    if(k=='q'){
        endwin();return 0;
    }
    }
    

    // Nettoyage de Ncurses
    

    
}
