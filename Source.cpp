#include"CMatrice.h"

int main()
{
	CMatrice M1;
	CMatrice M2;
	CMatrice M3;
	int S;
	const char* fichier = "Essai.txt";
	int choix;

	cout << " 1 : addition de deux matrices" << endl;
	cout << " 2 : soustraction de deux matrices" << endl;
	cout << " 3 : multiplication d une matrice avec un scalaire" << endl;
	cout << " 4 : multiplication de 2 matrices" << endl;
	cout << " 5 : matrice transposee" << endl;
	cout << " 6 : calcul du determinant d une matrice" << endl;
	cout << " 7 : calcul de la matrice inverse" << endl;
	cout << " 8 : test d'ecriture dans un fichier" << endl;
	cout << " 9 : test de lecture dans un fichier" << endl;
	cin >> choix;

	switch (choix)
	{
	case 1:
		cout << " Operation + " << endl;
		cout << "Saisissez le nombre de ligne et de colonne de votre 1er matrice" << endl;
		M1.FillRand();
		cout << M1 << endl;
		cout << "Saisissez le nombre de ligne et de colonne de votre 2eme matrice" << endl;
		M2.FillRand();
		cout << M2 << endl;
		cout << "le resultat de M1+M2 est :" << endl;
		M3 = M1 + M2;
		cout << M3 << endl;
		break;
	case 2:
		cout << " Operation - " << endl;
		cout << "Saisissez le nombre de ligne et de colonne de votre 1er matrice" << endl;
		M1.FillRand();
		cout << M1 << endl;
		cout << "Saisir le nombre de ligne et de colonne de la matrice 2" << endl;
		M2.FillRand();
		cout << M2 << endl;
		cout << "le resultat de M1-M2 est :" << endl;
		M3 = M1 - M2;
		cout << M3 << endl;
		break;

	case 3:
		cout << "Operation * d'un scalaire et d'une matrice " << endl;
		cout << "Saisissez le nombre de ligne et de colonne de votre 1er matrice" << endl;
		M1.FillRand();
		cout << M1 << endl;
		cout << "Saisir la valeur du scalaire " << endl;
		cin >> scalaire;
		cout << "le resultat de M1*" << scalaire << " est :" << endl;
		M3 = M1 * scalaire;
		cout << M3 << endl;
		break;
	case 4:
		cout << "Operation * de 2 matrices " << endl;
		cout << "Saisissez le nombre de ligne et de colonne de votre 1er matrice" << endl;
		M1.FillRand();
		cout << M1 << endl;
		cout << "Saisissez le nombre de ligne et de colonne de votre 2eme matrice" << endl;
		M2.FillRand();
		cout << M2 << endl;
		cout << "le resultat de M1*M2 est :" << endl;
		M3 = M1 * M2;
		cout << M3 << endl;
		break;
	case 5:
		cout << "Calcul de la transposee " << endl;
		cout << "Saisissez le nombre de ligne et de colonne de votre matrice" << endl;
		M1.FillRand();
		cout << M1 << endl;
		cout << "le resultat de la matrice transposee est :" << endl;
		M3 = M1.Transposee();
		cout << M3 << endl;
		break;
	case 6:
		cout << "Calcul du determinant d une matrice" << endl;
		cout << "Saisissez le nombre de ligne et de colonne de votre matrice" << endl;
		M1.FillRand();
		cout << M1 << endl;
		cout << "le resultat du determinant de la matrice est :" << endl;
		cout << M1.Det() << endl;
		break;
	case 7:
		cout << "Calcul de la matrice inverse " << endl;
		cout << "Saisir le nombre de ligne et de colonne de la matrice" << endl;
		M1.FillRand();
		cout << M1 << endl;
		cout << "le resultat de la matrice inverse est :" << endl;
		M3 = M1.Inv(M1);
		cout << M3 << endl;
		break;
	case 8:
		M1.Sauvegarde(fichier);
		break;
	case 9:
		M1.Lecture(fichier);
		cout << M1;
		break;

	default:
		cout << " erreur";
	}
	return 0;
}

