#include <Windows.h>
#include <Ntsecapi.h>
#include <wchar.h>
#include <stdio.h>
#include <stdbool.h>

bool HasMinimumLength(const WCHAR* password)
{
    return wcslen(password) >= 10;
}

bool HasSpecialCharacter(const WCHAR* password)
{
    for (const WCHAR* ch = password; *ch != L'\0'; ch++)
    {
        if (iswgraph(*ch) && !iswalnum(*ch))
        {
            return true;
        }
    }
    return false;
}

bool HasNumber(const WCHAR* password)
{
    for (const WCHAR* ch = password; *ch != L'\0'; ch++)
    {
        if (iswdigit(*ch))
        {
            return true;
        }
    }
    return false;
}

bool HasUppercase(const WCHAR* password)
{
    for (const WCHAR* ch = password; *ch != L'\0'; ch++)
    {
        if (iswupper(*ch))
        {
            return true;
        }
    }
    return false;
}

BOOL FilterPassword(PUNICODE_STRING AccountName, PUNICODE_STRING FullName, PUNICODE_STRING Password, BOOLEAN SetOperation)
{
    UNREFERENCED_PARAMETER(SetOperation);

    WCHAR passwordString[MAX_PATH + 1] = { 0 };
    WCHAR accountNameString[MAX_PATH + 1] = { 0 };
    WCHAR fullNameString[MAX_PATH + 1] = { 0 };

    wcsncpy_s(passwordString, MAX_PATH, Password->Buffer, Password->Length / sizeof(WCHAR));
    wcsncpy_s(accountNameString, MAX_PATH, AccountName->Buffer, AccountName->Length / sizeof(WCHAR));
    wcsncpy_s(fullNameString, MAX_PATH, FullName->Buffer, FullName->Length / sizeof(WCHAR));
    _wcslwr_s(passwordString, MAX_PATH);
    _wcslwr_s(accountNameString, MAX_PATH);
    _wcslwr_s(fullNameString, MAX_PATH);

    if (!HasMinimumLength(passwordString))
    {
        return FALSE;
    }

    if (!HasSpecialCharacter(passwordString))
    {
        return FALSE;
    }

    if (!HasNumber(passwordString))
    {
        return FALSE;
    }

    if (!HasUppercase(passwordString))
    {
        return FALSE;
    }

    FILE* file;
    if (_wfopen_s(&file, L"C:\\Private\\filter.txt", L"r") == 0)
    {
        wchar_t forbiddenPassword[MAX_PATH];
        while (fgetws(forbiddenPassword, MAX_PATH, file) != NULL)
        {
            wchar_t* newlinePos = wcschr(forbiddenPassword, L'\n');
            if (newlinePos != NULL)
            {
                *newlinePos = L'\0';
            }

            if (wcsstr(passwordString, forbiddenPassword) != NULL)
            {
                fclose(file);
                return FALSE;
            }
        }

        fclose(file);
    }

    if (wcsstr(passwordString, accountNameString) != NULL ||
        wcsstr(passwordString, fullNameString) != NULL)
    {
        return FALSE;
    }

    return TRUE;
}