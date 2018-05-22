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
#ifndef QCOMMANDEDIT_H
#define QCOMMANDEDIT_H

#include <QLineEdit>
#include <QStringList>

class QCommandEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit QCommandEdit(QWidget *parent = nullptr);

    void setShowMatchingHistory(bool show);
    void setAutoAcceptLongestCommonCompletionPrefix(bool accept);

    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);

public Q_SLOTS:
    void clear();
    void setHistory(const QStringList &history);
    void navigateHistory(int delta);
    void setHistoryIndex(int index);
    void insertTextAtCursor(const QString &txt, bool selected);
    void setCompletion(const QStringList &completion);
    void resetCompletion();
    void setCurrentCompletion(const QString &s);
    void navigateCompletion(int delta);
    void acceptCompletion();
    void cancelCompletion();
    void setToolTipAtCursor(const QString &tip);
    void moveCursorToEnd();

Q_SIGNALS:
    void execute(const QString &cmd);
    void askCompletion(const QString &cmd, int cursorPos);
    void escape();
    void escapePressed();
    void upPressed();
    void downPressed();
    void tabPressed();
    void shiftTabPressed();

private Q_SLOTS:
    void onReturnPressed();
    void onEscapePressed();
    void onUpPressed();
    void onDownPressed();
    void onTabPressed();
    void onShiftTabPressed();
    void onSelectionChanged();
    void onCursorPositionChanged(int old, int now);
    void onTextEdited();

private:
    struct HistoryState
    {
        QStringList history_;
        int index_;
        QString prefixFilter_;

        void reset();
    } historyState_;

    struct CompletionState
    {
        QStringList completion_;
        bool requested_;
        int index_;

        void reset();
    } completionState_;

    void searchMatchingHistoryAndShowGhost();

    bool showMatchingHistory_;
    bool autoAcceptLongestCommonCompletionPrefix_;
    QString ghostSuffix_; // for showing matching history
};

#endif // QCOMMANDEDIT_H
