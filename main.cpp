//
//  main.cpp
//  Rubiks2
//
//  Created by 田 博 on 12-12-8.
//  Copyright (c) 2012年 田 博. All rights reserved.
//

#include <iostream>
#include "rubiks.h"
#include "stage.h"
//#include "rubikstest.cpp"

void solve(Rubiks &now)
{
    //stage2(now);
    stage3(now);
    /*stage4(now);
    stage5(now);
    stage6(now);*/
}

void test_rubiks1()
{
    Rubiks now;
    while (true) {
        now.print_state();
        cout << "please input command(-1 to skip this test):";
        int opt;
        cin >> opt;
        switch (opt) {
            case 0:now.R();break;
            case 1:now.Ri();break;
            case 2:now.L();break;
            case 3:now.Li();break;
            case 4:now.D();break;
            case 5:now.Di();break;
            case 6:now.U();break;
            case 7:now.Ui();break;
            case 8:now.F();break;
            case 9:now.Fi();break;
            case 10:now.B();break;
            case 11:now.Bi();break;
            case 12:now.FtoD();break;
            case 13:now.FtoU();break;
            case 14:now.FtoR();break;
            case 15:now.FtoL();break;
            default:
                return ;
        }
    }
}

void test_rubiks2()
{
    int data[6][3][3] = {{White, Red, White, Orange, Red, Blue, Green, Red, Yellow},
        {Red, Orange, Blue, Green, Orange, Yellow, Yellow, Orange, Orange},
        {Yellow, White, Red, White, White, White, Red, White, Blue},
        {Green, Red, Yellow, Green, Yellow, Yellow, Blue, Green, Red},
        {White, Green, Orange, Orange, Green, Blue, White, Blue, Orange},
        {Orange, Yellow, Green, Red, Blue, Yellow, Blue, Blue, Green}};
    Rubiks now(data);
    //now.output = false;
    stage3(now);
    now.print_state();
}

void test_rubiks3()
{
    Rubiks now, cnow;
    now.shuffle();
    cnow = now;
    solve(now);
    for (int i = 0; i < 6; i++) {
        int cur = now.data[i][1][1];
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3;k++)
                if (cur != now.data[i][j][k])
                {
                    cerr << "Not right!" << endl;
                    cerr << "Begin"<< endl;
                    cnow.print_state();
                    cerr << "End" << endl;
                    now.print_state();
                    goto OUT;
                }
        }
    }
OUT:;
}

int main(int argc, const char * argv[])
{
    //test_rubiks1();
    test_rubiks2();
    //test_rubiks3();
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

