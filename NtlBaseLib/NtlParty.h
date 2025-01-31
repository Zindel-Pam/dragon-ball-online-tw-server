﻿#pragma once

#include "NtlSharedDef.h"
#include "NtlSharedType.h"
#include "NtlVector.h"
#include "NtlItem.h"

enum eINVITATION_RESPONSE
{
	INVITATION_RESPONSE_ACCEPT = 0,		// 파티 초대에 응하기
	INVITATION_RESPONSE_DECLINE,		// 파티 초대를 거절하기
	INVITATION_RESPONSE_EXPIRE,			// 파티 초대가 타임아웃 되었음을 알리기

	INVITATION_RESPONSE_COUNT,

	INVITATION_RESPONSE_FIRST = INVITATION_RESPONSE_ACCEPT,
	INVITATION_RESPONSE_LAST = INVITATION_RESPONSE_EXPIRE
};

enum ePARTY_ZENNY_LOOTING
{
	PARTY_ZENNY_LOOTING_GREEDILY = 0,		// 제니를 줍는 멤버가 모두 가진다.
	PARTY_ZENNY_LOOTING_SHARED,				// 제니를 멤버에게 공평하게 나눠준다.

	PARTY_ZENNY_LOOTING_COUNT,

	PARTY_ZENNY_LOOTING_UNKNOWN = 0xFF,

	PARTY_ZENNY_LOOTING_FIRST = PARTY_ZENNY_LOOTING_GREEDILY,
	PARTY_ZENNY_LOOTING_LAST = PARTY_ZENNY_LOOTING_SHARED
};

enum ePARTY_ITEM_LOOTING
{
	PARTY_ITEM_LOOTING_GREEDILY = 0,			// 아이템을 줍는 멤버가 무조건 가진다.
	PARTY_ITEM_LOOTING_IN_ORDER,				// 아이템의 종류에 관계 없이 무조건 순서대로 분배한다.
	PARTY_ITEM_LOOTING_IN_ORDER_SEPERATELY,		// Normal 등급의 분배 순서와 Excellent 등급 이상의 분배 순서를 따로 취급한다.
	
	PARTY_ITEM_LOOTING_IN_LEADER,				// 리더가 임의로 분배
	PARTY_ITEM_LOOTING_BY_ZENNY,				// 제니를 등록하고 승락하여 분배
	PARTY_ITEM_LOOTING_DICE,					// 주사위로 분배

	PARTY_ITEM_LOOTING_COUNT,

	PARTY_ITEM_LOOTING_UNKNOWN = 0xFF,

	PARTY_ITEM_LOOTING_FIRST = PARTY_ITEM_LOOTING_GREEDILY,
	PARTY_ITEM_LOOTING_LAST = PARTY_ITEM_LOOTING_DICE
};

enum eDBO_PARTY_OPTION
{
	DBO_PARTY_OPTION_CANT_INVITE = 0,
	DBO_PARTY_OPTION_CANT_LEAVE,
	DBO_PARTY_OPTION_CANT_KICK_OUT,
	DBO_PARTY_OPTION_CANT_APPOINT_LEADER
};

enum eDBO_PARTY_OPTION_FLAG
{
	DBO_PARTY_OPTION_FLAG_CANT_INVITE = 1 << DBO_PARTY_OPTION_CANT_INVITE,
	DBO_PARTY_OPTION_FLAG_CANT_LEAVE = 1 << DBO_PARTY_OPTION_CANT_LEAVE,
	DBO_PARTY_OPTION_FLAG_CANT_KICK_OUT = 1 << DBO_PARTY_OPTION_CANT_KICK_OUT,
	DBO_PARTY_OPTION_FLAG_CANT_APPOINT_LEADER = 1 << DBO_PARTY_OPTION_CANT_APPOINT_LEADER
};

//-----------------------------------------------------------------------------------
//	파티 관련 상수 정의
//-----------------------------------------------------------------------------------
// Basic Values
const DWORD MAX_PARTY_COUNT = 2000;

const DWORD MAX_MEMBER_IN_PARTY = 5;
const float VALID_DISTANCE_FOR_EXP_FROM_VICTIM = 100.0f;
const float DBO_VALID_DISTANCE_TO_GET_ZENNY_IN_PARTY = 100.0f;
const float DBO_VALID_DISTANCE_TO_GET_ITEM_IN_PARTY = 100.0f;

// Charm
const DWORD PARTY_CHARM_INVENTORY_COUNT = 2;
const DWORD SLOT_COUNT_IN_PARTY_CHARM_INVENTORY = 11;
const DWORD MAX_PARTY_BUFF = 2;

const DWORD DBO_MAX_TIME_PARTY_CHARM_DICE = 30000;		//30sec 
const DWORD DBO_MAX_TIME_PARTY_DICE_ITEM = 30000;		//30sec 
const BYTE	DBO_PARTY_INVEN_DEFAULT_ITEM_RANK = ITEM_RANK_SUPERIOR;
// Contribution Point
//const DWORD PARTY_MAX_CONTRIBUTION_POINT = 200;

// Party Inventory
const DWORD PARTY_INVENTORY_SLOT_COUNT = 16;

// Party Option
const DWORD DBO_PARTY_OPTION_FLAG_DEFAULT = 0;
const DWORD DBO_PARTY_OPTION_FLAG_TMQ =
			DBO_PARTY_OPTION_FLAG_CANT_INVITE |
			DBO_PARTY_OPTION_FLAG_CANT_LEAVE |
			DBO_PARTY_OPTION_FLAG_CANT_KICK_OUT |
			DBO_PARTY_OPTION_FLAG_CANT_APPOINT_LEADER;
const DWORD DBO_PARTY_OPTION_FLAG_RANK_BATTLE =
			DBO_PARTY_OPTION_FLAG_CANT_INVITE |
			DBO_PARTY_OPTION_FLAG_CANT_LEAVE |
			DBO_PARTY_OPTION_FLAG_CANT_KICK_OUT |
			DBO_PARTY_OPTION_FLAG_CANT_APPOINT_LEADER;

const DWORD DBO_PARTY_OPTION_FLAG_BUDOKAI = 
			DBO_PARTY_OPTION_FLAG_CANT_INVITE |
			DBO_PARTY_OPTION_FLAG_CANT_LEAVE |
			DBO_PARTY_OPTION_FLAG_CANT_KICK_OUT |
			DBO_PARTY_OPTION_FLAG_CANT_APPOINT_LEADER;
			

const DWORD MAX_SHARETARGET_COUNT = 5;// 공유타겟 슬롯 최대 개수[3/28/2008 SGpro]
//-----------------------------------------------------------------------------------


#pragma pack(1)

struct sPARTY_MEMBER_INFO
{
	HOBJECT hHandle;
	WCHAR awchMemberName[MAX_SIZE_CHAR_NAME_UNICODE + 1];
	BYTE byRace;
	BYTE byClass;
	BYTE byLevel;
	DWORD wCurLP;
	DWORD wMaxLP;
	WORD wCurEP;
	WORD wMaxEP;
	DWORD dwZenny;
	TBLIDX worldTblidx;
	WORLDID worldId;
	sVECTOR3 vCurLoc;
	bool IsOnline;
};

struct sVICTIM_ITEM_DATA
{
	CHARACTERID charId;
	BYTE byPlace;
	BYTE byPos;
	HOBJECT hItem;
	ITEMID itemId;
};

struct sDBO_PARTY_VICTIM_ITEM_INFO
{
	BYTE bySlotIndex;
	TBLIDX itemTblidx;
};

struct sDBO_ZENNY_DATA
{
	CHARACTERID		memberCharId;
	DWORD			dwZenny;
};

struct sINVEST_ZENNY_INFO
{
	HOBJECT hMember;
	DWORD dwZenny;
};

struct sPARTY_INVENTORY_ITEM_INFO
{
	TBLIDX tblidx;
	// bNeedToIdentify가 true일 때는 byStackCount, byRank, byGrade, option은 의미가 없는 값이다.
	// byStackCount, byRank, byGrade and option's values are meaningless if bNeedToIdentify is true.
	// by YOSHIKI(2006-10-31)
	BYTE byStackCount;
	BYTE byRank;
	BYTE byGrade;
	bool bNeedToIdentify;
	BYTE byBattleAttribute;
	TBLIDX			aOptionTblidx[MAX_OPTION_IN_ITEM];
};

struct sDBO_PARTY_INVENTORY_SLOT_INFO
{
	BYTE							bySlotIndex;
	sPARTY_INVENTORY_ITEM_INFO		itemInfo;
};

struct sDBO_VICTIM_INFO
{
	HOBJECT							hMember;
	DWORD							dwZenny;
};

struct sDBO_VICTIM_DATA
{
	CHARACTERID						charId;
	DWORD							dwZenny;
};

struct sZENNY_INFO
{
	CHARACTERID charId;
	DWORD dwZenny; //획득한 총 제니( dwOrgZenny + dwBonusZenny )
	DWORD dwOrgZenny; //원래 획득할 제니
	DWORD dwBonusZenny; //추가 획득 제니
};

// 공유타겟 데이타 [3/28/2008 SGpro]
struct sSHARETARGET_INFO
{
	HOBJECT hTarget;

public:
	sSHARETARGET_INFO()
		: hTarget( INVALID_HOBJECT )
	{
	}
};

#pragma pack()