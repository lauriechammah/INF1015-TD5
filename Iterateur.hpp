#pragma once
#include "noeud.hpp"
#include "gsl/gsl_assert"
template<typename T>
class Iterateur
{
	friend class ListeLiee<T>;
public:
	//TODO: Constructeur(s).
	void avancer()
	{
		Expects(position_ != nullptr);
		//TODO: changez la position de l'itérateur pour le noeud suivant
	}
	void reculer()
	{
		//NOTE: On ne demande pas de supporter de reculer à partir de l'itérateur end().
		Expects(position_ != nullptr);
		//TODO: Changez la position de l'itérateur pour le noeud précédent
	}
	T& operator*()
	{
		return position_->donnee_;
	}
	//TODO: Ajouter ce qu'il manque pour que les boucles sur intervalles fonctionnent sur une ListeLiee.
	bool operator==(const Iterateur<T>& it) const = default;
private:
	Noeud<T>* position_;
};
