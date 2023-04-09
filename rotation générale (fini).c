#include <stdio.h>

#define colo 8
#define lign 6

void tourner(int tableau[lign][colo],int x,int y,int rota,int xx){


  //création tableau fils "caa" carré de taille xx à partir des coordonnés (x,y)
  int caa[xx][xx];
  int *ptr = &tableau[y][x];
  
  for(int i=0; i<xx; i++){
    for(int j=0; j<xx; j++){
      caa[i][j] = *(ptr + i*colo + j);
    }
  }

  //impression tableau père
  for(int i=0;i<lign;i++){
  for(int j=0;j<colo;j++){
    printf("%d ",tableau[i][j]);}
  printf("\n");}

  printf("\n");

  //impression tableau fils
    for(int i=0;i<xx;i++){
  for(int j=0;j<xx;j++){
    printf("%d ",caa[i][j]);}
  printf("\n");}

  printf("\n");

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
  
  //impression tableau fils retournée
    for(int i=0;i<xx;i++){
    for(int j=0;j<xx;j++){
      printf("%d ",caa[i][j]);
    }
    printf("\n");
  }
printf("\n");
  
  //imbriquement tableau fils dans le tableau père 
  for(int i=0; i<xx; i++){
  for(int j=0; j<xx; j++){
    tableau[i+y][j+x] = caa[i][j];
  }
}

  // impression tableau père modifiée
  for(int i=0;i<lign;i++){
  for(int j=0;j<colo;j++){
    printf("%d ",tableau[i][j]);}
  printf("\n");}
  

}

int main(){
  int tableau[lign][colo];
  int as =10;
  for(int i=0;i<lign;i++){
    for(int j=0;j<colo;j++){
      tableau[i][j]=as;
      as++;
    }
  }
  
  tourner(tableau,1,2,0,4);


}
