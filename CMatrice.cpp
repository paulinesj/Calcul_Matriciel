#include "CMatrice.h"


CMatrice:: CMatrice() //Constructeur par défaut
{
	M_Tab = NULL;
	M_nbLigne = 0;
	M_nbColonne = 0;

}

CMatrice::~CMatrice(void)//Destructeur
{
	if (M_Tab != NULL)
	{
		for (int i = 0; i < M_nbLigne; i++)
		{
			delete[] M_Tab[i];
			delete[] M_Tab;
		}
	}
}

CMatrice::CMatrice(int Ligne, int Colonne, double valeur)//Constructeur avec paramètres
{
	M_nbLigne = Ligne;
	M_nbColonne = Colonne;
	M_Tab = new double* [M_nbLigne];
	for (int i = 0; i < M_nbLigne; i++)
	{
		M_Tab[i] = new double[M_nbColonne];

	}
	for (int i = 0; i < M_nbLigne; i++)//pour le nombre de ligne
	{
		for (int j = 0; j < M_nbLigne; j++)//pour le nombre de colonne
		{
			M_Tab[i][j] = valeur;
		}
	}
}

CMatrice::CMatrice(const CMatrice& M)//Constructeur de copie
{
	M_nbLigne = M.M_nbLigne;
	M_nbColonne = M.M_nbColonne;
	M_Tab = new double* [M_nbLigne];
	for (int i = 0; i < M_nbLigne; i++)
	{
		M_Tab[i] = new double[M_nbColonne];
	}
	for (int i = 0; i < M_nbLigne; i++)
	{
		for (int j = 0; j < M_nbColonne; j++)
		{
			M_Tab[i][j] = M.M_Tab[i][j];
		}
	}
}
ostream& operator<<(ostream& os, const CMatrice& M)//Affichage matrice
{
	os << "Affichage des donnees : " << endl;

	for (int i = 0; i < M.M_nbLigne; i++)//parcourt les lignes de la matrice
	{
		for (int j = 0; j < M.M_nbColonne; j++)//parcourt les colonnes de la matrice
		{
			os.width(11);//largeur de l'affichage
			os.fill(' ');//spécifie le caractère de remplissage
			os.setf(ios::left, ios::adjustfield);//indique que le contenu doit être aligné à gauche
			os << M.M_Tab[i][j];//affiche chaque élément de la matrice
		}

		os << endl; //apres chaque colonne écrite il va aller à la ligne
	}

	return os;
}

istream& operator>>(istream& is, const CMatrice& M)//Permet à l'utilisateur de rentrer le nombre de lignes, de colonnnes
{
	if (M.M_Tab != NULL)//vérifie si la matrice est déjà initialisée
	{
		for (int i = 0; i < M.M_nbLigne; i++)
		{
			delete[]M.M_Tab[i];//libère de la mémoire
			delete[]M.M_Tab;//libère de la mémoire
		}
	}
	cout << "Saisie des donnees de la matrice. " << endl;
	cout << "Entrer le nombre de lignes : " << endl;
	is >> M.M_nbLigne;// lit le nombre de lignes entrées par l'utilisateur et le stocke dans la variable M_nbLigne de l'objet M
	cout << "Entrer le nombre de colonnes : " << endl;
	is >> M.M_nbColonne;//lit le nombre de colonnes entréees par l'utilisateur et le stocke dans la variable M_nbColonne de l'objet M
	M.M_Tab = new double* [M.M_nbLigne];//stocker les pointeurs de chaque ligne de la matrice
	for (int i = 0; i < M.M_nbLigne; i++)
	{
		M.M_Tab[i] = new double[M.M_nbColonne];//stocker les valeurs de la colonne
	}
	M.FillRand();//appelle la fonction FillRand pour remplir la matrice avec des nombres aléatoires
	return is;
}

CMatrice CMatrice ::operator=(const CMatrice& M)
{
	if (M_Tab != NULL)
	{
		for (int i = 0; i < M_nbLigne; i++) delete[]M_Tab[i]; //on détruit le tableau pour être sûre que la matrice soit vide
		delete[]M_Tab;
	}
	//je recrée le tableau
	M_nbLigne = M.M_nbLigne;
	M_nbColonne = M.M_nbColonne;
	M_Tab = new double* [M_nbLigne];
	for (int i = 0; i < M_nbLigne; i++)
	{
		M_Tab[i] = new double[M_nbColonne];
	}
	// je copie la matrice passée en paramètre dans le tableau
	for (int i = 0; i < M_nbLigne; i++)
	{
		for (int j = 0; j < M_nbColonne; j++)
		{
			M_Tab[i][j] = M.M_Tab[i][j];
		}
	}
	return *this;
}

CMatrice CMatrice::operator+(const CMatrice& M)
{
	if (M.M_Tab != NULL)//vérifie que la matrice est non nulle
	{
		//il faut vérifier que le nombre de lignes et de colonnes des 2 matrices soient identiques = même taille !
		if (M_nbColonne == M.M_nbColonne && M_nbLigne == M.M_nbLigne)
		{
			for (int i = 0; i < M_nbLigne; i++)
			{
				for (int j = 0; j < M_nbColonne; j++)
				{
					M_Tab[i][j] += M.M_Tab[i][j]; //équivaut à M_Tab[i][j] = M_Tab[i][j] + M.M_Tab[i][j]
				}
			}
		}
	}
	return *this;
}

CMatrice CMatrice::operator-(const CMatrice& M)
{
	if (M.M_Tab != NULL)//vérifie que la matrice est non nulle
	{
	{
		//il faut vérifier que le nombre de lignes et de colonnes des 2 matrices soient identiques
		if (M_nbColonne == M.M_nbColonne && M_nbLigne == M.M_nbLigne)
		{
			for (int i = 0; i < M_nbLigne; i++)
			{
				for (int j = 0; j < M_nbColonne; j++)
				{
					M_Tab[i][j] -= M.M_Tab[i][j]; //équivaut à M_Tab[i][j] = M_Tab[i][j] - M.M_Tab[i][j]
				}
			}
		}
	}
	return *this;
}


CMatrice CMatrice::operator*(double S) // Multiplication par un scalaire
{
	CMatrice Produit(M_nbLigne, M_nbColonne, 0);//Création matrice produit

	for (int i = 0; i < M_nbLigne; i++//parcourt les lignes
	{
		for (int j = 0; j < M_nbColonne; j++)//parcourt les colonnes
		{
			Produit.M_Tab[i][j] = S * M_Tab[i][j]; // je multiplie un scalaire avec une matrice 
		}
	}

	return Produit;
}

CMatrice CMatrice ::operator*(const CMatrice& M) //Multiplication entre 2 matrices
{
	//Vérifie si le nombre de colonnes de la matrice n°1 est égal au nombre de lignes de la matrice n°2 = condition nécésaire !
	if (M_nbColonne == M.M_nbLigne)
	{
		CMatrice Produit(M_nbLigne, M.M_nbColonne, 0);
		for (int i = 0; i < M.M_nbLigne; i++)//Parcourt les lignes de la matrice
		{
			for (int j = 0; j < M.M_nbColonne; j++)//Parcourt les colonnes de la matrice
			{
				for (int k = 0; k < M.M_nbColonne; k++)//Parcourt les colonnes de la matrice courante
				{
					Produit.M_Tab[i][j] = Produit.M_Tab[i][j] + M_Tab[i][k] * M.M_Tab[k][j];
				}
			}
		}
		return Produit;
	}
	//Si les dimensions ne sont pas compatibles, affiche un message d'erreur
	else
	{
		cout << " les dimensions ne sont pas compatibles, le produit de ces 2 matrices est impossible " << endl;
	}
}
double CMatrice::Det_2x2
{
	if ((M_nbColonne == 2) && (M_nbLigne == 2))//Vérifie si c'est une matrice 2x2
	{
		return M_Tab[0][0] * M_Tab[1][1] - M_Tab[1][0] * M_Tab[0][1];//formule du Gamma (voir intro)
	}
	//Sinon, message d'erreur !
	else
	{
		cout << "La matrice n'est pas une matrice 2x2" << endl;
	}
};

double CMatrice::Signe_Cofacteur(int i, int j)
{
	return pow(-1, (i + j));
}

double CMatrice::Det()
{
	if ((M_nbColonne == M_nbLigne))//Vérifie si la matrice est carrée
	{
		if (M_nbColonne == 1)//Matrice d'ordre 1
		{
			return this->M_Tab[0][0];
		}
		else if (M_nbColonne == 2)//Matrice d'ordre 2
		{
			return this->Det_2x2();//On retrouve la fonction prédédente Det_2x2
		}
		else//Tous les autres cas, cad les matrices d'ordre > 2
		{
			double Det = 0;
			for (int i = 0; i < M_nbColonne; i++)
			{
				double cofacteur = M_Tab[0][i];//Stocke l'élément de la première ligne à la position i, qui servira de cofacteur
				double signe = Signe_Cofacteur(0, i);//Appelle une fonction pour obtenir le signe du cofacteur
				CMatrice Mineur(M_nbLigne - 1, M_nbColonne - 1, 0);//Matrice Mineur (voir ligne 311)
				for (int l = 0; l < M_nbLigne; l++)//ligne mat mineur
				{
					int c = 0;//Initialise un compteur pour les colonnes de la matrice mineur
					for (int k = 0; k < M_nbColonne; k++)//colonne mat mineur
					{
						if (k == 1)
						{
							continue;
						}
						else
						{
							Mineur.M_Tab[l - 1][c] = M_Tab[l][k];
							c++.
						}
					}
				}
				double d=Mineur.Det();
				Det=Det+cofacteur*signe*d;//Ajoute le produit du cofacteur, du signe et du déterminant de la matrice mineure au déterminant total

			}
			return Det;
		}
	}
	//Sinon, message d'erreur !
	else
	{
		cout << "La matrice ne possede pas de determinant" << endl;
	}
}

CMatrice CMatrice::Comatrice()
{
	CMatrice Comatrice(M_nbLigne, M_nbColonne, 0);//stocker la comatrice
	//Parcours de chaque élément de la matrice d'origine
	for (int i = 0; i < M.nligne; i++)
	{
		for (int j = 0; j < M_nbColonne; j++)
		{
			Comatrice.M_Tab[i][j] = Signe_Cofacteur(i, j) * Mineur(i, j).Det();
		}
	}
	return Comatrice;
}


CMatrice CMatrice::Transposee() 
{
	if (M_nbColonne == M_nbLigne)// Vérifie si c'est une matrice carrée
	{
		CMatrice Transposee(M_nbColonne, M_nbLigne, 0);
		for (int i = 0; i < M_nbLigne; i++)
		{
			for (int j = 0; j < M_nbColonne; j++)
			{
				Transposee.M_Tab[i][j] = M_Tab[j][i]; // on inverse les lignes avec les colonnes 
			}
		}
		return Transposee;
	}
	//Sinon impossible = message d'erreur
	else
	{
		cout << "la matrice n'est pas carree, la matrice transpose n'existe pas " << endl;
		return *this;
	}
}


CMatrice CMatrice::Inv(CMatrice& M)
{
	if ((M.Det() != 0) && (M.M_nbColonne == M.M_nbLigne))//Vérif si Det est différent de 0 + Matrice carrée ?! -> nb ligne = nb colonne
														//OK, la matrice est inversible (les conditions ont été vérifiées !
	{
		CMatrice temp(M.M_nbLigne, M.M_nbColonne, 0);//Création d'une matrice temporaire pour stocker l'inverse
		CMatrice Comatrice(M.M_nbLigne, M.M_nbColonne, 0);//stocker la comatrice
		CMatrice M_Comatrice(M.M_nbLigne, M.M_nbColonne, 0);//stocker la transposée
		double Inv_Det = 0;//initialise l'inverse du déterminant (utile pour la formule)
		Comatrice = M.Comatrice();
		M_Comatrice = Comatrice.Transposee();// je fais la transposée de la comatrice pour la formule finale
		Inv_Det = 1 / M.Det();// je fais 1/déterminant pour la formule finale
		temp = M_Comatrice * Inv_Det;//formule de la matrice inverse 
		return temp;
	}
	else
	{
		cout << "la matrice n'est pas inversible car son determinant est nul et non carre" << endl;
	}
}



CMatrice CMatrice::Mineur(int Ligne, int Colonne)// matrice mineur
{
	CMatrice Mineur(Ligne - 1, Colonne - 1, 0);//taille réduite de 1 par rapport à la matrice actuelle
	//Initialise les indices pour parcourir le mineur
	int i2 = 0;
	int j2 = 0;

	for (int i = 0; i < Ligne; i++)//parcourt les lignes de la matrice
	{
		if (i != Ligne)//Vérifie si l'indice de la ligne est différent de l'indice de la ligne spécifiée
		{
			for (int j = 0; j < Colonne; j++)//parcourt les colonnes de la matrice
			{
				if (j != Colonne)//Vérifie si l'indice de la colonne est différent de l'indice de la colonne spécifiée
				{
					Mineur.Tab[i2][j2] = Tab[i][j];//Copie l'élément de la matrice actuelle dans le mineur
					j2++;//incrémente l'indice de la colonne du mineur
				}
			}
			i2++;//incrémente l'indice de la ligne du mineur
			j2 = 0;//Réinitialise l'indice de la colonne du mineur
		}
	}
	return Mineur;
}


void CMatrice::FillRand() 
{
	if (M_Tab == NULL) //vérifie si la matrice est déjà initialisée
	{
		cout << "Entrer le nombre de lignes : ";
		cin >> M_nbLigne;
		cout << "Entrer le nombre de colonnes : ";
		cin >> M_nbColonne;

		M_Tab = new double* [M_nbLigne];//stocker les pointeurs de chaque ligne de la matrice
		for (int i = 0; i < M_nbLigne; i++) {
			M_Tab[i] = new double[M_nbColonne];//stocker les valeurs de la colonne
		}
	}

	// Remplir la matrice avec des nombres aléatoires
	for (int i = 0; i < M_nbLigne; i++) 
	{
		for (int j = 0; j < M_nbColonne; j++) 
		{
			M_Tab[i][j] = ((double)rand() / RAND_MAX) * 100; // Génère un nombre entre 0 et 100
		}
	}
}



void CMatrice::Lecture(const char* nom_fichier)//def fonction Lecture, qui prend en paramètre le nom du fichier à lire
{
	ifstream fichier(nom_fichier, ios::in);//Crée un objet ifstream nommé fichier pour la lecture du fichier spécifié par nom_fichier
	if (!fichier) 
	{
		cerr << "Erreur: Impossible d'ouvrir le fichier." << endl;
		return;
	}

	// Réinitialiser la matrice
	if (M_Tab != NULL) 
	{
		for (int i = 0; i < M_nbLigne; i++) 
		{
			delete[] M_Tab[i];
		}
		delete[] M_Tab;
	}

	fichier >> M_nbLigne >> M_nbColonne;

	// Allouer de la mémoire pour la nouvelle matrice
	M_Tab = new double* [M_nbLigne];
	for (int i = 0; i < M_nbLigne; i++) 
	{
		M_Tab[i] = new double[M_nbColonne];
	}

	// Remplir la matrice à partir du fichier
	for (int i = 0; i < M_nbLigne; i++) 
	{
		for (int j = 0; j < M_nbColonne; j++) 
		{
			fichier >> M_Tab[i][j];
		}
	}
	fichier.close();//ferme le fichier après la lecture
}

void CMatrice::Sauvegarde(const char* nom_fichier)//def fonction Sauvegarde, qui prend en paramètre le nom du fichier où sauvegarder la matrice
{
	ofstream fichier(nom_fichier, ios::out);//Crée un objet ofstream nommé fichier pour l'écriture dans le fichier spécifié par nom_fichier
	if (!fichier) 
	{
		cerr << "Erreur: Impossible de créer le fichier." << endl;
		return;
	}

	fichier << M_nbLigne << " " << M_nbColonne << endl;

	// Écrire les éléments de la matrice dans le fichier
	for (int i = 0; i < M_nbLigne; i++) 
	{
		for (int j = 0; j < M_nbColonne; j++)
		{
			fichier << M_Tab[i][j] << " ";
		}
		fichier << endl; // Passer à la ligne suivante après chaque ligne de la matrice
	}
	fichier.close();//ferme le fichier après la sauvegarde
}





	





