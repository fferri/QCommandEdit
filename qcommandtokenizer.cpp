/* QCommandEdit - a widget for entering commands, with completion and history
 * Copyright (C) 2018 Federico Ferri
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "qcommandtokenizer.h"

bool QCommandTokenizer::Token::overlaps(int index) const
{
    return start_ <= index && index <= end_;
}

void QCommandTokenizer::setCommand(const QString &cmd)
{
    clear();
    command_ = cmd;
    tokenize();
}

QList<QCommandTokenizer::Token> QCommandTokenizer::getTokens() const
{
    QList<QCommandTokenizer::Token> tokens;
    for(const Token &t : tokens_)
        tokens << t;
    return tokens;
}

QCommandTokenizer::Token QCommandTokenizer::getTokenAtCharPos(int index) const
{
    if(index < 0 || index > command_.length())
        throw "Character index out of bounds";

    for(const Token &t : tokens_)
    {
        if(t.overlaps(index))
            return t;
    }

    throw "No token";
}

void QCommandTokenizer::clear()
{
    command_ = "";
    tokens_.clear();
}

bool QSimpleCommandTokenizer::isSeparator(QChar c) const
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

void QSimpleCommandTokenizer::tokenize()
{
    Token cur;
    cur.type_ = cur.start_ = cur.end_ = 0;

    int n = command_.length();
    for(int i = 0; i <= n; i++)
    {
        QChar c = i < n ? command_.at(i) : ' ';
        if(i == n || isSeparator(c))
        {
            if(!cur.token_.isEmpty())
            {
                cur.end_ = i;
                tokens_.append(cur);
                cur.token_ = "";
            }
            cur.start_ = cur.end_ = i + 1;
        }
        else
        {
            cur.token_.append(c);
        }
    }
}
