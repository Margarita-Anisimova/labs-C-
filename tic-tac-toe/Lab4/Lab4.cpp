
// Анисимова М.В. РИ-280001
//#include "stdafx.h"
#include <iostream>
#include "PlayField.h"
#include "TreeNode.h"
#include <string>


using namespace std;

struct Counter
{
    int win = 0;
    int lose = 0;
    int draw = 0;
};

Counter FillRoot(TreeNode root, Counter counter)
{
    if (root.isTerminal())
    {
        auto field = root.value();
        switch (field.checkFieldStatus())
        {
        case PlayField::fsCrossesWin:
            counter.win++;
            break;
        case PlayField::fsNoughtsWin:
            counter.lose++;
            break;
        case PlayField::fsDraw:
            counter.draw++;
            break;
        default:
            break;
        }
        return counter;
    }

    auto nowField = root.value();
    for (int i = 0; i < 9; ++i)
    {
        PlayField::CellIdx cell(i / 3, i % 3);
        if (nowField[cell] == PlayField::csEmpty)
        {
            TreeNode newChild(&nowField.makeMove(cell), &root);
            root.addChild(newChild);
            counter = FillRoot(newChild, counter);
        }
    }
    return counter;
}

void PrintRerult(int i, Counter count)
{
    cout << i / 3 << ' ' << i % 3 << endl;
    cout << "win " << count.win << " lose " << count.lose<< " draw " << count.draw << endl;
}


void СalculationOutcomeGame(TreeNode root)
{
    Counter total;
    for (int i = 0; i < 9; ++i)
    {
        Counter counter;
        auto nowField = root.value();
        PlayField::CellIdx cell(i / 3, i % 3);
        if (nowField[cell] == PlayField::csEmpty)
        {
            TreeNode newChild(&nowField.makeMove(cell), &root);
            root.addChild(newChild);
            counter = FillRoot(newChild, counter);
            total.win += counter.win;
            total.lose += counter.lose;
            total.draw += counter.draw;
            PrintRerult(i, counter);
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





