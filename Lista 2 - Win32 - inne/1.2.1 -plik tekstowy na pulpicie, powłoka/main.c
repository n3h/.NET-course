#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <Shlobj.h>
#include <Shlwapi.h>

int main()
{
    wchar_t szPath[MAX_PATH];

    if(SUCCEEDED(SHGetFolderPath(NULL,
                                 CSIDL_DESKTOPDIRECTORY |CSIDL_FLAG_CREATE,
                                 NULL,
                                 0,
                                 szPath)))
    {
        PathAppend(szPath, "data.txt");
        HANDLE hFile = CreateFile(szPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            printf("Nie mozna otworzyc pliku");
            return;
        }

        SYSTEMTIME st, lt;

        GetSystemTime(&st);
        GetLocalTime(&lt);

        char systemTime[100] = "";
        char localTime[100] = "\n";

        sprintf(systemTime,"systemowy: %d-%d-%d, %d:%d:%d", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond);
        sprintf(localTime,"\r\nlokalny: %d-%d-%d, %d:%d:%d", lt.wDay, lt.wMonth, lt.wYear, lt.wHour, lt.wMinute, lt.wSecond);

        DWORD written = 0;
        BOOL error = WriteFile(hFile, systemTime, strlen(systemTime), &written, NULL);
        BOOL error2 = WriteFile(hFile, localTime, strlen(localTime), &written, NULL);
        if(error == FALSE || error2 == FALSE)
        {
            printf("Nie mozna zapisac do pliku\n");
        }
    }

    return 0;
}
