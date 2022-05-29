#ifndef texte_H
#define texte_H

#include <windows.h>

#define REDIRECT_IF(condition, label) if(condition) goto label
#define EXIT_LABEL local_exit
#define EXIT_IF(condition) REDIRECT_IF(condition, EXIT_LABEL)

using namespace std ;

/********************* Texte fenetre principale ****************************************/

char *titre1 = "Keygen FIAT LUX";
char *titre2 = "Template XTX Keygen FIAT LUX";
char *coder = "Coder : ";
char *gfxer = "GFX : ++Meat";

/********************* Texte fenetre About *********************************************/
//Pour centrer le texte ajouter des espaces devant
char *AboutLigne1  = "Template keygen FIAT LUX";
char *AboutLigne2  = "         Codé en C/C++";
char *AboutLigne3  = "       Kirjo - Team XTX";
char *AboutLigne4  = "";
char *AboutLigne5  = "             Greetz to :";
char *AboutLigne6  = "              ++Meat";
char *AboutLigne7  = "           Aux membres";
char *AboutLigne8  = "          de la team XTX";
char *AboutLigne9  = "           Aux membres";
char *AboutLigne10 = "           du forum XTX";

/********************* Texte fenetre Warning1 ******************************************/
//Pour centrer le texte ajouter des espaces devant
char *Warning1Ligne1  = "";
char *Warning1Ligne2  = "          ATTENTION !";
char *Warning1Ligne3  = "";
char *Warning1Ligne4  = "";
char *Warning1Ligne5  = "";
char *Warning1Ligne6  = "";
char *Warning1Ligne7  = "";
char *Warning1Ligne8  = "";
char *Warning1Ligne9  = "";
char *Warning1Ligne10 = "";

/********************* Texte fenetre Warning2 ******************************************/
//Pour centrer le texte ajouter des espaces devant
char *Warning2Ligne1  = "";
char *Warning2Ligne2  = "          ATTENTION !";
char *Warning2Ligne3  = "";
char *Warning2Ligne4  = "";
char *Warning2Ligne5  = "";
char *Warning2Ligne6  = "";
char *Warning2Ligne7  = "";
char *Warning2Ligne8  = "";
char *Warning2Ligne9  = "";
char *Warning2Ligne10 = "";

/********************* Texte fenetre Warning3 ******************************************/
//Pour centrer le texte ajouter des espaces devant
char *Warning3Ligne1  = "";
char *Warning3Ligne2  = "          ATTENTION !";
char *Warning3Ligne3  = "";
char *Warning3Ligne4  = "";
char *Warning3Ligne5  = "";
char *Warning3Ligne6  = "";
char *Warning3Ligne7  = "";
char *Warning3Ligne8  = "";
char *Warning3Ligne9  = "";
char *Warning3Ligne10 = "";

#endif
