#include <stdlib.h>
#include <stdio.h>

#define TAILLEINITIALE 100

typedef struct Tableau {
	int *elt; // le tableau d�entiers
	int size; // la taille de ce tableau d�entiers
	int eltsCount; // le nombre d��l�ments dans le tableau
} TABLEAU;

TABLEAU newArray (){
	TABLEAU tab = { malloc(TAILLEINITIALE * sizeof(int)), TAILLEINITIALE, 0 }; 
	return tab; 
}

int incrementArraySize (TABLEAU* tab, int incrementValue) {
	int* temp = tab->elt; 
	int newsize; 
	newsize = tab->size + incrementValue; 
	tab->elt = (int*)realloc((tab->elt), newsize * sizeof(int)); 
	if (tab->elt == NULL) {
		return (-1); 
	}
	return newsize; 
}

int setElement(TABLEAU* tab, int pos, int element) {
	if (tab == NULL || pos <= 0) {
		return 0;
	}
	if (pos > (tab->size)) {
		int *temp; 
		temp = tab->elt;
		int newsize = (tab->size) + (pos - (tab->size)); // Ajout de l'ecart entre pos et size � taille
		tab->elt = (int*) realloc (tab->elt, newsize*sizeof(int));
		if (tab->elt== NULL) {
			tab->elt = temp;
			return 0;
		}
		for (int i = (tab->size); i < pos-1; i++) { 
			*(tab->elt +i) = 0;
		}
		*(tab->elt +pos-1) = element; // tab->elt est � la position 1 et � l'indice 0 du tableau donc pos correspond � l'indice pos-1 du tableau.
		(tab->eltsCount) += 1;
		(tab->size)= newsize;
		return pos;
	}
	*(tab->elt + pos-1) = element;
	(tab->eltsCount) += 1;
	return pos;
}

int displayElements(TABLEAU* tab, int startPos, int endPos) {
	if (tab == NULL || startPos <= 0 || endPos <= 0 || startPos > (tab->size) /*|| endPos > (tab->size)*/) {
		return (-1);
	}
	if (startPos>= endPos)
		for (int i = endPos; i <= startPos; i++) {
			printf("Element numero %d : %d", i, *(tab->elt + i-1)); 
	}

	for (int i = startPos; i <= endPos; i++) {
		printf("Element numero %d : %d", i, *(tab->elt + i-1));
	}
	return 0;
}

int deleteElements(TABLEAU* tab, int startPos, int endPos) {
	if (tab == NULL || startPos <= 0 || endPos <= 0 || startPos > (tab->size) || endPos > (tab->size)) {
		return (-1);
	}
	
	if (startPos >= endPos) { //On intervertie les valeurs de de starPos et endPos si startPos est plus grand.
		int temp = startPos; 
		startPos = endPos; 
		endPos = temp;
	}
	
	for (int i = 1 ; i< (endPos - startPos);i++){ // On recule le tableau d'une valeur �cart � partir de startPos et endPos; les positions startPos et endPos sont aussi supprim�e.
		*(tab->elt + startPos + i - 1) = *(tab->elt + endPos + i);
	}
	int newsize = tab->size - (endPos - startPos);
	tab->elt =(int*)realloc(tab->elt, newsize*sizeof(int));
	if (tab->elt == NULL) {
		return (-1);
	}
	return newsize;
}

int main() {
	TABLEAU Test = newArray();
	for (int i = 0; i < (Test.size); i++) { // initialisation des �l�ment � 0;
		*(Test.elt + i) = 0;
	}
	int position1 = setElement(&Test, 50, 45); // On remarque que 45 est affich� � la position 50
	
	if (displayElements(&Test, 30, 50) >=0) {
		printf("\n\n");
	}
	if (incrementArraySize(&Test, 50) >= 0) { // Lors du test on remarque que cette fonction n'arrive pas � modifier la taille du TABLEAU, 
		printf("\n\n");                      // cela est probablement d� au fait que Tailleinitiale est d�calr� en Macro 
	}  
	if (displayElements(&Test, 100, 150) == 0) {
		printf("\n\n");
	}
	
	setElement(&Test, 110, 145); 
	displayElements(&Test, 100, 115);

	system("PAUSE");
	return (EXIT_SUCCESS);
}

