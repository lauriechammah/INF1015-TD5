#include "Personnage.hpp"
#include "Heros.hpp"
#include "Vilain.hpp"
#include "VilainHeros.hpp"
#include "ListeLiee.hpp"
#include <fstream>
#include <vector>
#include <functional>
#include "cppitertools/range.hpp"
#include "bibliotheque_cours.hpp"
#include <set>
using namespace std;
using namespace iter;

using UInt8  = uint8_t;
using UInt16 = uint16_t;

UInt8 lireUint8(istream& fichier)
{
	UInt8 valeur = 0;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}

UInt16 lireUint16(istream& fichier)
{
	UInt16 valeur = 0;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}

string lireString(istream& fichier)
{
	string texte;
	texte.resize(lireUint16(fichier));
	fichier.read(reinterpret_cast<char*>(&texte[0]), streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}

template <typename T>
vector<T> lireFichier(istream& fichier)
{
	vector<T> elements;
	for ([[maybe_unused]] int i : range(lireUint16(fichier)))
		elements.push_back(T(fichier));
	return elements;
}

ifstream ouvrirLectureFichierBinaire(const string& nomFichier)
{
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);
	return fichier;
}

// Permet d'avoir une référence non-const à un objet temporaire.
template <typename T> T& temporaireModifiable(T&& objet) { return objet; }

template <typename T>
vector<T> lireFichier(const string& nomFichier)
{
	return lireFichier<T>(temporaireModifiable(
		ouvrirLectureFichierBinaire(nomFichier)));
}

template <typename T>
Iterateur<T> trouverParNom(ListeLiee<T>& liste, const string& nom)
{
	Iterateur<T> fin = liste.end();
	for (Iterateur<T> pos = liste.begin(); pos != fin; pos.avancer()) {
		if ((*pos).getNom() == nom)
			return pos;
	}
	return fin;
}

int main()
{
	#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi();
	#pragma endregion
	
	// Trait de separation
	static const string trait =
		"═════════════════════════════════════════════════════════════════════════";

	static const string separateurSections = "\033[95m" + trait + "\033[0m\n";
	static const string separateurElements = "\033[33m" + trait + "\033[0m\n";

	//{ Solutionnaire du TD4:
	vector<Heros> heros = lireFichier<Heros>("heros.bin");
	vector<Vilain> vilains = lireFichier<Vilain>("vilains.bin");
	vector<unique_ptr<Personnage>> peronnages;  // Doit être des pointeurs pour le polymorphisme, l'énoncé ne force pas les unique_ptr.

	#if 1 //TODO: Vous n'avez pas à conserver ces affichages pour le TD5, ils sont pour le solutionnaire du TD4:
	cout << separateurSections << "Heros:" << endl;
	for (auto& h : heros) {
		cout << separateurElements;
		h.changerCouleur(cout, 0);
		h.afficher(cout);
	}

	cout << separateurSections << "Vilains:" << endl;
	for (auto& v : vilains) {
		cout << separateurElements;
		v.changerCouleur(cout, 0);
		v.afficher(cout);
	}

	for (auto& h : heros)
		peronnages.push_back(make_unique<Heros>(h));

	for (auto& v : vilains)
		peronnages.push_back(make_unique<Vilain>(v));

	peronnages.push_back(make_unique<VilainHeros>(vilains[1], heros[2]));

	cout << separateurSections << "Personnages:" << endl;
	for (auto& p : peronnages) {
		cout << separateurElements;
		p->changerCouleur(cout, 0);
		p->afficher(cout);
	}
	cout << separateurSections << "Un autre vilain heros (exemple de l'énoncé du TD):" << endl;
	VilainHeros kefkaCrono(vilains[2], heros[0]);
	kefkaCrono.changerCouleur(cout,1);
	kefkaCrono.afficher(cout);
	#endif
	//}

	//TODO: Transférez les héros du vecteur heros dans une ListeLiee.
	ListeLiee<Heros> listeLieeHeros;
	for (auto& h : heros)
	{
		listeLieeHeros.push_back(h);
	}


	//TODO: Créez un itérateur sur la liste liée à la position du héros Alucard
	// Servez-vous de la fonction trouverParNom définie plus haut
	Iterateur<Heros> alucard = trouverParNom(listeLieeHeros, "Alucard");
	if (alucard != listeLieeHeros.end())
	{
		cout << "Alucard trouve: ";
		(*alucard).afficher(cout);
		cout << "\n";
	}
	else
	{
		cout << "Alucard introuvable\n";
	}

	//TODO: Servez-vous de l'itérateur créé précédemment pour trouver l'héroine Aya Brea,
	// en sachant qu'elle se trouve plus loin dans la liste.
	Iterateur<Heros> aya = listeLieeHeros.end();

	for (Iterateur<Heros> it = alucard; it != listeLieeHeros.end(); ++it)
	{
		if ((*it).getNom() == "Aya Brea")
		{
			aya = it;
			cout << "Aya Brea trouvee!\n" << endl;
			break;
		}
	}

	//TODO: Ajouter un hero bidon à la liste avant Aya Brea en vous servant de l'itérateur.
	//TODO: Assurez-vous que la taille de la liste est correcte après l'ajout.
	if (aya != listeLieeHeros.end())
	{
		Heros herosBidon("Laruie", "John Pork Saga 67", "Mayonnaise-Josai");
		herosBidon.ajouterAllie("Fartiya Samprout");
		herosBidon.ajouterAllie("Florineige");
		herosBidon.ajouterAllie("Yassine Parfum");
		herosBidon.ajouterAllie("Gloria");
		cout << "Taille de la liste avant ajout du heros bidon: " << listeLieeHeros.size() << endl;
		listeLieeHeros.insert(aya, herosBidon);
		cout << "Taille de la liste apres l'ajout du heros bidon: " << listeLieeHeros.size() << endl;
	}
	else
	{
		cout << "Aya Brea introuvable, insertion annulee.\n";
	}
	

	//TODO: Reculez votre itérateur jusqu'au héros Mario et effacez-le en utilisant l'itérateur, puis affichez le héros suivant dans la liste (devrait êter "Naked Snake/John").
	//TODO: Assurez-vous que la taille de la liste est correcte après le retrait.
	Iterateur<Heros> suivantMario = listeLieeHeros.end();
	bool marioTrouve = false;

	for (Iterateur<Heros> it = aya; it != listeLieeHeros.end(); --it)
	{
		if ((*it).getNom() == "Mario")
		{
			marioTrouve = true;
			cout << "Taille de la liste avant retrait Mario: " << listeLieeHeros.size() << endl;
			listeLieeHeros.erase(it);
			cout << "Taille de la liste apres retrait Mario: " << listeLieeHeros.size() << endl;
			break;
		}
	}
	
	if (!marioTrouve)
	{
		cout << "Mario introuvable\n";
	}
	else if (suivantMario != listeLieeHeros.end())
	{
		(*suivantMario).afficher(cout);
		cout << "\n";
	}
	else
	{
		cout << "Mario etait le dernier element.\n";
	}

	//TODO: Effacez le premier élément de la liste.
	Iterateur<Heros> premierElement = listeLieeHeros.begin();
	if (premierElement != listeLieeHeros.end())
	{
		listeLieeHeros.erase(premierElement);		
	}

	//TODO: Affichez votre liste de héros en utilisant un itérateur. La liste débute
	// avec le héros Randi et n'a pas Mario.
	// Servez-vous des methodes begin et end de la liste...

	for (Iterateur<Heros> it = listeLieeHeros.begin(); it != listeLieeHeros.end(); ++it)
	{
		(*it).afficher(cout);
		cout << "\n";
	}

	//TODO: Refaite le même affichage mais en utilisant une simple boucle "for" sur intervalle.
	for (Heros& h : listeLieeHeros)
	{
		h.afficher(cout);
		cout << "\n";
	}
	
	//TODO: Utilisez un conteneur pour avoir les héros en ordre alphabétique (voir point 2 de l'énoncé).
	
	//2.1

	cout << "═════════════════════════════════════════════════════════════════════════\n";
	cout << "Liste en ordre alphabetique\n" << "═════════════════════════════════════════════════════════════════════════\n";
	multiset<Heros> listeAlphaHeros;
	for (const Heros& heroAPlacer : listeLieeHeros) 
	{
		listeAlphaHeros.insert(heroAPlacer);
	}

	for (const auto& heroAPlacer : listeAlphaHeros)
	{
		heroAPlacer.afficher(cout);
		cout << "\n";
	}
	cout << "═════════════════════════════════════════════════════════════════════════\n";
	

	//2.2
	bool herosTrouve = false;
	for (const Heros& hAlpha : listeAlphaHeros)
	{
		if (hAlpha.getNom() == "Laruie")
		{
			hAlpha.afficher(cout);
			cout << "\n";
			herosTrouve = true;
			break;
		}
	}
	if (!herosTrouve)
		cout << "Hero recherche introuvable.\n";

	//TODO: Assurez-vous de n'avoir aucune ligne non couverte dans les classes pour la liste liée.  Il peut y avoir des lignes non couvertes dans les personnages...
}


