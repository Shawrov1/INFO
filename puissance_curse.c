#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

int colo;
int lign;
#define WIN_LENGTH 5

//xx=dim returne 1 si ça marhce
int verif_tourner(int tableau[lign][colo],int x,int y,int xx){
    int caa[xx][xx];
    int *ptr = &tableau[y][x];

    int total=32*xx*xx;
    int tot=0;


  for(int i=0; i<xx; i++){
    for(int j=0; j<xx; j++){
      caa[i][j] = *(ptr + i*colo + j);
    }
  }
    

    for (int i = 0; i < xx; i++) {
        for (int j = 0; j < xx; j++) {
            tot += caa[i][j];
        }
    }
    if(tot==total){
        return 0;
    }
    else{return 1;}
}
// xx=dim
void tourner(int tableau[lign][colo],int x,int y,int rota,int xx){  


    //création tableau fils "caa" carré de taille xx à partir des coordonnés (x,y)
    int caa[xx][xx];
    int *ptr = &tableau[y][x];


  for(int i=0; i<xx; i++){
    for(int j=0; j<xx; j++){
      caa[i][j] = *(ptr + i*colo + j);
    }
  }
    
  //1= rotation à droite, autre= rotation à gauche
  if(rota==1){
    //rotation 90° vers la droite
    for(int i=0; i<xx/2; i++) {
        for(int j=i; j<xx-i-1; j++) {
            int temp = caa[i][j];
            caa[i][j] = caa[xx-j-1][i];
            caa[xx-j-1][i] = caa[xx-i-1][xx-j-1];
            caa[xx-i-1][xx-j-1] = caa[j][xx-i-1];
            caa[j][xx-i-1] = temp;
        }
    }}
  else{
    //rotation 90° vers la gauche
    for(int i=0;i<3;i++){
        for(int i=0; i<xx/2; i++) {
        for(int j=i; j<xx-i-1; j++) {
            int temp = caa[i][j];
            caa[i][j] = caa[xx-j-1][i];
            caa[xx-j-1][i] = caa[xx-i-1][xx-j-1];
            caa[xx-i-1][xx-j-1] = caa[j][xx-i-1];
            caa[j][xx-i-1] = temp;
        }
    }}
  }
  
  //imbriquement tableau fils dans le tableau père 
  for(int i=0; i<xx; i++){
  for(int j=0; j<xx; j++){
    tableau[i+y][j+x] = caa[i][j];
  }
}
  
}



void afficher_grille(int grille[lign][colo]) {
    printw("\n");
    for (int i = 0; i < lign; i++) {
        //printw("%d  ",i+1);
        for (int j = 0; j < colo; j++) {
            printw("| %c ", grille[i][j]);
        }
        printw("|\n");
    }
    if(colo==8){
        printw("_________________________________\n");
        printw("  1   2   3   4   5   6   7   8  \n"); 
    }
    else{
        printw("_________________________________________\n");
        printw("  1   2   3   4   5   6   7   8   9  10 \n");
    }
    refresh();

}

/*int jouer_coup(int grille[lign][colo], int colonne, char jeton) {
    for (int i = lign - 1; i >= 0; i--) {
        if (grille[i][colonne] == ' ') {
            grille[i][colonne] = jeton;
            return 1;
        }
    }
    printf("La colonne est pleine.\n");
    return 0;
}*/

//placer le coup joué
int jouer_coup(int grille[lign][colo], int colonne, char jeton) {
    //vérifier si la colonne n'est pas obstrué par un bloc
    if(grille[0][colonne] =='#'){
        printf("la colonne est pleine.\n");
        return 0;
    }

    for (int i = 0; i < lign; i++) {
        if (grille[i][colonne] == ' ' && grille[i+1][colonne]!= ' ') {
            grille[i][colonne] = jeton;
            return 1;
        }
    }
    printf("La colonne est pleine.\n");
    return 0;
}

// Vérifier s'il y a un gagnant
int verifier_gagnant(int grille[lign][colo], char jeton) {
    // Vérifier les lignes
    for (int i = 0; i < lign; i++) {
        for (int j = 0; j <= colo - WIN_LENGTH; j++) {
            int k;
            for (k = 0; k < WIN_LENGTH; k++) {
                if (grille[i][j+k] != jeton) {
                    break;
                }
            }
            if (k == WIN_LENGTH) {
                return jeton;
            }
        }}
   
// Vérifier les colonnes
for (int i = 0; i <= lign - WIN_LENGTH; i++) {
    for (int j = 0; j < colo; j++) {
        int k;
        for (k = 0; k < WIN_LENGTH; k++) {
            if (grille[i+k][j] != jeton) {
                break;
            }
        }
        if (k == WIN_LENGTH) {
            return jeton;
        }
    }
}

// Vérifier les diagonales 
for (int i = WIN_LENGTH - 1; i < lign; i++) {
    for (int j = 0; j <= colo - WIN_LENGTH; j++) {
        int k;
        for (k = 0; k < WIN_LENGTH; k++) {
            if (grille[i-k][j+k] != jeton) {
                break;
            }
        }
        if (k == WIN_LENGTH) {
            return jeton;
        }
    }
}

// Vérifier les diagonales 
for (int i = WIN_LENGTH - 1; i < lign; i++) {
    for (int j = WIN_LENGTH - 1; j < colo; j++) {
        int k;
        for (k = 0; k < WIN_LENGTH; k++) {
            if (grille[i-k][j-k] != jeton) {
                break;
            }
        }
        if (k == WIN_LENGTH) {
            return jeton;
        }
    }
}return 0;}


void gravite(int tableau[lign][colo]){
    for(int k=0;k<(lign-1);k++){
        for(int i=0;i<colo;i++){
            for(int f=lign-1;f!=0;f--){
                if(tableau[f][i]==32 && tableau[f-1][i]!=32 && tableau[f-1][i]!='#'){
                tableau[f][i] = tableau[f-1][i];
                tableau[f-1][i]=32;}
        }
    }
  }
}

void creation_tableau(int tableau[lign][colo]){
    
    for (int i = 0; i < lign; i++) {
        for (int j = 0; j < colo; j++) {
            tableau[i][j] = ' ';
        }
    }
    tableau[0][0]='#';
    tableau[0][colo-1]='#';
    tableau[lign-1][0]='#';
    tableau[lign-1][colo-1]='#';
}

void creation_tableau_jeton(int cotab_jeton[colo]){
    for(int i=0;i<colo;i++){
        cotab_jeton[i]=' ';
    }
    cotab_jeton[0]='^';
}
void affichage_tableau_jeton(int cotab_jeton[colo]){
    for(int i=0;i<colo;i++){
        printw("  %c ",cotab_jeton[i]);
    }
    refresh();
}
void deplacement_jeton(int cotab_jeton[colo],int ch_jeton,int *co_jeton,int*play_jeton){
    switch (ch_jeton)
    {
    case KEY_LEFT:
        if((*co_jeton)>0){
            cotab_jeton[(*co_jeton)]=' ';
            (*co_jeton)--;
            cotab_jeton[(*co_jeton)]='^';
        }
        break;
    case KEY_RIGHT:
        if((*co_jeton)<colo-1){
            cotab_jeton[(*co_jeton)]=' ';
            (*co_jeton)++;
            cotab_jeton[(*co_jeton)]='^';
        }
        break;
    case '\n':
        (*play_jeton)--;
    }
    clear();

    //affichage_tableau_jeton(cotab_jeton);
}

void deplacement_rota(int tab[lign][colo],int ch_rota,int *x,int *y,int *m,int dim,int coo_x,int coo_y){
    switch(ch_rota) {
            case KEY_LEFT:
                if ((*y) > 0) {
                    (*y)--;
                }
                break;
            case KEY_RIGHT:
                if ((*y) < colo-dim) {
                    (*y)++;
                }
                break;
            case KEY_UP:
                if ((*x) > 0) {
                    (*x)--;
                }
                break;
            case KEY_DOWN:
                if ((*x) < lign-dim) {
                    (*x)++;
                }
                break;

            case '\n':
                if(verif_tourner(tab,coo_x,coo_y,dim)){
                    (*m)--;
                    break;
                }
        }
        clear();
}

void affichage_rota(int tab[lign][colo],int coo_x,int coo_y,int dim){
    printw("\n");
    for (int i = 0; i < lign; i++) {
    //printw("%d  ",i+1);
        for (int j = 0; j < colo; j++) {
            if(i>=coo_x && i<coo_x+dim && j>=coo_y && j<coo_y+dim){
                printw("|");
                attron(A_REVERSE);
                printw(" %c ",tab[i][j]);
                attroff(A_REVERSE);
            }
            else{printw("| %c ", tab[i][j]);}
        }
    printw("|\n");
    } 
}

void creation_choix_rota(int tab_choix_rota[1]){
    tab_choix_rota[0]='>';
    tab_choix_rota[1]=' ';
}

void deplacement_choix_rota(int tab_choix_rota[1],int ch_choix_rota,int *coo_choix_rota,int *play_choix_rota){
    switch (ch_choix_rota){
        case KEY_UP:
            if((*coo_choix_rota)>0){
                tab_choix_rota[0]='>';
                tab_choix_rota[1]=' ';
                (*coo_choix_rota)--;
            }
            break;
        case KEY_DOWN:
            if((*coo_choix_rota)<1){
                tab_choix_rota[0]=' ';
                tab_choix_rota[1]='>';
                (*coo_choix_rota)++;
            }
            break;
        case '\n':
            (*play_choix_rota)--;
            break;
    }
    clear();
}

void affichage_choix_rota(int tab_choix_rota[1]){
    printw("%c à gauche\n%c à droite",tab_choix_rota[0],tab_choix_rota[1]);
}



int main(){
    char jeton = 'X';
    int taille_grille =1;
    int nb_joueur = 2;
    int ch_jeton;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    //printf("Vous pouvez jouer à 2 ou 3 joueurs, à combien de joueur voulez vous jouer ?\n");
    //scanf("%d",&nb_joueur);

    //printf("vous voulez jouer dans une grille 8x6 ou 10x8:\n-0:8x6\n-1:10x8\n");
    //scanf("%d",&taille_grille);
    if(taille_grille){lign=8;colo=10;}
    else{lign=6;colo=8;}
    int jeu;
    int gagnant =0;
    int tableau[lign][colo];
    creation_tableau(tableau);
    afficher_grille(tableau);


    /*while (caca)
    {
        afficher_grille(tableau);
        printf("\n");
        scanf("%d",&jeu);
        printf("\n");
        jouer_coup(tableau,jeu,jeton);
        afficher_grille(tableau);
        tourner(tableau,1,1,0,3);
        afficher_grille(tableau);
        printf("6666666666666666666666666666666666666");
        printf("\n");
        printf("\n");
        printf("\n");
    }*/

    while (!gagnant) {

        int co_jeton=0;
        int cotab_jeton[colo];
        
        int play_jeton=1;
        int m=1;
        int play_choix_rota=1;
        int coo_choix_rota =0;


        int tab_choix_rota[1];
        creation_tableau_jeton(cotab_jeton);
        creation_choix_rota(tab_choix_rota);
        

        clear();
        // Afficher la grille actuelle
        //afficher_grille(tableau);
        int coo_x=0;
        int coo_y=0;
        
        
        
        srand(time(NULL));
        int dim= rand() % 2;
        if(dim==0){dim=3;}
        else{dim=5;}

        

        while(play_jeton){
            afficher_grille(tableau);
            affichage_tableau_jeton(cotab_jeton);
            printw("\njoueur %c, à vous de jouer",jeton);
            printw("\n");
            ch_jeton= getch();

            deplacement_jeton(cotab_jeton,ch_jeton,&co_jeton,&play_jeton);
        }

        if(jouer_coup(tableau,co_jeton,jeton)){
            //afficher_grille(tableau);
    


            while(m){
                affichage_rota(tableau,coo_x,coo_y,dim);
                printw("\n");
                printw("%d %d",coo_y,coo_x);
                printw("\nvous avez obtenu la dimension %d, choisissez où vous voulez l'appliquer.",dim);
                printw("\n");
                int ch_rota= getch();

                //x,y inversé
                deplacement_rota(tableau,ch_rota,&coo_x,&coo_y,&m,dim,coo_y,coo_x);
            }

            while(play_choix_rota){
                affichage_rota(tableau,coo_x,coo_y,dim);
                printw("\n");
                affichage_choix_rota(tab_choix_rota);
                printw("\n");
                int ch_choix_rota=getch();
                deplacement_choix_rota(tab_choix_rota,ch_choix_rota,&coo_choix_rota,&play_choix_rota);

            }
            
            // x,y inversé
            tourner(tableau,coo_y,coo_x,coo_choix_rota,dim);
            gravite(tableau);



            gagnant = verifier_gagnant(tableau, jeton);
        }
        else{
            continue;
        }
        
        /*

        afficher_grille(tableau);printf("affichage classique");

        // Jouer le coup et vérifier s'il y a un gagnant
        if (jouer_coup(tableau, jeu, jeton)) {
            afficher_grille(tableau);printf("affichage après jeu\n");


            printf("vous avez obtenu la dimension %d !\n",dim);
            printf("entrez les coordonnées d'où vous voulez faire tourner\n");
            printf("x: ");
            scanf("%d",&coo_x);
            printf("\ny: ");
            scanf("%d",&coo_y);

        

            if(dim==3){
                if(!tourner(tableau,coo_x-2,coo_y-2,1,dim)){
                    do{
                        printf("réessayez svp");
                        printf("\nx: ");
                        scanf("%d",&coo_x);
                        printf("\ny: ");
                        scanf("%d",&coo_y);
                    }while(!tourner(tableau,coo_x-2,coo_y-2,1,dim));
                }; 
            }
            else{
                if(!tourner(tableau,coo_x-3,coo_y-3,1,dim)){
                    do{
                        printf("réessayez svp");
                        printf("\nx: ");
                        scanf("%d",&coo_x);
                        printf("\ny: ");
                        scanf("%d",&coo_y);
                    }while(!tourner(tableau,coo_x-3,coo_y-3,1,dim));
                }; 
            }


            afficher_grille(tableau);printf("affichage après rotation");
            gravite(tableau);
            afficher_grille(tableau);printf("affichage après gravité");
            gagnant = verifier_gagnant(tableau, jeton);
        }

        printf("\n");
        printf("\n");
        printf("\n");*/

        // Changer le jeton pour le prochain joueur
        if(nb_joueur==2){
            if(jeton=='X'){jeton='O';}
            else{jeton='X';}};
        if(nb_joueur==3){
            if(jeton=='X'){jeton='+';}
            else if(jeton=='+'){jeton='O';}
            else {jeton='X';}
        }
    }
    endwin();
    exit(0);
    
}
