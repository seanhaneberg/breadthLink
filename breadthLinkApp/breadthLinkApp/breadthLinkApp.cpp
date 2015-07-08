// breadthLinkApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include <string>
#include <math.h>
#include <time.h>
#include <queue>


struct BNode
{
    std::string name;
    BNode* left;
    BNode* right;
    BNode* sibling;
};

void PrintTree(BNode* tree, unsigned int printLevel = 0)
{
    for (unsigned int i = 0; i < printLevel; i++)
    {
        printf("   ");
    }

    if (printLevel > 0)
    {
        printf("+");
    }

    if (!tree)
    {
        printf("(null)\n");
        return;
    }

    std::string output = "";

    output += "(";
    output += std::to_string(printLevel);
    output += ")";
    output += "Name: " + tree->name;
    output += (tree->sibling ? " : Sibling: " + tree->sibling->name : "");
    output += "\n";

    printf("%s", output.c_str());

    unsigned int nextLevel = printLevel + 1;
    PrintTree(tree->right, nextLevel);

    PrintTree(tree->left, nextLevel);
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
const int g_NodeCreationChance = 55;
const int g_NodeCreationDenominator = 100;
const int g_maxLevel = 5;

bool DoGenerateNewNode(int level)
{
    if (level > g_maxLevel)
    {
        return false;
    }

    int r = rand();
    int percentageDecision = r * g_NodeCreationDenominator;
    percentageDecision = percentageDecision / RAND_MAX;

    if (percentageDecision > g_NodeCreationChance)
    {
        return false;
    }

    return true;
}

void GenerateBinaryTree(BNode** tree, int level = 0)
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
    if (DoGenerateNewNode(level))
    {
        GenerateBinaryTree(&(pTree->left), level + 1);
    }
    else
    {
        pTree->left = nullptr;
    }

    // Right chance!
    if (DoGenerateNewNode(level))
    {
        GenerateBinaryTree(&(pTree->right), level + 1);
    }
    else
    {
        pTree->right = nullptr;
    }
}

void DestroyTree(BNode** tree)
{
    if (!tree || !*tree)
    {
        return;
    }

    BNode* pTree = *tree;

    DestroyTree(&(pTree->left));
    DestroyTree(&(pTree->right));

    delete pTree;
    *tree = nullptr;
}


std::queue<BNode*> g_VisitQueue;
std::vector<BNode*> g_LeftSiblingStack;


void WireSiblings(BNode* tree)
{
    if (!tree)
    {
        return;
    }

    if (!g_LeftSiblingStack.empty())
    {
        BNode* sibling = g_LeftSiblingStack.back();
        tree->sibling = sibling;
        g_LeftSiblingStack.pop_back();
    }

    if (tree->left)
    {
        WireSiblings(tree->left);
    }

    g_LeftSiblingStack.push_back(tree->left);

    if (tree->right)
    {
        WireSiblings(tree->right);
    }

}

int _tmain(int argc, _TCHAR* argv[])
{
    BNode* tree = new BNode();

    srand((unsigned int)time(nullptr));
    GenerateBinaryTree(&tree);
    PrintTree(tree);
    WireSiblings(tree);
    printf("\n\nAfter wiring...\n");
    PrintTree(tree);
    printf("\n\nPress Any Key to Continue");
    DestroyTree(&tree);
    getchar();
    return 0;
}

