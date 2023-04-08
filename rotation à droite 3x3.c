#include <stdio.h>

#define colo 5
#define lign 5

int main(){
  int tableau[lign][colo];
  int as =10;
  for(int i=0;i<lign;i++){
    for(int j=0;j<colo;j++){
      tableau[i][j]=as;
      as++;
    }
  }
  int y=2;
  int x=2;
  //int (*caa)[colo] = tableau;

  //création tableau caa 3x3 à partir des coordonnés xy
    int caa[3][3];
  int *ptr = &tableau[y][x];
  
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      caa[i][j] = *(ptr + i*colo + j);
    }
  }

  //impression complet
  for(int i=0;i<colo;i++){
  for(int j=0;j<lign;j++){
    printf("%d ",tableau[i][j]);}
  printf("\n");}

  printf("\n");

  //impression du sous tableau crée
    for(int i=0;i<3;i++){
  for(int j=0;j<3;j++){
    printf("%d ",caa[i][j]);}
  printf("\n");}

  printf("\n");
  
  
    // Rotation à 90 degrés vers la droite du sous tableau
  int temp;
  for(int i=0;i<3;i++){
    for(int j=i+1;j<3;j++){
      temp = caa[i][j];
      caa[i][j] = caa[j][i];
      caa[j][i] = temp;
    }
  }
  for(int i=0;i<3;i++){
    int tempo;
    tempo=caa[i][0];
    caa[i][0]=caa[i][2];
    caa[i][2]=tempo;
  }
  //impression du sous tableau retourné
    for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      printf("%d ",caa[i][j]);
    }
    printf("\n");
  }
printf("\n");
  
  //imbriquement dans le tableau principal 


  for(int i=0; i<3; i++){
  for(int j=0; j<3; j++){
    tableau[i+y][j+x] = caa[i][j];
  }
}

  // impression tableau complet avec toutes les modifs
  for(int i=0;i<colo;i++){
  for(int j=0;j<lign;j++){
    printf("%d ",tableau[i][j]);}
  printf("\n");}
  

  return 0;
}
