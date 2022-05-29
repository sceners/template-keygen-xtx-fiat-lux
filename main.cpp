#include <windows.h>
#include <string>
#include<sstream>
#include "texte.h"

using namespace std ;

/******************** Declaration des variables de fenetres ****************************/
HINSTANCE hinst;
HWND hwnd, Warning;
WNDCLASS wc, wc2;
MSG msg;
HWND hEdit[2];
HWND hBtn[4];
int TypeMsgBox;

/******************** Declaration des couleurs *****************************************/
COLORREF blanc = RGB(255,255,255);
const HBRUSH noir = CreateSolidBrush(RGB(0,0,0));

/******************** Declaration des fonctions ****************************************/
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MainWndProc2(HWND Warning, UINT uMsg2, WPARAM wParam2, LPARAM lParam2);
void AfficherTexte (HWND fenetre, HDC dc, char *chaine, int Xleft, int Ytop, int taille,
                    BOOL italique);
int Copier(const char *text);
const char* GenerateSerial (string strNom) ;

/********************** WinMain ********************************************************/
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{

hinst = hinstance;

/********************** Creation fenetre principale */
wc.style = 0;
wc.lpfnWndProc = MainWndProc;
wc.cbClsExtra = 0;
wc.cbWndExtra = 0;
wc.hInstance = hinstance;
wc.hIcon = LoadIcon(NULL, "Icone");
wc.hCursor = LoadCursor(NULL, IDC_ARROW);
wc.hbrBackground = (HBRUSH)(1 + COLOR_BTNFACE);
wc.lpszMenuName = NULL;
wc.lpszClassName = "MaClasse";

if (!RegisterClass(&wc)) return FALSE;

//Recupère la taille du bureau
HWND hwndScreen = GetDesktopWindow();
RECT rcScreen ;
GetWindowRect(hwndScreen,&rcScreen) ;
int cxScreen = rcScreen.right ;
int cyScreen = rcScreen.bottom ;

//Création de la fenêtre
hwnd = CreateWindow("MaClasse",
                    titre1,
                    WS_POPUPWINDOW,
                    (cxScreen - 480)/2,
                    (cyScreen - 270)/2,
                    480,
                    270,
                    NULL,
                    NULL,
                    hinstance,
                    NULL);

if (!hwnd) return FALSE;

/********************** Creation fenetre About/Warning */
wc2.style = 0;
wc2.lpfnWndProc = MainWndProc2;
wc2.cbClsExtra = 0;
wc2.cbWndExtra = 0;
wc2.hInstance = hinstance;
wc2.hIcon = LoadIcon(NULL, "Icone");
wc2.hCursor = LoadCursor(NULL, IDC_ARROW);
wc2.hbrBackground = (HBRUSH)(1 + COLOR_BTNFACE);
wc2.lpszMenuName = NULL;
wc2.lpszClassName = "MaClasse2";

if (!RegisterClass(&wc2)) return FALSE;

const char* title;
if (TypeMsgBox == 0)
{
    title = "About";
}
else
{
    title = "Warning";
}

//Recupère la taille du bureau
hwndScreen = GetDesktopWindow();
GetWindowRect(hwndScreen,&rcScreen) ;

//Création de la fenêtre
Warning = CreateWindow("MaClasse2",
                     title,
                     WS_POPUPWINDOW,
                     (cxScreen - 148)/2,
                     (cyScreen - 270)/2,
                     148,
                     270,
                     NULL,
                     NULL,
                     hinstance,
                     NULL);

if (!Warning) return FALSE;

//Affiche la fenêtre principale
ShowWindow(hwnd, nCmdShow);
UpdateWindow(hwnd);

while (GetMessage(&msg, NULL, 0, 0))
{
    TranslateMessage(&msg);
    DispatchMessage(&msg);
}
return msg.wParam;
}
/********************** Procedure fenetre principale ***********************************/
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HFONT hFont;
    static LOGFONT lf;
    static RECT rc;
    static POINT lp;
    static int dx = 0,dy = 0;
    switch (uMsg)
    {
        case WM_CREATE:
            //Nom
            hEdit[0]=CreateWindow("EDIT",
                            "",
                            WS_VISIBLE|WS_CHILD|ES_CENTER | ES_NUMBER,
                            37,189,294,24,
                            hwnd,NULL,hinst,NULL);
            //Serial
            hEdit[1]=CreateWindow("STATIC",
                            "",
                            WS_CHILD | WS_VISIBLE |ES_CENTER | SS_NOPREFIX,
                            37,232,294,27,
                            hwnd,NULL,hinst,NULL);
            //Fermer
            hBtn[0]=CreateWindow("STATIC",
                           "",
                           WS_CHILD|WS_VISIBLE|SS_BITMAP,
                           432,198, 0,0,
                           hwnd,NULL,hinst,NULL);
            //Generer
            hBtn[1]=CreateWindow("STATIC",
                           "",
                           WS_CHILD|WS_VISIBLE|SS_BITMAP,
                           394,187, 0,0,
                           hwnd,NULL,hinst,NULL);
            //About
            hBtn[2]=CreateWindow("STATIC",
                           "",
                           WS_CHILD|WS_VISIBLE|SS_BITMAP,
                           400,222, 0,0,
                           hwnd,NULL,hinst,NULL);
            //Copy
            hBtn[3]=CreateWindow("STATIC",
                           "",
                           WS_CHILD|WS_VISIBLE|SS_BITMAP,
                           398,237, 0,0,
                           hwnd,NULL,hinst,NULL);

            ZeroMemory(&lf, sizeof(LOGFONT));
            lstrcpy(lf.lfFaceName,"Times New Roman");
            lf.lfHeight = 15;
            lf.lfWeight = FW_BOLD;
            hFont = CreateFontIndirect(&lf);
            SendMessage(hEdit[0],WM_SETFONT,(UINT)hFont,TRUE);
            SendMessage(hEdit[0], WM_SETTEXT,0, (LPARAM) "Enter your name here ...");

            ZeroMemory(&lf, sizeof(LOGFONT));
            lstrcpy(lf.lfFaceName,"Times New Roman");
            lf.lfHeight = 14;
            lf.lfWeight = FW_BOLD;
            hFont = CreateFontIndirect(&lf);
            SendMessage(hEdit[1],WM_SETFONT,(UINT)hFont,TRUE);
            SendMessage(hEdit[1], WM_SETTEXT,0, (LPARAM) "Your serial will pop here ...");

            HANDLE hImageBtn=LoadBitmap(hinst,"Xoff");
            SendMessage(hBtn[0],STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,(LPARAM)hImageBtn);

            hImageBtn=LoadBitmap(hinst,"Dooff");
            SendMessage(hBtn[1],STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,(LPARAM)hImageBtn);

            hImageBtn=LoadBitmap(hinst,"Aboff");
            SendMessage(hBtn[2],STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,(LPARAM)hImageBtn);

            hImageBtn=LoadBitmap(hinst,"Copyoff");
            SendMessage(hBtn[3],STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,(LPARAM)hImageBtn);

            return 0;

        case WM_PAINT:
            HBITMAP hBmp;
            HDC hdc;
            PAINTSTRUCT ps;
            hBmp=LoadBitmap(hinst,"Fond");
            hdc = BeginPaint(hwnd, &ps);
            DrawState(hdc,NULL,NULL,(long)hBmp,WPARAM (NULL),0,0,0,0,DST_BITMAP);
            AfficherTexte(hwnd, hdc, titre2, 5, 2, 20, false);
            AfficherTexte(hwnd, hdc, coder, 5, 22, 16, true);
            AfficherTexte(hwnd, hdc, gfxer, 5, 37, 16, true);
            EndPaint(hwnd, &ps);
            DeleteObject(hBmp);

            return 0;

        case WM_CTLCOLORSTATIC:
            HDC textDC = (HDC)wParam;
            if ((HWND)lParam == hEdit[1])
            {
            SetTextColor(textDC, blanc);
            SetBkMode(textDC, TRANSPARENT);
            }
            static HBRUSH brush = noir;
            return (LRESULT)brush;

        case WM_MOUSEMOVE:
            GetWindowRect(hwnd,&rc);
            GetCursorPos(&lp);
            dx = lp.x - rc.left;
            dy = lp.y -rc.top;

            //Change le curseur sur les zones de clic
            if (((dx >= 453) && (dy >= 12) && (dx <= 467) && (dy <= 25))||
                ((dx >= 282) && (dy >= 156) && (dx <= 306) && (dy <= 165))||
                ((dx >= 434) && (dy >= 206) && (dx <= 444) && (dy <= 218))||
                ((dx >= 396) && (dy >= 195) && (dx <= 422) && (dy <= 219))||
                ((dx >= 402) && (dy >= 226) && (dx <= 434) && (dy <= 235))||
                ((dx >= 402) && (dy >= 240) && (dx <= 432) && (dy <= 251)))
            SetCursor(LoadCursor(NULL,IDC_HAND));

            //Deplace la fenetre
            else
            {
            if(wParam & MK_LBUTTON) PostMessage(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
            break;
            }

            return 0;

        case WM_LBUTTONDOWN:
            //Détermine ou a lieu le clic
            GetWindowRect(hwnd,&rc);
            GetCursorPos(&lp);
            dx = lp.x - rc.left;
            dy = lp.y -rc.top;

            //Bouton Fermer
            if ((dx >= 434) && (dy >= 206) && (dx <= 444) && (dy <= 218))
            {
                hImageBtn=LoadBitmap(hinst,"Xon");
                SendMessage(hBtn[0],STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,(LPARAM)hImageBtn);
            }

            //Bouton Generer
            if ((dx >= 396) && (dy >= 195) && (dx <= 422) && (dy <= 219))
            {
                hImageBtn=LoadBitmap(hinst,"Doon");
                SendMessage(hBtn[1],STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,(LPARAM)hImageBtn);
            }

            //Bouton About
            if ((dx >= 402) && (dy >= 226) && (dx <= 434) && (dy <= 235))
            {
                hImageBtn=LoadBitmap(hinst,"Abon");
                SendMessage(hBtn[2],STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,(LPARAM)hImageBtn);
            }

            //Bouton Copy
            if ((dx >= 398) && (dy >= 237) && (dx <= 436) && (dy <= 253))
            {
                hImageBtn=LoadBitmap(hinst,"Copyon");
                SendMessage(hBtn[3],STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,(LPARAM)hImageBtn);
            }


            return 0;

        case WM_LBUTTONUP:
            //Détermine ou a lieu le clic
            GetWindowRect(hwnd,&rc);
            GetCursorPos(&lp);
            dx = lp.x - rc.left;
            dy = lp.y -rc.top;

            //Clic sur Reduire
            if ((dx >= 453) && (dy >= 12) && (dx <= 467) && (dy <= 25))
            ShowWindow (hwnd,SW_MINIMIZE);

            //Clic sur XTX
            if ((dx >= 282) && (dy >= 156) && (dx <= 306) && (dy <= 165))
            ShellExecute(NULL,NULL,"http://xtx.a.nf/",NULL,NULL,SW_SHOW);

            //Bouton Fermer
            if ((dx >= 434) && (dy >= 206) && (dx <= 444) && (dy <= 218))
            {
            hImageBtn=LoadBitmap(hinst,"Xoff");
            SendMessage(hBtn[0],STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,(LPARAM)hImageBtn);
            SendMessage(hwnd,WM_DESTROY,0,0);
            }

            //Bouton Générer
            if ((dx >= 396) && (dy >= 195) && (dx <= 422) && (dy <= 219))
            {
            hImageBtn=LoadBitmap(hinst,"Dooff");
            SendMessage(hBtn[1],STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,(LPARAM)hImageBtn);
            int L = SendMessage( hEdit[0], WM_GETTEXTLENGTH,wParam,lParam);
            char Text[L] ;
            const char* Resultat ;
            //Recupere le nom
            GetWindowText (hEdit[0],Text,256);
            string nom = Text ;
            //Appelle la fonction de calcul du serial
            Resultat = GenerateSerial (nom) ;
            if (TypeMsgBox == 1 || TypeMsgBox == 2 || TypeMsgBox == 3)
            {
                ShowWindow(Warning, SW_SHOW);
                UpdateWindow(Warning);
            }
            //Affiche le resultat
            SendMessage(hEdit[1], WM_SETTEXT,0, (LPARAM) Resultat);
            }

            //Bouton About
            if ((dx >= 402) && (dy >= 226) && (dx <= 434) && (dy <= 235))
            {
            hImageBtn=LoadBitmap(hinst,"Aboff");
            SendMessage(hBtn[2],STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,(LPARAM)hImageBtn);
            TypeMsgBox = 0;
            ShowWindow(Warning, SW_SHOW);
            UpdateWindow(Warning);
            }

            //Bouton Copy
            if ((dx >= 398) && (dy >= 237) && (dx <= 436) && (dy <= 2253))
            {
            hImageBtn=LoadBitmap(hinst,"Copyoff");
            SendMessage(hBtn[3],STM_SETIMAGE,(WPARAM)IMAGE_BITMAP,(LPARAM)hImageBtn);
            int LongueurTexte = SendMessage(hEdit[1], WM_GETTEXTLENGTH,wParam,lParam);
            char TexteACopier[LongueurTexte] ;
            GetWindowText (hEdit[1],TexteACopier,256);
            string strTexteACopier = TexteACopier ;
            Copier(strTexteACopier.c_str()) ;
            }

            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
/********************** Procedure fenetre About/Warning ****************************************/
LRESULT CALLBACK MainWndProc2(HWND Warning, UINT uMsg2, WPARAM wParam2, LPARAM lParam2)
{
    switch (uMsg2)
    {
        case WM_PAINT:
            HBITMAP hBmp;
            HDC hdc;
            PAINTSTRUCT ps;
            hBmp=LoadBitmap(hinst,"DlgFond");
            hdc = BeginPaint(Warning, &ps);
            DrawState(hdc,NULL,NULL,(long)hBmp,WPARAM (NULL),0,0,0,0,DST_BITMAP);

            //Affichage texte About
            if (TypeMsgBox == 0)
            {
                AfficherTexte(Warning, hdc, AboutLigne1,  5,  38, 14, false);
                AfficherTexte(Warning, hdc, AboutLigne2,  5,  56, 14, false);
                AfficherTexte(Warning, hdc, AboutLigne3,  5,  74, 14, false);
                AfficherTexte(Warning, hdc, AboutLigne4,  5,  92, 14, false);
                AfficherTexte(Warning, hdc, AboutLigne5,  5, 110, 14, false);
                AfficherTexte(Warning, hdc, AboutLigne6,  5, 128, 14, false);
                AfficherTexte(Warning, hdc, AboutLigne7,  5, 146, 14, false);
                AfficherTexte(Warning, hdc, AboutLigne8,  5, 164, 14, false);
                AfficherTexte(Warning, hdc, AboutLigne9,  5, 182, 14, false);
                AfficherTexte(Warning, hdc, AboutLigne10, 5, 200, 14, false);
            }

            //Affichage texte fenetre Warning1
            if (TypeMsgBox == 1)
            {
                AfficherTexte(Warning, hdc, Warning1Ligne1,  5,  38, 14, false);
                AfficherTexte(Warning, hdc, Warning1Ligne2,  5,  56, 14, false);
                AfficherTexte(Warning, hdc, Warning1Ligne3,  5,  74, 14, false);
                AfficherTexte(Warning, hdc, Warning1Ligne4,  5,  92, 14, false);
                AfficherTexte(Warning, hdc, Warning1Ligne5,  5, 110, 14, false);
                AfficherTexte(Warning, hdc, Warning1Ligne6,  5, 128, 14, false);
                AfficherTexte(Warning, hdc, Warning1Ligne7,  5, 146, 14, false);
                AfficherTexte(Warning, hdc, Warning1Ligne8,  5, 164, 14, false);
                AfficherTexte(Warning, hdc, Warning1Ligne9,  5, 182, 14, false);
                AfficherTexte(Warning, hdc, Warning1Ligne10, 5, 200, 14, false);
            }

            //Affichage texte fenetre Warning2
            if (TypeMsgBox == 2)
            {
                AfficherTexte(Warning, hdc, Warning2Ligne1,  5,  38, 14, false);
                AfficherTexte(Warning, hdc, Warning2Ligne2,  5,  56, 14, false);
                AfficherTexte(Warning, hdc, Warning2Ligne3,  5,  74, 14, false);
                AfficherTexte(Warning, hdc, Warning2Ligne4,  5,  92, 14, false);
                AfficherTexte(Warning, hdc, Warning2Ligne5,  5, 110, 14, false);
                AfficherTexte(Warning, hdc, Warning2Ligne6,  5, 128, 14, false);
                AfficherTexte(Warning, hdc, Warning2Ligne7,  5, 146, 14, false);
                AfficherTexte(Warning, hdc, Warning2Ligne8,  5, 164, 14, false);
                AfficherTexte(Warning, hdc, Warning2Ligne9,  5, 182, 14, false);
                AfficherTexte(Warning, hdc, Warning2Ligne10, 5, 200, 14, false);
            }

            //Affichage texte fenetre Warning3
            if (TypeMsgBox == 3)
            {
                AfficherTexte(Warning, hdc, Warning3Ligne1,  5,  38, 14, false);
                AfficherTexte(Warning, hdc, Warning3Ligne2,  5,  56, 14, false);
                AfficherTexte(Warning, hdc, Warning3Ligne3,  5,  74, 14, false);
                AfficherTexte(Warning, hdc, Warning3Ligne4,  5,  92, 14, false);
                AfficherTexte(Warning, hdc, Warning3Ligne5,  5, 110, 14, false);
                AfficherTexte(Warning, hdc, Warning3Ligne6,  5, 128, 14, false);
                AfficherTexte(Warning, hdc, Warning3Ligne7,  5, 146, 14, false);
                AfficherTexte(Warning, hdc, Warning3Ligne8,  5, 164, 14, false);
                AfficherTexte(Warning, hdc, Warning3Ligne9,  5, 182, 14, false);
                AfficherTexte(Warning, hdc, Warning3Ligne10, 5, 200, 14, false);
            }

            EndPaint(Warning, &ps);
            DeleteObject(hBmp);
            return 0;

        case WM_LBUTTONUP:
            ShowWindow(Warning, SW_HIDE);
            ShowWindow(hwnd, SW_SHOW);
            return 0;

        default:
            return DefWindowProc(Warning, uMsg2, wParam2, lParam2);
    }
}
/********************** Fonction affichage de texte ************************************/
void AfficherTexte (HWND fenetre, HDC dc, char *chaine, int Xleft, int Ytop, int taille,
                    BOOL italique)
{
        //Déclarations des variables
        LOGFONT structFonte2;
        HFONT fonte2;

        //Remplissage de la LOGFONT
        ZeroMemory(&structFonte2, sizeof(LOGFONT));
        strcpy(structFonte2.lfFaceName, "Times New Roman");
        structFonte2.lfWeight = FW_BOLD;
        structFonte2.lfHeight = taille;
        structFonte2.lfItalic = italique;

        //Création de la fonte
        fonte2 = CreateFontIndirect(&structFonte2);

        //Permet au texte d'avoir un fond transparent
        SetBkMode(dc, TRANSPARENT);
        //Applique la fonte au dc de texte
        SelectObject(dc, fonte2);
        //Applique la couleur de texte au dc
        SetTextColor(dc, blanc);

        //Affichage du texte
        TextOut(dc, Xleft, Ytop, chaine, strlen(chaine));

        return;
}
/******************* fonction copier ***************************************************/
int Copier(const char *text)
{
    int ret = 0;

    HANDLE hGlobalMem = GlobalAlloc(GHND, lstrlen(text)+1);
    char *lpGlobalMem = NULL;

    EXIT_IF(hGlobalMem == NULL);

    lpGlobalMem = (char*)GlobalLock(hGlobalMem);

    EXIT_IF(lpGlobalMem == NULL);

    lstrcpy(lpGlobalMem, text);

    GlobalUnlock(hGlobalMem);

    EXIT_IF(!OpenClipboard(NULL));

    EmptyClipboard();

    if(SetClipboardData(CF_TEXT, hGlobalMem) != NULL)
        ret = 1;

    CloseClipboard();

    EXIT_LABEL:
        return ret; /* 1 : Succeed, 0 : Failure */
}
/******************* Fonction calcul du serial *****************************************/
const char* GenerateSerial (string strNom)
{
    const char* constSerial ;

    /*****************************************************************************
    ******************************************************************************
    ** Créer le code de generetion du serial ici                                **
    ** Le résultat devra être un const char* et être transféré dans constSerial **
    **                                                                          **
    ** Vous avez à disposition 3 boites de dialogues Warning.                           **
    ** Pour les appeler :                                                       **
    **                                                                          **
    **        TypeMsgBox = 1; ( ou 2, ou 3)                                     **
    **        ShowWindow(Warning, SW_SHOW);                                     **
    **        UpdateWindow(Warning);                                            **
    **                                                                          **
    ** Le texte peut être personaliser dans texte.h, vous disposer de 10 lignes.**
    ******************************************************************************
    *****************************************************************************/

    TypeMsgBox = 4;
    return constSerial ;

}
/***************************************************************************************/
