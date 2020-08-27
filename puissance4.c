#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#define L 6
#define C 7
enum couleur
{
    VIDE,
    JAUNE,
    ROUGE,
};

void initialisegrille(int grille [L][C]){
  int i,j;
  for (i=0;i<L;i++){
    for (j=0;j<C;j++){
      grille [i][j]=VIDE;
    }
  }
}

int coupvalide (int grille[L][C],int colonne,int couleur){
    int ligne=L-1;
    if (colonne >=C || colonne<0) return 0;
    if (grille [0][colonne]!=VIDE) return 0;
    while (ligne>=0 && grille[ligne][colonne]!=VIDE ) ligne--;
    if ( ligne>=0){
      grille[ligne][colonne]=couleur;
      return 1;
   }
   return 0;
}

int compte (int grille[L][C],int ligneD,int colonneD,int DirLigne,int DirColonne){
   int compteur=0;
   int ligne=ligneD;
   int colonne=colonneD;
   while (ligne>=0 && ligne<L && colonne>=0 && colonne<C && grille[ligne][colonne]==grille[ligneD][colonneD]){ 
     compteur ++;
     ligne=ligne+DirLigne;
     colonne=colonne+DirColonne;
   }
   return compteur;
 }
int gagne(int grille[L][C],int couleur){
   int i,j;
   for (i=0;i<L;i++){
        for (j=0;j<C;j++){
            if (grille [i][j]==couleur ){
                if(
                    ((compte(grille,i,j,-1,+1)>=4))||
                    ((compte(grille,i,j,0,+1)>=4)) ||
                    ((compte(grille,i,j,+1,0)>=4))||
                    ((compte(grille,i,j,+1,+1)>=4))
                   )

                {
                    return 1;
                }
            }
        }
   }
    return 0;
}
int max (int a, int b){
	if(a<b) return b;
	return a;
}
//ia

int calcule_nb_jetons_depuis(int grille[L][C], int couleur)
{
    
    int maxi=0;
    int i,j,k;
    for (j=0;j<C;j++){
    	i=L-1;
    	while(i>=0 && grille[i][j] !=VIDE) i--;
    	if(i>=0){
    		grille[i][j] =  couleur;
        	int m = maxi;
            maxi = max(maxi, 2*compte(grille,i,j,0,+1) +  2*compte(grille,i,j,0,-1) );
            maxi = max(maxi,2*compte(grille,i,j,+1,0) + 2*compte(grille,i,j,-1,0) );
            maxi = max(maxi,2*compte(grille,i,j,+1,+1) + 2*compte(grille,i,j,-1,-1) );
            maxi = max(maxi,2*compte(grille,i,j,-1,+1) + 2*compte(grille,i,j,1,-1) );
            grille[i][j] =  3- couleur;
            maxi = max(maxi, 2*compte(grille,i,j,0,+1) +  2*compte(grille,i,j,0,-1)-1);
            maxi = max(maxi,2*compte(grille,i,j,+1,0) + 2*compte(grille,i,j,-1,0) - 1);
            maxi = max(maxi,2*compte(grille,i,j,+1,+1) + 2*compte(grille,i,j,-1,-1) - 1);
            maxi = max(maxi,2*compte(grille,i,j,-1,+1) + 2*compte(grille,i,j,1,-1) - 1);
            if(maxi>m) k =j;
            grille[i][j]= VIDE;
        }
    }
    return k+1;
}


void affiche(int grille[L][C]){
  int i,j;
  for (i=0;i<L;i++){
  	printf("%d",i);
    for (j=0;j<C;j++){
      printf (" %c ",".XO"[grille[i][j]]);//converstion auto en entier
    }
    printf("\n");
    
  }
  printf("  1  2  3  4  5  6  7\n");
}

int main(){
  srand(time(0));
  int grille[L][C];
  int valide= 0;
  int colonne,gain=0;
  initialisegrille(grille);
  affiche(grille);
  enum  couleur couleur = JAUNE;
  int joueur, joueur1, joueur2;
  printf("Le joueur 1 est il un humain ou un ordinateur ? Entrer 0 ou 1\n");
  scanf("%d", &joueur1);
  printf("Le joueur 2 est il un humain ou un ordinateur ? Entrer 0 ou 1\n");
  scanf("%d", &joueur2);
  joueur=joueur1;
  do {
    do{
      printf("Joueur ");
      if(couleur==JAUNE) printf("X :");
      if(couleur==ROUGE) printf("O :");
      if(joueur==0){
        printf(" Entrez un numero de colonne: ");
        scanf("%d",&colonne);
      }
      if(joueur==1) {
      	colonne = calcule_nb_jetons_depuis( grille,  couleur);
	  }
      printf(" La colonne choisie est :%d\n", colonne);
      colonne--;
      valide=coupvalide(grille,colonne,couleur);
      if (!valide) printf("Le coup n'est pas valide\n");
    }while(!valide);
    affiche(grille);
    gain=gagne(grille,couleur);
    if(couleur==JAUNE){
      couleur=ROUGE;
      joueur=joueur2;
    }else{
      couleur=JAUNE;
      joueur=joueur1;
    }
    }while (!gain) ;
  if (gain ==1){
    if (couleur==JAUNE)  printf ("Le joueur gagnant est O, BRAVO!");
    if (couleur==ROUGE)  printf ("Le joueur gagnant est X, BRAVO!");
  }
  else  printf("Match null;");
  return 0;
}