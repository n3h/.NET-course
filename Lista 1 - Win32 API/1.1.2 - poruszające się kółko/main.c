/*
w opraciu o przyklad
https://www-user.tu-chemnitz.de/~heha/petzold/ch08c.htm
settimer
potem podobnie jak w wm_size
dodany wm_timer
*/
/*
 *
 * Tworzenie grafiki za pomoc¹ GDI
 *
 */
#include <windows.h>
#include <string.h>
#include <stdbool.h>

/* Deklaracja wyprzedzaj¹ca: funkcja obs³ugi okna */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
/* Nazwa klasy okna */
char szClassName[] = "PRZYKLAD";

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
    wincl.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);

    /* Rejestruj klasê okna */
    if(!RegisterClassEx(&wincl)) return 0;

    /* Twórz okno */
    hwnd = CreateWindowEx(
           0,
           szClassName,
           "ZAD 1.1.2",
           WS_OVERLAPPEDWINDOW,
           CW_USEDEFAULT,
           CW_USEDEFAULT,
           512,
           512,
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

int xSize, ySize;

/* Tê funkcjê wo³a DispatchMessage( ) */
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message,
                                 WPARAM wParam, LPARAM lParam)
{
    char sText[] = "Witamy w GDI";
    static HDC         hdc ; // kontekst urz¹dzenia
    int         i ;
    PAINTSTRUCT ps ;
    RECT r;
    static int x = 250, y=0;
    static bool addX = true, addY = true;

    HPEN   hPen;
    HBRUSH hBrush;

    switch (message)
    {
           case WM_DESTROY:
              KillTimer(hwnd, 1);
              PostQuitMessage(0);
              break;
           case WM_CREATE:
                SetTimer (hwnd, 1, 15, NULL) ;
                break;
           case WM_SIZE:
              xSize = LOWORD(lParam);
              ySize = HIWORD(lParam);

              GetClientRect( hwnd, &r ); // Zwraca lokalne koordynaty obszaru okna.
              InvalidateRect( hwnd, &r, 1 ); // Odświeża określony obszar okna.

              break;
            case WM_TIMER:
                if (xSize < 20+x)
                    addX = false;
                else if (x < 0)
                    addX = true;

                if (ySize < 20+y)
                    addY = false;
                else if (y < 0)
                    addY = true;

                if (addX)
                    x+=1;
                else
                    x-=1;

                if (addY)
                    y+=1;
                else
                    y-=1;
                GetClientRect( hwnd, &r );
                InvalidateRect( hwnd, &r, 1 );

              break;

           case WM_PAINT:
              hdc = BeginPaint (hwnd, &ps) ;

              // kszta³ty
              //SetBkColor( hdc, RGB(0, 255, 0) );
              hBrush = CreateSolidBrush( RGB(255, 55, 55));
              SelectObject( hdc, hBrush );
              Ellipse(hdc, 0+x, 0+y, 20+x, 20+y);
              DeleteObject( hBrush );


              EndPaint(hwnd, &ps);
              break;

           default:
              return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}
