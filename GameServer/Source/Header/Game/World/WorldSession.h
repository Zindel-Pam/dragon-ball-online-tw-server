#ifndef __WORLDSESSION_H
#define __WORLDSESSION_H

#include <Define.h>

#include <SharedDef.h>
#include <SharedType.h>

#include <deque>
#include <mutex>
#include <memory>

enum AccountTypes
{
	PLAYER = 0,
	GAME_MASTER
};
class Packet;
class GameSocket;
class Player;
enum eCHARSTATE;
struct sITEM_PROFILE;
class WorldSession
{
public:
	WorldSession(uint32 id, GameSocket* sock, AccountTypes sec);
	~WorldSession();
	void			SendPacket(char* packet, size_t size);

	AccountTypes	GetSecurity() const { return _security; }
	uint32			GetAccountId() const { return _accountId; }
	void			SetSecurity(AccountTypes security) { _security = security; }
	const			std::string &GetRemoteAddress() const;
	void			QueuePacket(std::unique_ptr<Packet> new_packet);
	bool			Update();
	void			LogoutPlayer(bool save);
	void			KickPlayer();
	bool			CreatePlayer(CHARACTERID id);
	// PACKET
	void			PacketParser(Packet& packet);
	// PACKET PROCESS
	void			SendAvatarCharInfo();
	void			SendAvatarSkillInfo();
	void			SendUpdateSkillPassiveAtribute();
	void			SendUpdateSkillPassiveAtributeByID(TBLIDX SkillID, bool isRemove);
	void			SendAvatarItemInfo();
	void			SendAvatarBuffInfo();
	void			SendAvatarHTBInfo();
	void			SendPortalInfo();
	void			SendAvatarTitleInfo();
	void			SendMascotInfo();
	void			SendHoiPoiMixInfo();//Craft list
	void			SendSlotInfo();
	void			SendAvatarInfoEnd();
	void			SendAvatarWagguInfo();
	void			SendAvatarItemCashInfo();
	void			SendAvatarWarFogInfo();
	void			SendNetMarbleMemberShipNfy();
	void			SendWorldEnter();
	void			SendEnterWorldComplete();
	void			SendGameLeave(Packet& packet, bool moveToChar = false);
	void			SendShopRequest(Packet& packet, bool enter);
	void			SendTargetSelection(HOBJECT hTarget);
	// move
	void			SendCharMoveSync(Packet &packet);
	void			SendCharMove(Packet& packet);
	void			SendCharJump(Packet& packet);
	void			SendCharJumpEnd(Packet& packet);
	void			SendCharToggleSitDown(Packet& packet);
	void			SendCharHeadChanging(Packet& packet);
	void			SendCharDestLoc(Packet& packet);
	void			SendCharFollowMove(Packet& packet);
	void			SendCharSyncFollow(Packet& packet);
	// portal
	void			SendPortalTeleport(Packet& packet);
	void			SendAddPortal(Packet& packet);
	void			SendEnterWorldTeleport();
	//Dangeon Teleport
	void			SendDangeonTeleport(HOBJECT	handle, WORD Dificulty);
	// warfog
	void			SendFogOfWarRes(Packet& packet);
	// quick slot
	void			SendUpdateQuickSlots(Packet& packet);
	void			SendRemoveQuickSlots(Packet& packet);
	// inventory
	void			SendItemMove(Packet& packet);
	void			SendItemMoveStack(Packet& packet);
	void			SendRemoveItem(Packet& packet);
	void			SendItemCreate(sITEM_PROFILE *createdItem);

	void			SendPickUp(HOBJECT handle);
	// SHOP
	void			SendShopBuy(Packet& packet);
	void			SendShopEventBuy(Packet& packet);
	void			SendShopItemChange(Packet& packet);
	void			SendShopSell(Packet& packet);
	// AutoAttck
	void			SendToggleAutoAttack(bool val);
	// Free pvp zone
	void			SendFreePVPZoneEntered();
	void			SendFreePVPZoneLeft();
	//Skills
	void			HandleUseSkill(Packet& packet);
	void			LearnSkill(TBLIDX id);
	void			UpgradeSkill(Packet& packet);
	void			ResetSkill(Packet& packet);
	//Budokay
	//buffs
	void			BuffDrop(Packet& packet);
	//Events
	void			SendDragonBallsCheck(Packet& packet);
	void			SendShenlongReward(Packet& packet);
	// command
	void			ExecuteServerCommand(Packet& packet);
	// social
	void			SendSocialSkill(Packet& packet);
private:
	GameSocket * const m_Socket;                       // socket pointer is owned by the network thread which created 
	AccountTypes	_security;
	uint32			_accountId;

	std::mutex		m_recvQueueLock;
	std::deque<std::unique_ptr<Packet>> m_recvQueue;

	bool			requestToLogout;
	/*	 PLAYER INFO	*/
	Player*			_player;
	/*		END			*/
};
#endif
/// @}
