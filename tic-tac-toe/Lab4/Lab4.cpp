
// Анисимова М.В. РИ-280001
//#include "stdafx.h"
#include <iostream>
#include "PlayField.h"
#include "TreeNode.h"
#include <string>


using namespace std;

struct Result
{
    int win;
    int lose;
    int draw;

    Result& operator+=(const Result& nowResult)
    {
        win += nowResult.win;
        lose += nowResult.lose;
        draw += nowResult.draw;
        return *this;
    }

    void PrintRerult(int i)
    {
        cout << i / 3 << ' ' << i % 3 << endl;
        cout << "win " << win << " lose " << lose << " draw " << draw << endl;
    }

};

Result FillRoot(TreeNode root, Result result)
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
        return result;
    }

    auto nowField = root.value();
    for (int i = 0; i < 9; ++i)
    {
        PlayField::CellIdx cell(i / 3, i % 3);
        if (nowField[cell] == PlayField::csEmpty)
        {
            TreeNode newChild(&nowField.makeMove(cell), &root);
            root.addChild(newChild);
            result = FillRoot(newChild, result);
        }
    }
    return result;
}


void СalculationOutcomeGame(TreeNode root)
{
    Result total;
    for (int i = 0; i < 9; ++i)
    {
        Result result = { 0,0,0 };
        auto nowField = root.value();
        PlayField::CellIdx cell(i / 3, i % 3);
        if (nowField[cell] == PlayField::csEmpty)
        {
            TreeNode newChild(&nowField.makeMove(cell), &root);
            root.addChild(newChild);
            result = FillRoot(newChild, result);
            total += result;
            result.PrintRerult(i);
        }
    }
    cout << "total " << "win " << total.win << " lose " << total.lose << " draw " << total.draw << endl;
}

int main()
{
    PlayField playfield;
    TreeNode root(&playfield, nullptr);
    СalculationOutcomeGame(root);
    return 0;
}