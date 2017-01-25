#pragma once
#include<stdlib.h>

typedef struct
{
short speeds[3];
short strength;
short awareness;
short catching;
short carry;
short jump;
short breakTackle;
short tackle;
short throwing[2];
short blocking[2];
short kicking[2];
short kickReturn;
short injury;
short stamina;
short toughness;
short import;
}
MAD04__PLATER_RATINGS;

typedef struct
{
	short ht;
	short wt;
	
	MAD04__PLATER_RATINGS
		rtg;
}
MAD04__PLATER_PROTOTYPE_STRUCT;


MAD04__PLATER_PROTOTYPE_STRUCT
RTG_VARIANCE=
{3,20,{{12,12,12},20,50,15,15,15,25,25,{10,25},{20,15},{10,10},60,10,10,10,60}};

MAD04__PLATER_PROTOTYPE_STRUCT
RTG_MIN=
{60,0,{{0,0,0},0,0,0,0,0,0,0,{0,0},{0,0},{0,0},0,0,0,0,0}};

MAD04__PLATER_PROTOTYPE_STRUCT
RTG_MAX=
{90,255,{{99,99,99},99,99,99,99,99,99,99,{99,99},{99,99},{99,99},99,99,99,99,99}};

const short NUM_PROT_RATINGS=22;

short*RTG_VARY_ARRAY=(short*)&RTG_VARIANCE;

short*RTG_MAX_ARRAY=(short*)&RTG_MAX;

short*RTG_MIN_ARRAY=(short*)&RTG_MIN;




const short MAD04__NUM_BASES__QB=4;

#define madw(w) (__max(__min((w),415),160)-160)
#define madh(f,i) (__min((((f)*12+(i))),127))

MAD04__PLATER_PROTOTYPE_STRUCT
qbBases[MAD04__NUM_BASES__QB]=
{
	{madh(6,4),madw(225),{{65,65,65},65,85,50,50,65,65,50,{90,90},{50,50},{50,50},50,85,85,70,80}},
	{madh(6,2),madw(200),{{75,75,75},55,80,50,60,75,75,50,{80,95},{50,50},{50,50},50,85,85,55,75}},
	{madh(6,0),madw(190),{{85,85,85},45,70,60,75,85,60,50,{85,70},{50,50},{50,50},50,85,85,67,80}},
	{madh(6,6),madw(240),{{55,55,55},75,75,50,50,60,85,50,{95,85},{50,50},{50,50},50,85,85,85,75}},
};


const short MAD04__NUM_BASES__RB=4;

MAD04__PLATER_PROTOTYPE_STRUCT
rbBases[MAD04__NUM_BASES__RB]=
{
	{madh(5,8),madw(195),{{90,95,95},65,70,70,80,80,75,50,{50,50},{50,55},{50,50},75,85,85,75,75}},
	{madh(6,1),madw(225),{{90,80,85},75,70,60,85,70,90,50,{50,50},{55,60},{50,50},65,85,85,85,75}},
	{madh(6,0),madw(200),{{95,95,95},60,70,85,75,90,65,50,{50,50},{45,50},{50,50},85,85,85,65,75}},
	{madh(5,11),madw(250),{{85,85,80},85,70,55,85,65,95,50,{50,50},{60,65},{50,50},60,85,85,90,75}},
};

const short MAD04__NUM_BASES__FB=2;

MAD04__PLATER_PROTOTYPE_STRUCT
fbBases[MAD04__NUM_BASES__FB]=
{
	{madh(6,0),madw(260),{{75,70,75},85,75,60,65,70,95,50,{50,50},{75,70},{50,50},50,85,85,80,75}},
	{madh(6,2),madw(230),{{80,80,80},75,75,80,65,80,80,50,{50,50},{60,60},{50,50},55,85,85,70,75}},
};

const short MAD04__NUM_BASES__WR=3;

MAD04__PLATER_PROTOTYPE_STRUCT
wrBases[MAD04__NUM_BASES__WR]=
{
	{madh(6,0),madw(195),{{95,95,95},55,70,90,60,90,50,50,{50,50},{50,50},{50,50},80,85,85,55,75}},
	{madh(6,5),madw(225),{{90,85,85},70,70,90,65,90,70,50,{50,50},{55,55},{50,50},65,85,85,65,75}},
	{madh(5,9),madw(175),{{95,99,99},50,70,85,50,95,50,50,{50,50},{50,50},{50,50},95,85,85,60,75}},
};

const short MAD04__NUM_BASES__TE=2;

MAD04__PLATER_PROTOTYPE_STRUCT
teBases[MAD04__NUM_BASES__TE]=
{
	{madh(6,3),madw(225),{{85,80,80},70,70,90,70,85,75,50,{50,50},{60,60},{50,50},55,85,85,70,75}},
	{madh(6,6),madw(260),{{75,70,70},80,70,80,70,75,90,50,{50,50},{70,70},{50,50},50,85,85,80,75}},
};

const short MAD04__NUM_BASES__OL=3;

MAD04__PLATER_PROTOTYPE_STRUCT
olBases[MAD04__NUM_BASES__OL]=
{
	{madh(6,7),madw(320),{{60,50,55},95,75,50,50,65,50,50,{50,50},{85,85},{50,50},50,85,85,85,75}},
	{madh(6,3),madw(295),{{65,55,60},90,75,50,50,65,50,50,{50,50},{90,80},{50,50},50,85,85,90,75}},
	{madh(6,5),madw(340),{{57,50,50},95,75,50,50,65,50,50,{50,50},{80,90},{50,50},50,85,85,80,75}},
};

const short MAD04__NUM_BASES__DE=3;

MAD04__PLATER_PROTOTYPE_STRUCT
deBases[MAD04__NUM_BASES__DE]=
{
	{madh(6,3),madw(260),{{80,75,80},80,65,50,50,75,50,85,{50,50},{50,50},{50,50},50,85,85,85,75}},
	{madh(6,5),madw(290),{{70,65,75},95,65,50,50,65,50,90,{50,50},{50,50},{50,50},50,85,85,85,75}},
	{madh(6,7),madw(275),{{75,70,70},87,65,50,50,85,50,80,{50,50},{50,50},{50,50},50,85,85,85,75}},
};

const short MAD04__NUM_BASES__DT=2;

MAD04__PLATER_PROTOTYPE_STRUCT
dtBases[MAD04__NUM_BASES__DT]=
{
	{madh(6,2),madw(310),{{65,65,70},95,70,50,50,65,60,80,{50,50},{50,50},{50,50},50,85,85,90,75}},
	{madh(6,4),madw(340),{{60,60,65},95,75,50,50,60,60,90,{50,50},{50,50},{50,50},50,85,85,80,75}},
};

const short MAD04__NUM_BASES__LB=3;

MAD04__PLATER_PROTOTYPE_STRUCT
lbBases[MAD04__NUM_BASES__LB]=
{
	{madh(6,3),madw(230),{{80,80,85},70,70,75,50,80,50,80,{50,50},{50,50},{50,50},60,85,85,90,75}},
	{madh(6,4),madw(250),{{75,75,75},80,65,55,50,70,50,90,{50,50},{50,50},{50,50},50,85,85,95,75}},
	{madh(6,2),madw(240),{{70,70,75},80,80,65,50,75,50,95,{50,50},{50,50},{50,50},50,85,85,99,75}},
};

const short MAD04__NUM_BASES__CB=2;

MAD04__PLATER_PROTOTYPE_STRUCT
cbBases[MAD04__NUM_BASES__CB]=
{
	{madh(5,10),madw(175),{{95,95,95},50,75,80,60,90,50,55,{50,50},{50,50},{50,50},85,85,85,70,75}},
	{madh(6,1),madw(195),{{90,90,90},55,65,75,50,85,50,65,{50,50},{50,50},{50,50},90,85,85,75,75}},
};


const short MAD04__NUM_BASES__S=2;

MAD04__PLATER_PROTOTYPE_STRUCT
safBases[MAD04__NUM_BASES__S]=
{
	{madh(6,1),madw(210),{{90,90,90},70,75,90,50,85,50,85,{50,50},{50,50},{50,50},80,85,85,80,75}},
	{madh(5,11),madw(225),{{85,85,85},75,75,75,50,80,50,90,{50,50},{50,50},{50,50},70,85,85,90,75}},
};

const short MAD04__NUM_BASES__KP=2;
 
MAD04__PLATER_PROTOTYPE_STRUCT
kpBases[MAD04__NUM_BASES__KP]=
{
	{madh(6,0),madw(180),{{70,70,70},50,75,50,50,70,50,55,{50,50},{50,50},{75,90},50,85,85,60,75}},
	{madh(6,3),madw(225),{{80,80,80},70,75,50,50,77,50,75,{50,50},{50,50},{90,75},50,85,85,77,75}},
};

const short
MAD04__POS_ID__QB=0,
MAD04__POS_ID__RB=1,
MAD04__POS_ID__FB=2,
MAD04__POS_ID__WR=3,
MAD04__POS_ID__TE=4,
MAD04__POS_ID__LT=5,
MAD04__POS_ID__LG=6,
MAD04__POS_ID__C=7,
MAD04__POS_ID__RG=8,
MAD04__POS_ID__RT=9,
MAD04__POS_ID__LE=10,
MAD04__POS_ID__RE=11,
MAD04__POS_ID__DT=12,
MAD04__POS_ID__LOLB=13,
MAD04__POS_ID__ILB=14,
MAD04__POS_ID__ROLB=15,
MAD04__POS_ID__CB=16,
MAD04__POS_ID__FS=17,
MAD04__POS_ID__SS=18,
MAD04__POS_ID__K=19,
MAD04__POS_ID__P=20;

