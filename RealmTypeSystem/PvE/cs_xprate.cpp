/* ScriptData
SDAuthor: frostI
SDName: cs_xprate
SD%Complete: 100
SDComment:
SDCategory: Custom
EndScriptData */

#include "ScriptPCH.h"
#include "Language.h"
#include "../Custom/RealmTypeSystem/rts.h"

#define MAX_XP_RATE 10

class cs_xprate : public CommandScript
{
public:
	cs_xprate() : CommandScript("cs_xprate") { }

	ChatCommand* GetCommands() const override
	{
		static ChatCommand commandTable[] =
		{
			{ "xprate", rbac::RBAC_PERM_COMMAND_XP_RATE, false, &HandleXpRateCommand, "", NULL },
			{ NULL, 0, false, NULL, "", NULL }
		};
		return commandTable;
	}

	static bool HandleXpRateCommand(ChatHandler* handler, char const* args)
	{
		if (!*args)
			return false;

		Player* player = handler->GetSession()->GetPlayer();
		if (player->GetRealmType() == RTS_PVE || player->GetRealmType() == RTS_DONATOR)
		{
			float xp_rate = atof((char*)args);
			if (xp_rate < 0 || xp_rate > MAX_XP_RATE)
			{
				handler->PSendSysMessage(LANG_BAD_VALUE);
				handler->SetSentErrorMessage(true);
				return false;
			}
			player->SetXpRate(xp_rate);
			player->SaveToDB();
			handler->PSendSysMessage(LANG_SET_XPRATE, player->GetXpRate());
			return true;
		}
		else
			handler->SendSysMessage(LANG_COMMAND_ERROR_PVE);
		return false;
	}
};

void AddSC_cs_xprate()
{
	new cs_xprate();
}