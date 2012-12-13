//
//  rubiks.cpp
//  Rubiks
//
//  Created by 田 博 on 12-12-8.
//  Copyright (c) 2012年 田 博. All rights reserved.
//

#include "rubiks.h"

static Opt_ptr opt_ptr1[6][2] = {&Rubiks::R, &Rubiks::Ri, &Rubiks::L, &Rubiks::Li, &Rubiks::U, &Rubiks::Ui,
    &Rubiks::D, &Rubiks::Di, &Rubiks::F, &Rubiks::Fi, &Rubiks::B, &Rubiks::Bi};


static Opt_ptr opt_ptr2[12] = {&Rubiks::R, &Rubiks::Ri, &Rubiks::L, &Rubiks::Li, &Rubiks::U, &Rubiks::Ui,
    &Rubiks::D, &Rubiks::Di, &Rubiks::F, &Rubiks::Fi, &Rubiks::B, &Rubiks::Bi};

Rubiks::Rubiks()
{
    int ncolor[6] = {Green, Blue, Orange, Red, Yellow, White};
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                data[i][j][k] = ncolor[i];
            }
        }
    }
    output = true;
    init_front = (Color)data[Front][1][1];
    init_right = (Color)data[Right][1][1];
}

Rubiks::Rubiks(int _data[6][3][3])
{
    memcpy(data, _data, sizeof(data));
    output = true;
    init_front = (Color)data[Front][1][1];
    init_right = (Color)data[Right][1][1];
}

//数组向右移动gap位
//顺时针移动gap=2、3 逆时针gap=-2、-3
void Rubiks::_Rotate(const vector<int*> &all,int gap)
{
    int size = (int)all.size();
    assert(size != 0);
    vector<int> val(size);
    for (int i = 0; i < size; i++) {
        val[i] = *all[i];
    }
    for (int i = 0; i < size; i++) {
        *all[i] = val[(i - gap + size)%size];
    }
}

//返回右边面上下前后周围形成的圈
void Rubiks::_right_element_circle(vector<int*> &all)
{
    all.clear();
    int seq[] = {Front, Up, Back, Down};
    for (int i = 0; i < 4; i++) {
        for (int j = 2; j >=0; j--) {
            all.push_back(&data[seq[i]][j][2]);
        }
    }
}

//返回某个面四周格子顺时针形成的圈
void Rubiks::side_circle(vector<int*> &all, Side side)
{
    all.clear();
    for (int i = 0; i < 3; i++) {
        all.push_back(&data[side][0][i]);
    }
    all.push_back(&data[side][1][2]);
    for (int i = 2; i >= 0; i--) {
        all.push_back(&data[side][2][i]);
    }
    all.push_back(&data[side][1][0]);
}

//以下函数的作用均为把正面转到某个面
void Rubiks::FtoR()
{
    static int tmp[6][3][3];
    memcpy(tmp, data, sizeof(data));
    
    memcpy(data[Right], tmp[Front], sizeof(tmp[0]));
    memcpy(data[Front], tmp[Left], sizeof(tmp[0]));
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
            data[Back][j][k] = tmp[Right][2-j][2-k];
        }
    }
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
            data[Left][j][k] = tmp[Back][2-j][2-k];
        }
    }
    
    vector<int*> all;
    side_circle(all, Up);
    _Rotate(all, -2);
    
    side_circle(all, Down);
    _Rotate(all, 2);
    
}

void Rubiks::FtoL()
{
    static int tmp[6][3][3];
    memcpy(tmp, data, sizeof(data));
    
    memcpy(data[Front], tmp[Right], sizeof(tmp[0]));
    memcpy(data[Left], tmp[Front], sizeof(tmp[0]));
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
            data[Right][j][k] = tmp[Back][2-j][2-k];
        }
    }
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
            data[Back][j][k] = tmp[Left][2-j][2-k];
        }
    }
    
    vector<int*> all;
    side_circle(all, Up);
    _Rotate(all, 2);
    
    side_circle(all, Down);
    _Rotate(all, -2);
    
}

void Rubiks::FtoU()
{
    static int tmp[6][3][3];
    memcpy(tmp, data, sizeof(data));
    int seq[] = {Front, Up, Back, Down};
    for (int i = 0; i < 4; i++) {
        memcpy(data[seq[(i+1)%4]], tmp[seq[i]], sizeof(tmp[0]));
    }
    
    vector<int*> all;
    side_circle(all, Right);
    _Rotate(all, 2);
    
    side_circle(all, Left);
    _Rotate(all, -2);
}

void Rubiks::FtoD()
{
    static int tmp[6][3][3];
    memcpy(tmp, data, sizeof(data));
    int seq[] = {Front, Down, Back, Up};
    for (int i = 0; i < 4; i++) {
        memcpy(data[seq[(i+1)%4]], tmp[seq[i]], sizeof(tmp[0]));
    }
    
    vector<int*> all;
    side_circle(all, Right);
    _Rotate(all, -2);
    
    side_circle(all, Left);
    _Rotate(all, 2);
}

void Rubiks::R()
{
    Rubiks *before = NULL;
    if (output)
        before = new Rubiks(*this);
    
    vector<int*> all;
    _right_element_circle(all);
    _Rotate(all, 3);
    side_circle(all, Right);
    _Rotate(all, 2);
    
    if (before)
    {
        output_R(before);
        delete before;
    }
    
}

void Rubiks::Ri()
{
    Rubiks *before = NULL;
    if (output)
        before = new Rubiks(*this);
    
    vector<int*> all;
    _right_element_circle(all);
    _Rotate(all, -3);
    side_circle(all, Right);
    _Rotate(all, -2);
    
    if (before)
    {
        output_R(before);
        delete before;
    }
}

void Rubiks::L()
{
    FtoR();
    FtoR();
    R();
    FtoL();
    FtoL();
}

void Rubiks::Li()
{
    FtoR();
    FtoR();
    Ri();
    FtoL();
    FtoL();
}

void Rubiks::D()
{
    FtoU();
    FtoR();
    R();
    FtoL();
    FtoD();
}

void Rubiks::Di()
{
    FtoU();
    FtoR();
    Ri();
    FtoL();
    FtoD();
}

void Rubiks::F()
{
    FtoR();
    R();
    FtoL();
}

void Rubiks::Fi()
{
    FtoR();
    Ri();
    FtoL();
}

void Rubiks::B()
{
    FtoL();
    R();
    FtoR();
}

void Rubiks::Bi()
{
    FtoL();
    Ri();
    FtoR();
}

void Rubiks::U()
{
    FtoD();
    FtoR();
    R();
    FtoL();
    FtoU();
}

void Rubiks::Ui()
{
    FtoD();
    FtoR();
    Ri();
    FtoL();
    FtoU();
}

void Rubiks::print_state()
{
    cerr << "output order is  Right = 0, Left, Up, Down, Front, Back" << endl;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                cerr<<data[i][j][k]<<' ';
            }
            cerr<<endl;
        }
        cerr<<endl;
    }
    
    cerr << '"' << 'R' << "\":[";
    for (int j = 2; j >=0 ; j--) {
        for (int k = 2; k >=0; k--) {
            if (j!=2 || k!=2)
                cerr<<',';
            cerr<<data[0][j][k];
        }
    }
    cerr <<"]"<<endl;
    
    cerr << '"' << 'L' << "\":[";
    for (int j = 2; j >=0 ; j--) {
        for (int k = 0; k < 3; k++) {
            if (j!=2 || k!=0)
                cerr<<',';
            cerr<<data[1][j][k];
        }
    }
    cerr <<"]"<<endl;
    
    cerr << '"' << 'U' << "\":[";
    for (int j = 0; j <=2 ; j++) {
        for (int k = 0; k < 3; k++) {
            if (j!=0 || k!=0)
                cerr<<',';
            cerr<<data[2][k][j];
        }
    }
    cerr <<"]"<<endl;
    
    cerr << '"' << 'D' << "\":[";
    for (int j = 0; j <3 ; j++) {
        for (int k = 2; k >=0; k--) {
            if (j!=0 || k!=2)
                cerr<<',';
            cerr<<data[3][k][j];
        }
    }
    cerr <<"]"<<endl;
    
    cerr << '"' << 'F' << "\":[";
    for (int j = 0; j <3 ; j++) {
        for (int k = 2; k >=0; k--) {
            if (j!=0 || k!=2)
                cerr<<',';
            cerr<<data[4][k][j];
        }
    }
    cerr <<"]"<<endl;
    
    cerr << '"' << 'B' << "\":[";
    for (int j = 0; j < 3; j++) {
        if (j!=0)
            cerr <<",";
        cerr << data[5][j][0];
    }
    for (int j = 0; j <3; j++) {
        cerr <<",";
        cerr << data[5][j][1];
    }
    for (int j = 0; j < 3; j++) {
        cerr <<",";
        cerr << data[5][j][2];
    }
    cerr <<"]"<<endl;
}

//change side1 to front side2 to right
void Rubiks::change_vp(Side side1, Side side2)
{
    if (opposite(side1) == side2 || side1 == side2)
    {
        cerr << "illegal view point request!" << side1 << ' ' << side2 << endl;
        assert(false);
    }
    
    Color color1 = (Color)data[side1][1][1], color2 = (Color)data[side2][1][1];
    
    //First, we change side2 to front
    switch (side2) {
        case Back:
            FtoL();
            FtoL();
            break;
        case Left:
            FtoR();
            break;
        case Right:
            FtoL();
            break;
        case Down:
            FtoU();
            break;
        case Up:
            FtoD();
            break;
        default:
            assert(side2 == Front);
            break;
    }
    
    assert(data[Front][1][1] == color2);
    
    //update side1
    for (int i = 0; i < 6; i++) {
        if (data[i][1][1] == color1)
        {
            side1 = (Side)i;
            break;
        }
    }
    
    switch (side1) {
        case Left:
            FtoR();
            break;
        case Right:
            FtoU();
            FtoL();
            FtoL();
            FtoD();
            FtoR();
            break;
        case Down:
            FtoU();
            FtoR();
            FtoD();
            break;
        case Up:
            FtoL();
            FtoD();
            break;
        default:
            assert(false);
            break;
    }
}

void Rubiks::change_vp(Color color1, Color color2)
{
    Side side1 , side2;
    bool flag1 = false, flag2 = false;
    for (int i = 0; i < 6; i++) {
        if (data[i][1][1] == color1)
        {
            side1 = (Side)i;
            flag1 = true;
        }
        if (data[i][1][1] == color2)
        {
            side2 = (Side)i;
            flag2 = true;
        }
    }
    
    if (!flag1 || !flag2)
    {
        cerr << "Invail color!" << endl;
        assert(false);
    }
    
    change_vp(side1, side2);
}

Edge Rubiks::find_edge_piece(Color color1, Color color2)
{
#define find(s1,x1,y1,s2,x2,y2)  {if ((data[s1][x1][y1] == color1 && data[s2][x2][y2] == color2) || \
(data[s1][x1][y1] == color2 && data[s2][x2][y2] == color1)) \
return Edge(s1,s2);}
    find(Front, 0, 1, Up, 2, 1);
    find(Right, 0, 1, Up, 1, 2);
    find(Back, 2, 1, Up, 0, 1);
    find(Left, 0, 1, Up, 1, 0);
    
    find(Front, 2, 1, Down, 0, 1);
    find(Right, 2, 1, Down, 1, 2);
    find(Back, 0, 1, Down, 2, 1);
    find(Left, 2, 1, Down, 1, 0);
    
    find(Front, 1, 0, Left, 1, 2);
    find(Front, 1, 2, Right, 1, 0);
    find(Back, 1, 0, Left, 1, 0);
    find(Back, 1, 2, Right, 1, 2);
    
    assert(false);
}

void Rubiks::shuffle()
{
    srand((unsigned)time(0));
    for (int i = 0;  i < 100; i++) {
        switch (rand() % 12) {
            case 0:R();break;
            case 1:Ri();break;
            case 2:L();break;
            case 3:Li();break;
            case 4:D();break;
            case 5:Di();break;
            case 6:U();break;
            case 7:Ui();break;
            case 8:F();break;
            case 9:Fi();break;
            case 10:B();break;
            case 11:Bi();break;
            default:
                assert(false);
                break;
        }
    }
}

bool Rubiks::same_data(const int data1[][3][3], const int data2[][3][3])
{
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                if (data1[i][j][k] != data2[i][j][k])
                    return false;
    return true;
}

void Rubiks::output_R(Rubiks *tmp)
{
    Color nfront = (Color)data[Front][1][1], nright = (Color)data[Right][1][1];
    tmp->output = false;
    tmp->change_vp(init_front, init_right);
    
    int r_side = -1;
    for (int i = 0; i < 6; i++) {
        if (tmp->data[i][1][1] == nright)
        {
            r_side = i;
            break;
        }
    }
    
    assert(r_side >= 0 && r_side <=5);
    
    (tmp->*opt_ptr1[r_side][0])();
    
    tmp->change_vp(nfront, nright);
    bool same = same_data(data, tmp->data);
        
    char opt_str[6][2][3] = {"R", "Ri", "L", "Li", "U", "Ui", "D", "Di", "F", "Fi", "B", "Bi"};
    
    cout << opt_str[r_side][(same ? 0 : 1)] << endl;
    
#ifdef _DEBUG
    if (!same)
    {
        tmp->change_vp(init_front, init_right);
        (tmp->*opt_ptr1[r_side][1])();
        (tmp->*opt_ptr1[r_side][1])();
        tmp->change_vp(nfront, nright);
        assert(same_data(data, tmp->data));
    }
#endif
    
}
