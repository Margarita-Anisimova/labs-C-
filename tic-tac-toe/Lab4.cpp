
// Анисимова М.В. РИ-280001
//#include "stdafx.h"
#include <iostream>
#include "PlayField.h"
#include "TreeNode.h"
#include <string>

using namespace std;

struct Result
{
    int win=0;
    int lose = 0;
    int draw=0;

    Result operator+=(const Result& nowResult)
    {
        win += nowResult.win;
        lose += nowResult.lose;
        draw += nowResult.draw;
        return *this;
    }
};

Result FillRoot(TreeNode& root, Result& result)
{
    if (root.isTerminal())
        return result;
    for (auto cell : root.value().getEmptyCells())
    {
        root.addChild(new TreeNode(root.value().makeMove(cell)));
        FillRoot(root[root.childCount() - 1]);
    }
    return;
}

void СalculationOutcomeGame(TreeNode& root, Result& result)
{
    if (root.isTerminal())
    {
        auto field = root.value();
        switch (field.checkFieldStatus())
        {
        case PlayField::fsCrossesWin:
            result.win++;
            break;
        case PlayField::fsNoughtsWin:
            result.lose++;
            break;
        case PlayField::fsDraw:
            result.draw++;
            break;
        default:
            break;
        }
        return;
    }
    for (int i = 0; i < root.childCount(); i++)
        СalculationOutcomeGame(root[i], result);
    return;
}

void PrintResult(int pos, Result result)
{
    int s = PlayField::getSize();
    for (int i = 0; i < s * s; i++)
    {
        if (i % 3 == 0)
            cout << endl;
        if (i == pos)
            cout << "|X|";
        else
            cout << "| |";
    }
    cout << endl << "win " << result.win << " lose " << result.lose << " draw " << result.draw << endl;
}

int main()
{
    Result total;
    PlayField playfield;
    TreeNode root(playfield);
    FillRoot(root);
    for (int i = 0; i < root.childCount(); i++)
    {
        Result result;
        СalculationOutcomeGame(root[i], result);
        total += result;
        PrintResult(i, result);
    }
    cout << "total " << "win " << total.win << " lose " << total.lose << " draw " << total.draw << endl;
}

