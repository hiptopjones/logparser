// Copyright (c) 2014, Peter James

#include "precomp.h"

// Basic structure looks like a pipeline:
//      Input -> Tuple Stream -> Filter/Selection -> Tuple Stream -> Output
// Input is anything that can turned into a stream of tuples
// Additional stages may be added to the pipeline for sorting, grouping, joining, etc.

// http://stackoverflow.com/questions/14995074/c-sql-parser-to-a-table

int main()
{
    std::wstring value = L"Hello, world!";
    std::wcout << "My message to you is '" << value.c_str() << "'...\n";

    SqlLexer lex(L"SELECT field1, field2 FROM file WHERE fieldN = ''");

    while (true)
    {
        SqlToken token = lex.NextToken();

        if (token.Type == TOKEN_ERROR)
        {
            std::wcout << "Syntax error: unexpected '" << token.Value.c_str() << "' at column " << token.Index << "\n";
            break;
        }
        else if (token.Type == TOKEN_KEYWORD)
        {
            std::wcout << "TOKEN_KEYWORD: " << token.Value << "\n";
        }
        else if (token.Type == TOKEN_STRING)
        {
            std::wcout << "TOKEN_STRING: " << token.Value << "\n";
        }
        else if (token.Type == TOKEN_NUMBER)
        {
            std::wcout << "TOKEN_NUMBER: " << token.Value << "\n";
        }
        else if (token.Type == TOKEN_WHITESPACE)
        {
            std::wcout << "TOKEN_WHITESPACE" << "\n";
        }
        else if (token.Type == TOKEN_COMMA)
        {
            std::wcout << "TOKEN_COMMA" << "\n";
        }
        else if (token.Type == TOKEN_EQUAL)
        {
            std::wcout << "TOKEN_EQUAL" << "\n";
        }
        else if (token.Type == TOKEN_EOF)
        {
            std::wcout << "Lexing complete" << "\n";
            break;
        }
    }

    return 0;
}
