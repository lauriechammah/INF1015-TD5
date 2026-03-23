#pragma once
#include <fstream>
using namespace std;
// Entêtes copiées du main.cpp fourni (ou du fichier du TD3):

using UInt8  = uint8_t;
using UInt16 = uint16_t;

UInt8 lireUint8(istream& fichier);
UInt16 lireUint16(istream& fichier);
string lireString(istream& fichier);
