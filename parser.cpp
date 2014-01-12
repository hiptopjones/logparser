// Copyright (c) 2014, Peter James

#include "precomp.h"

SqlLexer::SqlLexer(std::wstring strQuery)
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

        while (true)
        {
            ch = psz[i++];

            if (state == STATE_NONE)
            {
                if (iswalpha(ch) || ch == L'_')
                {
                    token.Index = start;
                    token.Type = TOKEN_KEYWORD;

                    state = STATE_KEYWORD;
                    continue;
                }
                if (iswdigit(ch))
                {
                    token.Index = start;
                    token.Type = TOKEN_NUMBER;

                    state = STATE_NUMBER;
                    continue;
                }
                else if (ch == L'\'')
                {
                    token.Index = start;
                    token.Type = TOKEN_STRING;

                    state = STATE_STRING;
                    continue;
                }
                else if (ch == L'=')
                {
                    token.Index = start;
                    token.Type = TOKEN_EQUAL;

                    break;
                }
                else if (ch == L',')
                {
                    token.Index = start;
                    token.Type = TOKEN_COMMA;

                    break;
                }
                else if (iswspace(ch))
                {
                    token.Index = start;
                    token.Type = TOKEN_WHITESPACE;

                    state = STATE_WHITESPACE;
                    continue;
                }
                else
                {
                    token.Index = start;
                    token.Type = TOKEN_ERROR;
                    token.Value = m_strQuery.substr(start, 1);
                    break;
                }
            }
            else if (state == STATE_KEYWORD)
            {
                // First character must be letter or underscore, but rest can be
                // letter, number or underscore
                if (!iswalnum(ch) && ch != L'_')
                {
                    i--;
                    token.Value = m_strQuery.substr(start, i - start);
                    break;
                }
            }
            else if (state == STATE_NUMBER)
            {
                if (!iswdigit(ch))
                {
                    i--;
                    token.Value = m_strQuery.substr(start, i - start);
                    break;
                }
            }
            else if (state == STATE_STRING)
            {
                // TODO: Allow escaping quotes in a string

                if (ch == L'\'')
                {
                    // Do not include the quotation/apostrophe characters in the value
                    start++;
                    token.Value = m_strQuery.substr(start, (i - 1) - start);
                    break;
                }
            }
            else if (state == STATE_WHITESPACE)
            {
                if (!iswspace(ch))
                {
                    i--;
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

