/*
 *
 * Tworzenie okna aplikacji
 *
 */
#define _WIN32_IE 0x0900

#include <windows.h>
#include <CommCtrl.h> //LVS_REPORT itd.

/* Deklaracja wyprzedzaj1ca: funkcja obs3ugi okna */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
/* Nazwa klasy okna */
char szClassName[] = "PRZYKLAD";

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nShowCmd)
{
    HWND hwnd;               /* Uchwyt okna */
    MSG messages;            /* Komunikaty okna */
    WNDCLASSEX wincl;        /* Struktura klasy okna */

    /* Common Controls */
    INITCOMMONCONTROLSEX icex;
    icex.dwICC = ICC_LISTVIEW_CLASSES;
    InitCommonControlsEx(&icex);

    /* Klasa okna */
    wincl.hInstance     = hInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc   = WindowProcedure;    // wskaYnik na funkcje
    // obs3ugi okna
    wincl.style         = CS_DBLCLKS;
    wincl.cbSize        = sizeof(WNDCLASSEX);

    /* Domyolna ikona i wskaYnik myszy */
    wincl.hIcon   = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    /* Jasnoszare t3o */
    wincl.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);

    /* Rejestruj klase okna */
    if(!RegisterClassEx(&wincl)) return 0;

    /* Twórz okno */
    hwnd = CreateWindowEx(
               0, szClassName,
               "Przyklad",
               WS_OVERLAPPEDWINDOW,
               CW_USEDEFAULT, CW_USEDEFAULT,
               512, 512,
               HWND_DESKTOP, NULL,
               hInstance, NULL );

    ShowWindow(hwnd, nShowCmd);
    /* Petla obs3ugi komunikatów */
    while(GetMessage(&messages, NULL, 0, 0))
    {
        /* T3umacz kody rozszerzone */
        TranslateMessage(&messages);
        /* Obs3u? komunikat */
        DispatchMessage(&messages);
    }

    /* Zwróa parametr podany w PostQuitMessage( ) */
    return messages.wParam;
}

HWND hWndListView, progressBar, t1, t2, t3;
LVITEM lv  = { 0 };

int licznik = 3;

/* Te funkcje wo3a DispatchMessage( ) */
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message,
                                 WPARAM wParam, LPARAM lParam)
{
    int length1, length2, length3;
    char* text1;
    char* text2;
    char* text3;

    switch (message)
    {
    case WM_CREATE:
    {
        SetTimer (hwnd, 1, 300, NULL) ;

        hWndListView = CreateWindow(WC_LISTVIEW,
                                    "",
                                    WS_VISIBLE | WS_CHILD | LVS_REPORT | LVS_EDITLABELS,
                                    0, 0,
                                    500,
                                    380,
                                    hwnd,
                                    (HMENU)0,
                                    ((LPCREATESTRUCT) lParam)->hInstance,
                                    NULL);

        ListView_SetExtendedListViewStyle(hWndListView, LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);

        LVCOLUMN lvc = { 0 };
        lvc.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH  | LVCF_FMT;
        lvc.fmt  = LVCFMT_LEFT;

        lvc.iSubItem = 0;
        lvc.cx       = 30;
        lvc.pszText  = TEXT("");
        ListView_InsertColumn(hWndListView, 0, &lvc);

        lvc.iSubItem = 1;
        lvc.cx       = 90;
        lvc.pszText  = TEXT("Imie");
        ListView_InsertColumn(hWndListView, 1, &lvc);

        lvc.iSubItem = 2;
        lvc.cx       = 90;
        lvc.pszText  = TEXT("Nazwisko");
        ListView_InsertColumn(hWndListView, 2, &lvc);

        lvc.iSubItem = 3;
        lvc.cx       = 120;
        lvc.pszText  = TEXT("Numer indeksu");
        ListView_InsertColumn(hWndListView, 3, &lvc);

        lv.iItem = 0;
        ListView_InsertItem(hWndListView, &lv);
        ListView_SetItemText(hWndListView, 0, 1, TEXT("Kamil"));
        ListView_SetItemText(hWndListView, 0, 2, TEXT("Bebenek"));
        ListView_SetItemText(hWndListView, 0, 3, TEXT("258340"));
        ListView_SetCheckState(hWndListView, 0, TRUE);

        lv.iItem = 1;
        ListView_InsertItem(hWndListView, &lv);
        ListView_SetItemText(hWndListView, 1, 1, TEXT("Jacek"));
        ListView_SetItemText(hWndListView, 1, 2, TEXT("Kowalski"));
        ListView_SetItemText(hWndListView, 1, 3, TEXT("255225"));
        ListView_SetCheckState(hWndListView, 1, FALSE);

        lv.iItem = 2;
        ListView_InsertItem(hWndListView, &lv);
        ListView_SetItemText(hWndListView, 2, 1, TEXT("Marcin"));
        ListView_SetItemText(hWndListView, 2, 2, TEXT("Nowak"));
        ListView_SetItemText(hWndListView, 2, 3, TEXT("334422"));
        ListView_SetCheckState(hWndListView, 2, TRUE);

        t1 = CreateWindow("EDIT", "",
                          WS_VISIBLE | WS_CHILD | WS_BORDER,
                          40, 392, 100, 20,
                          hwnd, (HMENU) 20, ((LPCREATESTRUCT) lParam)->hInstance, NULL);

        t2 = CreateWindow("EDIT", "",
                          WS_VISIBLE | WS_CHILD | WS_BORDER,
                          150, 392, 100, 20,
                          hwnd, (HMENU) 21, ((LPCREATESTRUCT) lParam)->hInstance, NULL);

        t3 = CreateWindow("EDIT", "",
                          WS_VISIBLE | WS_CHILD | WS_BORDER,
                          260, 392, 100, 20,
                          hwnd, (HMENU) 22, ((LPCREATESTRUCT) lParam)->hInstance, NULL);

        CreateWindow("BUTTON", "Dodaj",
                     WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                     370, 390, 80, 25,
                     hwnd, (HMENU) 23, ((LPCREATESTRUCT) lParam)->hInstance, NULL);


        progressBar = CreateWindow(PROGRESS_CLASS,
                                   "",
                                   WS_CHILD | WS_VISIBLE | PBS_SMOOTH,
                                   30, 420,
                                   430,
                                   30,
                                   hwnd,
                                   (HMENU)2,
                                   ((LPCREATESTRUCT) lParam)->hInstance,
                                   NULL);

        SendMessage(progressBar, PBM_SETRANGE, 0, MAKELPARAM(0, 50));
        SendMessage(progressBar, PBM_SETSTEP, 1, 0 );

        HWND hStatus = CreateWindow(STATUSCLASSNAME, "", WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP,
                                    0, 0, 0, 0, hwnd, (HMENU)15, ((LPCREATESTRUCT) lParam)->hInstance, NULL);

        int szerokosci[] = {150, 300, 400, -1};

        SendMessage(hStatus, SB_SETPARTS, (WPARAM)(sizeof(szerokosci)/sizeof(int)), (LPARAM)szerokosci);
        SendMessage((HWND) hStatus, (UINT) SB_SETTEXT, (WPARAM)(INT) 0 , (LPARAM) (LPSTR) TEXT("TEKST"));

        break;
    }

    case WM_COMMAND:

        if ( HIWORD(wParam) == BN_CLICKED )
        {
            switch( LOWORD(wParam) )
            {
            case 23:

                length1 = SendMessage( t1, WM_GETTEXTLENGTH, 0, 0 );
                text1 =(char *) GlobalAlloc(GMEM_FIXED,length1+1);
                if(text1)
                {
                    SendMessage(t1, WM_GETTEXT, length1+1, (LPARAM)text1);
                }
                length2 = SendMessage( t2, WM_GETTEXTLENGTH, 0, 0 );
                text2 =(char *) GlobalAlloc(GMEM_FIXED,length2+1);
                if(text2)
                {
                    SendMessage(t2, WM_GETTEXT, length2+1, (LPARAM)text2);
                }

                length3 = SendMessage( t3, WM_GETTEXTLENGTH, 0, 0 );
                text3 =(char *) GlobalAlloc(GMEM_FIXED,length3+1);
                if(text3)
                {
                    SendMessage(t3, WM_GETTEXT, length3+1, (LPARAM)text3);
                }

                lv.iItem = licznik;
                ListView_InsertItem(hWndListView, &lv);
                ListView_SetItemText(hWndListView, licznik, 1, text1);
                ListView_SetItemText(hWndListView, licznik, 2, text2);
                ListView_SetItemText(hWndListView, licznik, 3, text3);
                licznik++;

                GlobalFree(text1);
                GlobalFree(text2);
                GlobalFree(text3);
            }
        }
        break;

    case WM_TIMER:
        SendMessage( progressBar, PBM_STEPIT, 0, 0 );
        break;

    case WM_DESTROY:
        KillTimer(hwnd, 1);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}
