/**
 * Creation et definition de la classe Noeud
 * \file   Noeud.hpp
 * \author CHAMMAH (2451396) et SARKIS (2461138)
 * \date   1 avril 2026
 * Modifie le 24 mars 2026
 */

#pragma once
#include <gsl/pointers>
template<typename T> class ListeLiee;
template<typename T> class Iterateur;

template<typename T>
class Noeud
{
	friend class ListeLiee<T>;
	friend class Iterateur<T>;
public:
	//TODO: Constructeur(s).
	Noeud(const T& donnee) : donnee_(donnee) {}

private:
	//TODO: Attributs d'un noeud.
	Noeud* suivant_ = past_end;
	Noeud* precedent_ = past_end;
	T donnee_;

	inline static Noeud* past_end = nullptr;
};
