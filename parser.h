// Copyright (c) 2014, Peter James

#pragma once

class SqlParser
{
public:
    SqlParser(SqlLexer* pLexer);

private:
    SqlLexer* m_pLexer;
};
