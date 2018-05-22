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
#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

#include "qcommandtokenizer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if defined(TEST_SIMPLE_TOKENIZER)
    QString cmd = "  foo bar  baz";
    QSimpleCommandTokenizer t;
    t.setCommand(cmd);
    qDebug() << "command: " << cmd;
    for(const QCommandTokenizer::Token &tok : t.getTokens())
        qDebug() << tok.token_ << tok.start_ << tok.end_;
    qDebug() << "token at 9: " << t.getTokenAtCharPos(9).token_;
    return 0;
#else
    MainWindow w;
    w.show();

    return a.exec();
#endif
}
