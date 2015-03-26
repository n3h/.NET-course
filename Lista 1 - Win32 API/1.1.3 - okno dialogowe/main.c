/*
zmienione tlo na kolor okna
*/
/*
 *
 * Tworzenie okien potomnych
 *
 */
#include <windows.h>
#include <string.h>

/* Deklaracja wyprzedzaj¹ca: funkcja obs³ugi okna */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
/* Nazwa klasy okna */
char szClassName[] = "Wybor uczelni";

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance,
                   LPSTR lpszArgument, int nFunsterStil)
{
    HWND hwnd;               /* Uchwyt okna */
    MSG messages;            /* Komunikaty okna */
    WNDCLASSEX wincl;        /* Struktura klasy okna */

    /* Klasa okna */
    wincl.hInstance     = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc   = WindowProcedure;    // wskaŸnik na funkcjê
    // obs³ugi okna
    wincl.style         = CS_DBLCLKS;
    wincl.cbSize        = sizeof(WNDCLASSEX);

    /* Domyœlna ikona i wskaŸnik myszy */
    wincl.hIcon   = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    /* Jasnoszare t³o */
    wincl.hbrBackground = (HBRUSH)COLOR_WINDOW;
    /* Rejestruj klasê okna */
    if(!RegisterClassEx(&wincl)) return 0;

    /* Twórz okno */
    hwnd = CreateWindowEx(
               0,
               szClassName,
               "Wybor uczelni",
               WS_OVERLAPPEDWINDOW,
               CW_USEDEFAULT, CW_USEDEFAULT,
               455, 285,
               HWND_DESKTOP,
               NULL,
               hThisInstance,
               NULL
           );

    ShowWindow(hwnd, nFunsterStil);
    /* Pêtla obs³ugi komunikatów */
    while(GetMessage(&messages, NULL, 0, 0))
    {
        /* T³umacz kody rozszerzone */
        TranslateMessage(&messages);
        /* Obs³u¿ komunikat */
        DispatchMessage(&messages);
    }

    /* Zwróæ parametr podany w PostQuitMessage( ) */
    return messages.wParam;
}


/* Tê funkcjê wo³a DispatchMessage( ) */
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message,
                                 WPARAM wParam, LPARAM lParam)
{
    static HWND elements[10];
    //int         i;
    int length1, length2, length3;
    char* text1;
    char* text2;
    char* text3;
    char* full_text;

    switch (message)
    {
    case WM_CREATE:
        // first GroupBox
        elements[0] = CreateWindow("BUTTON", "Uczelnia",
                                   WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
                                   10, 10, 420, 95,
                                   hwnd, (HMENU) 0, ((LPCREATESTRUCT) lParam)->hInstance, NULL);

        elements[1] = CreateWindow("STATIC", "Nazwa: ",
                                   WS_VISIBLE | WS_CHILD ,
                                   8, 30, 60, 20,
                                   elements[0], (HMENU) 1, ((LPCREATESTRUCT) lParam)->hInstance, NULL);

        elements[2] = CreateWindowEx(0, "EDIT", "Uniwersytet Wroclawski",
                                   WS_VISIBLE | WS_CHILD | WS_BORDER,
                                   85, 30, 330, 20,
                                   elements[0], (HMENU) 2, ((LPCREATESTRUCT) lParam)->hInstance, NULL);

        elements[3] = CreateWindow("STATIC", "Adres: ",
                                   WS_VISIBLE | WS_CHILD ,
                                   8, 60, 60, 20,
                                   elements[0], (HMENU) 3, ((LPCREATESTRUCT) lParam)->hInstance, NULL);

        elements[4] = CreateWindow("EDIT", "pl. Uniwersytecki 1, 50-137 Wroclaw",
                                   WS_VISIBLE | WS_CHILD | WS_BORDER,
                                   85, 60, 330, 20,
                                   elements[0], (HMENU) 4, ((LPCREATESTRUCT) lParam)->hInstance, NULL);

        // second ComboBox
        elements[5] = CreateWindow("BUTTON", "Rodzaj studiow",
                                   WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
                                   10, 115, 420, 95,
                                   hwnd, (HMENU) 5, ((LPCREATESTRUCT) lParam)->hInstance, NULL);

        elements[6] = CreateWindow("STATIC", "Cykl nauki: ",
                                   WS_VISIBLE | WS_CHILD,
                                   8, 30, 100, 20,
                                   elements[5], (HMENU) 6, ((LPCREATESTRUCT) lParam)->hInstance, NULL);

        elements[7] = CreateWindow("COMBOBOX", "",
                                   WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,
                                   85, 30, 330, 120,
                                   elements[5], (HMENU) 7, ((LPCREATESTRUCT) lParam)->hInstance, NULL);
        SendMessage(elements[7], CB_ADDSTRING, 0, (LPARAM)"1,5-letnie");
        SendMessage(elements[7], CB_ADDSTRING, 0, (LPARAM)"2-letnie");
        SendMessage(elements[7], CB_ADDSTRING, 0, (LPARAM)"3-letnie");
        SendMessage(elements[7], CB_ADDSTRING, 0, (LPARAM)"3,5-letnie");
        SendMessage(elements[7], CB_ADDSTRING, 0, (LPARAM)"5-letnie");

        elements[8] = CreateWindow("BUTTON", "dzienne",
                                   WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
                                   85, 60, 80, 20,
                                   elements[5], (HMENU) 8, ((LPCREATESTRUCT) lParam)->hInstance, NULL);

        elements[9] = CreateWindow("BUTTON", "uzupelniajace",
                                   WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
                                   170, 60, 150, 20,
                                   elements[5], (HMENU) 9, ((LPCREATESTRUCT) lParam)->hInstance, NULL);

        // two buttons
        CreateWindow("BUTTON", "Akceptuj",
                     WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                     10, 215, 80, 25,
                     hwnd, (HMENU) 10, ((LPCREATESTRUCT) lParam)->hInstance, NULL);

        CreateWindow("BUTTON", "Anuluj",
                     WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                     350, 215, 80, 25,
                     hwnd, (HMENU) 11, ((LPCREATESTRUCT) lParam)->hInstance, NULL);

        break;

    case WM_COMMAND:
        // jeœli klikniêto przycisk
        if ( HIWORD(wParam) == BN_CLICKED )
        {
            switch( LOWORD(wParam) )
            {
            case 10:
                //length1 = GetWindowTextLength(elements[2]);  //+GetWindowText
                length1 = SendMessage( elements[2], WM_GETTEXTLENGTH, 0, 0 );
                text1 =(char *) GlobalAlloc(GMEM_FIXED,length1+1);
                if(text1)
                {
                    SendMessage(elements[2], WM_GETTEXT, length1+1, (LPARAM)text1);
                }
                //length2 = GetWindowTextLength(elements[4]);
                length2 = SendMessage( elements[4], WM_GETTEXTLENGTH, 0, 0 );
                text2 =(char *) GlobalAlloc(GMEM_FIXED,length2+1);
                if(text2)
                {
                    SendMessage(elements[4], WM_GETTEXT, length2+1, (LPARAM)text2);
                }

                length3 = SendMessage( elements[7], WM_GETTEXTLENGTH, 0, 0 );
                text3 =(char *) GlobalAlloc(GMEM_FIXED,length3+1);
                if(text3)
                {
                    SendMessage(elements[7], WM_GETTEXT, length3+1, (LPARAM)text3);
                }

                if (SendMessage(elements[8], BM_GETCHECK, 0, 0) == BST_CHECKED)
                    length3 += 8;

                if (SendMessage(elements[9], BM_GETCHECK, 0, 0) == BST_CHECKED)
                    length3 += 13;

                full_text = (char *) GlobalAlloc(GMEM_FIXED,length1 + 1 + 2 + length2 + 1 + 2 + length3 + 1 + 2);
                strcpy(full_text, text1);
                strcat(full_text, "\n");
                strcat(full_text, text2);
                strcat(full_text, "\n");
                strcat(full_text, text3);
                strcat(full_text, "\n");

                if (SendMessage(elements[8], BM_GETCHECK, 0, 0) == BST_CHECKED)
                    strcat(full_text, "dzienne ");
                if (SendMessage(elements[9], BM_GETCHECK, 0, 0) == BST_CHECKED)
                    strcat(full_text, "uzupelniajace");

                MessageBox( hwnd, (LPCSTR)full_text, "Uczelnia", MB_OK );

                GlobalFree(text1);
                GlobalFree(text2);
                GlobalFree(text3);
                GlobalFree(full_text);

                break;

            case 11:
                PostQuitMessage(0);
                break;
            }
        }

        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}
