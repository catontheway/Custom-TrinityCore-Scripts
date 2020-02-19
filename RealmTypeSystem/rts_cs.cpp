/* ScriptData
SDAuthor: frostI
SDName: rts_cs
SD%Complete: 100
SDComment:
SDCategory: Custom
EndScriptData */

#include "ScriptPCH.h"
#include "Language.h"
#include "rts.h"

class rts_cs : public CommandScript
{
public:
	rts_cs() : CommandScript("rts_cs") { }

	ChatCommand* GetCommands() const
	{
		static ChatCommand RTSCommandTable[] =
		{
			{ "set", rbac::RBAC_PERM_COMMAND_RTS_SET, false, &HandleSetRealmTypeCommand, "", NULL },
			{ "get", rbac::RBAC_PERM_COMMAND_RTS_GET, false, &HandleGetRealmTypeCommand, "", NULL },
			{ "help", rbac::RBAC_PERM_COMMAND_RTS_HELP, false, &HandleRTSHelpCommand, "", NULL },
			{ NULL, 0, false, NULL, "", NULL }
		};

		static ChatCommand commandTable[] =
		{
			{ "rts", rbac::RBAC_PERM_COMMAND_RTS, false, NULL, "", RTSCommandTable },
			{ NULL, 0, false, NULL, "", NULL }
		};
		return commandTable;
	}

	static bool HandleSetRealmTypeCommand(ChatHandler* handler, char const* args)
	{
		if (!*args)
			return false;

		uint8 realmtype = (uint8)atoi((char*)args);

		if (realmtype < RTS_NONE || realmtype >= RTS_MAX)
		{
			handler->PSendSysMessage(LANG_BAD_VALUE);
			handler->SetSentErrorMessage(true);
			return false;
		}

		Player* target = handler->getSelectedPlayer();
		if (!target)
			target = handler->GetSession()->GetPlayer();

		uint8 oldRealmtype = target->GetRealmType();
		target->SetRealmType(realmtype);
		target->SaveToDB();
		uint8 newRealmtype = target->GetRealmType();
		handler->PSendSysMessage(LANG_SET_REALMTYPE, oldRealmtype, newRealmtype, target->GetName().c_str());
		return true;
	}

	static bool HandleGetRealmTypeCommand(ChatHandler* handler, char const* args)
	{
		Player* target = handler->getSelectedPlayer();
		if (!target)
			target = handler->GetSession()->GetPlayer();

		uint8 CurRealmType = target->GetRealmType();
		handler->PSendSysMessage(LANG_GET_REALMTYPE, CurRealmType, target->GetName().c_str());
		return true;
	}

	static bool HandleRTSHelpCommand(ChatHandler* handler, char const* /*args*/)
	{
		handler->PSendSysMessage("The RealmType System is based on numbers set in the database that correspond to the various types of gameplay available.\n* 1 = Player versus Environment (PvE)\n* 2 = Player versus Player (PvP)\n* 3 = Roleplayer (RP)\n* 4 = Twinker\n* 5 = Donator");
		return true;
	}
};

void AddSC_rts_cs()
{
	new rts_cs();
}