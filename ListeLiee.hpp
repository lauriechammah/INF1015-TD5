#pragma once
#include "Iterateur.hpp"
#include "gsl/gsl_assert"
template<typename T> class Iterateur;
template<typename T>
class ListeLiee
{
	friend class Iterateur<T>;
public:
	using iterator = Iterateur<T>;  // Définit un alias au type, pour que ListeLiee<T>::iterator corresponde au type de son itérateur.

	//TODO: La construction par défaut doit créer une liste vide valide.
	ListeLiee()
	  : tete_(nullptr),
		queue_(nullptr),
		taille_(0)
	{}
	
	~ListeLiee()
	{
		//TODO: Enlever la tête à répétition jusqu'à ce qu'il ne reste aucun élément.
		// Pour enlever la tête, 
		// 1. La tête doit devenir le suivant de la tête actuelle.
		// 2. Ne pas oublier de désallouer le noeud de l'ancienne tête (si pas fait automatiquement).
		Noeud<T>* temp;
		while (tete_) {
			temp = tete_;
			tete_ = tete_->suivant_;
			delete temp; 
		}
		queue_ = nullptr;
		taille_ = 0;
	}

	bool estVide() const  { return taille_ == 0; }
	unsigned size() const { return taille_; }
	//NOTE: to_address (C++20) permet que ce même code fonctionne que vous utilisiez des pointeurs bruts ou intelligents (ça prend le pointeur brut associé au pointeur intelligent, s'il est intelligent).
	iterator begin()  { return {to_address(tete_)}; }
	iterator end()    { return {Noeud<T>::past_end}; }

	// Ajoute à la fin de la liste.
	void push_back(const T& item)
	{
		//TODO: Vous devez créer un nouveau noeud en mémoire.
		//TODO: Si la liste était vide, ce nouveau noeud est la tête et la queue;
		// autrement, ajustez la queue et pointeur(s) adjacent(s) en conséquence.
		Noeud<T>* nouveauNoeud = new Noeud<T>(item);
		if (estVide())
		{
			tete_ = nouveauNoeud;
		}
		else
		{
			queue_->suivant_ = nouveauNoeud;
			nouveauNoeud->precedent_ = queue_;
		}
		queue_ = nouveauNoeud;
		++taille_;
	}

	// Insère avant la position de l'itérateur.
	iterator insert(iterator it, const T& item)
	{
		Expects(it.position_ != Noeud<T>::past_end);
		//NOTE: Pour simplifier, vous n'avez pas à supporter l'insertion à la fin (avant "past the end"),
		// ni l'insertion au début (avant la tête), dans cette méthode.
		//TODO:
		// 1. Créez un nouveau noeud initialisé avec item.
		Noeud<T>* nouveauNoeud = new Noeud<T>(item);
		// 2. Modifiez les attributs suivant_ et precedent_ du nouveau noeud
		//    afin que le nouveau noeud soit lié au noeud précédent et suivant
		//    à l'endroit où il est inséré selon notre itérateur.
		Noeud<T>* suivant_ = it.position_;
		Noeud<T>*  precedent_ = suivant_->precedent_;
		nouveauNoeud->suivant_ = suivant_;
		nouveauNoeud->precedent_ = precedent_;
		// 3. Modifiez l'attribut precedent_ du noeud après la position d'insertion
		//    (l'itérateur) afin qu'il pointe vers le noeud créé.
		suivant_->precedent_ = nouveauNoeud;
		// 4. Modifiez l'attribut suivant_ du noeud avant la position d'insertion
		//    (précédent de l'itérateur) afin qu'il point vers le noeud créé.
		precedent_->suivant_ = nouveauNoeud;
		// 5. Incrémentez la taille de la liste.
		++taille_;
		// 6. Retournez un nouvel itérateur initialisé au nouveau noeud.
		return iterator(nouveauNoeud);
	}

	// Enlève l'élément à la position it et retourne un itérateur vers le suivant.
	iterator erase(iterator it)
	{
		//TODO: Enlever l'élément à la position de l'itérateur.
		Expects(it.position_ != Noeud<T>::past_end);

		Noeud<T>* aEffacer = it.position_;
		Noeud<T>* suivant = aEffacer->suivant_;
		Noeud<T>* precedent = aEffacer->precedent_;
		
		if (precedent != Noeud<T>::past_end) {
			precedent->suivant_ = suivant;
		} else {
			tete_ = suivant;
		}
		
		if (suivant != Noeud<T>::past_end) {
			suivant->precedent_ = precedent;
		} else {
			queue_ = precedent;
		}

		delete aEffacer;
		--taille_;
		return iterator(suivant);
		//TODO: On veut supporter d'enlever le premier élément de la liste,
		//  donc en 2. il se peut qu'il n'y ait pas de précédent et alors c'est
		//  la tête de liste qu'il faut ajuster.
		//NOTE: On ne demande pas de supporter d'effacer le dernier élément (c'est similaire au cas pour enlever le premier).
	}

private:
	gsl::owner<Noeud<T>*> tete_;  //NOTE: Vous pouvez changer le type si vous voulez.
	Noeud<T>* queue_;
	unsigned taille_;
};
