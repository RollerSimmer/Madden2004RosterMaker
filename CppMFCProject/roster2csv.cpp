#include"playerFields.h"
#include"roster2csv.h"
#include"../tdbaccess/c++ include/tdbAccess.h"
#include<codeShortcuts.h>
#include"resource.h"
#include"numTeams.h"
#include<time.h>
#include"skinTone.h"
#include"playerAge.h"
#include"buildFlags.h"

#include"posPrototypes.h"
#include"overallRtg.h"

#include"teamArea.h"
#include"ProcessTemplate.h"


int RandVariance(int val,int varyVal,int minV,int maxV);


#define DO_FILE_SAVE 1
#define PRINT_ONLY_1_FIELD 0
#define DO_RAND_FIELDS 1

typedef bool JERSEY_NUM_STATES[100];
JERSEY_NUM_STATES*teamJrsyNums=NULL;



typedef struct 
{
	//info
	char name[12];
	char surname[14];
	short posId;
	short teamId;
	short collegeId;
	short jerseyNum;
	short age;
	short strongHand;
	short throwStyle;
	//appearance
	short skinTone;
	short hairColor;
	short hairStyle;
	short faceSkin;
	short faceShape;
	short tattoos[2];
	//build
	//
	short bodySize;
	short waistSize;
	short muscle[5];
	short fat[5];
	//equip
	short helmShell;
	short facemask;
	short visor;
	short eyePaint;
	short nasalStrap;
	short mouthpiece;
	short neckPad;
	short elbows[2];
	short wrists[2];
	short hands[2];
	short ankles[2];
	short knees;
	//ratings
	short overallRtg;
	
	union
	{
	struct
	{
	short height;
	short weight;

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
	};
	MAD04__PLATER_PROTOTYPE_STRUCT
		prototype;
	short rtgs[NUM_PROT_RATINGS];
	};


	//misc
	short photoID;

	CalcBuild();
	CalcOvrRtg();
	PrototypeVariance(MAD04__PLATER_PROTOTYPE_STRUCT&rv);
	PosPrototype();
	ReadPlayer_FromCSV(FILE*f,int index);
	WritePlayer_ToCSV(FILE*f,int index,CString outStr);
	ReadPlayer_FromROS(int tdbI,int index);
	WritePlayer_ToROS(int tdbI,int index);
	AutoPlayer(int numTeams,int ageType);
}
ROS_PLAYER;

AutoRos
(	char*rosNm,CEdit_Append&outEdit,bool createdTeamsOnly
	,CString unkTeamField,short ageType
	,bool useTemplate,char*tmpltNm
)
{
	char teamName[48],cityName[48];
	char*tmpS;

	if(useTemplate)
		ProcessTemplate(tmpltNm);
	else
		globCreatedTeamsOnly=createdTeamsOnly;

	TtdbTableProperties 
		playerTable,&pt=playerTable,
		teamTable,&tt=teamTable;
	CString tmpOut;

	char**teamNames;

	short teamDivSz=MAD04__MAX_TEAM_IDS*sz(short);

	short*teamDivs=(short*)malloc(teamDivSz);

	char nameBufr[8];
	char nameBufr_tm[8];
	char*tnp;

	long tdbI;
	bool ret;
	long playerBufSz;

	int 
		numPlayers,numTeams,
		pi,ti,tid,
		unk;

	ROS_PLAYER player,&p=player,
		*players;

	tnp=&teamName[0];

	pt.name=&nameBufr[0];
	tt.name=&nameBufr_tm[0];
	
	TDBInit();
	TDBInit();
	tdbI=TDBOpen(rosNm);
	outEdit.Set("");


	if(TDBTableGetProperties(tdbI,"TEAM",teamTable))
	{
		numTeams=tt.RecordCount;
		teamJrsyNums=
			(JERSEY_NUM_STATES*)
			malloc(numTeams*sz(JERSEY_NUM_STATES));
		memset(teamJrsyNums,false,(numTeams*sz(JERSEY_NUM_STATES)));
	}

	int fi;

	//switch for team field dump
	#if 0

	TtdbFieldProperties teamField;
	char fieldName[16];

	teamField.name=fieldName;

	for_i0(fi,tt.FieldCount)
	{

		TDBFieldGetProperties(tdbI,"TEAM",fi,teamField);


		tmpOut.Format
		(	
			"%u\t"
			"%s\t"			
			"%u\t"
			,
			fi
			,
			teamField.name
			,
			teamField.size
		);
		outEdit.Append(tmpOut);

		outEdit.Append("\r\n");
	}

	#endif

	//switch for team dump
	#if 0
	for_i0(ti,numTeams)
	{
		tmpS=(char*)&(teamName[0]);
		TDBFieldGetValueAsString(tdbI,"TEAM",FULL_TEAM_NAME,ti,tmpS);
		tmpS=(char*)&(cityName[0]);
		TDBFieldGetValueAsString(tdbI,"TEAM",CITY_NAME,ti,tmpS);
		tid=TDBFieldGetValueAsInteger(tdbI,"TEAM",TEAM_GLOBAL_ID,ti);
		unk=TDBFieldGetValueAsInteger(tdbI,"TEAM",unkTeamField.GetBuffer(0),ti);

		tmpOut.Format
		(	
			"%u\t"
			"%s\t"			
			"%s\t"
			"%u\t"
			"%u\t"
			,
			ti
			,
			cityName
			,
			teamName
			,
			tid
			,
			unk
		);
		outEdit.Append(tmpOut);

		#if 1
		outEdit.Append("\r\n");

		#endif


	}

	#else

		for_i0(tid,MAD04__MAX_TEAM_IDS)
		{
			teamDivs[tid]=MAD04__TEAM_DIV__AFC_EAST;
		}

		for_i0(ti,numTeams)
		{
			tid=TDBFieldGetValueAsInteger(tdbI,"TEAM",TEAM_GLOBAL_ID,ti);
			if(tid<MAD04__MAX_TEAM_IDS)
				teamDivs[tid]=TDBFieldGetValueAsInteger(tdbI,"TEAM",TEAM_DIVISION,ti);
		}

	#endif

	//switch for random players
	#if 1

	if(TDBTableGetProperties(tdbI,"PLAY",playerTable))
	{
		numPlayers=pt.RecordCount;

		playerBufSz=numPlayers*sz(*players);
		players=(ROS_PLAYER*)malloc(playerBufSz);

		for_i0(pi,numPlayers)
		{
			p.ReadPlayer_FromROS(tdbI,pi);
			#if(DO_RAND_FIELDS)
				if(globCreatedTeamsOnly)
				{
					if
					(	teamDivs[p.teamId]
						==
						MAD04__TEAM_DIV__CREATED
					)
						p.AutoPlayer(numTeams,ageType);
				}
				else
				{
					p.AutoPlayer(numTeams,ageType);
				}
			#endif 

			players[pi]=p;
			
			#if(!DO_FILE_SAVE)
				tmpOut.Format
				(	
					#if(!PRINT_ONLY_1_FIELD)
					"%s\t"
					"%s\t"
					"%u\t"
					"%u\t"
					"%u\t"
					#endif
					"%u\t"
					#if(!PRINT_ONLY_1_FIELD)
					,players[pi].name
					,players[pi].surname
					,players[pi].age
					,players[pi].posId
					,players[pi].skinTone
					#endif
					,players[pi].faceSkin

					#if(!PRINT_ONLY_1_FIELD)
					#endif
					#if 0
					,players[pi]
					,players[pi]
					,players[pi]
					,players[pi]
					#endif
				);
				outEdit.Append(tmpOut);

				#if 1
				outEdit.Append("\r\n");				

				#endif

			#else
			//file output
				players[pi].WritePlayer_ToROS(tdbI,pi);

				if((pi%200==0)||(pi==numPlayers-1))
				{
					tmpOut.Format("Player: %lu of %lu\r\n",pi,numPlayers-1);
					outEdit.Set(tmpOut);
				}



			#endif
		}

		if(players)
		{
			free(players);
		}
		outEdit.Append ("Done.\r\n");				
	}

	#endif

	if(teamJrsyNums)
	{
		free(teamJrsyNums);
		teamJrsyNums=NULL;
	}

	if(teamDivs)
	{
		free(teamDivs);
		teamDivs=NULL;
	}



	TDBSave(tdbI);
	TDBClose(tdbI);
	TDBDone();
	TDBDone();
}


Ros2Csv(char*rosNm,char*csvNm,CEdit_Append&outEdit)
{
	TtdbTableProperties 
		playerTable,&pt=playerTable,
		teamTable,&tt=teamTable;
	CString tmpOut;

	char**teamNames;

	char nameBufr[8];
	char nameBufr_tm[8];
	char teamName[48],*tnp;

	long tdbI;
	bool ret;
	long playerBufSz;

	int 
		numPlayers,numTeams,
		pi,ti;

	ROS_PLAYER player,&p=player,
		*players;

	tnp=&teamName[0];

	pt.name=&nameBufr[0];
	tt.name=&nameBufr_tm[0];

	TDBInit();
	TDBInit();
	tdbI=TDBOpen(rosNm);
	outEdit.Set("");

	if(TDBTableGetProperties(tdbI,"TEAM",teamTable))
	{
		if(TDBTableGetProperties(tdbI,"PLAY",playerTable))
		{
			numPlayers=pt.RecordCount;
			numTeams=tt.RecordCount;

			teamNames=(char**)malloc(sz(teamNames)*numTeams);

			for_i0(ti,numTeams)
			{
				if
				(
				
				ret
				=
				TDBFieldGetValueAsString
				(	tdbI,"TEAM","TMNA",ti,tnp	)
				
				)
				{
					tmpOut.Format("%s\r\n",teamName);
					//outEdit.Append(tmpOut);

					teamNames[ti]=(char*)malloc(strlen(teamName)+1);
					strcpy(teamNames[ti],teamName);
				}
				else
					teamNames[ti]=NULL;
			}

			playerBufSz=numPlayers*sz(*players);
			players=(ROS_PLAYER*)malloc(playerBufSz);

			for_i0(pi,numPlayers)
			{
				p.ReadPlayer_FromROS(tdbI,pi);
				players[pi]=p;
				if(p.teamId==ti)
				{
					#if 0
					tmpOut.Format("(%lu|%lu)",pi,ti);
					outEdit.Append(tmpOut);
					#endif
				}								
				#if 0
				outEdit.Append("\r\n");				
				#endif
			}

			
			#if 1
				for_i0(pi,numPlayers)
				{
					{
						#if 0
						tmpOut.Format
						(	
							"%lu\t"
							"%u\t"
							"%s\t"
							"%s\t"
							"%u\t"
							"%u\t"
							"%u\t"
							"%u\t"
							,pi
							,players[pi].teamId
							,players[pi].name
							,players[pi].surname
							,players[pi].skinTone
							,players[pi].jerseyNum
							,players[pi].posId
							,players[pi].faceSkin
							#if 0
							,players[pi]
							,players[pi]
							,players[pi]
							,players[pi]
							#endif
						);
						outEdit.Append(tmpOut);


						#else
						//file output



						#endif
					}								
					#if 1
					outEdit.Append("\r\n");				
					#endif
				}
			#endif
			//for_i0(pi,numPlayers)

			if(teamNames)	
			{
				for_i0(ti,numTeams)
				{	if(teamNames[ti])	free(teamNames[ti]);	}
				free(teamNames);
			}
			if(players)
			{
				free(players);
			}
		}
	}
	
	TDBClose(tdbI);
	TDBDone();
	TDBDone();
}


ROS_PLAYER::ReadPlayer_FromCSV(FILE*f,int index)
{


	
}

ROS_PLAYER::WritePlayer_ToCSV(FILE*f,int index,CString outStr)
{

	
}

#define GetStr(a,b)\
	tmpS=(char*)&(this->a[0]);\
	TDBFieldGetValueAsString(tdbI,"PLAY",&b[0],index,tmpS);
#define GetInt(a,b)\
	this->a=TDBFieldGetValueAsInteger(tdbI,"PLAY",&b[0],index);

ROS_PLAYER::ReadPlayer_FromROS(int tdbI,int index)
{
	char*tmpS;

	//info
	GetInt(age,AGE);

	GetStr(name,FIRST_NAME);
	GetStr(surname,LAST_NAME);
	GetInt(posId,POSITION_ID);
	GetInt(teamId,TEAM_GLOBAL_ID);
	GetInt(jerseyNum,JERSEY_NUM);	
	GetInt(skinTone,SKIN_COLOR);
	GetInt(faceSkin,FACE_ID);
	GetInt(photoID,PLAYER_PHOTO);
	GetInt(collegeId,COLLEGE_ID);

	//size

	GetInt(height,HEIGHT);
	GetInt(weight,WEIGHT);

	//hair
	GetInt(hairColor,HAIR_COLOR);
	GetInt(hairStyle,HAIR_STYLE);

	//ratings
	GetInt(speeds[0],SPEED);
	GetInt(speeds[1],AGILITY);
	GetInt(speeds[2],ACCELERATION);
	GetInt(strength,STRENGTH);
	GetInt(awareness,AWARENESS);
	GetInt(catching,CATCHING);
	GetInt(carry,CARRYING);
	GetInt(jump,JUMPING);
	GetInt(breakTackle,BREAK_TACKLE);
	GetInt(tackle,TACKLE);
	GetInt(throwing[0],THROW_POWER);
	GetInt(throwing[1],THROW_ACCURACY);
	GetInt(blocking[0],PASS_BLOCKING);
	GetInt(blocking[1],RUN_BLOCKING);
	GetInt(kicking[0],KICK_POWER);
	GetInt(kicking[1],KICK_ACCURACY);
	GetInt(kickReturn,KICK_RETURN);
	GetInt(injury,INJURY);
	GetInt(stamina,STAMINA);
	GetInt(toughness,TOUGHNESS);
	GetInt(import,PLYR_IMPORT);

	//overall rating
	GetInt(overallRtg,OVERALL);	


	//BUILD

	GetInt(muscle[0],BODY_MUSCLE);
	GetInt(muscle[1],ARMS_MUSCLE);
	GetInt(muscle[2],LEGS_THIGH_MUSCLE);
	GetInt(muscle[3],LEGS_CALF_MUSCLE);
	GetInt(muscle[4],BUTT_MUSCLE);

	GetInt(fat[0],BODY_FAT);
	GetInt(fat[1],ARMS_FAT);
	GetInt(fat[2],LEGS_THIGH_FAT);
	GetInt(fat[3],LEGS_CALF_FAT);
	GetInt(fat[4],BUTT_FAT);

	GetInt(bodySize,BODY_OVERALL);

	GetInt(waistSize,BODY_WEIGHT);
}

#undef GetStr
#undef GetInt

#define SetStr(a,b)\
	tmpS=(char*)&(this->a[0]);\
	TDBFieldSetValueAsString(tdbI,"PLAY",&b[0],index,tmpS);
#define SetInt(a,b)\
	TDBFieldSetValueAsInteger(tdbI,"PLAY",&b[0],index,this->a);


ROS_PLAYER::WritePlayer_ToROS(int tdbI,int index)
{
	char*tmpS;
	//info
	SetInt(age,AGE);

	SetStr(name,FIRST_NAME);
	SetStr(surname,LAST_NAME);
	SetInt(posId,POSITION_ID);
	SetInt(teamId,TEAM_GLOBAL_ID);
	SetInt(jerseyNum,JERSEY_NUM);	
	SetInt(skinTone,SKIN_COLOR);
	SetInt(faceSkin,FACE_ID);
	SetInt(photoID,PLAYER_PHOTO);
	SetInt(collegeId,COLLEGE_ID);

	//size

	SetInt(height,HEIGHT);
	SetInt(weight,WEIGHT);

	//hair
	SetInt(hairColor,HAIR_COLOR);
	SetInt(hairStyle,HAIR_STYLE);

	//ratings
	SetInt(speeds[0],SPEED);
	SetInt(speeds[1],AGILITY);
	SetInt(speeds[2],ACCELERATION);
	SetInt(strength,STRENGTH);
	SetInt(awareness,AWARENESS);
	SetInt(catching,CATCHING);
	SetInt(carry,CARRYING);
	SetInt(jump,JUMPING);
	SetInt(breakTackle,BREAK_TACKLE);
	SetInt(tackle,TACKLE);
	SetInt(throwing[0],THROW_POWER);
	SetInt(throwing[1],THROW_ACCURACY);
	SetInt(blocking[0],PASS_BLOCKING);
	SetInt(blocking[1],RUN_BLOCKING);
	SetInt(kicking[0],KICK_POWER);
	SetInt(kicking[1],KICK_ACCURACY);
	SetInt(kickReturn,KICK_RETURN);
	SetInt(injury,INJURY);
	SetInt(stamina,STAMINA);
	SetInt(toughness,TOUGHNESS);
	SetInt(import,PLYR_IMPORT);

	//overall rating
	SetInt(overallRtg,OVERALL);

	//BUILD



	SetInt(muscle[0],BODY_MUSCLE);
	SetInt(muscle[1],ARMS_MUSCLE);
	SetInt(muscle[2],LEGS_THIGH_MUSCLE);
	SetInt(muscle[3],LEGS_CALF_MUSCLE);
	SetInt(muscle[4],BUTT_MUSCLE);

	SetInt(fat[0],BODY_FAT);
	SetInt(fat[1],ARMS_FAT);
	SetInt(fat[2],LEGS_THIGH_FAT);
	SetInt(fat[3],LEGS_CALF_FAT);
	SetInt(fat[4],BUTT_FAT);

	SetInt(bodySize,BODY_OVERALL);

	SetInt(waistSize,BODY_WEIGHT);

}
#undef SetStr
#undef SetInt


GetNameBufLine(char*lineBuf,char**buf,bool bufInc)
{
	char*svP=*buf;
	int i;
	while((**buf!='\r')&&(**buf!='\n')&&(**buf!=0))
	{
		*(lineBuf++)=*((*buf)++);
	}
	*(lineBuf++)=0;
	while(((**buf=='\r')||(**buf=='\n'))&&(**buf!=0))
	{
		++(*buf);
	}

	if(!bufInc)
		*buf=svP;
}

int GetNameRandIndex(int numNames,int numTiers)
{
	int tier,rangeSpan;
	int randI;

	tier=rand()%numTiers;

	rangeSpan=numNames;
	while(tier>0)
	{
		rangeSpan/=2;	
		--tier;
		rangeSpan=__max(1,rangeSpan);
	}

	return(randI=rand()%rangeSpan);
}

const short NUM_NAME_TIERS=4;

GetRandPlayerName(char*buffer,int szBuf)
{
	static bool init=false;

	typedef char RAND_NAME__ENTRY[16];

	static char*rsrcBuf,*rsrcBufBs;
	static RAND_NAME__ENTRY*names;

	char tmpStr[48];
	static int numNames;

	int i,randI;

	if(!init)
	{
		HRSRC frsrc;
		HGLOBAL rsrc;
		frsrc
		=
		FindResource
		(
			NULL,
			MAKEINTRESOURCE(IDR_NAMES),  // pointer to resource name
			"NAME_LIST"   // pointer to resource type
		);
		rsrc=LoadResource(NULL,frsrc);
		rsrcBufBs=rsrcBuf=(char*)LockResource(rsrc);

		GetNameBufLine(tmpStr,&rsrcBuf,true);
		sscanf(tmpStr,"%lu",&numNames);

		names=(RAND_NAME__ENTRY*)malloc(sz(RAND_NAME__ENTRY)*numNames);

		for_i0(i,numNames)
		{
			GetNameBufLine(tmpStr,&rsrcBuf,true);
			strncpy(&names[i][0],tmpStr,sz(names[i])-1);
		}

		init=true;
	}

	randI=GetNameRandIndex(numNames,NUM_NAME_TIERS);

	strncpy(buffer,&names[randI][0],szBuf-1);
}

GetRandPlyrSurname(char*buffer,int szBuf)
{
	static bool init=false;

	typedef char RAND_NAME__ENTRY[16];

	static char*rsrcBuf,*rsrcBufBs;
	static RAND_NAME__ENTRY*names;

	char tmpStr[48];
	static int numNames;

	int i,randI;

	if(!init)
	{
		HRSRC frsrc;
		HGLOBAL rsrc;
		frsrc
		=
		FindResource
		(
			NULL,
			MAKEINTRESOURCE(IDR_SURNAMES),  // pointer to resource name
			"NAME_LIST"   // pointer to resource type
		);
		rsrc=LoadResource(NULL,frsrc);
		rsrcBufBs=rsrcBuf=(char*)LockResource(rsrc);


		GetNameBufLine(tmpStr,&rsrcBuf,true);
		sscanf(tmpStr,"%lu",&numNames);


		names=(RAND_NAME__ENTRY*)malloc(sz(RAND_NAME__ENTRY)*numNames);

		for_i0(i,numNames)
		{
			GetNameBufLine(tmpStr,&rsrcBuf,true);
			strncpy(&names[i][0],tmpStr,sz(names[i])-1);
		}

		init=true;
	}

	randI=GetNameRandIndex(numNames,NUM_NAME_TIERS);

	strncpy(buffer,&names[randI][0],szBuf-1);
}

const int NUM_FACE_SKINS=450;
const int NUM_SKIN_TONES=7;
const int SKINS_PER_TONE
	=NUM_FACE_SKINS/NUM_SKIN_TONES;

const int NUM_COLLEGES=266;


short RandRange(int lo,int hi)
{
	if(hi<lo)return(RandRange(hi,lo));

	int r,span=hi-lo;
	
	r=rand()%(span+1);
	return(r+=lo);
}


short RandJerseyNum(short pos)
{
	int jn=0;

	switch(pos)
	{
	case MAD04__POS_ID__QB:
		jn=RandRange(0,19);
		break;
	case MAD04__POS_ID__RB:
	case MAD04__POS_ID__FB:
	case MAD04__POS_ID__CB:
	case MAD04__POS_ID__FS:
	case MAD04__POS_ID__SS:
		jn=RandRange(0,49);
		break;
	case MAD04__POS_ID__WR:
	case MAD04__POS_ID__TE:
		switch(rand()%3)
		{
		case 0:
			jn=RandRange(80,89);
			break;
		case 1:
		case 2:
		default:
			jn=RandRange(0,49);
			break;
		}
		break;
	case MAD04__POS_ID__LT:
	case MAD04__POS_ID__LG:
	case MAD04__POS_ID__C:
	case MAD04__POS_ID__RG:
	case MAD04__POS_ID__RT:
		jn=RandRange(50,79);
		break;
	case MAD04__POS_ID__LE:
	case MAD04__POS_ID__RE:
	case MAD04__POS_ID__DT:
		switch(rand()%3)
		{
		case 0:
			jn=RandRange(0,99);
			break;
		case 1:
		case 2:
		default:
			jn=RandRange(90,99);
			break;
		}
		break;
	case MAD04__POS_ID__LOLB:
	case MAD04__POS_ID__ILB:
	case MAD04__POS_ID__ROLB:
		switch(rand()%4)
		{
		case 0:
			jn=RandRange(0,99);
			break;
		case 1:
		case 2:
		case 3:
		default:
			jn=RandRange(30,59);
			break;
		}
		break;
	case MAD04__POS_ID__K:
	case MAD04__POS_ID__P:
		switch(rand()%2)
		{
		case 0:
			jn=RandRange(0,99);
			break;
		case 1:
		default:
			jn=RandRange(0,19);
			break;
		}
		break;
	};

	return(jn);
}



short GenUniqueJerseyNum(short pos,int teamI,int numTeams)
{
	short ujn,pass=0;

	if(teamI<numTeams)
	{
		do
		{		
			ujn=RandJerseyNum(pos);
			++pass;
		}
		while((pass<4)&&(teamJrsyNums[teamI][ujn]));

		while(teamJrsyNums[teamI][ujn])
		{
			if(ujn<99)
				++ujn;
			else
				ujn=0;
		}

		teamJrsyNums[teamI][ujn]=true;
	}
	else
		ujn=RandJerseyNum(pos);
	


	return(ujn);
}


int GetFaceSkin(int skinTone)
{
	int gfs=0;

	switch(skinTone)
	{
	case 0:gfs=RandRange(114,122);break;
	case 1:gfs=RandRange(123,133);break;
	case 2:gfs=RandRange(134,140);break;
	case 3:gfs=RandRange(141,149);break;
	case 4:gfs=RandRange(150,158);break;
	case 5:gfs=RandRange(159,167);break;
	case 6:gfs=RandRange(168,176);break;
	case 7:gfs=RandRange(177,177);break;
	}

	return gfs;


}

RandProbability(int lo,int hi,int*weights)
{
	if(lo>hi)return(RandProbability(hi,lo,weights));

	int numWeights=abs(hi-lo+1);
	long wtTally,i; 

	long rndN;

	wtTally=0;

	for_i0(i,numWeights)
	{
		wtTally+=weights[i];		
	}

	rndN=rand()%wtTally;
	wtTally=0;

	for_i0(i,numWeights)
	{	
		wtTally+=weights[i];
		if(rndN<wtTally)
			return(lo+i);
	}
	return lo;
}


ROS_PLAYER::AutoPlayer(int numTeams,int ageType)
{
	static bool init=false;
	if(!init){srand((unsigned int)time(NULL));init=true;}

	switch(ageType)
	{
	case 0://high school
		age=RandRange(13,19);
		break;
	case 1://college
		age=RandRange(17,24);
		break;
	case 2://pro
	default:
		age=RandRange(18,32);
		break;
	case 3://custom
		age=RandRange(ageMin,ageMax);
		break;
	}
	
	this->skinTone=RandProbability(0,7,&SKIN_TONE_DISTRIBUTION[0]);
	this->faceSkin=GetFaceSkin(this->skinTone);

	this->photoID=0;
	this->collegeId=rand()%NUM_COLLEGES;

	this->hairColor=rand()%5;
	this->hairStyle=rand()%16;

	PosPrototype();

	GetRandPlayerName(this->name,sz(this->name));
	GetRandPlyrSurname(this->surname,sz(this->surname));

	this->jerseyNum=GenUniqueJerseyNum(this->posId,this->teamId,numTeams);

	#if 1
	CalcBuild();
	#endif
}




ROS_PLAYER::PosPrototype()
{
	short pti;


	switch(this->posId)
	{
	case MAD04__POS_ID__QB:
		pti=rand()%MAD04__NUM_BASES__QB;
		this->prototype=qbBases[pti];
		break;
	case MAD04__POS_ID__RB:
		pti=rand()%MAD04__NUM_BASES__RB;
		this->prototype=rbBases[pti];
		break;
	case MAD04__POS_ID__FB:
		pti=rand()%MAD04__NUM_BASES__FB;
		this->prototype=fbBases[pti];
		break;
	case MAD04__POS_ID__WR:
		pti=rand()%MAD04__NUM_BASES__WR;
		this->prototype=wrBases[pti];
		break;
	case MAD04__POS_ID__TE:
		pti=rand()%MAD04__NUM_BASES__TE;
		this->prototype=teBases[pti];
		break;
	case MAD04__POS_ID__LT:
	case MAD04__POS_ID__LG:
	case MAD04__POS_ID__C:
	case MAD04__POS_ID__RG:
	case MAD04__POS_ID__RT:
		pti=rand()%MAD04__NUM_BASES__OL;
		this->prototype=olBases[pti];
		break;
	case MAD04__POS_ID__LE:
	case MAD04__POS_ID__RE:
		pti=rand()%MAD04__NUM_BASES__DE;
		this->prototype=deBases[pti];
		break;
	case MAD04__POS_ID__DT:
		pti=rand()%MAD04__NUM_BASES__DT;
		this->prototype=dtBases[pti];
		break;
	case MAD04__POS_ID__LOLB:
	case MAD04__POS_ID__ILB:
	case MAD04__POS_ID__ROLB:
		pti=rand()%MAD04__NUM_BASES__LB;
		this->prototype=lbBases[pti];
		break;
	case MAD04__POS_ID__CB:
		pti=rand()%MAD04__NUM_BASES__CB;
		this->prototype=cbBases[pti];
		break;
	case MAD04__POS_ID__FS:
	case MAD04__POS_ID__SS:
		pti=rand()%MAD04__NUM_BASES__S;
		this->prototype=safBases[pti];
		break;
	case MAD04__POS_ID__K:
	case MAD04__POS_ID__P:
		pti=rand()%MAD04__NUM_BASES__KP;
		this->prototype=kpBases[pti];
		break;
	}


	PrototypeVariance(RTG_VARIANCE);

	CalcOvrRtg();



}



int RandVariance(int val,int varyVal,int lo,int hi)
{
	if(lo>hi)return(RandVariance(val,varyVal,hi,lo));
	int rndInc;

	rndInc=(int)rand()%((varyVal+1)*2)-varyVal;

	val+=rndInc;
	val=__min(val,hi);
	val=__max(val,lo);

	return(val);
}


ROS_PLAYER::PrototypeVariance(MAD04__PLATER_PROTOTYPE_STRUCT&rv)
{
	int ri;

	for_i0(ri,NUM_PROT_RATINGS)
	{
		rtgs[ri]
		=
		RandVariance
		(
			rtgs[ri]
			,
			RTG_VARY_ARRAY[ri]
			,
			RTG_MIN_ARRAY[ri]
			,
			RTG_MAX_ARRAY[ri]
		);
	}

}

ROS_PLAYER::CalcOvrRtg()
{
	int ovrPos;
	int ri;


	switch(this->posId)
	{
	case MAD04__POS_ID__QB:
		ovrPos=MAD04_OVR_QB;
		break;
	case MAD04__POS_ID__RB:
		ovrPos=MAD04_OVR_RB;
		break;
	case MAD04__POS_ID__FB:
		ovrPos=MAD04_OVR_FB;
		break;
	case MAD04__POS_ID__WR:
		ovrPos=MAD04_OVR_WR;
		break;
	case MAD04__POS_ID__TE:
		ovrPos=MAD04_OVR_TE;
		break;
	case MAD04__POS_ID__LT:
	case MAD04__POS_ID__RT:
		ovrPos=MAD04_OVR_T;
		break;
	case MAD04__POS_ID__LG:
	case MAD04__POS_ID__RG:
		ovrPos=MAD04_OVR_G;
		break;
	case MAD04__POS_ID__C:
		ovrPos=MAD04_OVR_C;
		break;
	case MAD04__POS_ID__LE:
	case MAD04__POS_ID__RE:
		ovrPos=MAD04_OVR_DE;
		break;
	case MAD04__POS_ID__DT:
		ovrPos=MAD04_OVR_DT;
		break;
	case MAD04__POS_ID__LOLB:
	case MAD04__POS_ID__ROLB:
		ovrPos=MAD04_OVR_OLB;
		break;
	case MAD04__POS_ID__ILB:
		ovrPos=MAD04_OVR_ILB;
		break;
	case MAD04__POS_ID__CB:
		ovrPos=MAD04_OVR_CB;
		break;
	case MAD04__POS_ID__FS:
		ovrPos=MAD04_OVR_FS;
		break;
	case MAD04__POS_ID__SS:
		ovrPos=MAD04_OVR_SS;
		break;
	case MAD04__POS_ID__K:
		ovrPos=MAD04_OVR_K;
		break;
	case MAD04__POS_ID__P:
		ovrPos=MAD04_OVR_P;
		break;
	default: 
		return(0);
	}

	this->overallRtg=baseOvrRtgs[ovrPos];

	for_i0(ri,NUM_ABILITY_RATINGS)
	{
		overallRtg
		+=
		(
		this->rtgs[2+ofm[ri]]
		*
		posOvrWts[ovrPos][ri]
		)
		/
		100;
	}

	overallRtg=__max(overallRtg,12);
	overallRtg=__min(overallRtg,99);
}

long ScaleWeight_7feet(short ht,short wt)
{
	long sw;

	long htFactor=84*100/ht,shf;

	wt+=160;

	//cube it
	shf=htFactor;
	htFactor=(htFactor*shf)/100;
	#if 1
	htFactor=(htFactor*shf)/100;
	#endif

	sw=(long(wt)*htFactor)/100;

	return(sw);
}

ROS_PLAYER::CalcBuild()
{
	int i;
	bool dummy;
	long scaleWeight;
	long muscleMass,fatMass,totMass;
	scaleWeight=ScaleWeight_7feet(this->height,this->weight);
	totMass=__max(0,scaleWeight-250);

	if(strength>95)
	{
		dummy=true;
	}

	muscleMass=__min(totMass,strength*3/2);
	fatMass=totMass-muscleMass;

	muscleMass=muscleMass*2/3;
	fatMass=fatMass*2/3;
	muscleMass=__max(0,__min(99,(muscleMass)));
	fatMass=__max(0,__min(99,(fatMass)));

	for_i0(i,5)
	{
		this->fat[i]=fatMass;
		this->muscle[i]=muscleMass;
	}
	fat[0]/=2;
	muscle[0]=muscle[0]*2/3;
	//muscle[0]/=2;

	bodySize=totMass*2/3;
	bodySize=__min(bodySize,99);
	bodySize=__max(bodySize,0);

	waistSize=0;
}



