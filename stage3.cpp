//
//  stage3.cpp
//  Rubiks2
//
//  Created by 田 博 on 12-12-8.
//  Copyright (c) 2012年 田 博. All rights reserved.
//

#include "stage3.h"
#include "rubiks.h"

void stage3_init(Rubiks &now)
{
    for (int i = 0; i < 6; i++) {
        if (now.data[i][1][1] == White)
        {
            now.change_vp(Side(i), Side((i+2)%6));
            now.FtoU();
            return ;
        }
    }
}

void stage3_check(Rubiks &now)
{
    for (int i = 0; i < 3; i++) {
        if (now.data[Up][1][i] != White)
        {
            cerr << "Up 1 " << i << " is not white!\n";
            now.print_state();
            assert(false);
        }
        if (now.data[Up][i][1] != White)
        {
            cerr << "Up " << i << " 1 is not white!\n";
            now.print_state();
            assert(false);
        }
    }
    const Side seq[4] = {Front, Left, Right};
    for (int i = 0; i < 4; i++) {
        if (now.data[seq[i]][0][1] != now.data[seq[i]][1][1])
        {
            cerr << "seq "<<i<<" color not same!"<<endl;
            assert(false);
        }
    }
    
    if (now.data[Back][2][1] != now.data[Back][1][1])
    {
        cerr << "Back "<<" color not same!"<<endl;
        assert(false);
    }
}

bool down_to_up(Rubiks &now)
{
    int (*data)[3][3] = now.data;

    for (int i = 0; i < 4; i++) {
        now.FtoR();
        if (data[Up][2][2] == White)
        {
            //assert(data[Front][0][2] == data[Front][0][1] && data[Right][0][0] == data[Right][0][1]);
        }
        else
        {
            bool in[6], flag = false;
            for (int j = 0; j < 4; j++) {
                memset(in, false, sizeof(in));
                in[data[Front][2][2]] = in[data[Down][0][2]] = in[data[Right][2][0]] = true;
                if (in[data[Front][0][1]] && in[data[Right][0][1]] && in[White]) {
                    flag = true;
                    break;
                }
                now.D();
            }
            
            if (!flag)
                continue;
            
            while (!(data[Up][2][2] == White && data[Front][0][2] == data[Front][0][1] && data[Right][0][0] == data[Right][0][1]))
            {
                now.Ri();
                now.Di();
                now.R();
                now.D();
            }
            return true;
        }
    }
    
    return false;
}

bool up_to_down(Rubiks &now)
{
    int (*data)[3][3] = now.data;

    for (int i = 0; i < 4; i++) {
        bool flag = false;
        while ((data[Front][0][2] == White || data[Right][0][0] == White) ||
               (data[Up][2][2] == White && (data[Front][0][2] != data[Front][0][1] || data[Right][0][0] != data[Right][0][1])))
        {
            now.Ri();
            now.Di();
            now.R();
            flag = true;
        }
        
        if (flag)
            return true;
        now.FtoR();
    }
    
    return false;
}


void stage3(Rubiks &now)
{
    cerr << "Enter stage2\n";
    now.print_state();
        
    stage3_init(now);
    
    stage3_check(now);
    
    now.print_state();
    
    while(down_to_up(now));
    
    while (up_to_down(now)) {
        while (!down_to_up(now))
            assert(false);
    }
        
    now.print_state();
    cerr << "Leave stage2\n";
}
