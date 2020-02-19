/* ScriptData
SDAuthor: frostI
SDName: rts_informator
SD%Complete: 100
SDComment:
SDCategory: Custom
EndScriptData */

#include "ScriptPCH.h"

enum spell
{
	SPELL_TELEPORT = 33056
};

#define ERROR_MSG_REALM_TYPE "You must to choose a realm type first!"
#define ERROR_MSG_LEVEL_19 "You are already level 19!"
#define ERROR_MSG_LEVEL_80 "You are already level 80!"
#define ERROR_MSG_REQUIRE_80 "You must be level 80!"
#define ERROR_MSG_TWINK "Twinks got their own mall!"

#define MESSAGE_LEVEL_19 "You have been leveled up to 19!"
#define MESSAGE_LEVEL_80 "You have been leveled up to 80!"

class npc_rts_informator : public CreatureScript
{
public:
	npc_rts_informator() : CreatureScript("npc_rts_informator") { }

	bool OnGossipHello(Player* player, Creature* creature)
	{
		player->ADD_GOSSIP_ITEM(10, "Npc information:\nThis npc is mainly for BETA purposes\n\n.Server Information:\nYou are now in the Start Hub.\nHere you can choose your Realm Type.\nTypes: PvE'r, PvP'r, RP'r and Twinker.\nEach type will get special features, Donators can mix certain types.\n\nNewest updates:\n\n- General updates.\n- Fixed pocket pets.\n- Added this gossip npc\n- Added Gunship Battle in ICC\n- Spawned malls and events\n- Added realm type specific features", GOSSIP_SENDER_MAIN, 50);
		player->ADD_GOSSIP_ITEM_EXTENDED(10, "Level me up!", GOSSIP_SENDER_MAIN, 1, "Are you sure?", 0, 0);
		player->ADD_GOSSIP_ITEM_EXTENDED(10, "(Temporarily) Gear Mall.", GOSSIP_SENDER_MAIN, 2, "Are you sure?", 0, 0);
		player->PlayerTalkClass->SendGossipMenu(DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();
		WorldSession* handler = player->GetSession();
		switch (action)
		{
		case 1:
			player->CLOSE_GOSSIP_MENU();
			if (player->GetRealmType() == 0)
			{
				handler->SendNotification(ERROR_MSG_REALM_TYPE);
			}
			else if (player->GetRealmType() == 4)
			{
				if (player->getLevel() == 19)
					handler->SendNotification(ERROR_MSG_LEVEL_19);
				else if (player->getLevel() < 19)
				{
					player->SetLevel(19);
					player->GetSession()->SendAreaTriggerMessage(MESSAGE_LEVEL_19);
				}
			}
			else if (player->GetRealmType() == 1 || player->GetRealmType() == 2 || player->GetRealmType() == 3)
			{
				if (player->getLevel() == 80)
					handler->SendNotification(ERROR_MSG_LEVEL_80);
				else if (player->getLevel() < 80)
				{
					player->SetLevel(80);
					player->GetSession()->SendAreaTriggerMessage(MESSAGE_LEVEL_80);
				}
			}
			break;
		case 2:
			player->CLOSE_GOSSIP_MENU();
			if (player->GetRealmType() == 0)
				handler->SendNotification(ERROR_MSG_REALM_TYPE);
			else if (player->GetRealmType() == 4)
			{
				if (player->getLevel() == 19)
					handler->SendNotification(ERROR_MSG_TWINK);
			}
			else if (player->GetRealmType() == 1 || player->GetRealmType() == 2 || player->GetRealmType() == 3)
			{
				if (player->getLevel() == 80)
				{
					player->CastSpell(player, SPELL_TELEPORT);
					player->TeleportTo(1, 16226.200195f, 16257.0f, 13.202200f, 1.650070f);
				}
				else if (player->getLevel() < 80)
					handler->SendNotification(ERROR_MSG_REQUIRE_80);
			}
			break;
		}
		return true;
	}
};

void AddSC_rts_npc_informator()
{
	new npc_rts_informator();
}