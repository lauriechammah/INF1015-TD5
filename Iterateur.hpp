/**
 * Creation, definition et implementation de la classe Iterateur
 * \file   Iterateur.hpp
 * \author CHAMMAH (2451396) et SARKIS (2461138)
 * \date   1 avril 2026
 * Modifie le 24 mars 2026
 */

#pragma once
#include "Noeud.hpp"
#include "gsl/gsl_assert"

template<typename T>
class Iterateur
{
	friend class ListeLiee<T>;
public:
	// TODO: Constructeur
	Iterateur(Noeud<T>* position = Noeud<T>::past_end) : position_(position) {}

	void avancer()
	{
		Expects(position_ != nullptr);
		//TODO: changez la position de l'itérateur pour le noeud suivant
		position_ = position_->suivant_;
	}
	void reculer()
	{
		//NOTE: On ne demande pas de supporter de reculer à partir de l'itérateur end().
		Expects(position_ != nullptr);
		//TODO: Changez la position de l'itérateur pour le noeud précédent
		position_ = position_->precedent_;
	}
	T& operator*()
	{
		Expects(position_ != Noeud<T>::past_end);
		return position_->donnee_;
	}
	//TODO: Ajouter ce qu'il manque pour que les boucles sur intervalles fonctionnent sur une ListeLiee.
	Iterateur& operator++()
	{
		avancer();
		return *this;
	}
	Iterateur& operator--()
	{
		reculer();
		return *this;
	}

	bool operator==(const Iterateur<T>& it) const
	{
		return position_ == it.position_;
	}

	bool operator!=(const Iterateur<T>& it) const
	{
		return position_ != it.position_;
	}



private:
	Noeud<T>* position_;
};
