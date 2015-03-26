/*
linker do gdi32
*/

/*
 *
 * Tworzenie grafiki za pomoc¹ GDI
 *
 */
#include <windows.h>
#include <string.h>

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
               "ZAD 1.1.1",
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
    HDC         hdc ; // kontekst urz¹dzenia
    int         i ;
    PAINTSTRUCT ps ;
    RECT r;

    HPEN   hPen;

    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_SIZE:
        xSize = LOWORD(lParam);
        ySize = HIWORD(lParam);

        GetClientRect( hwnd, &r );
        InvalidateRect( hwnd, &r, 1 );

        break;
    case WM_PAINT:
        hdc = BeginPaint (hwnd, &ps) ;

        // linie
        hPen = CreatePen (PS_SOLID, 1, RGB (0, 0, 0));
        SelectObject( hdc, hPen );
        MoveToEx( hdc, xSize/2, 0, NULL );
        LineTo( hdc, xSize/2, ySize );
        MoveToEx( hdc, 0, ySize/2, NULL );
        LineTo( hdc, xSize, ySize/2 );
        DeleteObject( hPen );

        // |x|
        hPen = CreatePen (PS_SOLID, 1, RGB (255, 0, 0));
        SelectObject( hdc, hPen );
        MoveToEx( hdc, xSize/2, ySize/2, NULL );
        LineTo( hdc, xSize/2-ySize/2, 0 );
        MoveToEx( hdc, xSize/2, ySize/2, NULL );
        LineTo( hdc, (xSize+ySize)/2, 0 );
        DeleteObject( hPen );

        // x^2
        // calculate points
        POINT* points;
        points = (POINT*)GlobalAlloc(GMEM_FIXED,(ySize/2)*sizeof(*points));
        for (int i = 0; i < ySize/2; i++)
        {
            points[i].x = xSize/2 + 6*i;
            points[i].y = (ySize/2 - i*i);
        }

        // draw
        hPen = CreatePen (PS_DOT, 1, RGB (0, 255, 0));
        SelectObject( hdc, hPen );
        Polyline( hdc, points, ySize/2);

        // reverse points
        for (int i = 0; i < ySize/2; i++)
        {
            points[i].x = xSize/2 - 6*i;
        }
        Polyline( hdc, points, ySize/2);

        DeleteObject( hPen );
        GlobalFree(points);

        EndPaint(hwnd, &ps);
        break;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}
