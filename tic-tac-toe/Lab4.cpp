
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

    void PrintResult(int i)
    {
        cout << i / PlayField::getSize() << ' ' << i % PlayField::getSize() << endl;
        cout << "win " << win << " lose " << lose << " draw " << draw << endl;
    }
};

Result FillRoot(TreeNode& root, Result& result)
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
    for(auto cell : nowField.getEmptyCells())
    {
        TreeNode newChild(nowField.makeMove(cell));
        root.addChild(&newChild);
        result = FillRoot(newChild, result);
    }
    return result;
}

void СalculationOutcomeGame(TreeNode& root)
{
    Result total;
    auto nowField = root.value();
    vector<Result> results;
    for (auto cell : nowField.getEmptyCells())
    {
        Result result;
        TreeNode newChild(nowField.makeMove(cell));
        root.addChild(&newChild);
        FillRoot(newChild, result);
        total += result;
        result.PrintResult(cell.convertToInt());
    }    
    cout << "total " << "win " << total.win << " lose " << total.lose << " draw " << total.draw << endl;
}

int main()
{
    PlayField playfield;
    TreeNode root(playfield);
    СalculationOutcomeGame(root);
    return 0;
}

