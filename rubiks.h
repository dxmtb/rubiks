//
//  rubiks.h
//  Rubiks
//
//  Created by 田 博 on 12-12-8.
//  Copyright (c) 2012年 田 博. All rights reserved.
//

#ifndef __Rubiks__rubiks__
#define __Rubiks__rubiks__

#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

#define _DEBUG

enum Side{
    Right = 0,
    Left = 1,
    Up = 2,
    Down = 3,
    Front = 4,
    Back = 5
};

inline Side opposite(const Side &s)
{
    return (Side)((int)s^1);
}

enum Color{
    White = 0,
    Blue = 1,
    Orange = 2,
    Green = 3,
    Red = 4,
    Yellow = 5
};

struct Edge
{
    int x, y;
    Edge(int _x = 0, int _y = 0):x(_x), y(_y){}
};

class Rubiks
{
public:
    Rubiks();
    Rubiks(int data[6][3][3]);
    int data[6][3][3];
    Color init_front, init_right;
    void R();
    void Ri();
    void L();
    void Li();
    void U();
    void Ui();
    void D();
    void Di();
    void F();
    void Fi();
    void B();
    void Bi();
    void print_state();
    void FtoR();
    void FtoL();
    void FtoU();
    void FtoD();
    void change_vp(Side side1, Side side2);
    void change_vp(Color color1, Color color2);
    Edge find_edge_piece(Color color1, Color color2);
    void shuffle();
    bool output;
private:
    void _right_element_circle(vector<int*> &all);
    void _Rotate(const vector<int*> &all,int gap);
    void side_circle(vector<int*> &all, Side side);
    void output_R(Rubiks*);
    bool same_data(const int data1[][3][3], const int data2[][3][3]);
};

typedef void (Rubiks::*Opt_ptr)();

#endif /* defined(__Rubiks__rubiks__) */
