
// Анисимова М.В. РИ-280001
//#include "stdafx.h"
#include <iostream>
#include "PlayField.h"
#include "TreeNode.h"
#include "XOPlayer.h"
#include "Score.h"
#include <string>

using namespace std;

void FillRoot(TreeNode& root)
{
    if (root.isTerminal())
        return;
    for (auto cell : root.value().getEmptyCells())
    {
        root.addChild(new TreeNode(root.value().makeMove(cell)));
        FillRoot(root[root.childCount() - 1]);
    }
    return;
}

Score СalculationOutcomeGame(TreeNode& root)
{
    if (root.isTerminal())
    {
        auto field = root.value();
        switch (field.checkFieldStatus())
        {
        case PlayField::fsCrossesWin:
            return Score(1,0,0);
        case PlayField::fsNoughtsWin:
            return Score(0, 1, 0);
        case PlayField::fsDraw:
            return Score(0, 0, 1);
        }
    }
    for (int i = 0; i < root.childCount(); i++)
    {
        root.score += СalculationOutcomeGame(root[i]);       
    }
    return root.score;
}

void PrintField(PlayField field)
{
    int s = PlayField::getSize();
    for (int i = 0; i < s; i++)
    {
        for (int j = 0; j < s; j++)
        {
            switch (field[PlayField::CellIdx(i, j)])
            {
            case PlayField::csCross:
                cout << "|X|";
                break;
            case PlayField::csNought:
                cout << "|0|";
                break;
            case PlayField::csEmpty:
                cout << "| |";
                break;
            }
        }
        cout << endl;
    }
}

int main()
{
    PlayField playfield;
    TreeNode root(playfield);
    FillRoot(root);
    СalculationOutcomeGame(root);
    std::cout << "Select player (0 - Xs, 1 - Os)" << std::endl;
    int sel_player;
    cin >> sel_player;
    XOPlayer player(&root, (sel_player != 0 ? PlayField::csCross : PlayField::csNought));
    if (player.selectPlayer() == PlayField::csCross)
        player.makeMove();
    PrintField(player.currentState());
    while (player.fieldStatus() == PlayField::fsNormal)
    {
        int x;
        int y;
        std::cout << "Make move, enter the cell coordinates separated by a space: X Y" << std::endl;
        cin >> x >> y;
        try
        {
            player.makeMove(PlayField::CellIdx(x - 1, y - 1));
            player.makeMove();
        }
        catch (int i)
        {
            cout << "this cell is already occupied" << endl;
        }
        PrintField(player.currentState());
    }
    cout << endl << "game over winner: ";
    switch (player.fieldStatus())
    {
    case PlayField::fsDraw:
        cout << "draw";
        break;
    case PlayField::fsCrossesWin:
        cout << "crosss";
        break;
    case PlayField::fsNoughtsWin:
        cout << "noughts";
        break;
    }
    return 0;
}

