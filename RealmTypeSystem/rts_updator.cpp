/* ScriptData
SDAuthor: frostI
SDName: rts_updator
SD%Complete: 100
SDComment:
SDCategory: Custom
EndScriptData */

#include "ScriptPCH.h"
#include "AccountMgr.h"
#include "WorldSession.h"
#include "Map.h"

#define NPC_RTS_RESURRECTOR 5000300

#define ON_MAX_LEVEL_19 "Your XP Rate has been set to 0 and you received The Advanced Pocket Kite!"
#define ON_MAX_LEVEL_80 "You received The Advanced Pocket Kite!"

#define NAXX_STAGE_ONE "You advanced to stage 1!"
#define NAXX_STAGE_TWO "You advanced to stage 2!"
#define NAXX_STAGE_THREE "You advanced to stage 3!"
#define NAXX_STAGE_FOUR "You advanced to stage 4!"
#define NAXX_STAGE_FIVE "You advanced to stage 5!"
#define NAXX_STAGE_SIX "You advanced to stage 6!"
#define NAXX_STAGE_SEVEN "You advanced to stage 7!"
#define NAXX_STAGE_LAST "You advanced to the last stage!"

class rts_updator : public PlayerScript
{
public:
	rts_updator() : PlayerScript("rts_updator_2") { }

	void OnPVPKill(Player* killer, Player* killed)
	{
		if (killed->GetRealmType() == 2 && killed->GetZoneId() == 3456)
			killed->SummonCreature(NPC_RTS_RESURRECTOR, killed->GetPositionX() - 3.5f, killed->GetPositionY() - 5.0f, killed->GetPositionZ() + 4.0f, 0.0f, TEMPSUMMON_MANUAL_DESPAWN);
		if (killer->HasAura(20367) && killer->getLevel() > 0 && killer->getLevel() < 9)
			killer->GiveXP(250, killer);
		if (killer->HasAura(20368) && killer->getLevel() > 8 && killer->getLevel() < 19)
			killer->GiveXP(625, killer);
		if (killer->HasAura(20369) && killer->getLevel() > 18 && killer->getLevel() < 29)
			killer->GiveXP(1560, killer);
		if (killer->HasAura(20370) && killer->getLevel() > 28 && killer->getLevel() < 39)
			killer->GiveXP(3905, killer);
		if (killer->HasAura(20371) && killer->getLevel() > 38 && killer->getLevel() < 49)
			killer->GiveXP(9765, killer);
		if (killer->HasAura(20372) && killer->getLevel() > 48 && killer->getLevel() < 59)
			killer->GiveXP(24415, killer);
		if (killer->HasAura(20373) && killer->getLevel() > 58 && killer->getLevel() < 69)
			killer->GiveXP(48830, killer);
		if (killer->HasAura(20374) && killer->getLevel() > 68 && killer->getLevel() < 79)
			killer->GiveXP(122070, killer);
		if (killer->HasAura(22429) && killer->getLevel() == 79)
			killer->GiveXP(122070, killer);
	}

	void OnPlayerKilledByCreature(Creature* /*killer*/, Player* killed)
	{
		if (killed->GetZoneId() == 3456 && killed->GetRealmType() == 2)
			killed->SummonCreature(NPC_RTS_RESURRECTOR, killed->GetPositionX() - 3.5f, killed->GetPositionY() - 5.0f, killed->GetPositionZ() + 4.0f, 0.0f, TEMPSUMMON_MANUAL_DESPAWN);
	}

	void OnLevelChanged(Player* player, uint8 newLevel)
	{
		switch (newLevel)
		{
		case 18:
			if (player->GetRealmType() == 4 && !player->HasSpell(45127))
			{
				player->LearnSpell(45127, false);
				player->SetXpRate(0.0f);
				player->GetSession()->SendAreaTriggerMessage(ON_MAX_LEVEL_19);
			}
			break;
		case 79:
			if (player->GetRealmType() == 1 || player->GetRealmType() == 2 || player->GetRealmType() == 3 && !player->HasSpell(45127))
			{
				player->LearnSpell(45127, false);
				player->SetXpRate(0.0f);
				player->GetSession()->SendAreaTriggerMessage(ON_MAX_LEVEL_80);
			}
			break;
		}

		if (player->GetZoneId() == 3456 && player->GetRealmType() == 2)
		{
			switch (newLevel)
			{
			case 8:
				switch (urand(0, 1))
				{
				    case 0: { player->TeleportTo(533, 3115.019531f, -3585.915527f, 287.080627f, player->GetOrientation()); break; }
				    case 1: { player->TeleportTo(533, 3210.555664f, -3575.030518f, 287.081329f, player->GetOrientation()); break; }
						player->GetSession()->SendAreaTriggerMessage(NAXX_STAGE_ONE);
				}
				break;
			case 18:
				switch (urand(0, 1))
				{
				    case 0: { player->TeleportTo(533, 3380.567383f, -3694.015625f, 259.081146f, player->GetOrientation()); break; }
				    case 1: { player->TeleportTo(533, 3235.829346f, -3808.203857f, 273.935242f, player->GetOrientation()); break; }
						player->GetSession()->SendAreaTriggerMessage(NAXX_STAGE_TWO);
				}
				break;
			case 28:
				switch (urand(0, 1))
				{
				    case 0: { player->TeleportTo(533, 3396.401611f, -3841.288086f, 294.665802f, player->GetOrientation()); break; }
				    case 1: { player->TeleportTo(533, 3473.942383f, -3874.982422f, 297.452515f, player->GetOrientation()); break; }
						player->GetSession()->SendAreaTriggerMessage(NAXX_STAGE_THREE);
				}
				break;
			case 38:
				switch (urand(0, 1))
				{
				    case 0: { player->TeleportTo(533, 2838.597900f, -3905.002930f, 267.600189f, player->GetOrientation()); break; }
				    case 1: { player->TeleportTo(533, 2880.051758f, -4027.369385f, 273.681305f, player->GetOrientation()); break; }
						player->GetSession()->SendAreaTriggerMessage(NAXX_STAGE_FOUR);
				}
				break;
			case 48:
				switch (urand(0, 1))
				{
				    case 0: { player->TeleportTo(533, 2889.514893f, -3152.179932f, 273.787537f, player->GetOrientation()); break; }
				    case 1: { player->TeleportTo(533, 2813.166016f, -3070.372559f, 273.769867f, player->GetOrientation()); break; }
						player->GetSession()->SendAreaTriggerMessage(NAXX_STAGE_FIVE);
				}
				break;
			case 58:
				switch (urand(0, 1))
				{
				    case 0: { player->TeleportTo(533, 2753.865723f, -3169.587646f, 267.654785f, player->GetOrientation()); break; }
				    case 1: { player->TeleportTo(533, 2713.648682f, -3262.009766f, 267.680023f, player->GetOrientation()); break; }
						player->GetSession()->SendAreaTriggerMessage(NAXX_STAGE_SIX);
				} break;
			case 68:
				switch (urand(0, 1))
				{
				    case 0: { player->TeleportTo(533, 3489.364502f, -5317.934082f, 139.577301f, player->GetOrientation()); break; }
				    case 1: { player->TeleportTo(533, 3499.708740f, -5188.914063f, 138.738800f, player->GetOrientation()); break; }
						player->GetSession()->SendAreaTriggerMessage(NAXX_STAGE_SEVEN);
				}
				break;
			case 78:
				switch (urand(0, 1))
				{
				    case 0: { player->TeleportTo(533, 3674.613525f, -5114.908691f, 142.031281f, player->GetOrientation()); break; }
				    case 1: { player->TeleportTo(533, 3714.757568f, -5044.175293f, 143.903030f, player->GetOrientation()); break; }
						player->GetSession()->SendAreaTriggerMessage(NAXX_STAGE_LAST);
				}
				break;
			}
		}
		else
			return;
	}

	void OnUpdateZone(Player* player, uint32 /*newZone*/, uint32 newArea)
	{
		// realm type 0
		if (player->GetRealmType() == 0
			&& newArea != 3486)
			player->TeleportTo(0, 1.32059f, -1621.36f, 196.653f, 0, 544785);
		// realm type 1
		if (player->GetRealmType() == 1 && player->GetPhaseMask() == 5
			&& newArea != 4290)
			player->SetPhaseMask(1, true);
		// realm type 2
		if (player->GetRealmType() == 2 && player->GetPhaseMask() == 2
			&& newArea != 3456
			&& newArea != 4234
			&& newArea != 41
			&& newArea != 10)
			player->SetPhaseMask(1, true);
		// realm type 3
		if (player->GetRealmType() == 5 && player->GetPhaseMask() == 8
			&& newArea != 69)
			player->SetPhaseMask(1, true);
		// realm type 4
		if (player->GetRealmType() == 4 && player->GetPhaseMask() == 16
			&& newArea != 395)
			player->SetPhaseMask(1, true);

		switch (newArea)
		{
		case 3456: // naxxramas pvp
			if (player->GetRealmType() == 2)
			{
				if (player->GetSession()->GetSecurity() > SEC_PLAYER)
					player->SetGameMaster(false);
				player->SetPhaseMask(2, true);
			}
			break;
		case 4290: // pve mall
			if (player->GetRealmType() == 1 || player->GetRealmType() == 5)
				player->SetPhaseMask(5, true);
			break;
		case 41: // pvp mall
			if (player->GetRealmType() == 2 || player->GetRealmType() == 5)
				player->SetPhaseMask(2, true);
			break;
		case 10: // pvp mall
			if (player->GetRealmType() == 2 || player->GetRealmType() == 5)
				player->SetPhaseMask(2, true);
			break;
		case 69: // roleplay mall
			if (player->GetRealmType() == 3 || player->GetRealmType() == 5)
				player->SetPhaseMask(8, true);
			break;
		case 395: // twink mall
			if (player->GetRealmType() == 4)
				player->SetPhaseMask(16, true);
			break;
		}
	}
};

void AddSC_rts_updator()
{
	new rts_updator;
}