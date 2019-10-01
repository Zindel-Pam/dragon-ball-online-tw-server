#ifndef __PLAYER_H
#define __PLAYER_H

#pragma once

#include <Game\Object\Manager\Fight.h>
#include <NtlCharacter.h>
#include "Manager\Skills.h"
#include "Manager\Attributes.h"
#include "Manager\Inventory.h"
#include <WorldSession.h>
#include <Packet.h>
#include <Packet\Game\PacketGU.h>
#include <Packet\Game\PacketUG.h>

class WorldSession;
class Map;

class Player : public Object
{
	friend class WorldSession;
	friend class CommunitySession;
public:
	explicit Player(WorldSession* session);
	explicit Player(CommunitySession* session);
	~Player();


	
	void				CleanupsBeforeDelete();

	void				AddToWorld() override;
	void				RemoveFromWorld() override;
	bool				Create(CHARACTERID id);
	void				Update(uint32 update_diff, uint32 time) override;
	//	------------------------------------------------------------------------
	// LOGIC
	//	------------------------------------------------------------------------
	void				CalculeLowLife();
	void				CalculePosition(uint32 _update_diff);
	void				LevelUp();
	//Comands
	void				LevelUpByComand(int Level);
	void				SetSpeed(int sppeed);
	void				ConvertClass(int ClassID);
	DWORD				GetClassFlag(int Class, int ItemType)const;
	void				ConvertAdult(int Adult);
	void				SendUpdateSize(int Size);
	void				SendAddTitle(int TitleID);

	void				SavePlayer();
	void				CalculeRpBall();

	void				RewardExpFromMob(MonsterData& data);
	void				RewardDropFromMob(MonsterData& data);

	void				UpdateZennyAmount(DWORD amount, eZENNY_CHANGE_TYPE zennyType);
	void				UpdateModusaAmount(DWORD amount);
	//	------------------------------------------------------------------------
	// GETTER
	//	------------------------------------------------------------------------
	
	WorldSession*		GetSession() const;
	MapReference&		GetMapRef();
	CHARACTERID			GetCharacterID();
	sPC_PROFILE			*GetPcProfile();
	sITEM_BRIEF			*GetCharEquippedItems();
	std::string			GetGuildName();
	eCHARSTATE			GetCharEState();
	BYTE				GetMoveDirection();
	std::string			GetName();
	HOBJECT				GetTarget() const ;
	PORTALID			GetPortalIdFromList(HOBJECT handle);
	ePC_CLASS			GetMyClass() const;
	AttributesManager	*GetAttributesManager();
	InventoryManager	*GetInventoryManager();
	sVECTOR3			GetMoveDestinationVector();
	bool				GetIsEmergency();
	bool                GetFlying();
	virtual DWORD		GetPowerLevel() override;
	//	------------------------------------------------------------------------
	// SETTER
	//	------------------------------------------------------------------------
	void				SetMoveDestinationLocation(sVECTOR3 pos);
	void				SetSession(WorldSession* s);
	void				SetIsFighting(bool val);
	void                SetFlying(bool val);
	void				SetMoveDirection(BYTE _moveDir);
	void				SetName(char* name);
	void				SetWorldID(WORLDID id);
	void				SetWorldTableID(TBLIDX id);
	void				SetMap(Map* m);
	void				ResetMap();
	void				SetTarget(HOBJECT hSerial);
	void				SetMyClass(ePC_CLASS _class);
	virtual void		UpdateState(eCHARSTATE _state) override;
	//	------------------------------------------------------------------------
	// PACKET
	//	------------------------------------------------------------------------
	bool				LoadFromDB(CHARACTERID id);
	void				BuildPacketForSpawn(SpawnPlayer& PC);
	void				BuildPacketForNewPlayer(Player& plr);
	void				SendPacket(char*, size_t size);
	//	------------------------------------------------------------------------
	// LIST
	//	------------------------------------------------------------------------
	void				FillList(Object& obj);
	void				RemoveFromList(Object& obj);
	void				SendToPlayerList(char* data, size_t size);
	bool				isInList(uint32 id);
	Object				*GetFromList(uint32 id);

	void				AddDropToList(DroppedObject& drop, HOBJECT dropHandle);
	void				RemoveDropFromList(HOBJECT handle);
	void				UpdateDropListTimer();
	DroppedObject		*GetPickupData(HOBJECT handle);

	void				ClearListAndReference();
	//	------------------------------------------------------------------------
	// UPDATE FUNCTION
	//	------------------------------------------------------------------------
	void				Regen();
	void				ExecuteLPFood();
	void				ExecuteEPFood();
	void				ExecuteStun();
	void				UpdateAspectState(BYTE State);
	//	------------------------------------------------------------------------
	// FIGHT FUNCTION
	//	------------------------------------------------------------------------
	void				Attack();
	virtual void		TakeDamage(uint32 amount) override;
	void				TakeMobDemage(uint32 amount);
	//	------------------------------------------------------------------------
	// MAIL FUNCTIONS
	//	------------------------------------------------------------------------
	void                StartMail(Packet pPacket);
	void                LoadMail(Packet pPacket);
	bool                CheckMailAwayStatus();
	void                SendMail(Packet pPacket);
	void                ReadMail(Packet pPacket);
	void                DeletMail(Packet pPacket);
	void                ReloadMail(Packet pPacket);
	void                ReturnMail(Packet pPacket);
	//	------------------------------------------------------------------------
	// Bank FUNCTIONS
	//	------------------------------------------------------------------------
	void               SendBankStart(Packet pPacket);
	void               SendBankLoad(Packet pPacket);
	void               SendBankInfo(Packet pPacket);
	void               SendBankEnd(Packet pPacket);
	void               SendBankItemDelete(Packet pPacket);
	void               SendBankBuyTab(Packet pPacket);
	DWORD              GetBankMoney();
	//	------------------------------------------------------------------------
	// Items FUNCTIONS
	//	------------------------------------------------------------------------
	void                HandleItemUse(Packet pPacket);
	void                ItemSoketInsert(Packet pPacket);
	void                ItemSoketDestroy(Packet pPacket);
	void                ItemOptionsChange(Packet pPacket);
	void			    SendItemUpgrade(Packet& packet);
	void			    SendItemUpgradeByCoupon(Packet& packet);
	void			    SendLearnSkillByItem(Packet& packet);
	//	------------------------------------------------------------------------
	// FreeBatle FUNCTIONS
	//	------------------------------------------------------------------------
	void			    HandleFreeBattleRange();
	void			    HandleFreeBattleWinners();
	//	------------------------------------------------------------------------
	// Free Pvp zone FUNCTIONS
	//	------------------------------------------------------------------------
	void HandeFreePvpZone();
private:
	//	------------------------------------------------------------------------
	// SERVER
	//	------------------------------------------------------------------------

	std::mutex			mutexPlayer;
	std::mutex			mutexDropList;

	std::map<uint32, Object*> objList;
	std::map<uint32, DroppedObject*>	DropList;
	WorldSession*		m_session;
	CommunitySession*   m_cSession;
	MapReference		m_mapRef;
	//	------------------------------------------------------------------------
	// CHARACTER
	//	------------------------------------------------------------------------
	AttributesManager	characterManager;
	CHARACTERID			charid;
	ACCOUNTID			accID;
	std::string			m_name;
	sVECTOR3			m_position_tmp;
	sVECTOR3			m_rotation_tmp;
	sVECTOR3			m_destination_pos;
	BYTE				moveDirection;
	HOBJECT				cur_target;
	Object*				cur_obj_tagert;
	bool				isLowLifeSend;
	ePC_CLASS			myClass;
	bool				isMovingToCharServer;
	bool				isInPvpZone;
	//	------------------------------------------------------------------------
	// ITEM
	//	------------------------------------------------------------------------
	InventoryManager	inventoryManager;
	//	------------------------------------------------------------------------
	// SKILLS
	//	------------------------------------------------------------------------
	FightManager		fightManager;
	SkillsManager		skillManager;
	BYTE				attackCount;
	//	------------------------------------------------------------------------
	// TIMER
	//	------------------------------------------------------------------------
	time_t				rpBallTimer;

	std::string			GuildName;

	void                SetGSHandle();

};

#endif