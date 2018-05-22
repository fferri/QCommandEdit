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
#ifndef QCOMMANDTOKENIZER_H
#define QCOMMANDTOKENIZER_H

#include <QString>
#include <QList>

class QCommandTokenizer
{
public:
    virtual ~QCommandTokenizer() {}

    struct Token
    {
        QString token_;
        int type_;
        int start_;
        int end_;

        bool overlaps(int index) const;
    };

    void setCommand(const QString &cmd);
    QList<QCommandTokenizer::Token> getTokens() const;
    QCommandTokenizer::Token getTokenAtCharPos(int index) const;
    void clear();

protected:
    virtual void tokenize() = 0;

    QString command_;
    QList<Token> tokens_;
};

class QSimpleCommandTokenizer : public QCommandTokenizer
{
protected:
    virtual bool isSeparator(QChar c) const;
    void tokenize();
};

#endif // QCOMMANDTOKENIZER_H
