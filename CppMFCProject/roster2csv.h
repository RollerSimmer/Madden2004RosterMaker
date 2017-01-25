//roster2csv.h
#pragma once
#include"stdafx.h"
#include"Edit_Append.h"


Ros2Csv(char*rosNm,char*csvNm,CEdit_Append&outEdit);
AutoRos
(	char*rosNm,CEdit_Append&outEdit,bool createdTeamsOnly
	,CString unkTeamField,short ageType
	,bool useTemplate,char*tmpltNm
);
ProcessTemplate(char*tmpltNm);