#include <mysqlconn_wrapper.h>
#include <Logger.h>
#include <Packet/Char/PacketCU.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <list>

void MySQLConnWrapper::UpdateQuickSlots(TBLIDX id, SLOTID slotID, CHARACTERID characterID)
{
	std::string query = "UPDATE quickslot SET slotId_" + std::to_string(static_cast<long long>(slotID));
	query.append(" = '%d' WHERE charId = '%d';");

	sql::ResultSet* result = sDB.executes(query.c_str(),
		id, characterID);
	if (result != NULL)
		delete result;
}
bool MySQLConnWrapper::CheckIfItemCanGoHere(CHARACTERID CharID, BYTE Place, BYTE Pos)
{
	sql::ResultSet* result = sDB.executes("SELECT * FROM items WHERE owner_id = '%d' AND place = '%d' AND pos = '%d';",
		CharID, Place, Pos);
	if (result == NULL)
		return false;
	if (result->rowsCount() == 0)
	{
		delete result;
		return true;
	}
	delete result;
	return false;
}
void MySQLConnWrapper::UpdateItemPosAndPlace(TBLIDX ItemID, BYTE Place, BYTE Pos)
{
	sql::ResultSet* result = sDB.executes("UPDATE items SET place = '%d' , pos = '%d' WHERE id = '%d';",
		Place, Pos, ItemID);
	if (result != NULL)
		delete result;
}
void MySQLConnWrapper::LearnSkill(TBLIDX skillID, CHARACTERID characterID, TBLIDX slotID)
{
	sql::ResultSet* result = sDB.executes("INSERT INTO skills (`skill_id`, `owner_id`, `SlotID`, `TimeRemaining`) VALUES('%d','%d','%d','0');",
		skillID, characterID, slotID);
	if (result != NULL)
		delete result;
}
void MySQLConnWrapper::AddItem(TBLIDX itemID, CHARACTERID characterID, int place, int pose, int count, int rank, int durability,int grade)
{
	sql::ResultSet* result = sDB.executes("INSERT INTO items (`owner_id`, `tblidx`, `place`, `pos`, `count`, `rank`, `durability`, `grade`) VALUES ('%d','%d','%d','%d','%d','%d','%d','%d');",
		characterID, itemID, place, pose, count, rank, durability,grade);
	if (result != NULL)
		delete result; 
}
void MySQLConnWrapper::AddCashItem(TBLIDX itemID, CHARACTERID characterID, int byStackCount, int Handle)
{
	sql::ResultSet* result = sDB.executes("INSERT INTO cashitem (`owner_id`, `tblidx`, `byStackCount`, `Handle`) VALUES ('%d','%d','%d','%d');",
		characterID, itemID, byStackCount, Handle);
	if (result != NULL)
		delete result;
}
void MySQLConnWrapper::UpdateSPPoint(int point, CHARACTERID id)
{
	sql::ResultSet* result = sDB.executes("UPDATE characters SET SkillPoints = '%d' WHERE CharacterID = '%d';",
		point, id);
	if (result != NULL)
		delete result;
}
void MySQLConnWrapper::UpdateSkill(TBLIDX NewskillID, CHARACTERID characterID, TBLIDX skillID)
{
	sql::ResultSet* result = sDB.executes("UPDATE skills SET skill_id = '%d' WHERE owner_id = '%d' AND skill_id = '%d';",
		NewskillID, characterID, skillID);
	if (result != NULL)
		delete result;
}
void MySQLConnWrapper::UpdatePlayerLevel(int _level, CHARACTERID CharID, int _exp)
{
	sql::ResultSet* result = sDB.executes("UPDATE characters SET CurrentLevel = '%d' , CurrentExp = '%d' WHERE CharacterID = '%d';",
		_level, _exp, CharID);
	if (result != NULL)
		delete result;
}
void MySQLConnWrapper::AddNewBind(CHARACTERID charid, WORLDID worldid, TBLIDX bindID)
{
	sql::ResultSet* result = sDB.executes("SELECT * FROM bind WHERE CharacterID = '%d';",
		charid);
	if (result == NULL)
		return;
	if (result->rowsCount() > 0)
	{
		result = sDB.executes("UPDATE bind SET WorldID = '%d', BindObjectTblIdx = '%d' WHERE CharacterID = '%d';",
			worldid, bindID, charid);
		if (result != NULL)
			delete result;
	}
	else
	{
		result = sDB.executes("INSERT INTO bind (`CharacterID`, `WorldID`, `BindObjectTblIdx`) VALUES ('%d','%d','%d');",
			charid, worldid, bindID);
		if (result != NULL)
			delete result;
	}
}
void MySQLConnWrapper::AddNewWarFog(HOBJECT id, CHARACTERID charid)
{

	sql::ResultSet* result = sDB.executes("INSERT INTO warfoginfo (`hObject`, `owner_id`) VALUES (%d,%d);"
	,id, charid);
	if (result != NULL)
		delete result;
}
void MySQLConnWrapper::SavePlayerPositionAndWorldID(sVECTOR3 position, sVECTOR3 direction, WORLDID w_id, WORLDID w_tblidx_id, CHARACTERID charid)
{
	sql::ResultSet* result = sDB.executes("UPDATE characters SET Position_X = '%f' , Position_Y = '%f' , Position_Z = '%f' , Direction_X = '%f' , Direction_Y = '%f' , Direction_Z = '%f' , WorldID = '%d' , WorldTableID = '%d' WHERE CharacterID = '%d';",
		position.x, position.y, position.z, direction.x, direction.y, direction.z, w_id, w_tblidx_id, charid);
	if (result != NULL)
		delete result;
}
void MySQLConnWrapper::SavePlayerLife(int CurLP, int CurEP, CHARACTERID charid)
{
	sql::ResultSet* result = sDB.executes("UPDATE characters_attributes SET CurLP = '%d' , CurEP = '%d' WHERE CharacterID = '%d';",
		CurLP, CurEP, charid);
	if (result != NULL)
		delete result;
}
void MySQLConnWrapper::SaveTitleMarket(int TitleMarket, CHARACTERID charid)
{
	sql::ResultSet* result = sDB.executes("UPDATE characters SET Title_Marking = '%d' WHERE CharacterID = '%d';",
		TitleMarket, charid);
	if (result != NULL)
		delete result;
}
void MySQLConnWrapper::SavePlayerWagguCoin(int WagguPoint, CHARACTERID charid)
{
	sql::ResultSet* result = sDB.executes("UPDATE characters SET WagguCoin = '%d' WHERE CharacterID = '%d';",
		WagguPoint, charid);
	if (result != NULL)
		delete result;
}
void MySQLConnWrapper::SavePlayerCashPoit(int Cash, CHARACTERID charid)
{
	sql::ResultSet* result = sDB.executes("UPDATE characters SET CashPoint = '%d' WHERE CharacterID = '%d';",
		Cash, charid);
	if (result != NULL)
		delete result;
}
void MySQLConnWrapper::AddMail(CHARACTERID CharID, int byDay, int byMailType, int byTextSize, char* wszText, char* wszTargetName, char* wszFromName, int bIsAccept, int bIsLock, int bIsRead)
{
	sql::ResultSet* result = sDB.executes("INSERT INTO mail (`CharacterID`, `byDay`, `byMailType`, `byTextSize`, `wszText`, `wszTargetName`, `wszFromName`, `bIsAccept`, `bIsLock`, `bIsRead`) VALUES('%d','%d','%d','%d','%s','%s','%s','%d','%d','%d');",
		CharID, byDay,  byMailType, byTextSize, wszText, wszTargetName, wszFromName, bIsAccept, bIsLock, bIsRead);
	if (result != NULL)
		delete result;
}
void MySQLConnWrapper::AddTitle(CHARACTERID characterID, TBLIDX TitleID)
{
	sql::ResultSet* result = sDB.executes("INSERT INTO titlelist (`CharacterID`,  `TitleID`) VALUES('%d','%d');",
		characterID, TitleID);
	if (result != NULL)
		delete result;
}
void MySQLConnWrapper::SaveQuickTeleport(CHARACTERID characterID, BYTE TeleportID, DWORD WorldID, float Loc_x, float Loc_y, float Loc_z, WORD Year, BYTE Moch, BYTE Day, BYTE Hour, BYTE Minute, BYTE Secound, DWORD MapTBLIDX)
{
	sql::ResultSet* result = sDB.executes("INSERT INTO QuickTeleporter (`CharacterID`, `TeleportID`, `WorldID`, `Loc_x`, `Loc_y`, `Loc_z`, `Year`, `Moch`, `Day`, `Hour`, `Minute`, `Secound`, `MapTblidx` ) VALUES('%d','%d','%d','%f','%f','%f','%d','%d','%d','%d','%d','%d','%d');",
		characterID, TeleportID, WorldID, Loc_x, Loc_y, Loc_z, Year, Moch, Day, Hour, Minute, Secound, MapTBLIDX);
	if (result != NULL)
		delete result;
}

void MySQLConnWrapper::SavePlayerZenny(int zenny, CHARACTERID charid)
{
	sql::ResultSet * result = sDB.executes("UPDATE characters SET ZennyInventory = %d WHERE CharacterID = %d", zenny, charid);

	if (result != NULL)
		delete result;
}
void MySQLConnWrapper::SavePlayerExp(int exp, CHARACTERID charid)
{
	sql::ResultSet * result = sDB.executes("UPDATE characters SET CurrentExp = %d WHERE CharacterID = %d", exp, charid);

	if (result != NULL)
		delete result;
}
