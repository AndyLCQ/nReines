#include<stdio.h>
#include<stdlib.h>

#define N 20 //Taille maximale de la matrice


typedef struct cases {
	int score [N][N]; //Indique le score de la case
	/*int dame; //booléen, indique si une dame est présente sur la case
	int conflit; //booléen, indique si une dame crée un conflit avec cette case*/
} cases;

typedef struct matrice {
	cases * cases; //Au pluriel, le mot case étant réservé par le langage
	int taille; //Indique la taille de la matrice
} matrice;


//Initialise la matrice de scores grâce à un fichier texte
matrice initialisation(FILE * instance) {
	matrice M;
	int  i, j;

	fscanf(instance, "%d", &(M.taille));
	if (M.taille < 4) {
		printf("La matrice est trop petite pour trouver une solution, veuillez utiliser une matrice de taille >= 4.\n");
		exit(EXIT_FAILURE);
	}	
	
	for (i = 0; i < M.taille; i++) 
		for (j = 0; j < M.taille; j++) {
			fscanf(instance, "%d", &(M.cases->score[i][j]));
			/*M.cases->dame = 0;
			M.cases->conflit = 0;*/
		}
	
	return M;
} //Fin initialisation

//Affiche la matrice de scores
void affiche(matrice M) {
	int i, j;
	
	for (i = 0; i < M.taille; i++) {
		for (j = 0; j < M.taille; j++)
			printf("%d ", M.cases->score[i][j]);
		printf("\n");
	}
} //Fin affiche 

//Retourne le maximum de deux entiers
int maximum(int a, int b) {

	if (a > b) return a;
	else return b;
} //Fin maximum

//Retourne la plus haute valeur d'une ligne
int maxLigne(matrice M, int i) {
	int max, j;

	max = M.cases->score[i][0];
	for (j = 0; j < M.taille-1; j++) {
		max = maximum(max, M.cases->score[i][j+1]);
	}

	return max;
} //Fin maxLigne

//Affiche le maximum de chaque ligne
void afficheMaxLigne(matrice M) {
	int i;
	
	for (i = 0; i < M.taille; i++)
		printf("Le plus haut score de la ligne %d est %d.\n", i, maxLigne(M, i));
} //Fin afficheMaxLigne

//Retourne la plus haute valeur de solution possible (sans tenir compte de la contrainte)
int maxSolution(matrice M) {
	int sol = 0, i;
	
	for (i = 0; i < M.taille; i++)
		sol += maxLigne(M, i);
		
	return sol;
} //Fin maxSolution

//Affiche le plus haut score atteignable (sans tenir compte de la contrainte)
void afficheMaxSolution(matrice M) {

	printf("Le plus haut score atteignable sans tenir compte de la contrainte est : %d.\n", maxSolution(M));
} //Fin afficheMaxSolution

int main(int argc, char **argv) {
	
	//Le nom du fichier texte n'est pas indiqué, le programme se ferme
	if (argc < 2) {
		printf("Le programme s'utilise en indiquant un nom de fichier texte : %s NOM DU FICHIER\n", argv[0]);
		return (EXIT_FAILURE);
	}
	
	matrice M;
	
	//Ouverture du fichier texte
	FILE * instance;
	char * nom_fichier = argv[1];
	instance = fopen(nom_fichier, "r");
	if (!instance) {
		printf("Erreur à l'ouverture du fichier.\n");
		exit(EXIT_FAILURE);
	}
	
	//Initialisation de la matrice de scores à partir du fichier texte
	M = initialisation(instance);

	//Affichage de la matrice de scores
	affiche(M);
	
	//Affiche la plus haute valeur de chaque ligne
	afficheMaxLigne(M);
	
	//Affichage du score maximale
	afficheMaxSolution(M);
	
	//Fermeture du fichier texte
	fclose(instance);
	
	return 0;
}
