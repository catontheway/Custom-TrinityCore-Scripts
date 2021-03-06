/* ScriptData
SDAuthor: frostI
SDName: npc_rts_resurrector_pvp
SD%Complete: 100
SDComment:
SDCategory: Custom
EndScriptData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "PassiveAI.h"
#include "Player.h"

enum Spells
{
	SPELL_REVIVE = 51918
};

enum Yells
{
	WHISPER_REVIVE = 0
};

class npc_rts_pvp_resurrector : public CreatureScript
{
public:
	npc_rts_pvp_resurrector() : CreatureScript("npc_rts_pvp_resurrector") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_rts_pvp_resurrectorAI(creature);
	}

	struct npc_rts_pvp_resurrectorAI : public PassiveAI
	{
		npc_rts_pvp_resurrectorAI(Creature* creature) : PassiveAI(creature) { }

		uint32 FlyBackTimer;
		float x, y, z;
		uint32 phase;

		void Reset()
		{
			me->setActive(true);
			me->SetVisible(false);
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
			me->SetCanFly(true);
			FlyBackTimer = 500;
			phase = 0;

			me->GetPosition(x, y, z);
			z += 4.0f;
			x -= 3.5f;
			y -= 5.0f;
			me->GetMotionMaster()->Clear(false);
			me->SetPosition(x, y, z, 0.0f);
		}

		void UpdateAI(uint32 diff)
		{
			if (FlyBackTimer <= diff)
			{
				Player* player = NULL;
				if (me->IsSummon())
					if (Unit* summoner = me->ToTempSummon()->GetSummoner())
						player = summoner->ToPlayer();

				if (!player)
					phase = 3;

				switch (phase)
				{
				case 0:
					me->SetCanFly(true);
					me->HandleEmoteCommand(EMOTE_STATE_FLYGRABCLOSED);
					FlyBackTimer = 500;
					break;
				case 1:
					player->GetClosePoint(x, y, z, me->GetObjectSize());
					z += 2.5f;
					x -= 2.0f;
					y -= 1.5f;
					me->GetMotionMaster()->MovePoint(0, x, y, z);
					me->SetTarget(player->GetGUID());
					me->SetVisible(true);
					FlyBackTimer = 3000;
					break;
				case 2:
					if (!player->isResurrectRequested())
					{
						me->HandleEmoteCommand(EMOTE_ONESHOT_CUSTOM_SPELL_01);
						DoCast(player, SPELL_REVIVE, true);
						Talk(WHISPER_REVIVE);
					}
					FlyBackTimer = 3000;
					break;
				case 3:
					me->SetVisible(false);
					FlyBackTimer = 3000;
					break;
				case 4:
					me->DisappearAndDie();
					break;
				default:
					//Nothing To DO
					break;
				}
				++phase;
			}
			else
				FlyBackTimer -= diff;
		}
	};
};

void AddSC_npc_rts_pvp_resurrector()
{
	new npc_rts_pvp_resurrector();
}