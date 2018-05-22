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
#include "ui_mainwindow.h"
#include "qcommandtokenizer.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->commandEdit, &QCommandEdit::execute, this, &MainWindow::onExecute);
    connect(ui->commandEdit, &QCommandEdit::askCompletion, this, &MainWindow::onAskCompletion);
    connect(ui->commandEdit, &QCommandEdit::escape, this, &MainWindow::onEscape);

    history_ << "break if x == 1"
             << "lambda x: try import foo else return"
             << "local y"
             << "raise Exception(...)"
             << "return 0"
             << "while x > 0: print(x); x += 1"
             << "for i in range(100): print(i)";
    ui->commandEdit->setHistory(history_);
    ui->commandEdit->setShowMatchingHistory(true);
    for(const QString &h : history_)
        ui->textCmdLog->append(h);

    words_ << "True" << "False" << "None" << "and" << "as" << "assert"
          << "break" << "class" << "continue" << "def" << "del" << "elif"
          << "else" << "except" << "finally" << "for" << "from" << "global"
          << "if" << "import" << "in" << "is" << "lambda" << "local"
          << "not" << "or" << "pass" << "raise" << "return" << "try"
          << "while" << "with" << "yield";

    ui->listWords->addItems(words_);

    ui->commandEdit->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onExecute(const QString &s)
{
    history_.append(s);
    ui->textCmdLog->append(s);
    ui->commandEdit->clear();
    ui->commandEdit->setHistory(history_);
}

void MainWindow::onAskCompletion(const QString &cmd, int cursorPos)
{
    QSimpleCommandTokenizer t;
    t.setCommand(cmd);
    try
    {
        QCommandTokenizer::Token tok = t.getTokenAtCharPos(cursorPos);

        if(cursorPos != tok.end_)
            throw "Not completing at middle of token";

        QStringList comp;
        for(const QString &w : words_)
            if(w.startsWith(tok.token_))
                comp << w.mid(tok.token_.length());

        ui->commandEdit->setCompletion(comp);

        qDebug() << "Completion:" << comp;
    }
    catch(const char *ex)
    {
        qDebug() << ex;
        return;
    }
}

void MainWindow::onEscape()
{
    qDebug() << "Escape!";
}
