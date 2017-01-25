#include"ProcessTemplate.h"

#include"playerAge.h"
#include"buildFlags.h"
#include"skinTone.h"
#include"posPrototypes.h"
#include"STDIO.H"
#include"codeshortcuts.h"
#include"stdafx.h"

const int TEMPLATE_LINE__MAX_LEN=500;

bool GetNextDataLine(FILE*f,char*lineBuf)
{
	bool result=true;
	int eofV=feof(f);
	lineBuf[0]=0;
	result=!eofV;
	if(!eofV)
	{
		do
		{
			fscanf(f," %[^\r\n]\n",lineBuf);
			eofV=feof(f);
		}
		while(!eofV&&((lineBuf[0]=='#')||(lineBuf[0]==0)));
	}

	result=result&&(lineBuf[0]!='#')&&(lineBuf[0]!=0);
	return(result);	
}

ReadPrototypeLine
(	MAD04__PLATER_PROTOTYPE_STRUCT&ps
	,char*line,bool translateWgt
)
{
	short htInch,htFt,wt;
	sscanf
	(	
		line
		,
		//#htFt	htIN	wt
		"%hi %hi %hi "
		//spd	agi	acc
		" %hi %hi %hi"
		//	str	awr
		" %hi %hi"
		//	cth	car
		" %hi %hi"
		//	jmp
		" %hi"
		//	btk	tak
		" %hi %hi"
		//	thp	tha
		" %hi %hi"
		//	rbk	pbk
		" %hi %hi"
		//	kpw	kac	ret
		" %hi %hi %hi"
		//	inj	sta	tgh	imp
		" %hi %hi %hi %hi"
		,
		//#htFt	htIN	wt
		&htFt
		,&htInch
		,&wt
		//spd	agi	acc
		,&ps.rtg.speeds[0]
		,&ps.rtg.speeds[1]
		,&ps.rtg.speeds[2]
		//	str	awr
		,&ps.rtg.strength
		,&ps.rtg.awareness
		//	cth	car
		,&ps.rtg.catching
		,&ps.rtg.carry
		//	jmp
		,&ps.rtg.jump
		//	btk	tak
		,&ps.rtg.breakTackle
		,&ps.rtg.tackle
		//	thp	tha
		,&ps.rtg.throwing[0]
		,&ps.rtg.throwing[1]
		//	rbk	pbk
		,&ps.rtg.blocking[0]
		,&ps.rtg.blocking[1]
		//	kpw	kac	ret
		,&ps.rtg.kicking[0]
		,&ps.rtg.kicking[1]
		,&ps.rtg.kickReturn
		//	inj	sta	tgh	imp
		,&ps.rtg.injury
		,&ps.rtg.stamina
		,&ps.rtg.toughness
		,&ps.rtg.import
	);

	ps.ht=madh(htFt,htInch);
	ps.wt=(translateWgt)?madw(wt):wt;

}

bool VersionTest
(	
	short major,short minor,
	short tgtMajor,short tgtMinor
)
{
	return(major==tgtMajor)&&(minor==tgtMinor);
}

ProcessTemplate(char*tmpltNm)
{
	short majorVer,minorVer; 
	FILE*f;
	char lineBuf[TEMPLATE_LINE__MAX_LEN];
	f=fopen(tmpltNm,"r+b");
	if(f)
	{
		//#== Template Version Info == 
		if(GetNextDataLine(f,lineBuf))
			sscanf
			(	lineBuf," %hi %hi",
				&majorVer,&minorVer
			);

		if(VersionTest(majorVer,minorVer,1,0))
		{



		}
		else 
		{
			MessageBox
			(
				NULL,
				"Invalid version number, using default template",
				"Template Version Error",
				MB_OK
			);
			return;
		}

		//#== flags == 
		if(GetNextDataLine(f,lineBuf))
			sscanf
			(	lineBuf," %hi",
				&globCreatedTeamsOnly
			);
		int i;
		
		//#QB prototypes
		for_i0(i,MAD04__NUM_BASES__QB)
		{
			if(GetNextDataLine(f,lineBuf))
				ReadPrototypeLine
				(	qbBases[i],lineBuf,true);
		}
		//#RB prototypes
		for_i0(i,MAD04__NUM_BASES__RB)
		{
			if(GetNextDataLine(f,lineBuf))
				ReadPrototypeLine
				(	rbBases[i],lineBuf,true);
		}
		//#FB prototypes
		for_i0(i,MAD04__NUM_BASES__FB)
		{
			if(GetNextDataLine(f,lineBuf))
				ReadPrototypeLine
				(	fbBases[i],lineBuf,true);
		}
		//#WR prototypes
		for_i0(i,MAD04__NUM_BASES__WR)
		{
			if(GetNextDataLine(f,lineBuf))
				ReadPrototypeLine
				(	wrBases[i],lineBuf,true);
		}
		//#TE prototypes
		for_i0(i,MAD04__NUM_BASES__TE)
		{
			if(GetNextDataLine(f,lineBuf))
				ReadPrototypeLine
				(	teBases[i],lineBuf,true);
		}
		//#OL prototypes
		for_i0(i,MAD04__NUM_BASES__OL)
		{
			if(GetNextDataLine(f,lineBuf))
				ReadPrototypeLine
				(	olBases[i],lineBuf,true);
		}
		//#DE prototypes
		for_i0(i,MAD04__NUM_BASES__DE)
		{
			if(GetNextDataLine(f,lineBuf))
				ReadPrototypeLine
				(	deBases[i],lineBuf,true);
		}
		//#DT prototypes
		for_i0(i,MAD04__NUM_BASES__DT)
		{
			if(GetNextDataLine(f,lineBuf))
				ReadPrototypeLine
				(	dtBases[i],lineBuf,true);
		}
		//#LB prototypes
		for_i0(i,MAD04__NUM_BASES__LB)
		{
			if(GetNextDataLine(f,lineBuf))
				ReadPrototypeLine
				(	lbBases[i],lineBuf,true);
		}
		//#CB prototypes
		for_i0(i,MAD04__NUM_BASES__CB)
		{
			if(GetNextDataLine(f,lineBuf))
				ReadPrototypeLine
				(	cbBases[i],lineBuf,true);
		}
		//#S prototypes
		for_i0(i,MAD04__NUM_BASES__S)
		{
			if(GetNextDataLine(f,lineBuf))
				ReadPrototypeLine
				(	safBases[i],lineBuf,true);
		}
		//#KP prototypes
		for_i0(i,MAD04__NUM_BASES__KP)
		{
			if(GetNextDataLine(f,lineBuf))
				ReadPrototypeLine
				(	kpBases[i],lineBuf,true);
		}

		
		//#Variance range +/-
		if(GetNextDataLine(f,lineBuf))
			ReadPrototypeLine
			(	RTG_VARIANCE,lineBuf,false);
		//#min
		if(GetNextDataLine(f,lineBuf))
			ReadPrototypeLine
			(	RTG_MIN,lineBuf,true);
		//#max
		if(GetNextDataLine(f,lineBuf))
			ReadPrototypeLine
			(	RTG_MAX,lineBuf,true);

		//#== Skin tones ==
		if(GetNextDataLine(f,lineBuf))
		{
			sscanf
			(	
				lineBuf
				,
				" %hi"
				" %hi"
				" %hi"
				" %hi"
				" %hi"
				" %hi"
				" %hi"
				" %hi"
				,&SKIN_TONE_DISTRIBUTION[0]
				,&SKIN_TONE_DISTRIBUTION[1]
				,&SKIN_TONE_DISTRIBUTION[2]
				,&SKIN_TONE_DISTRIBUTION[3]
				,&SKIN_TONE_DISTRIBUTION[4]
				,&SKIN_TONE_DISTRIBUTION[5]
				,&SKIN_TONE_DISTRIBUTION[6]
				,&SKIN_TONE_DISTRIBUTION[7]
			);
		}

		//#== Age ==
		if(GetNextDataLine(f,lineBuf))
		{
			sscanf
			(	
				lineBuf
				,
				" %hi"
				" %hi"
				,&ageMin
				,&ageMax
			);
		}
	}
}
