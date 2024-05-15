#include "CMatrice.h"


CMatrice:: CMatrice() //Constructeur par d�faut
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

CMatrice::CMatrice(int Ligne, int Colonne, double valeur)//Constructeur avec param�tres
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
			os.fill(' ');//sp�cifie le caract�re de remplissage
			os.setf(ios::left, ios::adjustfield);//indique que le contenu doit �tre align� � gauche
			os << M.M_Tab[i][j];//affiche chaque �l�ment de la matrice
		}

		os << endl; //apres chaque colonne �crite il va aller � la ligne
	}

	return os;
}

istream& operator>>(istream& is, const CMatrice& M)//Permet � l'utilisateur de rentrer le nombre de lignes, de colonnnes
{
	if (M.M_Tab != NULL)//v�rifie si la matrice est d�j� initialis�e
	{
		for (int i = 0; i < M.M_nbLigne; i++)
		{
			delete[]M.M_Tab[i];//lib�re de la m�moire
			delete[]M.M_Tab;//lib�re de la m�moire
		}
	}
	cout << "Saisie des donnees de la matrice. " << endl;
	cout << "Entrer le nombre de lignes : " << endl;
	is >> M.M_nbLigne;// lit le nombre de lignes entr�es par l'utilisateur et le stocke dans la variable M_nbLigne de l'objet M
	cout << "Entrer le nombre de colonnes : " << endl;
	is >> M.M_nbColonne;//lit le nombre de colonnes entr�ees par l'utilisateur et le stocke dans la variable M_nbColonne de l'objet M
	M.M_Tab = new double* [M.M_nbLigne];//stocker les pointeurs de chaque ligne de la matrice
	for (int i = 0; i < M.M_nbLigne; i++)
	{
		M.M_Tab[i] = new double[M.M_nbColonne];//stocker les valeurs de la colonne
	}
	M.FillRand();//appelle la fonction FillRand pour remplir la matrice avec des nombres al�atoires
	return is;
}

CMatrice CMatrice ::operator=(const CMatrice& M)
{
	if (M_Tab != NULL)
	{
		for (int i = 0; i < M_nbLigne; i++) delete[]M_Tab[i]; //on d�truit le tableau pour �tre s�re que la matrice soit vide
		delete[]M_Tab;
	}
	//je recr�e le tableau
	M_nbLigne = M.M_nbLigne;
	M_nbColonne = M.M_nbColonne;
	M_Tab = new double* [M_nbLigne];
	for (int i = 0; i < M_nbLigne; i++)
	{
		M_Tab[i] = new double[M_nbColonne];
	}
	// je copie la matrice pass�e en param�tre dans le tableau
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
	if (M.M_Tab != NULL)//v�rifie que la matrice est non nulle
	{
		//il faut v�rifier que le nombre de lignes et de colonnes des 2 matrices soient identiques = m�me taille !
		if (M_nbColonne == M.M_nbColonne && M_nbLigne == M.M_nbLigne)
		{
			for (int i = 0; i < M_nbLigne; i++)
			{
				for (int j = 0; j < M_nbColonne; j++)
				{
					M_Tab[i][j] += M.M_Tab[i][j]; //�quivaut � M_Tab[i][j] = M_Tab[i][j] + M.M_Tab[i][j]
				}
			}
		}
	}
	return *this;
}

CMatrice CMatrice::operator-(const CMatrice& M)
{
	if (M.M_Tab != NULL)//v�rifie que la matrice est non nulle
	{
	{
		//il faut v�rifier que le nombre de lignes et de colonnes des 2 matrices soient identiques
		if (M_nbColonne == M.M_nbColonne && M_nbLigne == M.M_nbLigne)
		{
			for (int i = 0; i < M_nbLigne; i++)
			{
				for (int j = 0; j < M_nbColonne; j++)
				{
					M_Tab[i][j] -= M.M_Tab[i][j]; //�quivaut � M_Tab[i][j] = M_Tab[i][j] - M.M_Tab[i][j]
				}
			}
		}
	}
	return *this;
}


CMatrice CMatrice::operator*(double S) // Multiplication par un scalaire
{
	CMatrice Produit(M_nbLigne, M_nbColonne, 0);//Cr�ation matrice produit

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
	//V�rifie si le nombre de colonnes de la matrice n�1 est �gal au nombre de lignes de la matrice n�2 = condition n�c�saire !
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
	if ((M_nbColonne == 2) && (M_nbLigne == 2))//V�rifie si c'est une matrice 2x2
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
	if ((M_nbColonne == M_nbLigne))//V�rifie si la matrice est carr�e
	{
		if (M_nbColonne == 1)//Matrice d'ordre 1
		{
			return this->M_Tab[0][0];
		}
		else if (M_nbColonne == 2)//Matrice d'ordre 2
		{
			return this->Det_2x2();//On retrouve la fonction pr�d�dente Det_2x2
		}
		else//Tous les autres cas, cad les matrices d'ordre > 2
		{
			double Det = 0;
			for (int i = 0; i < M_nbColonne; i++)
			{
				double cofacteur = M_Tab[0][i];//Stocke l'�l�ment de la premi�re ligne � la position i, qui servira de cofacteur
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
				Det=Det+cofacteur*signe*d;//Ajoute le produit du cofacteur, du signe et du d�terminant de la matrice mineure au d�terminant total

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
	//Parcours de chaque �l�ment de la matrice d'origine
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
	if (M_nbColonne == M_nbLigne)// V�rifie si c'est une matrice carr�e
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
	if ((M.Det() != 0) && (M.M_nbColonne == M.M_nbLigne))//V�rif si Det est diff�rent de 0 + Matrice carr�e ?! -> nb ligne = nb colonne
														//OK, la matrice est inversible (les conditions ont �t� v�rifi�es !
	{
		CMatrice temp(M.M_nbLigne, M.M_nbColonne, 0);//Cr�ation d'une matrice temporaire pour stocker l'inverse
		CMatrice Comatrice(M.M_nbLigne, M.M_nbColonne, 0);//stocker la comatrice
		CMatrice M_Comatrice(M.M_nbLigne, M.M_nbColonne, 0);//stocker la transpos�e
		double Inv_Det = 0;//initialise l'inverse du d�terminant (utile pour la formule)
		Comatrice = M.Comatrice();
		M_Comatrice = Comatrice.Transposee();// je fais la transpos�e de la comatrice pour la formule finale
		Inv_Det = 1 / M.Det();// je fais 1/d�terminant pour la formule finale
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
	CMatrice Mineur(Ligne - 1, Colonne - 1, 0);//taille r�duite de 1 par rapport � la matrice actuelle
	//Initialise les indices pour parcourir le mineur
	int i2 = 0;
	int j2 = 0;

	for (int i = 0; i < Ligne; i++)//parcourt les lignes de la matrice
	{
		if (i != Ligne)//V�rifie si l'indice de la ligne est diff�rent de l'indice de la ligne sp�cifi�e
		{
			for (int j = 0; j < Colonne; j++)//parcourt les colonnes de la matrice
			{
				if (j != Colonne)//V�rifie si l'indice de la colonne est diff�rent de l'indice de la colonne sp�cifi�e
				{
					Mineur.Tab[i2][j2] = Tab[i][j];//Copie l'�l�ment de la matrice actuelle dans le mineur
					j2++;//incr�mente l'indice de la colonne du mineur
				}
			}
			i2++;//incr�mente l'indice de la ligne du mineur
			j2 = 0;//R�initialise l'indice de la colonne du mineur
		}
	}
	return Mineur;
}


void CMatrice::FillRand() 
{
	if (M_Tab == NULL) //v�rifie si la matrice est d�j� initialis�e
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

	// Remplir la matrice avec des nombres al�atoires
	for (int i = 0; i < M_nbLigne; i++) 
	{
		for (int j = 0; j < M_nbColonne; j++) 
		{
			M_Tab[i][j] = ((double)rand() / RAND_MAX) * 100; // G�n�re un nombre entre 0 et 100
		}
	}
}



void CMatrice::Lecture(const char* nom_fichier)//def fonction Lecture, qui prend en param�tre le nom du fichier � lire
{
	ifstream fichier(nom_fichier, ios::in);//Cr�e un objet ifstream nomm� fichier pour la lecture du fichier sp�cifi� par nom_fichier
	if (!fichier) 
	{
		cerr << "Erreur: Impossible d'ouvrir le fichier." << endl;
		return;
	}

	// R�initialiser la matrice
	if (M_Tab != NULL) 
	{
		for (int i = 0; i < M_nbLigne; i++) 
		{
			delete[] M_Tab[i];
		}
		delete[] M_Tab;
	}

	fichier >> M_nbLigne >> M_nbColonne;

	// Allouer de la m�moire pour la nouvelle matrice
	M_Tab = new double* [M_nbLigne];
	for (int i = 0; i < M_nbLigne; i++) 
	{
		M_Tab[i] = new double[M_nbColonne];
	}

	// Remplir la matrice � partir du fichier
	for (int i = 0; i < M_nbLigne; i++) 
	{
		for (int j = 0; j < M_nbColonne; j++) 
		{
			fichier >> M_Tab[i][j];
		}
	}
	fichier.close();//ferme le fichier apr�s la lecture
}

void CMatrice::Sauvegarde(const char* nom_fichier)//def fonction Sauvegarde, qui prend en param�tre le nom du fichier o� sauvegarder la matrice
{
	ofstream fichier(nom_fichier, ios::out);//Cr�e un objet ofstream nomm� fichier pour l'�criture dans le fichier sp�cifi� par nom_fichier
	if (!fichier) 
	{
		cerr << "Erreur: Impossible de cr�er le fichier." << endl;
		return;
	}

	fichier << M_nbLigne << " " << M_nbColonne << endl;

	// �crire les �l�ments de la matrice dans le fichier
	for (int i = 0; i < M_nbLigne; i++) 
	{
		for (int j = 0; j < M_nbColonne; j++)
		{
			fichier << M_Tab[i][j] << " ";
		}
		fichier << endl; // Passer � la ligne suivante apr�s chaque ligne de la matrice
	}
	fichier.close();//ferme le fichier apr�s la sauvegarde
}





	





