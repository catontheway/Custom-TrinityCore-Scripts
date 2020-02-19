/* ScriptData
SDAuthor: frostI
SDName: rts_welcomer
SD%Complete: 100
SDComment:
SDCategory: Custom
EndScriptData */

#include "ScriptPCH.h"
#include "InstanceSaveMgr.h"

#define GOSSIP_ITEM_1 "I would like to follow the road of a true PvE'r!"
#define GOSSIP_ITEM_2 "I would like to follow the road of a true PvP'r!"
#define GOSSIP_ITEM_3 "I would like to follow the road of a true Roleplayer!"
#define GOSSIP_ITEM_4 "I would like to follow the road of a true Twinker!"
#define GOSSIP_ITEM_5 "I would like to teleport to my start location!"
#define GOSSIP_ITEM_6 "I would like to teleport to my start location!"
#define GOSSIP_ITEM_7 "Coming Soon!"
#define GOSSIP_ITEM_8 "Coming Soon!"

#define COMING_SOON "Coming Soon!"

#define GOSSIP_CONFIRM_ROAD_PVE "Are you sure you want to\nfollow the road of a true PvE'r?"
#define GOSSIP_CONFIRM_ROAD_PVP "Are you sure you want to\nfollow the road of a true PvP'r?"
#define GOSSIP_CONFIRM_ROAD_RP "Are you sure you want to\nfollow the road of a true Roleplayer?"
#define GOSSIP_CONFIRM_ROAD_TWINK "Are you sure you want to\nfollow the road of a true Twinker?"

#define GOSSIP_CONFIRM_START_LOC_PVE "Are you sure you want to teleport to your\nRace Specific Start Location?"
#define GOSSIP_CONFIRM_START_LOC_PVP "Are you sure you want to teleport to\nThe Naxxramas PvP Leveling Arena?"
#define GOSSIP_CONFIRM_START_LOC_RP "Are you sure you want to teleport to your\nRace Specific Start Location?"
#define GOSSIP_CONFIRM_START_LOC_TWINK "Are you sure you want to teleport to your\nRace Specific Start Location?"

#define MESSAGE_SELECT_PVE "Congratulations! You have chosen to become a PvE'r. You are now able to teleport to your Realm Type specific start location."
#define MESSAGE_SELECT_PVP "Congratulations! You have chosen to become a PvP'r. You are now able to teleport to your Realm Type specific start location."
#define MESSAGE_SELECT_RP "Congratulations! You have chosen to become a Roleplayer. You are now able to teleport to your Realm Type specific start location."
#define MESSAGE_SELECT_TWINK "Congratulations! You have chosen to become a Twinker. You are now able to teleport to your Realm Type specific start location."

#define MESSAGE_ON_SELECT_PVE "You received The Starter Pocket Kite!"
#define MESSAGE_ON_SELECT_PVP "Your skills are tought and you received The Starter Pocket Kite!"
#define MESSAGE_ON_SELECT_RP "You received The Starter Pocket Kite!"
#define MESSAGE_ON_SELECT_TWINK "You received The Starter Pocket Kite!"

#define NPC_MESSAGE_ONE "Welcome to InterKasa! I will show you the endless possibilities this realm offers."
#define NPC_MESSAGE_TWO "Greetings and welcome! Please enjoy your stay."
#define NPC_MESSAGE_THREE "It's possible we'r getting a small snow storm, so stay warm!"

#define MAP_NAXXRAMAS 533

class npc_rts_welcomer : public CreatureScript
{
public:
	npc_rts_welcomer() : CreatureScript("npc_rts_welcomer") { }

	bool OnGossipHello(Player* player, Creature* creature)
	{
		if (player->GetRealmType() == 0)
		{
			player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_DOT, GOSSIP_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1, GOSSIP_CONFIRM_ROAD_PVE, 0, 0);
			player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_DOT, GOSSIP_ITEM_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2, GOSSIP_CONFIRM_ROAD_PVP, 0, 0);
			player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_DOT, GOSSIP_ITEM_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3, GOSSIP_CONFIRM_ROAD_TWINK, 0, 0);
			player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_DOT, GOSSIP_ITEM_4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4, GOSSIP_CONFIRM_ROAD_RP, 0, 0);
		}
		if (player->GetRealmType() == 1 && player->getLevel() < 80)
			player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_DOT, GOSSIP_ITEM_5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5, GOSSIP_CONFIRM_START_LOC_PVE, 0, 0);
		if (player->GetRealmType() == 2 && player->getLevel() < 80)
			player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_DOT, GOSSIP_ITEM_6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6, GOSSIP_CONFIRM_START_LOC_PVP, 0, 0);
		if (player->GetRealmType() == 3 && player->getLevel() < 80)
			player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_DOT, GOSSIP_ITEM_7, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7, COMING_SOON, 0, 0);
		if (player->GetRealmType() == 4 && player->getLevel() < 19)
			player->ADD_GOSSIP_ITEM_EXTENDED(10, GOSSIP_ITEM_8, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8, COMING_SOON, 0, 0);
		
		player->SEND_GOSSIP_MENU(60001, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();
		WorldSession* handler = player->GetSession();
		// Skills
		uint32 SkillSpellsWarrior[19] = { 264, 5011, 674, 15590, 8737, 750, 196, 198, 201, 197, 266, 199, 202, 227, 2764, 2567, 200, 9116, 3018 };
		uint32 SkillSpellsPaladin[12] = { 107, 8737, 750, 196, 198, 201, 197, 199, 202, 200, 27762, 9116 };
		uint32 SkillSpellsDeathknight[11] = { 674, 8737, 750, 196, 198, 201, 197, 199, 202, 200, 52665 };
		uint32 SkillSpellsHunter[12] = { 264, 5011, 674, 15590, 8737, 196, 201, 197, 266, 202, 227, 200 };
		uint32 SkillSpellsShaman[10] = { 107, 8737, 15590, 196, 198, 197, 199, 227, 27763, 9116 };
		uint32 SkillSpellsRogue[11] = { 264, 5011, 674, 15590, 196, 201, 198, 266, 2764, 2567, 3018 };
		uint32 SkillSpellsDruid[9] = { 15590, 198, 227, 199, 200, 1180, 27764 };
		uint32 SkillSpellsPriest[5] = { 198, 227, 1180, 5019, 5009 };
		uint32 SkillSpellsMage[5] = { 201, 227, 1180, 5019, 5009 };
		uint32 SkillSpellsWarlock[5] = { 201, 227, 1180, 5019, 5009 };
		// Items
		uint32 ItemsWarrior[8] = { 44096, 44096, 44092, 44093, 48685, 44099, 50255, 42991 };
		uint32 ItemsPaladin[9] = { 44094, 44092, 48685, 44099, 50255, 48683, 44100, 42991, 42992 };
		uint32 ItemsDeathknight[8] = { 44096, 44096, 44092, 48685, 44099, 50255, 42991 };
		uint32 ItemsHunter[7] = { 48677, 44101, 44093, 44096, 44096, 50255, 42991 };
		uint32 ItemsShaman[10] = { 48677, 48683, 44101, 44102, 48716, 48716, 48716, 50255, 42991, 42992 };
		uint32 ItemsRogue[9] = { 48689, 44103, 44091, 44091, 44096, 44096, 44093, 50255, 42991 };
		uint32 ItemsDruid[9] = { 48689, 44103, 44105, 48687, 44095, 44094, 50255, 42991, 42992 };
		uint32 ItemsPriest[5] = { 44094, 44095, 44107, 48691, 42992 };
		uint32 ItemsMage[4] = { 44095, 44107, 48691, 42992 };
		uint32 ItemsWarlock[4] = { 44095, 44107, 48691, 42992 };
		switch (action)
		{
		case GOSSIP_ACTION_INFO_DEF + 1: // pve
			player->SetRealmType(1);
			player->LearnSpell(68767, false);
			player->SaveToDB();
			player->GetSession()->SendAreaTriggerMessage(MESSAGE_ON_SELECT_PVE);
			ChatHandler(player->GetSession()).PSendSysMessage(MESSAGE_SELECT_PVE);
			player->CLOSE_GOSSIP_MENU();
			break;
		case GOSSIP_ACTION_INFO_DEF + 2: // pvp
			player->SetRealmType(2);
			/*if (player->getClass() == CLASS_DEATH_KNIGHT)
			player->SetLevel(1);*/
			if (player->GetTeam() == HORDE)
				player->AddItem(44097, 1);
			else if (player->GetTeam() == ALLIANCE)
				player->AddItem(44098, 1);
			if (player->getClass() == 1) // warrior
			{
				for (uint8 i = 0; i < 19; ++i)
					if (!player->HasSpell(SkillSpellsWarrior[i]))
						player->LearnSpell(SkillSpellsWarrior[i], true);
				for (uint8 i = 0; i < 8; ++i)
					if (!player->HasItemCount(ItemsWarrior[i]))
						player->AddItem(ItemsWarrior[i], 1);
			}
			if (player->getClass() == 2) // paladin
			{
				for (uint8 i = 0; i < 12; ++i)
					if (!player->HasSkill(SkillSpellsPaladin[i]))
						player->LearnSpell(SkillSpellsPaladin[i], true);
				for (uint8 i = 0; i < 9; ++i)
					if (!player->HasItemCount(ItemsPaladin[i]))
						player->AddItem(ItemsPaladin[i], 1);
			}
			if (player->getClass() == 6) // death knight
			{
				for (uint8 i = 0; i < 11; ++i)
					if (!player->HasSkill(SkillSpellsDeathknight[i]))
						player->LearnSpell(SkillSpellsDeathknight[i], true);
				for (uint8 i = 0; i < 8; ++i)
					if (!player->HasItemCount(ItemsDeathknight[i]))
						player->AddItem(ItemsDeathknight[i], 1);
			}
			if (player->getClass() == 3) // hunter
			{
				for (uint8 i = 0; i < 12; ++i)
					if (!player->HasSkill(SkillSpellsHunter[i]))
						player->LearnSpell(SkillSpellsHunter[i], true);
				for (uint8 i = 0; i < 7; ++i)
					if (!player->HasItemCount(ItemsHunter[i]))
						player->AddItem(ItemsHunter[i], 1);
			}
			if (player->getClass() == 7) // shaman
			{
				for (uint8 i = 0; i < 10; ++i)
					if (!player->HasSkill(SkillSpellsShaman[i]))
						player->LearnSpell(SkillSpellsShaman[i], true);
				for (uint8 i = 0; i < 10; ++i)
					if (!player->HasItemCount(ItemsShaman[i]))
						player->AddItem(ItemsShaman[i], 1);
			}
			if (player->getClass() == 4) // rogue
			{
				for (uint8 i = 0; i < 11; ++i)
					if (!player->HasSkill(SkillSpellsRogue[i]))
						player->LearnSpell(SkillSpellsRogue[i], true);
				for (uint8 i = 0; i < 9; ++i)
					if (!player->HasItemCount(ItemsRogue[i]))
						player->AddItem(ItemsRogue[i], 1);
			}
			if (player->getClass() == 11) // druid
			{
				for (uint8 i = 0; i < 9; ++i)
					if (!player->HasSkill(SkillSpellsDruid[i]))
						player->LearnSpell(SkillSpellsDruid[i], true);
				for (uint8 i = 0; i < 9; ++i)
					if (!player->HasItemCount(ItemsDruid[i]))
						player->AddItem(ItemsDruid[i], 1);
			}
			if (player->getClass() == 5) // priest
			{
				for (uint8 i = 0; i < 5; ++i)
					if (!player->HasSkill(SkillSpellsPriest[i]))
						player->LearnSpell(SkillSpellsPriest[i], true);
				for (uint8 i = 0; i < 5; ++i)
					if (!player->HasItemCount(ItemsPriest[i]))
						player->AddItem(ItemsPriest[i], 1);
			}
			if (player->getClass() == 8) // mage
			{
				for (uint8 i = 0; i < 5; ++i)
					if (!player->HasSkill(SkillSpellsMage[i]))
						player->LearnSpell(SkillSpellsMage[i], true);
				for (uint8 i = 0; i < 4; ++i)
					if (!player->HasItemCount(ItemsMage[i]))
						player->AddItem(ItemsMage[i], 1);
			}
			if (player->getClass() == 9) // warlock
			{
				for (uint8 i = 0; i < 5; ++i)
					if (!player->HasSkill(SkillSpellsWarlock[i]))
						player->LearnSpell(SkillSpellsWarlock[i], true);
				for (uint8 i = 0; i < 4; ++i)
					if (!player->HasItemCount(ItemsWarlock[i]))
						player->AddItem(ItemsWarlock[i], 1);
			}
			player->LearnSpell(68767, false);
			player->SaveToDB();
			player->GetSession()->SendAreaTriggerMessage(MESSAGE_ON_SELECT_PVP);
			ChatHandler(player->GetSession()).PSendSysMessage(MESSAGE_SELECT_PVP);
			break;
		case GOSSIP_ACTION_INFO_DEF + 3: // roleplay
			player->SetRealmType(3);
			if (player->getClass() == CLASS_DEATH_KNIGHT)
				player->SetLevel(1);
			player->LearnSpell(68767, false);
			player->SaveToDB();
			//ChatHandler(player->GetSession()).PSendSysMessage(MESSAGE_SELECT_RP);
			player->GetSession()->SendAreaTriggerMessage(MESSAGE_ON_SELECT_RP);
			ChatHandler(player->GetSession()).PSendSysMessage("Roleplay leveling is still under construction!");
			player->CLOSE_GOSSIP_MENU();
			break;
		case GOSSIP_ACTION_INFO_DEF + 4: // twink
			player->SetRealmType(4);
			if (player->getClass() == CLASS_DEATH_KNIGHT)
				player->SetLevel(1);
			player->LearnSpell(68767, false);
			player->SaveToDB();
			//ChatHandler(player->GetSession()).PSendSysMessage("Congratulations! You have chosen to become a Twinker. You are now able to teleport to your Realm Type specific starting location.");
			player->GetSession()->SendAreaTriggerMessage(MESSAGE_ON_SELECT_TWINK);
			ChatHandler(player->GetSession()).PSendSysMessage(MESSAGE_SELECT_TWINK);
			player->CLOSE_GOSSIP_MENU();
			break;
		case GOSSIP_ACTION_INFO_DEF + 5: // pve
			if (player->getRace() == 1)
				player->TeleportTo(0, -8949.95f, -132.493f, 83.5312f, 0.0f);
			if (player->getRace() == 2)
				player->TeleportTo(1, -618.518f, -4251.67f, 38.718f, 0.0f);
			if (player->getRace() == 3)
				player->TeleportTo(0, -6240.32f, 331.033f, 382.758f, 6.17716f);
			if (player->getRace() == 4)
				player->TeleportTo(1, 10311.3f, 832.463f, 1326.41f, 5.69632f);
			if (player->getRace() == 5)
				player->TeleportTo(0, 1676.71f, 1678.31f, 121.67f, 2.70526f);
			if (player->getRace() == 6)
				player->TeleportTo(1, -2917.58f, -257.98f, 52.9968f, 0.0f);
			if (player->getRace() == 7)
				player->TeleportTo(0, -6240.0f, 331.0f, 383.0f, 0.0f);
			if (player->getRace() == 8)
				player->TeleportTo(1, -618.518f, -4251.67f, 38.718f, 0.0f);
			if (player->getRace() == 10)
				player->TeleportTo(530, 10349.6f, -6357.29f, 33.4026f, 5.31605f);
			if (player->getRace() == 11)
				player->TeleportTo(530, -3961.64f, -13931.2f, 100.615f, 2.08364f);
			player->CLOSE_GOSSIP_MENU();
			break;
		case GOSSIP_ACTION_INFO_DEF + 6: // pvp
		    {
		    	player->SetGameMaster(true);
		    	InstancePlayerBind* bind = player->GetBoundInstance(MAP_NAXXRAMAS, RAID_DIFFICULTY_10MAN_NORMAL);
		    	if (!bind) 
		    	{
		    		if (InstanceSave* save = sInstanceSaveMgr->AddInstanceSave(MAP_NAXXRAMAS, 50, RAID_DIFFICULTY_10MAN_NORMAL, 7 * DAY, true, false))
		    			player->BindToInstance(save, !save->CanReset());
		    	}
		    	if (player->getLevel() > 0 && player->getLevel() < 9)
		    	{
		    		switch (urand(0, 1))
					{
		    		    case 0: { player->TeleportTo(MAP_NAXXRAMAS, 2664.764160f, -3623.427246f, 265.783905f, 0.0f, TELE_TO_GM_MODE); break; }
		    		    case 1: { player->TeleportTo(MAP_NAXXRAMAS, 2827.711914f, -3548.045654f, 253.234314f, 0.0f, TELE_TO_GM_MODE); break; }
		    		}
		    	}
		    	if (player->getLevel() > 8 && player->getLevel() < 19)
		    	{
		    		switch (urand(0, 1))
					{
		    		    case 0: { player->TeleportTo(MAP_NAXXRAMAS, 3115.019531f, -3585.915527f, 287.080627f, 0.0f, TELE_TO_GM_MODE); break; }
		    		    case 1: { player->TeleportTo(MAP_NAXXRAMAS, 3210.555664f, -3575.030518f, 287.081329f, 0.0f, TELE_TO_GM_MODE); break; }
		    		}
		    	}
		    	if (player->getLevel() > 18 && player->getLevel() < 29)
		    	{
		    		switch (urand(0, 1))
					{
		    		    case 0: { player->TeleportTo(MAP_NAXXRAMAS, 3380.567383f, -3694.015625f, 259.081146f, 0.0f, TELE_TO_GM_MODE); break; }
		    		    case 1: { player->TeleportTo(MAP_NAXXRAMAS, 3235.829346f, -3808.203857f, 273.935242f, 0.0f, TELE_TO_GM_MODE); break; }
		    		}
		    	}
		    	if (player->getLevel() > 28 && player->getLevel() < 39)
		    	{
		    		switch (urand(0, 1))
					{
		    		    case 0: { player->TeleportTo(MAP_NAXXRAMAS, 3396.401611f, -3841.288086f, 294.665802f, 0.0f, TELE_TO_GM_MODE); break; }
		    		    case 1: { player->TeleportTo(MAP_NAXXRAMAS, 3473.942383f, -3874.982422f, 297.452515f, 0.0f, TELE_TO_GM_MODE); break; }
		    		}
		    	}
		    	if (player->getLevel() > 38 && player->getLevel() < 49)
		    	{
		    		switch (urand(0, 1))
					{
		    		    case 0: { player->TeleportTo(MAP_NAXXRAMAS, 2838.597900f, -3905.002930f, 267.600189f, 0.0f, TELE_TO_GM_MODE); break; }
		    		    case 1: { player->TeleportTo(MAP_NAXXRAMAS, 2880.051758f, -4027.369385f, 273.681305f, 0.0f, TELE_TO_GM_MODE); break; }
		    		}
		    	}
		    	if (player->getLevel() > 48 && player->getLevel() < 59)
		    	{
		    		switch (urand(0, 1))
					{
		    		    case 0: { player->TeleportTo(MAP_NAXXRAMAS, 2889.514893f, -3152.179932f, 273.787537f, 0.0f, TELE_TO_GM_MODE); break; }
		    		    case 1: { player->TeleportTo(MAP_NAXXRAMAS, 2813.166016f, -3070.372559f, 273.769867f, 0.0f, TELE_TO_GM_MODE); break; }
		    		}
		    	}
		    	if (player->getLevel() > 58 && player->getLevel() < 69)
		    	{
		    		switch (urand(0, 1))
					{
		    		    case 0: { player->TeleportTo(MAP_NAXXRAMAS, 2753.865723f, -3169.587646f, 267.654785f, 0.0f, TELE_TO_GM_MODE); break; }
		    		    case 1: { player->TeleportTo(MAP_NAXXRAMAS, 2713.648682f, -3262.009766f, 267.680023f, 0.0f, TELE_TO_GM_MODE); break; }
		    		}
		    	}
		    	if (player->getLevel() > 68 && player->getLevel() < 79)
		    	{
		    		switch (urand(0, 1))
		    		{
		    		   case 0: { player->TeleportTo(MAP_NAXXRAMAS, 3489.364502f, -5317.934082f, 139.577301f, 0.0f, TELE_TO_GM_MODE); break; }
		    		   case 1: { player->TeleportTo(MAP_NAXXRAMAS, 3499.708740f, -5188.914063f, 138.738800f, 0.0f, TELE_TO_GM_MODE); break; }
		    		}
		    	}
		    	if (player->getLevel() == 79) 
		    	{
		    		switch (urand(0, 1)) 
		    		{
		    		    case 0: { player->TeleportTo(MAP_NAXXRAMAS, 3674.613525f, -5114.908691f, 142.031281f, 0.0f, TELE_TO_GM_MODE); break; }
		    		    case 1: { player->TeleportTo(MAP_NAXXRAMAS, 3714.757568f, -5044.175293f, 143.903030f, 0.0f, TELE_TO_GM_MODE); break; }
		    		}
		    	}
		    } 
	        break;
		case GOSSIP_ACTION_INFO_DEF + 7: // roleplay
			player->CLOSE_GOSSIP_MENU();
			break;
		case GOSSIP_ACTION_INFO_DEF + 8: // twink
			player->CLOSE_GOSSIP_MENU();
			break;
		}

		return true;
	}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_rts_welcomerAI(creature);
	}

	struct npc_rts_welcomerAI : public ScriptedAI
	{
		npc_rts_welcomerAI(Creature* creature) : ScriptedAI(creature) { }
		uint32 SaySomething_Timer;

		void Reset()
		{
			SaySomething_Timer = urand(25000, 50000);
		}

		void UpdateAI(uint32 diff)
		{
			if (SaySomething_Timer <= diff) 
			{
				switch (urand(0, 2)) 
				{
				    case 0: 
					{ 
						me->Say(NPC_MESSAGE_ONE, LANG_UNIVERSAL); 
						break; 
					}
				    case 1: 
					{ 
						me->Say(NPC_MESSAGE_TWO, LANG_UNIVERSAL); 
						break; 
					}
				    case 2: 
					{ 
						me->Say(NPC_MESSAGE_THREE, LANG_UNIVERSAL); 
						break; 
					}
				}
				SaySomething_Timer = urand(25000, 50000);
			}
			else SaySomething_Timer -= diff;
		}
	};
};

void AddSC_rts_npc_welcomer()
{
	new npc_rts_welcomer();
}