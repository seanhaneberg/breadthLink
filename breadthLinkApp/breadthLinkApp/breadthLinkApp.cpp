// breadthLinkApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include <string>
#include <math.h>


struct BNode
{
    std::string name;
    BNode* left;
    BNode* right;
    BNode* sibling;
};

void PrintTree(BNode* tree, unsigned int printLevel = 0)
{
    if (!tree)
    {
        return;
    }

    if (printLevel > 0)
    {
        printf("+");
    }

    for (unsigned int i = 0; i < printLevel; i++)
    {
        printf("---");
    }

    if (printLevel > 0)
    {
        printf("| ");
    }

    std::string output = "Name: " + tree->name;
    output += (tree->sibling ? " : Sibling: " + tree->sibling->name : "");
    output += "\n";

    printf("%s", output.c_str());

    unsigned int nextLevel = printLevel + 1;
    PrintTree(tree->left, nextLevel);
    PrintTree(tree->right, nextLevel);
}

char g_nextLetter = 'A';
int suffixCount = 0;

std::string GetNextName()
{
    std::string ret = "";

    ret += g_nextLetter;

    for (int i = 0; i < suffixCount; i++)
    {
        ret += g_nextLetter;
    }

    if (g_nextLetter >= 'Z')
    {
        g_nextLetter = 'A';
        suffixCount++;
    }
    else
    {
        g_nextLetter++;
    }


    return ret;
}

// out of 100
const unsigned int g_NodeCreationChance = 80;
const unsigned int g_NodeCreationDenominator = 100;

void GenerateBinaryTree(BNode** tree)
{
    if (!tree)
    {
        return;
    }

    *tree = new BNode();
    BNode* pTree = *tree;
    pTree->name = GetNextName();

    pTree->sibling = nullptr;

    // Left chance!
    if (((rand() * g_NodeCreationDenominator) / RAND_MAX) >= g_NodeCreationChance)
    {
        GenerateBinaryTree(&(pTree->left));
    }
    else
    {
        pTree->left = nullptr;
    }

    // Right chance!
    if (((rand() * g_NodeCreationDenominator) / RAND_MAX) <= g_NodeCreationChance)
    {
        GenerateBinaryTree(&(pTree->right));
    }
    else
    {
        pTree->right = nullptr;
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    BNode* tree = new BNode();

    GenerateBinaryTree(&tree);
    PrintTree(tree);

    printf("\n\nPress Any Key to Continue");
    getchar();
    return 0;
}

