/*
 *
 * Tworzenie okna aplikacji
 *
 */
#include <windows.h>

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

    /* Pobierz rozmiar okna */
    DWORD xSize, ySize;
    HKEY hKey;

    if(RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Programowanie pod Windows\\1.2.2", 0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        DWORD dwSize = sizeof(DWORD);
        if(RegQueryValueEx(hKey, "xSize", NULL, NULL, (LPBYTE)&xSize, &dwSize) == ERROR_SUCCESS)
            xSize += 16;
        else
            xSize = 512;
        if(RegQueryValueEx(hKey, "ySize", NULL, NULL, (LPBYTE)&ySize, &dwSize) == ERROR_SUCCESS)
            ySize += 39;
        else
            ySize = 512;
        RegCloseKey(hKey);
    }
    else
    {
        xSize = 512;
        ySize = 512;
    }

    /* Twórz okno */
    hwnd = CreateWindowEx(
               0, szClassName,
               "Przyk3ad",
               WS_OVERLAPPEDWINDOW,
               CW_USEDEFAULT, CW_USEDEFAULT,
               xSize, ySize,
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

/* Te funkcje wo3a DispatchMessage( ) */
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message,
                                 WPARAM wParam, LPARAM lParam)
{
    //
    HKEY hKey;
    DWORD disposition;
    RECT r;

    switch (message)
    {
    case WM_DESTROY:
        if(RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Programowanie pod Windows\\1.2.2",
                          0, NULL, 0, KEY_ALL_ACCESS, NULL, &hKey, &disposition) == ERROR_SUCCESS)
        {
            if(GetClientRect(hwnd, &r) == TRUE)
            {
                if(RegSetValueEx(hKey, "xSize", 0, REG_DWORD, (LPBYTE)&r.right, sizeof(DWORD)) != ERROR_SUCCESS)
                    return 1;
                if(RegSetValueEx(hKey, "ySize", 0, REG_DWORD, (LPBYTE)&r.bottom, sizeof(DWORD))!= ERROR_SUCCESS)
                    return 1;
            }
            RegCloseKey(hKey);
        }
        else
        {
            return 1;
        }
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}
