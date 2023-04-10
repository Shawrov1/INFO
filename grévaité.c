#include <stdio.h>
#define lign 4
#define colo 5


int main() {
  int tableau[lign][colo] = {
    {2, 0, 1, 0, 1},
    {0, 1, 2, 0, 1},
    {2, 0, 0, 0, 1},
    {0, 0, 0, 2, 1}
  };

  // impression
  for (int i = 0; i < lign; i++) {
    for (int j = 0; j < colo; j++) {
      printf("%d ", tableau[i][j]);
    }
    printf("\n");
  }

  // gravité activé
  for(int k=0;k<(lign-1);k++){
  for(int i=0;i<colo;i++){
    for(int f=lign-1;f!=0;f--){
        if(tableau[f][i]==0 && tableau[f-1][i]!=0){
            tableau[f][i] = tableau[f-1][i];
            tableau[f-1][i]=0;}
        }
    }
  }
  printf("\n");

  //réimpression
    for (int i = 0; i < lign; i++) {
    for (int j = 0; j < colo; j++) {
      printf("%d ", tableau[i][j]);
    }
    printf("\n");
  }

  return 0;
}
