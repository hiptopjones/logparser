// Copyright (c) 2014, Peter James

#include "precomp.h"

SqlLexer::SqlLexer(const std::wstring& strQuery)
    : m_strQuery(strQuery),
      m_currentIndex(0)
{

}

SqlToken SqlLexer::NextToken()
{
    SqlToken token;

    int i = m_currentIndex;
    size_t len = m_strQuery.size();
    const wchar_t* psz = m_strQuery.c_str();

    if (i >= len)
    {
        token.Type = TOKEN_EOF;
        token.Index = i;
    }
    else
    {
        int start = i;
        wchar_t ch = L'\0';

        SqlLexerState state = STATE_NONE;

        token.Index = start;

        while (true)
        {
            ch = psz[i++];

            if (state == STATE_NONE)
            {
                if (iswalpha(ch) || ch == L'_')
                {
                    state = STATE_IDENTIFIER;
                }
                else if (iswdigit(ch) || ch == L'-')
                {
                    state = STATE_NUMBER;
                }
                else if (ch == L'\'')
                {
                    state = STATE_STRING;
                }
                else if (iswpunct(ch))
                {
                    state = STATE_PUNCTUATION;
                }
                else if (iswspace(ch))
                {
                    state = STATE_WHITESPACE;
                }
                else
                {
                    token.Type = TOKEN_ERROR;
                    token.Value = m_strQuery.substr(start, 1);
                    break;
                }
            }
            else if (state == STATE_IDENTIFIER)
            {
                // First character must be letter or underscore, but rest can be
                // letter, number or underscore
                if (!iswalnum(ch) && ch != L'_')
                {
                    i--;
                    token.Value = m_strQuery.substr(start, i - start);
                    token.Type = GetIdentifierTokenType(token.Value);
                    break;
                }
            }
            else if (state == STATE_NUMBER)
            {
                if (!iswdigit(ch))
                {
                    i--;
                    token.Value = m_strQuery.substr(start, i - start);
                    token.Type = TOKEN_NUMBER;
                    break;
                }
            }
            else if (state == STATE_STRING)
            {
                // TODO: Allow escaping quotes in a string

                if (ch == L'\'')
                {
                    
                    start++; // Do not include the quotation/apostrophe characters in the value
                    token.Value = m_strQuery.substr(start, (i - 1) - start);
                    token.Type = TOKEN_STRING;
                    break;
                }
            }
            else if (state == STATE_PUNCTUATION)
            {
                if (!iswpunct(ch))
                {
                    i--;
                    token.Value = m_strQuery.substr(start, i - start);
                    token.Type = GetPunctuationTokenType(token.Value);
                    break;
                }
            }
            else if (state == STATE_WHITESPACE)
            {
                if (!iswspace(ch))
                {
                    i--;
                    token.Value = m_strQuery.substr(start, i - start);
                    token.Type = TOKEN_WHITESPACE;
                    break;
                }
            }
        }

        m_currentIndex = i;
    }

    // Ignore whitespace, return next token instead
    if (token.Type == TOKEN_WHITESPACE)
    {
        token = NextToken();
    }

    return token;
}

SqlTokenType SqlLexer::GetIdentifierTokenType(const std::wstring& strValue)
{
    if (strValue == L"SELECT")
    {
        return TOKEN_SELECT;
    }
    else if (strValue == L"FROM")
    {
        return TOKEN_FROM;
    }
    else if (strValue == L"WHERE")
    {
        return TOKEN_WHERE;
    }
    else if (strValue == L"AS")
    {
        return TOKEN_AS;
    }
    else
    {
        return TOKEN_IDENTIFIER;
    }
}

SqlTokenType SqlLexer::GetPunctuationTokenType(const std::wstring& strValue)
{
    if (strValue == L"=")
    {
        return TOKEN_EQUAL;
    }
    else if (strValue == L"<")
    {
        return TOKEN_LESSTHAN;
    }
    else if (strValue == L"<=")
    {
        return TOKEN_LESSTHANOREQUAL;
    }
    else if (strValue == L">")
    {
        return TOKEN_GREATERTHAN;
    }
    else if (strValue == L">=")
    {
        return TOKEN_GREATERTHANOREQUAL;
    }
    else if (strValue == L",")
    {
        return TOKEN_COMMA;
    }
    else if (strValue == L";")
    {
        return TOKEN_SEMICOLON;
    }
    else
    {
        return TOKEN_ERROR;
    }
}

