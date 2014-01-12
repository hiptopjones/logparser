// Copyright (c) 2014, Peter James

#pragma once

// Support basic SQL query:
// SELECT field1, field2 FROM file WHERE fieldN = ""

enum SqlTokenType
{
    // Special tokens
    TOKEN_ERROR = -1,
    TOKEN_EOF = 0,

    // Value tokens (have value)
    TOKEN_KEYWORD,
    TOKEN_STRING,
    TOKEN_NUMBER,
    TOKEN_WHITESPACE,

    // Indicator tokens (no value)
    TOKEN_COMMA,
    TOKEN_EQUAL,
};

enum SqlLexerState
{
    STATE_NONE = 0,

    STATE_KEYWORD,
    STATE_NUMBER,
    STATE_STRING,
    STATE_WHITESPACE,
};

struct SqlToken
{
    // Default constructor to ensure initialized
    SqlToken()
        : Type(TOKEN_ERROR),
          Index(0)
    {
    }

    // Type of the token
    SqlTokenType Type;

    // Raw value of the token
    std::wstring Value;

    // Character index of the token
    int Index;
};

class SqlLexer
{
public:
    SqlLexer(std::wstring strQuery);

    SqlToken NextToken();

private:
    std::wstring m_strQuery;
    int m_currentIndex;
};
