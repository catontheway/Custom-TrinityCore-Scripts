#include "ScriptPCH.h"

struct SystemInfo
{
	uint32 KillStreak;
	uint32 LastGUIDKill;
	uint32 DeathStreak;
};

static std::map<uint32, SystemInfo> KillingStreak;

class player_pvp_killstreaks : public PlayerScript
{
public:
	player_pvp_killstreaks() : PlayerScript("player_pvp_killstreaks") { }

	void OnPVPKill(Player* killer, Player* killed)
	{
		uint32 kGUID;
		uint32 vGUID;
		kGUID = killer->GetGUID();
		vGUID = killed->GetGUID();

		if (kGUID == vGUID)
			return;

		if ((killer->getLevel() != 80 || killed->getLevel() != 80))
			return;

		KillingStreak[vGUID].KillStreak = 0;
		KillingStreak[vGUID].LastGUIDKill = 0;
		KillingStreak[kGUID].DeathStreak = 0;

		if (killer->GetGroup())
		{
			if (killer->InBattleground() && !killer->InArena())
				KillingStreak[vGUID].DeathStreak++;
		}
		else
			KillingStreak[vGUID].DeathStreak++;

		switch (KillingStreak[vGUID].DeathStreak)
		{
		case 5:
			killed->ResurrectPlayer(1.0f);
			killed->SetPower(POWER_MANA, killed->GetMaxPower(POWER_MANA));
			killed->SpawnCorpseBones();
			killed->SaveToDB();
			killed->CastSpell(killed, 21074, true);
			killed->CastSpell(killed, 24378, true);
			killed->CastSpell(killed, 71586, true);
			killed->RemoveArenaSpellCooldowns();
			char msg[500];
			sprintf(msg, "%s is on a Death Spree and has been assisted by the server!", killed->GetName().c_str());
			sWorld->SendZoneText(killer->GetZoneId(), msg);
			KillingStreak[vGUID].DeathStreak++;
			break;
		}

		if (!(KillingStreak[kGUID].LastGUIDKill == vGUID))
		{
			if (!killer->GetGroup() || (killer->InBattleground() && !killer->InArena()))
			{
				KillingStreak[kGUID].KillStreak++;
				KillingStreak[kGUID].LastGUIDKill = vGUID;
				if (killer->GetAreaId() == 3217)
					killer->AddItem(54637, 1);
			}
			else
				return;
		}
		else
			return;

		switch (KillingStreak[kGUID].KillStreak)
		{
		case 2:
		{
			int x = urand(0, 10);
			int RandomSpell[] = { 70788, 62398, 60342, 69861, 65712, 70571, 11010, 72523, 44800, 72100, 71994 };
			killer->CastSpell(killer, RandomSpell[x], true);
		}
		break;
		case 4:
			killer->CastSpell(killer, 65828, true);
			break;
		case 5:
			char msg[500];
			sprintf(msg, "[PvP System]: %s killed %s and is on a Killing Spree! ", killer->GetName().c_str(), killed->GetName().c_str());
			sWorld->SendZoneText(killer->GetZoneId(), msg);
			killer->ModifyHonorPoints(250);
			killer->ModifyArenaPoints(25);
			break;
		case 6:
			killer->CastSpell(killer, 71586, true);
			break;
		case 8:
			killer->CastSpell(killer, 24378, true);
			break;
		case 10:
			sprintf(msg, "[PvP System]: %s killed %s and is on a Killing Frenzy! ", killer->GetName().c_str(), killed->GetName().c_str());
			sWorld->SendZoneText(killer->GetZoneId(), msg);
			killer->ModifyHonorPoints(250);
			killer->ModifyArenaPoints(25);
			break;
		case 15:
			sprintf(msg, "[PvP System]: %s killed %s and is a Running Riot! ", killer->GetName().c_str(), killed->GetName().c_str());
			sWorld->SendZoneText(killer->GetZoneId(), msg);
			killer->ModifyHonorPoints(500);
			killer->ModifyArenaPoints(50);
			break;
		case 20:
			sprintf(msg, "[PvP System]: %s killed %s and is on a Rampage! ", killer->GetName().c_str(), killed->GetName().c_str());
			sWorld->SendZoneText(killer->GetZoneId(), msg);
			killer->ModifyHonorPoints(750);
			killer->ModifyArenaPoints(75);
			break;
		case 25:
			sprintf(msg, "[PvP System]: %s killed %s and is Untouchable! ", killer->GetName().c_str(), killed->GetName().c_str());
			sWorld->SendZoneText(killer->GetZoneId(), msg);
			killer->ModifyHonorPoints(1000);
			killer->ModifyArenaPoints(100);
			break;
		case 50:
			sprintf(msg, "[PvP System]: %s killed %s and is Invincible! ", killer->GetName().c_str(), killed->GetName().c_str());
			sWorld->SendZoneText(killer->GetZoneId(), msg);
			killer->ModifyHonorPoints(5000);
			killer->ModifyArenaPoints(500);
			KillingStreak[kGUID].KillStreak = 0;
			break;
		}
	}
};

void AddSC_player_pvp_killstreaks()
{
	new player_pvp_killstreaks;
}