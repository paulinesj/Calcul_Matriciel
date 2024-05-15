#pragma once
#include<iostream>
#include<ctime>
#include<fstream>
using namespace std;
class CMatrice
{
private: //Dans le private, je créer mes variables

	double** M_Tab;//Un double car tableau 2D
	int M_nbLigne;// Un int car c'est un entier -> nombre de lignes
	int M_nbColonne; //Un int car c'est un entier -> nombre de colonnes

public:
	CMatrice();//Constructeur par défaut
	~CMatrice();//Destructeur
	CMatrice(int Ligne, int Colonne, double valeur);//constructeur avec paramètres permettant 
													//d'initialiser l'ensemble des données membres
	CMatrice(const CMatrice& M);//Constructeur de copie

	CMatrice FillRand(); //fonction qui remplit la matrice avec des valeurs aléatoires



	friend ostream& operator<<(ostream& os, const CMatrice& M);// Permet l'écriture sur la console
	friend istream& operator>>(istream& is, const CMatrice& M);//Permet de saisir sur la console
	friend ofstream& operator<<(ofstream& fichier, const CMatrice& M);//Permet d'écrire dans un fichier
	friend ifstream& operator>>(ifstream& fichier, const CMatrice& M);//Permet de saisir dans un fichier 

	void Sauvegarde(const char* nom);//fonction qui rend possible la sauvegarde de matrice dans un fichier
	void Lecture(const char* nom);//fonction qui rend possible la lecture de matrice dans un fichier

	CMatrice operator=(const CMatrice& M);//Permet l'affectation entre 2 matrices dans un fichier
	CMatrice operator+(const CMatrice& M);//Surcharge permettant l'addition de 2 matrices
	CMatrice operator-(const CMatrice& M);//Surcharge permettant la soustraction de 2 matrices
	CMatrice operator*(const CMatrice& M);//Surcharge permettant la multiplication de 2 matrices
	CMatrice operator*(double S);//Surcharge permettant la multiplication d'1 matrice avec un scalaire


	double Det_2x2();//Calcul du déterminant d'une matrice 2x2
	double Det();//Calcul du déterminant d'1 matrice
	double Signe_Cofacteur(int i, int j);//Calcul du signe du cofacteur (notations : i=ligne et j=colonne)

	CMatrice Transposee();//fonction qui rend possible la transposition d'une matrice
	CMatrice Comatrice();//fonction qui trouve la comatrice d'une matrice
	CMatrice Inv();//fonction qui trouve l'inverse d'une matrice
	CMatrice Mineur(int Ligne, int Colonne);

};

