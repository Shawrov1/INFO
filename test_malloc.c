#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include <locale.h>

//int colo;
//int lign;
#define WIN_LENGTH 5

//xx=dim returne 1 si ça marhce
int verif_tourner(int **tableau,int x,int y,int xx,int lign, int colo){
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
/*void tourner(int **tableau,int x,int y,int rota,int xx,int lign,int colo){  


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
  
}*/

void tourner(int **tableau, int x, int y, int rota, int xx, int lign, int colo) {  
    //création tableau fils "caa" carré de taille xx à partir des coordonnées (x,y)
    int caa[xx][xx];

    for (int i = 0; i < xx; i++) {
        for (int j = 0; j < xx; j++) {
            caa[i][j] = tableau[y + i][x + j];
        }
    }
    
    //1= rotation à droite, autre= rotation à gauche
    if (rota == 1) {
        //rotation 90° vers la droite
        for (int i = 0; i < xx / 2; i++) {
            for (int j = i; j < xx - i - 1; j++) {
                int temp = caa[i][j];
                caa[i][j] = caa[xx - j - 1][i];
                caa[xx - j - 1][i] = caa[xx - i - 1][xx - j - 1];
                caa[xx - i - 1][xx - j - 1] = caa[j][xx - i - 1];
                caa[j][xx - i - 1] = temp;
            }
        }
    } else {
        //rotation 90° vers la gauche
        for (int i = 0; i < xx / 2; i++) {
            for (int j = i; j < xx - i - 1; j++) {
                int temp = caa[i][j];
                caa[i][j] = caa[j][xx - i - 1];
                caa[j][xx - i - 1] = caa[xx - i - 1][xx - j - 1];
                caa[xx - i - 1][xx - j - 1] = caa[xx - j - 1][i];
                caa[xx - j - 1][i] = temp;
            }
        }
    }
  
    //imbriquement tableau fils dans le tableau père 
    for (int i = 0; i < xx; i++) {
        for (int j = 0; j < xx; j++) {
            tableau[y + i][x + j] = caa[i][j];
        }
    }
}




void afficher_grille(int **grille, int lign, int colo) {
    //setlocale(LC_ALL, "");
    printf("\n");
    for (int i = 0; i < lign; i++) {
        //printw("%d  ",i+1);
        for (int j = 0; j < colo; j++) {
            if(grille[i][j]==' '){
                printw("|  ");
            }
            else{
                wprintw(stdscr,"|%lc", grille[i][j]);
            }
            
        }
        printw("|\n");
    }

    for(int i=0;i<colo;i++){
        printw("___");
    }
    printw("_\n");
    for(int i=0;i<colo;i++){
        if(i>8){
            printw(" %d",i+1);
        }
        else{
            printw("  %d",i+1);
        }
    }
    printw("\n");
    /*if(colo==8){
        
        printw("_________________________\n");
        printw("  1  2  3  4  5  6  7  8  \n"); 
    }
    else{
        printw("______________________________\n");
        printw("  1  2  3  4  5  6  7  8  9 10 \n");
    }*/
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
/*int jouer_coup(int **grille, int colonne, int jeton,int lign, int colo) {
    //vérifier si la colonne n'est pas obstrué par un bloc
    if(grille[0][colonne]!=' '){
        printf("la colonne est pleine.\n");
        return 0;
    }

    for (int i = 0; i < (lign ); i++) {
    grille[i][colonne] = jeton;
    usleep(100000);
    clear();

    afficher_grille(grille, lign, colo);
    grille[i][colonne] = ' ';
    if (grille[i][colonne] == ' ' && grille[i+1][colonne] != ' ' || i==(lign-2)) {
        grille[i][colonne] = ' ';
        grille[i+1][colonne] = jeton;
        clear();
        return 1;
    }
}

    
    //printf("La colonne est pleine.\n");
    return 0;
}*/

int jouer_coup(int **grille, int colonne, int jeton, int lign, int colo) {
    // Vérifier si la colonne n'est pas obstruée par un bloc
    if (grille[0][colonne] != ' ') {
        printf("La colonne est pleine.\n");
        return 0;
    }

    // Parcourir les lignes de la colonne pour simuler le mouvement du jeton
    for (int i = 0; i < lign; i++) {
        // Placer temporairement le jeton dans la case courante
        grille[i][colonne] = jeton;

        // Effacer l'écran et afficher la grille modifiée temporairement
        usleep(100000);
        clear();
        afficher_grille(grille, lign, colo);

        // Retirer temporairement le jeton de la case courante
        grille[i][colonne] = ' ';

        // Si la case courante est vide et la case suivante est pleine, ou si nous sommes à la dernière ligne de la colonne
        if (grille[i][colonne] == ' ' && (i == lign-1 || grille[i+1][colonne] != ' ')) {
            // Placer le jeton dans la case courante
            grille[i][colonne] = jeton;

            // Effacer l'écran et retourner 1 pour indiquer que le coup a été joué avec succès
            clear();
            return 1;
        }
    }

    // Si la colonne est pleine, afficher un message d'erreur et retourner 0
    printf("La colonne est pleine.\n");
    return 0;
}


// Vérifier s'il y a un gagnant
int verifier_gagnant(int **grille, int jeton,int indices_gagnants[5][2],int lign,int colo) {
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
                // Stocker les indices des jetons gagnants
                for (int l = 0; l < WIN_LENGTH; l++) {
                    indices_gagnants[l][0] = i;
                    indices_gagnants[l][1] = j+l;
                }

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
            // Stocker les indices des jetons gagnants
            for (int l = 0; l < WIN_LENGTH; l++) {
                indices_gagnants[l][0] = i+l;
                indices_gagnants[l][1] = j;
            }
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
            // Stocker les indices des jetons gagnants
            for (int l = 0; l < WIN_LENGTH; l++) {
                indices_gagnants[l][0] = i-l;
                indices_gagnants[l][1] = j+l;
            }
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
            // Stocker les indices des jetons gagnants
            for (int l = 0; l < WIN_LENGTH; l++) {
                indices_gagnants[l][0] = i-l;
                indices_gagnants[l][1] = j-l;
            }
            return jeton;
        }
    }
}return 0;}


void gravite(int **tableau,int lign,int colo){
    for(int k=0;k<(lign-1);k++){
        for(int i=0;i<colo;i++){
            for(int f=lign-1;f!=0;f--){
                if(tableau[f][i]==32 && tableau[f-1][i]!=32 && tableau[f-1][i]!=0x2B1B){
                tableau[f][i] = tableau[f-1][i];
                tableau[f-1][i]=32;}
        }
    }
    
    clear();
    afficher_grille(tableau,lign,colo);
    usleep(100000);
  }
  clear();
}

void creation_tableau(int **tableau,int lign,int colo){
    
    for (int i = 0; i < lign; i++) {
        for (int j = 0; j < colo; j++) {
            tableau[i][j] = ' ';
        }
    }
    tableau[0][0]=0x2B1B;
    tableau[0][colo-1]=0x2B1B;
    tableau[lign-1][0]=0x2B1B;
    tableau[lign-1][colo-1]=0x2B1B;
}

void creation_tableau_jeton(int *cotab_jeton,int colo){
    for(int i=0;i<colo;i++){
        cotab_jeton[i]=' ';
    }
    //cotab_jeton[0]='^';
}
void affichage_tableau_jeton(int *cotab_jeton, int co_jeton,int colo){
    cotab_jeton[co_jeton]='^';
    for(int i=0;i<colo;i++){
        attron(COLOR_PAIR(1));
        printw("  %c",cotab_jeton[i]);
        attroff(COLOR_PAIR(1));
    }
    refresh();
}
void deplacement_jeton(int *cotab_jeton,int ch_jeton,int *co_jeton,int*play_jeton,int colo){
    switch (ch_jeton)
    {
    case KEY_LEFT:
        if((*co_jeton)>0){
            cotab_jeton[(*co_jeton)]=' ';
            (*co_jeton)--;
            cotab_jeton[(*co_jeton)]='^';
        }
        else{
            cotab_jeton[(*co_jeton)]=' ';
            (*co_jeton)=colo-1;
        }
        break;
    case KEY_RIGHT:
        if((*co_jeton)<colo-1){
            cotab_jeton[(*co_jeton)]=' ';
            (*co_jeton)++;
            cotab_jeton[(*co_jeton)]='^';
        }
        else{
            cotab_jeton[(*co_jeton)]=' ';
            (*co_jeton)=0;
        }
        break;
    case '\n':
        (*play_jeton)--;
    }
    clear();

    //affichage_tableau_jeton(cotab_jeton);
}

void deplacement_rota(int **tab,int ch_rota,int *x,int *y,int *m,int dim,int coo_x,int coo_y,int lign,int colo){
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
                if(verif_tourner(tab,coo_x,coo_y,dim,lign,colo)){
                    (*m)--;
                    break;
                }
        }
        clear();
}

void affichage_rota(int **tab,int coo_x,int coo_y,int dim,int lign,int colo){
    //printw("\n");
    for (int i = 0; i < lign; i++) {
    //printw("%d  ",i+1);
        for (int j = 0; j < colo; j++) {
            if(i>=coo_x && i<coo_x+dim && j>=coo_y && j<coo_y+dim){
                printw("|");
                attron(A_REVERSE);
                if(tab[i][j]==' '){
                    printw("  ");}
                else{
                    printw("%lc",tab[i][j]);
                }
                attroff(A_REVERSE);
            }
            else{
                if(tab[i][j]==' '){
                    printw("|  ");}
                else{
                    printw("|%lc", tab[i][j]);}
            }
    } 
    printw("|\n");
}}

void creation_choix_rota(int tab_choix_rota[2]){
    tab_choix_rota[0]=' ';
    tab_choix_rota[1]='>';
    tab_choix_rota[2]=' ';
}

void deplacement_choix_rota(int tab_choix_rota[1],int ch_choix_rota,int *coo_choix_rota,int *play_choix_rota){
    switch (ch_choix_rota){
        case KEY_UP:
            if((*coo_choix_rota)>0){
                tab_choix_rota[(*coo_choix_rota)]=' ';
                (*coo_choix_rota)--;
                tab_choix_rota[(*coo_choix_rota)]='>';
            }
            break;
        case KEY_DOWN:
            if((*coo_choix_rota)<2){
                tab_choix_rota[(*coo_choix_rota)]=' ';
                (*coo_choix_rota)++;
                tab_choix_rota[(*coo_choix_rota)]='>';
            }
            break;
        case '\n':
            if((*coo_choix_rota)!=1){
                (*play_choix_rota)--;
                break;
            }
    }
    clear();
}

void affichage_choix_rota(int tab_choix_rota[2]){
    //affichage avec seul le pointeur en noir
    /*attron(COLOR_PAIR(1));
    printw("%c ",tab_choix_rota[0]);
    attroff(COLOR_PAIR(1));
    printw("à gauche\n");
    attron(COLOR_PAIR(1));
    printw("%c ",tab_choix_rota[1]);
    attroff(COLOR_PAIR(1));
    printw("à droite");*/

    int carreau = 0x0001F538;
    if(tab_choix_rota[0]=='>'){
        attron(COLOR_PAIR(2));
        printw("%lc à gauche %lc\n",carreau,carreau);
        attroff(COLOR_PAIR(2));

        printw("   voir l'original\n");
        
        printw("   à droite");
    }
    else if(tab_choix_rota[1]=='>'){
        printw("   à gauche\n");
        attron(COLOR_PAIR(2));
        printw("   voir l'original\n");
        attroff(COLOR_PAIR(2));
        printw("   à droite");
    }
    else{
        printw("   à gauche\n");
        printw("   voir l'original\n");
        attron(COLOR_PAIR(2));
        printw("%lc à droite %lc",carreau,carreau);
        attroff(COLOR_PAIR(2));
    }
    //printw("%lc",carreau);
    //printw("prout")
}

int match_nul(int **tab,int lign,int colo){
    int draw=0;
    for(int i=0;i<colo;i++){
        if(tab[0][i]==' '){
            draw++;
        }
    }
    if(draw){
        return 0;
    }
    else{
        return 1;
    }
}

void tab_copy(int **tab,int **tab2,int lign,int colo){
    for (int i = 0; i < lign; i++) {
        for (int j = 0; j < colo; j++) {
            tab2[i][j] = tab[i][j];
        }
    }
}

void win_add(int **tab,int indices_gagnants[5][2],int jeton,int lign,int colo){
    for (int i = 0; i < 5; i++){
            tab[indices_gagnants[i][0]][indices_gagnants[i][1]]=jeton;   
        }
}

void animation_winner(int **tab, int indices_gagnants[5][2],int jeton,int lign,int colo){

    for(int i=0;i<colo;i++){
        for(int j=0;j<lign;j++){
            tab[j][i] = ' ';
        }
        win_add(tab,indices_gagnants,jeton,lign,colo);
        clear();
        afficher_grille(tab,lign,colo);
        refresh();
        usleep(100000);
    }
}

int main(){
    int lign,colo;

    setlocale(LC_ALL, "");
    int jeton = 0x0001F535;
    int taille_grille =1;
    int nb_joueur = 2;
    int ch_jeton;

    initscr();
    start_color();
    assume_default_colors(COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    //printf("Vous pouvez jouer à 2 ou 3 joueurs, à combien de joueur voulez vous jouer ?\n");
    //scanf("%d",&nb_joueur);

    //printf("vous voulez jouer dans une grille 8x6 ou 10x8:\n-0:8x6\n-1:10x8\n");
    //scanf("%d",&taille_grille);
    if(taille_grille){lign=8;colo=10;}
    else{lign=6;colo=8;}

    int **tableau = malloc(lign * sizeof(int *));
    for(int i = 0; i < lign; i++){
        tableau[i] = malloc(colo * sizeof(int));
    }
    int **tab_rota = malloc(lign * sizeof(int *));
    for(int i = 0; i < lign; i++){
        tab_rota[i] = malloc(colo * sizeof(int));
    }

    int jeu;
    int gagnant =0;
    //int tableau[lign][colo];
    //int tab_rota[lign][colo];


    int indices_gagnants[5][2];

    creation_tableau(tableau,lign,colo);
    afficher_grille(tableau,lign,colo);
    int co_jeton=0;
    int draw;


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

        draw=0;

        
        int cotab_jeton[colo];
        
        int play_jeton=1;
        int m=1;
        int play_choix_rota=1;
        int coo_choix_rota =1;


        int tab_choix_rota[2];
        creation_tableau_jeton(cotab_jeton,colo);
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
            afficher_grille(tableau,lign,colo);
            affichage_tableau_jeton(cotab_jeton,co_jeton,colo);
            printw("\njoueur %lc, à vous de jouer \n",jeton);
            printw("\n");
            ch_jeton= getch();

            deplacement_jeton(cotab_jeton,ch_jeton,&co_jeton,&play_jeton,colo);
        }

        if(jouer_coup(tableau,co_jeton,jeton,lign,colo)){
            //afficher_grille(tableau);
    


            while(m){
                affichage_rota(tableau,coo_x,coo_y,dim,lign,colo);
                printw("\n");
                printw("%d %d",coo_y,coo_x);
                printw("\nvous avez obtenu la dimension %d, choisissez où vous voulez l'appliquer.",dim);
                printw("\n");
                int ch_rota= getch();

                //x,y inversé
                deplacement_rota(tableau,ch_rota,&coo_x,&coo_y,&m,dim,coo_y,coo_x,lign,colo);
            }
            //printw("je mange du pain");
            //sleep(20);
            tab_copy(tableau,tab_rota,lign,colo);

            while(play_choix_rota){
                affichage_rota(tab_rota,coo_x,coo_y,dim,lign,colo);
                printw("\n");
                affichage_choix_rota(tab_choix_rota);
                printw("\n");
                int ch_choix_rota=getch();
                deplacement_choix_rota(tab_choix_rota,ch_choix_rota,&coo_choix_rota,&play_choix_rota);
                if(coo_choix_rota!=1){
                    tab_copy(tableau,tab_rota,lign,colo);
                    if(coo_choix_rota==2){
                        tourner(tab_rota,coo_y,coo_x,1,dim,lign,colo);
                    }
                    else{
                        tourner(tab_rota,coo_y,coo_x,0,dim,lign,colo);
                    }
                }
                else{
                    tab_copy(tableau,tab_rota,lign,colo);
                }
            }
            tab_copy(tab_rota,tableau,lign,colo);
            // x,y inversé
            //tourner(tableau,coo_y,coo_x,coo_choix_rota,dim);
            gravite(tableau,lign,colo);


            gagnant = verifier_gagnant(tableau, jeton,indices_gagnants,lign,colo);
            if(gagnant){
                break;
            }
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
            if(jeton== 0x0001F535){jeton=0x0001F7E1;}
            else{jeton= 0x0001F535;}};
        if(nb_joueur==3){
            if(jeton==0x0001F535){jeton=0x0001F7E2;}
            else if(jeton==0x0001F7E2){jeton=0x0001F7E1;}
            else {jeton=0x0001F535;}
        }
        if(match_nul(tableau,lign,colo)){
            draw++;
            break;
        }
    }
    if(draw){
        clear();
        printw("match nul\n");
        refresh();
        sleep(10);
    }
    if(gagnant){
        printw("\nil y un gagnant\n");
        animation_winner(tableau,indices_gagnants,jeton,lign, colo);
        for (int i = 0; i < 5; i++){
            printw("(%d, %d)\n", indices_gagnants[i][0], indices_gagnants[i][1]);    
        }
        refresh();
        sleep(20);
    }
    endwin();
    exit(0);
    
}