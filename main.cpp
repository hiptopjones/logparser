// Copyright (c) 2014, Peter James

#include "precomp.h"

// Basic structure looks like a pipeline:
//      Input -> Tuple Stream -> Filter/Selection -> Tuple Stream -> Output
// Input is anything that can turned into a stream of tuples
// Additional stages may be added to the pipeline for sorting, grouping, joining, etc.

// http://stackoverflow.com/questions/14995074/c-sql-parser-to-a-table
// http://www.garshol.priv.no/download/text/bnf.html

void DumpToken(const SqlToken& token);

int main()
{
    std::wstring value = L"Hello, world!";
    std::wcout << "My message to you is '" << value.c_str() << "'...\n";

    SqlLexer lex(L"SELECT field1, field2 FROM file WHERE fieldN = ''");

    while (true)
    {
        SqlToken token = lex.NextToken();

        if (token.Type == TOKEN_EOF)
        {
            std::wcout << "Lexing complete" << "\n";
            break;
        }

        DumpToken(token);
    }

    return 0;
}

void DumpToken(const SqlToken& token)
{
    switch (token.Type)
    {
        case TOKEN_SELECT:
            std::wcout << "TOKEN_SELECT: " << "\n";
            break;

        case TOKEN_FROM:
            std::wcout << "TOKEN_FROM: " << "\n";
            break;

        case TOKEN_WHERE:
            std::wcout << "TOKEN_WHERE " << "\n";
            break;

        case TOKEN_AS:
            std::wcout << "TOKEN_AS " << "\n";
            break;

        case TOKEN_IDENTIFIER:
            std::wcout << "TOKEN_IDENTIFIER: " << token.Value << "\n";
            break;

        case TOKEN_STRING:
            std::wcout << "TOKEN_STRING: '" << token.Value << "'\n";
            break;

        case TOKEN_NUMBER:
            std::wcout << "TOKEN_NUMBER: " << token.Value << "\n";
            break;

        case TOKEN_WHITESPACE:
            std::wcout << "TOKEN_WHITESPACE" << "\n";
            break;

        case TOKEN_COMMA:
            std::wcout << "TOKEN_COMMA" << "\n";
            break;

        case TOKEN_SEMICOLON:
            std::wcout << "TOKEN_SEMICOLON" << "\n";
            break;

        case TOKEN_EQUAL:
            std::wcout << "TOKEN_EQUAL" << "\n";
            break;

        case TOKEN_LESSTHAN:
            std::wcout << "TOKEN_LESSTHAN" << "\n";
            break;

        case TOKEN_GREATERTHAN:
            std::wcout << "TOKEN_GREATERTHAN" << "\n";
            break;

        case TOKEN_LESSTHANOREQUAL:
            std::wcout << "TOKEN_LESSTHANOREQUAL" << "\n";
            break;

        case TOKEN_GREATERTHANOREQUAL:
            std::wcout << "TOKEN_GREATERTHANOREQUAL" << "\n";
            break;

        case TOKEN_ERROR:
            std::wcout << "Syntax error: unexpected '" << token.Value.c_str() <<
                "' at column " << token.Index << "\n";
            break;

        default:
            std::wcout << "Unknown token: " << token.Type << " value: '" <<
                token.Value.c_str() << "' at column " << token.Index << "\n";
            break;
    }
}
