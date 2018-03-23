#include "stdlib.h"
#include "mylib.c"
#include "map_mainboard.h"
#include "col_mainboard.h"
#include "map_welcome.h"
#include "col_welcome.h"
#include "map_round1.h"
#include "col_round1.h"
#include "map_round2.h"
#include "col_round2.h"
#include "map3.h"
#include "map4.h"
#include "col3.h"
#include "col4.h"

void drawunderground(u8 x,u8 y)
{
    putSP(1,x,y,0xAC,3);
    putSP(2,x+8,y,0xAC,3);
    putSP(3,x+16,y,0xAC,3);
    putSP(4,x+24,y,0xAC,3);
    putSP(5,x+32,y,0xAC,3);
    putSP(6,x+40,y,0xAD,3);
}
int border_check(u8 x,u8 y)
{
    if( x <= 30)
    {
        return 1;
    }
    if(x>=135)
    {
        return 2;
    }
    if(y<=27)
    {
        return 3;
    }
}
void main()
{
    int flag_x = 1;
	int flag_y = -1;
	int life = 3;
	int begin = 1;
    u8 key=0, okey=0;
	u8 banzi_x=80, banzi_y=210;
	u8 ball_x = 90, ball_y = 200;
	int y = 8;
	int i = 0;
    int hahaha = 1;
    int start = 1;
    int win = 0;
    int lose = 0;
    int highestscore = 0;
    int j=0;
	int round_flag = 1;
	int pause;
	int array[12]={1,1,1,0,1,1,0,0,1,0,0,0};
	int win_check = 0;
	wait_VBlank();//等待垂直扫描
	while(1)
    {
        while(start)
        {
            if(hahaha == 1){
                disable_graphics();
                load_full_name_0((u8*)map_welcome);
                load_BG_palette((u8*)col_welcome);
                load_SP_palette((u8*)col_welcome);
                enable_graphics();
            }
            key=read_joy();
            if(presskey(button_A) || !hahaha)
            {
                begin = 1;
                hahaha = 0;
                start = 0;
				if(round_flag == 1){
					disable_graphics();
					load_full_name_0((u8*)map_round1);
					load_BG_palette((u8*)col_round1);
					load_SP_palette((u8*)col_round1);
					enable_graphics();
					while(start <=100)
					{
						wait_VBlank();
						start++;
					}
					start = 0;
					disable_graphics();
					load_full_name_0((u8*)map_mainboard);
					load_BG_palette((u8*)col_mainboard);
					load_SP_palette((u8*)col_mainboard);
					enable_graphics();
					wait_VBlank();
				}else
				{
					disable_graphics();
					load_full_name_0((u8*)map_round2);
					load_BG_palette((u8*)col_round2);
					load_SP_palette((u8*)col_round2);
					enable_graphics();
					address(PPU_ctrl_reg_2) = bin(	0,0,0,0,1,1,1,0);
					while(start <=100)
					{
						wait_VBlank();
						start++;
					}
					start = 0;
					begin = 1;
					for(i=0;i<12;i++)
					{
						array[i] = 1;
					}
					disable_graphics();
					load_full_name_0((u8*)map_mainboard);
					load_BG_palette((u8*)col_mainboard);
					load_SP_palette((u8*)col_mainboard);
					enable_graphics();
					wait_VBlank();
					ball_x = 90;
					ball_y = 200;
					flag_x = 1;
					flag_y = -1;
				}
            }
            hahaha = 2;
        }
        while(begin && round_flag == 1)
        {
            key=read_joy();
			if(presskey(button_START))
			{
				if(pause)
				{
					pause = 0;
					continue;
				}
				else
				{
					pause = 1;
					continue;
				}
			}
			if(!pause)
			{
				ball_x += flag_x;
				ball_y += flag_y;
				if(presskey(button_RIGHT) && banzi_x<103)++banzi_x;
				if(presskey(button_LEFT) && banzi_x>33)--banzi_x;
				gotoxy(21,8);
                cprintf("        ");
			}
			else
			{
				gotoxy(21,8);
                cprintf("pause!");
			}
            if(ball_y>=240)
            {
                life -= 1;
                ball_x = 90;
                ball_y = 200;
                flag_x = 1;
                flag_y = -1;
            }
            if(life<=0)
            {
                begin = 0;
                lose = 1;
                hahaha = 1;
            }
			gotoxy(27,2);
			cprintf("%d",round_flag);
            gotoxy(21,10);
            cprintf("score=%d",j*1000);
            if(border_check(ball_x,ball_y)==1)
            {
                flag_x *= -1;
            }
            if(border_check(ball_x,ball_y)==3)
            {
                flag_y *= -1;
            }
            if(border_check(ball_x,ball_y)==2)
            {
                flag_x *= -1;
            }
            if(ball_y == banzi_y && ball_x<=banzi_x+42 && ball_x >= banzi_x-2)
            {
                flag_y *= -1;
            }
			address(PPU_ctrl_reg_1) = bin(1,0,0,0,0,0,0,0);
            putSP(0,ball_x,ball_y,0xAE,0);
			drawunderground(banzi_x,banzi_y);
			address(PPU_ctrl_reg_1) = bin(1,0,1,0,0,0,0,0);
			//draw block
			//first line
			if(array[0]){
				if((ball_x+2==37 || ball_x+2 == 37+24) && ball_y+2<=48 && ball_y+2>=32)
				{
					array[0] = 0;
					flag_x *= -1;
					putSP(7,37,32,0xD2,34);
					putSP(8,37+8,32,0xC2,34);
					putSP(9,37+16,32,0xC4,34);
					j++;
				}
				else if((ball_y+2==48 || ball_y+2 == 32) && ball_x+2<=37+24 && ball_x+2>=37)
				{
					array[0] = 0;
					flag_y *= -1;
					putSP(7,37,32,0xD2,34);
					putSP(8,37+8,32,0xC2,34);
					putSP(9,37+16,32,0xC4,34);
					j++;
				}
				else
				{
					putSP(7,37,32,0xD2,2);
					putSP(8,37+8,32,0xC2,2);
					putSP(9,37+16,32,0xC4,2);
				}
			}
			if(array[1]){
				if((ball_x+2==61 || ball_x+2 == 61+24) && ball_y+2<=48 && ball_y+2>=32)
				{
					array[1] = 0;
					flag_x *= -1;
					putSP(10,61,32,0xD2,34);
					putSP(11,61+8,32,0xC2,34);
					putSP(12,61+16,32,0xC4,34);
					j++;
				}
				else if((ball_y+2==48 || ball_y+2 == 32) && ball_x+2<=61+24 && ball_x+2>=61)
				{
					array[1] = 0;
					flag_y *= -1;
					putSP(10,61,32,0xD2,34);
					putSP(11,61+8,32,0xC2,34);
					putSP(12,61+16,32,0xC4,34);
					j++;
				}
				else
				{
					putSP(10,61,32,0xD2,2);
					putSP(11,61+8,32,0xC2,2);
					putSP(12,61+16,32,0xC4,2);
				}
			}
			
			if(array[2]){
				if((ball_x+2==85 || ball_x+2 == 85+24) && ball_y+2<=48 && ball_y+2>=32)
				{
					array[2] = 0;
					flag_x *= -1;
					putSP(13,85,32,0xD2,34);
					putSP(14,85+8,32,0xC2,34);
					putSP(15,85+16,32,0xC4,34);
					j++;
				}
				else if((ball_y+2==48 || ball_y+2 == 32) && ball_x+2<=85+24 && ball_x+2>=85)
				{
					array[2] = 0;
					flag_y *= -1;
					putSP(13,85,32,0xD2,34);
					putSP(14,85+8,32,0xC2,34);
					putSP(15,85+16,32,0xC4,34);
					j++;
				}
				else
				{
					putSP(13,85,32,0xD2,2);
					putSP(14,85+8,32,0xC2,2);
					putSP(15,85+16,32,0xC4,2);
				}
			}
			
			if(array[3]){
				if((ball_x+2==109 || ball_x+2 == 109+24) && ball_y+2<=48 && ball_y+2>=32)
				{
					array[3] = 0;
					flag_x *= -1;
					putSP(16,109,32,0xD2,34);
					putSP(17,109+8,32,0xC2,34);
					putSP(18,109+16,32,0xC4,34);
					j++;
				}
				else if((ball_y+2==48 || ball_y+2 == 32) && ball_x+2<=109+24 && ball_x+2>=109)
				{
					array[3] = 0;
					flag_y *= -1;
					putSP(16,109,32,0xD2,34);
					putSP(17,109+8,32,0xC2,34);
					putSP(18,109+16,32,0xC4,34);
					j++;
				}
				else
				{
					putSP(16,109,32,0xD2,2);
					putSP(17,109+8,32,0xC2,2);
					putSP(18,109+16,32,0xC4,2);
				}
			}
			
			//seconde line
			if(array[4]){
				if((ball_x+2==37 || ball_x+2 == 37+24) && ball_y+2<=64 && ball_y+2>=48)
				{
					array[4] = 0;
					flag_x *= -1;
					putSP(19,37,32+16,0xD2,34);
					putSP(20,37+8,32+16,0xC2,34);
					putSP(21,37+16,32+16,0xC4,34);
					j++;
				}
				else if((ball_y+2==48 || ball_y+2 == 64) && ball_x+2<=37+24 && ball_x+2>=37)
				{
					array[4] = 0;
					flag_y *= -1;
					putSP(19,37,32+16,0xD2,34);
					putSP(20,37+8,32+16,0xC2,34);
					putSP(21,37+16,32+16,0xC4,34);
					j++;
				}
				else
				{
					putSP(19,37,32+16,0xD2,2);
					putSP(20,37+8,32+16,0xC2,2);
					putSP(21,37+16,32+16,0xC4,2);
				}
			}
			
			if(array[5]){
				if((ball_x+2==61 || ball_x+2 == 61+24) && ball_y+2<=64 && ball_y+2>=48)
				{
					array[5] = 0;
					flag_x *= -1;
					putSP(22,61,32+16,0xD2,34);
					putSP(23,61+8,32+16,0xC2,34);
					putSP(24,61+16,32+16,0xC4,34);
					j++;
				}
				else if((ball_y+2==48 || ball_y+2 == 64) && ball_x+2<=61+24 && ball_x+2>=61)
				{
					array[5] = 0;
					flag_y *= -1;
					putSP(22,61,32+16,0xD2,34);
					putSP(23,61+8,32+16,0xC2,34);
					putSP(24,61+16,32+16,0xC4,34);
					j++;
				}
				else
				{
					putSP(22,61,32+16,0xD2,2);
					putSP(23,61+8,32+16,0xC2,2);
					putSP(24,61+16,32+16,0xC4,2);
				}
			}
			
			if(array[6]){
				if((ball_x+2==85 || ball_x+2 == 85+24) && ball_y+2<=64 && ball_y+2>=48)
				{
					array[6] = 0;
					flag_x *= -1;
					putSP(25,85,32+16,0xD2,34);
					putSP(26,85+8,32+16,0xC2,34);
					putSP(27,85+16,32+16,0xC4,34);
					j++;
				}
				else if((ball_y+2==48 || ball_y+2 == 64) && ball_x+2<=85+24 && ball_x+2>=85)
				{
					array[6] = 0;
					flag_y *= -1;
					putSP(25,85,32+16,0xD2,34);
					putSP(26,85+8,32+16,0xC2,34);
					putSP(27,85+16,32+16,0xC4,34);
					j++;
				}
				else
				{
					putSP(25,85,32+16,0xD2,2);
					putSP(26,85+8,32+16,0xC2,2);
					putSP(27,85+16,32+16,0xC4,2);
				}
			}
			if(array[7]){
				if((ball_x+2==109 || ball_x+2 == 109+24) && ball_y+2<=64 && ball_y+2>=48)
				{
					array[7] = 0;
					flag_x *= -1;
					putSP(28,109,32+16,0xD2,34);
					putSP(29,109+8,32+16,0xC2,34);
					putSP(30,109+16,32+16,0xC4,34);
					j++;
				}
				else if((ball_y+2==48 || ball_y+2 == 64) && ball_x+2<=109+24 && ball_x+2>=109)
				{
					array[7] = 0;
					flag_y *= -1;
					putSP(28,109,32+16,0xD2,34);
					putSP(29,109+8,32+16,0xC2,34);
					putSP(30,109+16,32+16,0xC4,34);
					j++;
				}
				else
				{
					putSP(28,109,32+16,0xD2,2);
					putSP(29,109+8,32+16,0xC2,2);
					putSP(30,109+16,32+16,0xC4,2);
				}
			}
			
			//third line
			if(array[8]){
				if((ball_x+2==37 || ball_x+2 == 37+24) && ball_y+2<=80 && ball_y+2>=64)
				{
					array[8] = 0;
					flag_x *= -1;
					putSP(31,37,32+32,0xD2,34);
					putSP(32,37+8,32+32,0xC2,34);
					putSP(33,37+16,32+32,0xC4,34);
					j++;
				}
				else if((ball_y+2==80 || ball_y+2 == 64) && ball_x+2<=37+24 && ball_x+2>=37)
				{
					array[8] = 0;
					flag_y *= -1;
					putSP(31,37,32+32,0xD2,34);
					putSP(32,37+8,32+32,0xC2,34);
					putSP(33,37+16,32+32,0xC4,34);
					j++;
				}
				else
				{
					putSP(31,37,32+32,0xD2,2);
					putSP(32,37+8,32+32,0xC2,2);
					putSP(33,37+16,32+32,0xC4,2);
				}
			}
			if(array[9]){
				if((ball_x+2==61 || ball_x+2 == 61+24) && ball_y+2<=80 && ball_y+2>=64)
				{
					array[9] = 0;
					flag_x *= -1;
					putSP(34,61,32+32,0xD2,34);
					putSP(35,61+8,32+32,0xC2,34);
					putSP(36,61+16,32+32,0xC4,34);
					j++;
				}
				else if((ball_y+2==80 || ball_y+2 == 64) && ball_x+2<=61+24 && ball_x+2>=61)
				{
					array[9] = 0;
					flag_y *= -1;
					putSP(34,61,32+32,0xD2,34);
					putSP(35,61+8,32+32,0xC2,34);
					putSP(36,61+16,32+32,0xC4,34);
					j++;
				}
				else
				{
					putSP(34,61,32+32,0xD2,2);
					putSP(35,61+8,32+32,0xC2,2);
					putSP(36,61+16,32+32,0xC4,2);
				}
			}
			
			if(array[10]){
				if((ball_x+2==85 || ball_x+2 == 85+24) && ball_y+2<=80 && ball_y+2>=64)
				{
					array[10] = 0;
					flag_x *= -1;
					putSP(37,85,32+32,0xD2,34);
					putSP(38,85+8,32+32,0xC2,34);
					putSP(39,85+16,32+32,0xC4,34);
					j++;
				}
				else if((ball_y+2==80 || ball_y+2 == 64) && ball_x+2<=85+24 && ball_x+2>=85)
				{
					array[10] = 0;
					flag_y *= -1;
					putSP(37,85,32+32,0xD2,34);
					putSP(38,85+8,32+32,0xC2,34);
					putSP(39,85+16,32+32,0xC4,34);
					j++;
				}
				else
				{
					putSP(37,85,32+32,0xD2,2);
					putSP(38,85+8,32+32,0xC2,2);
					putSP(39,85+16,32+32,0xC4,2);
				}
			}
			if(array[11]){
				if((ball_x+2==109 || ball_x+2 == 109+24) && ball_y+2<=80 && ball_y+2>=64)
				{
					array[11] = 0;
					flag_x *= -1;
					putSP(40,109,32+32,0xD2,34);
					putSP(41,109+8,32+32,0xC2,34);
					putSP(42,109+16,32+32,0xC4,34);
					j++;
				}
				else if((ball_y+2==80 || ball_y+2 == 64) && ball_x+2<=109+24 && ball_x+2>=109)
				{
					array[11] = 0;
					flag_y *= -1;
					putSP(40,109,32+32,0xD2,34);
					putSP(41,109+8,32+32,0xC2,34);
					putSP(42,109+16,32+32,0xC4,34);
					j++;
				}
				else
				{
					putSP(40,109,32+32,0xD2,2);
					putSP(41,109+8,32+32,0xC2,2);
					putSP(42,109+16,32+32,0xC4,2);
				}
			}
			win_check = 0;
			wait_VBlank();
			if(!array[0]&&!array[1]&&!array[2]&&!array[3]&&!array[4]&&!array[5]&&!array[6]&&!array[7]&&!array[8]&&!array[9]&&!array[10]&&!array[11]){
				hahaha = 0;
				start = 1;
				begin = 0;
				round_flag = 2;
			}
		}
		
		while(begin && round_flag == 2)
        {
            key=read_joy();
			if(presskey(button_START))
			{
				if(pause)
				{
					pause = 0;
					continue;
				}
				else
				{
					pause = 1;
					continue;
				}
			}
			if(!pause)
			{
				ball_x += flag_x;
				ball_y += flag_y;
				if(presskey(button_RIGHT) && banzi_x<103)++banzi_x;
				if(presskey(button_LEFT) && banzi_x>33)--banzi_x;
				gotoxy(21,8);
                cprintf("        ");
			}
			else
			{
				gotoxy(21,8);
                cprintf("pause!");
			}
            if(ball_y>=240)
            {
                life -= 1;
                ball_x = 90;
                ball_y = 200;
                flag_x = 1;
                flag_y = -1;
            }
            if(life<=0)
            {
                begin = 0;
                lose = 1;
                hahaha = 1;
            }
			gotoxy(27,2);
			cprintf("%d",round_flag);
            gotoxy(21,10);
            cprintf("score=%d",j*1000);
            if(border_check(ball_x,ball_y)==1)
            {
                flag_x *= -1;
            }
            if(border_check(ball_x,ball_y)==3)
            {
                flag_y *= -1;
            }
            if(border_check(ball_x,ball_y)==2)
            {
                flag_x *= -1;
            }
            if(ball_y == banzi_y && ball_x<=banzi_x+42 && ball_x >= banzi_x-2)
            {
                flag_y *= -1;
            }
			address(PPU_ctrl_reg_1) = bin(1,0,0,0,0,0,0,0);
            putSP(0,ball_x,ball_y,0xAE,0);
			drawunderground(banzi_x,banzi_y);
			address(PPU_ctrl_reg_1) = bin(1,0,1,0,0,0,0,0);
			if(array[0]){
				if((ball_x+2==37 || ball_x+2 == 37+24) && ball_y+2<=48 && ball_y+2>=32)
				{
					array[0] = 0;
					flag_x *= -1;
					putSP(7,37,32,0xD2,34);
					putSP(8,37+8,32,0xC2,34);
					putSP(9,37+16,32,0xC4,34);
					j++;
				}
				else if((ball_y+2==48 || ball_y+2 == 32) && ball_x+2<=37+24 && ball_x+2>=37)
				{
					array[0] = 0;
					flag_y *= -1;
					putSP(7,37,32,0xD2,34);
					putSP(8,37+8,32,0xC2,34);
					putSP(9,37+16,32,0xC4,34);
					j++;
				}
				else
				{
					putSP(7,37,32,0xD2,2);
					putSP(8,37+8,32,0xC2,2);
					putSP(9,37+16,32,0xC4,2);
				}
			}
			if(array[1]){
				if((ball_x+2==61 || ball_x+2 == 61+24) && ball_y+2<=48 && ball_y+2>=32)
				{
					array[1] = 0;
					flag_x *= -1;
					putSP(10,61,32,0xD2,34);
					putSP(11,61+8,32,0xC2,34);
					putSP(12,61+16,32,0xC4,34);
					j++;
				}
				else if((ball_y+2==48 || ball_y+2 == 32) && ball_x+2<=61+24 && ball_x+2>=61)
				{
					array[1] = 0;
					flag_y *= -1;
					putSP(10,61,32,0xD2,34);
					putSP(11,61+8,32,0xC2,34);
					putSP(12,61+16,32,0xC4,34);
					j++;
				}
				else
				{
					putSP(10,61,32,0xD2,2);
					putSP(11,61+8,32,0xC2,2);
					putSP(12,61+16,32,0xC4,2);
				}
			}
			
			if(array[2]){
				if((ball_x+2==85 || ball_x+2 == 85+24) && ball_y+2<=48 && ball_y+2>=32)
				{
					array[2] = 0;
					flag_x *= -1;
					putSP(13,85,32,0xD2,34);
					putSP(14,85+8,32,0xC2,34);
					putSP(15,85+16,32,0xC4,34);
					j++;
				}
				else if((ball_y+2==48 || ball_y+2 == 32) && ball_x+2<=85+24 && ball_x+2>=85)
				{
					array[2] = 0;
					flag_y *= -1;
					putSP(13,85,32,0xD2,34);
					putSP(14,85+8,32,0xC2,34);
					putSP(15,85+16,32,0xC4,34);
					j++;
				}
				else
				{
					putSP(13,85,32,0xD2,2);
					putSP(14,85+8,32,0xC2,2);
					putSP(15,85+16,32,0xC4,2);
				}
			}
			
			if(array[3]){
				if((ball_x+2==109 || ball_x+2 == 109+24) && ball_y+2<=48 && ball_y+2>=32)
				{
					array[3] = 0;
					flag_x *= -1;
					putSP(16,109,32,0xD2,34);
					putSP(17,109+8,32,0xC2,34);
					putSP(18,109+16,32,0xC4,34);
					j++;
				}
				else if((ball_y+2==48 || ball_y+2 == 32) && ball_x+2<=109+24 && ball_x+2>=109)
				{
					array[3] = 0;
					flag_y *= -1;
					putSP(16,109,32,0xD2,34);
					putSP(17,109+8,32,0xC2,34);
					putSP(18,109+16,32,0xC4,34);
					j++;
				}
				else
				{
					putSP(16,109,32,0xD2,2);
					putSP(17,109+8,32,0xC2,2);
					putSP(18,109+16,32,0xC4,2);
				}
			}
			
			//seconde line
			if(array[4]){
				if((ball_x+2==37 || ball_x+2 == 37+24) && ball_y+2<=64 && ball_y+2>=48)
				{
					array[4] = 0;
					flag_x *= -1;
					putSP(19,37,32+16,0xD2,34);
					putSP(20,37+8,32+16,0xC2,34);
					putSP(21,37+16,32+16,0xC4,34);
					j++;
				}
				else if((ball_y+2==48 || ball_y+2 == 64) && ball_x+2<=37+24 && ball_x+2>=37)
				{
					array[4] = 0;
					flag_y *= -1;
					putSP(19,37,32+16,0xD2,34);
					putSP(20,37+8,32+16,0xC2,34);
					putSP(21,37+16,32+16,0xC4,34);
					j++;
				}
				else
				{
					putSP(19,37,32+16,0xD2,2);
					putSP(20,37+8,32+16,0xC2,2);
					putSP(21,37+16,32+16,0xC4,2);
				}
			}
			
			if(array[5]){
				if((ball_x+2==61 || ball_x+2 == 61+24) && ball_y+2<=64 && ball_y+2>=48)
				{
					array[5] = 0;
					flag_x *= -1;
					putSP(22,61,32+16,0xD2,34);
					putSP(23,61+8,32+16,0xC2,34);
					putSP(24,61+16,32+16,0xC4,34);
					j++;
				}
				else if((ball_y+2==48 || ball_y+2 == 64) && ball_x+2<=61+24 && ball_x+2>=61)
				{
					array[5] = 0;
					flag_y *= -1;
					putSP(22,61,32+16,0xD2,34);
					putSP(23,61+8,32+16,0xC2,34);
					putSP(24,61+16,32+16,0xC4,34);
					j++;
				}
				else
				{
					putSP(22,61,32+16,0xD2,2);
					putSP(23,61+8,32+16,0xC2,2);
					putSP(24,61+16,32+16,0xC4,2);
				}
			}
			
			if(array[6]){
				if((ball_x+2==85 || ball_x+2 == 85+24) && ball_y+2<=64 && ball_y+2>=48)
				{
					array[6] = 0;
					flag_x *= -1;
					putSP(25,85,32+16,0xD2,34);
					putSP(26,85+8,32+16,0xC2,34);
					putSP(27,85+16,32+16,0xC4,34);
					j++;
				}
				else if((ball_y+2==48 || ball_y+2 == 64) && ball_x+2<=85+24 && ball_x+2>=85)
				{
					array[6] = 0;
					flag_y *= -1;
					putSP(25,85,32+16,0xD2,34);
					putSP(26,85+8,32+16,0xC2,34);
					putSP(27,85+16,32+16,0xC4,34);
					j++;
				}
				else
				{
					putSP(25,85,32+16,0xD2,2);
					putSP(26,85+8,32+16,0xC2,2);
					putSP(27,85+16,32+16,0xC4,2);
				}
			}
			if(array[7]){
				if((ball_x+2==109 || ball_x+2 == 109+24) && ball_y+2<=64 && ball_y+2>=48)
				{
					array[7] = 0;
					flag_x *= -1;
					putSP(28,109,32+16,0xD2,34);
					putSP(29,109+8,32+16,0xC2,34);
					putSP(30,109+16,32+16,0xC4,34);
					j++;
				}
				else if((ball_y+2==48 || ball_y+2 == 64) && ball_x+2<=109+24 && ball_x+2>=109)
				{
					array[7] = 0;
					flag_y *= -1;
					putSP(28,109,32+16,0xD2,34);
					putSP(29,109+8,32+16,0xC2,34);
					putSP(30,109+16,32+16,0xC4,34);
					j++;
				}
				else
				{
					putSP(28,109,32+16,0xD2,2);
					putSP(29,109+8,32+16,0xC2,2);
					putSP(30,109+16,32+16,0xC4,2);
				}
			}
			
			//third line
			if(array[8]){
				if((ball_x+2==37 || ball_x+2 == 37+24) && ball_y+2<=80 && ball_y+2>=64)
				{
					array[8] = 0;
					flag_x *= -1;
					putSP(31,37,32+32,0xD2,34);
					putSP(32,37+8,32+32,0xC2,34);
					putSP(33,37+16,32+32,0xC4,34);
					j++;
				}
				else if((ball_y+2==80 || ball_y+2 == 64) && ball_x+2<=37+24 && ball_x+2>=37)
				{
					array[8] = 0;
					flag_y *= -1;
					putSP(31,37,32+32,0xD2,34);
					putSP(32,37+8,32+32,0xC2,34);
					putSP(33,37+16,32+32,0xC4,34);
					j++;
				}
				else
				{
					putSP(31,37,32+32,0xD2,2);
					putSP(32,37+8,32+32,0xC2,2);
					putSP(33,37+16,32+32,0xC4,2);
				}
			}
			if(array[9]){
				if((ball_x+2==61 || ball_x+2 == 61+24) && ball_y+2<=80 && ball_y+2>=64)
				{
					array[9] = 0;
					flag_x *= -1;
					putSP(34,61,32+32,0xD2,34);
					putSP(35,61+8,32+32,0xC2,34);
					putSP(36,61+16,32+32,0xC4,34);
					j++;
				}
				else if((ball_y+2==80 || ball_y+2 == 64) && ball_x+2<=61+24 && ball_x+2>=61)
				{
					array[9] = 0;
					flag_y *= -1;
					putSP(34,61,32+32,0xD2,34);
					putSP(35,61+8,32+32,0xC2,34);
					putSP(36,61+16,32+32,0xC4,34);
					j++;
				}
				else
				{
					putSP(34,61,32+32,0xD2,2);
					putSP(35,61+8,32+32,0xC2,2);
					putSP(36,61+16,32+32,0xC4,2);
				}
			}
			
			if(array[10]){
				if((ball_x+2==85 || ball_x+2 == 85+24) && ball_y+2<=80 && ball_y+2>=64)
				{
					array[10] = 0;
					flag_x *= -1;
					putSP(37,85,32+32,0xD2,34);
					putSP(38,85+8,32+32,0xC2,34);
					putSP(39,85+16,32+32,0xC4,34);
					j++;
				}
				else if((ball_y+2==80 || ball_y+2 == 64) && ball_x+2<=85+24 && ball_x+2>=85)
				{
					array[10] = 0;
					flag_y *= -1;
					putSP(37,85,32+32,0xD2,34);
					putSP(38,85+8,32+32,0xC2,34);
					putSP(39,85+16,32+32,0xC4,34);
					j++;
				}
				else
				{
					putSP(37,85,32+32,0xD2,2);
					putSP(38,85+8,32+32,0xC2,2);
					putSP(39,85+16,32+32,0xC4,2);
				}
			}
			if(array[11]){
				if((ball_x+2==109 || ball_x+2 == 109+24) && ball_y+2<=80 && ball_y+2>=64)
				{
					array[11] = 0;
					flag_x *= -1;
					putSP(40,109,32+32,0xD2,34);
					putSP(41,109+8,32+32,0xC2,34);
					putSP(42,109+16,32+32,0xC4,34);
					j++;
				}
				else if((ball_y+2==80 || ball_y+2 == 64) && ball_x+2<=109+24 && ball_x+2>=109)
				{
					array[11] = 0;
					flag_y *= -1;
					putSP(40,109,32+32,0xD2,34);
					putSP(41,109+8,32+32,0xC2,34);
					putSP(42,109+16,32+32,0xC4,34);
					j++;
				}
				else
				{
					putSP(40,109,32+32,0xD2,2);
					putSP(41,109+8,32+32,0xC2,2);
					putSP(42,109+16,32+32,0xC4,2);
				}
			}
			win_check = 0;
			wait_VBlank();
			if(!array[0]&&!array[1]&&!array[2]&&!array[3]&&!array[4]&&!array[5]&&!array[6]&&!array[7]&&!array[8]&&!array[9]&&!array[10]&&!array[11]){
				hahaha = 1;
                win = 1;
				begin = 0;
				start = 0;
			}
		}
		while(win)
        {
            if(hahaha == 1){
                disable_graphics();		//关显示
                load_full_name_0((u8*)map3);		//载入地图数据
                load_BG_palette((u8*)col3);		//载入背景调色板
                load_SP_palette((u8*)col3);		//载入精灵调色板
                enable_graphics();		//开显示
            }
            hahaha = 2;
            address(PPU_ctrl_reg_2) = REG_2_IM_able;    //关闭精灵显示
            address(PPU_ctrl_reg_2+1) = 0;
        }
        while(lose)
        {
            if(hahaha == 1){
                disable_graphics();		//关显示
                load_full_name_0((u8*)map4);		//载入地图数据
                load_BG_palette((u8*)col4);		//载入背景调色板
                load_SP_palette((u8*)col4);		//载入精灵调色板
                enable_graphics();		//开显示
            }
            hahaha = 2;
            address(PPU_ctrl_reg_2) = REG_2_IM_able;    //关闭精灵显示
            address(PPU_ctrl_reg_2+1) = 0;
        }
	}
}