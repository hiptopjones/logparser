// Copyright (c) 2014, Peter James

#pragma once

// Support basic SQL query:
// SELECT field1, field2 FROM file WHERE fieldN = ""
// http://sqlite.org/lang_select.html

enum SqlTokenType
{
    // Special tokens
    TOKEN_ERROR = -1,
    TOKEN_EOF = 0,

    TOKEN_IDENTIFIER,
    TOKEN_STRING,
    TOKEN_NUMBER,
    TOKEN_WHITESPACE,

    TOKEN_EQUAL,
    TOKEN_LESSTHAN,
    TOKEN_GREATERTHAN,
    TOKEN_LESSTHANOREQUAL,
    TOKEN_GREATERTHANOREQUAL,
    TOKEN_COMMA,
    TOKEN_SEMICOLON,

    TOKEN_SELECT,
    TOKEN_FROM,
    TOKEN_WHERE,
    TOKEN_AS,
};

enum SqlLexerState
{
    STATE_NONE = 0,

    STATE_IDENTIFIER,
    STATE_NUMBER,
    STATE_STRING,
    STATE_PUNCTUATION,
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

// http://dragonbook.stanford.edu/lecture-notes/Stanford-CS143/03-Lexical-Analysis.pdf
// http://ee.hawaii.edu/~tep/EE160/Book/chap14/subsection2.1.1.5.html
class SqlLexer
{
public:
    SqlLexer(const std::wstring& strQuery);

    SqlToken NextToken();

    static SqlTokenType GetIdentifierTokenType(const std::wstring& strValue);
    static SqlTokenType GetPunctuationTokenType(const std::wstring& strValue);

private:
    std::wstring m_strQuery;
    int m_currentIndex;
};
