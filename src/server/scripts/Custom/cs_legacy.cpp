#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "MapManager.h"
#include "Chat.h"
#include "Group.h"
#include "Player.h"
#include "AccountMgr.h"
#include "Language.h"
#include "PlayerDump.h"
#include <Pet.h>
#include <PetAI.h>
class cs_legacy : public CommandScript
{
public:
	cs_legacy() : CommandScript("cs_legacy") {}
	ChatCommand* GetCommands() const
	{
		static ChatCommand commandTable[] =
		{
			{ "warp",      rbac::RBAC_PERM_COMMAND_WARP,      false, &HandleWarpCommand,      "", NULL },
			{ "grantlife", rbac::RBAC_PERM_COMMAND_GRANTLIFE, false, &HandleGrantLifeCommand, "", NULL },
			{ "takelife",  rbac::RBAC_PERM_COMMAND_TAKELIFE,  false, &HandleTakeLifeCommand,  "", NULL },
			{ NULL,        0,                                 false, NULL,                    "", NULL }
		};

		return commandTable;
	}

	static bool HandleTakeLifeCommand(ChatHandler* handler, const char* args)
	{
		if (!args)
			return false;

		Player* target;
		ObjectGuid targetGuid;
		std::string targetName;

		if (!handler->extractPlayerTarget((char*)args, &target, &targetGuid, &targetName))
			return false;

		if (!target)
			return false;

        if (target->IsExecuted())
        {
            handler->SendSysMessage("Player already dead.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        target->SetExecuted(true);
        CharacterDatabase.PExecute("INSERT IGNORE INTO character_deaths (%u, 'GM Command')", target->GetGUIDLow());
        handler->PSendSysMessage("You have taken away the life of %s.", target->GetName().c_str());
        ChatHandler(target->GetSession()).SendSysMessage("Your life has been taken away.");

		return true;
	}

	static bool HandleGrantLifeCommand(ChatHandler* handler, const char* args)
	{
		if (!args)
			return false;

		Player* target;
		ObjectGuid targetGuid;
		std::string targetName;

		if (!handler->extractPlayerTarget((char*)args, &target, &targetGuid, &targetName))
			return false;

		if (!target)
			return false;
        
        if (!target->IsExecuted())
        {
            handler->SendSysMessage("Target already alive.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        target->SetExecuted(false);
        CharacterDatabase.PExecute("DELETE FROM character_deaths WHERE guid = %u", target->GetGUIDLow());

        handler->PSendSysMessage("You have refunded %s.", target->GetName().c_str());
        ChatHandler(target->GetSession()).SendSysMessage("Your life has been refunded.");

		return true;
	}

	static bool HandleWarpCommand(ChatHandler* handler, const char* args)
	{
		if (!*args)
			return false;
		Player* player = handler->GetSession()->GetPlayer();

		char* distance = strtok((char*)args, " ");
		char* direction = strtok(NULL, " ");

		if (!distance || !direction)
			return false;

		char d = direction[0];
		float value = float(atof(distance));
		float x = player->GetPositionX();
		float y = player->GetPositionY();
		float z = player->GetPositionZ();
		float o = player->GetOrientation();
		uint32 mapid = player->GetMapId();

		switch (d)
		{
		case 'l': // LEFT DIRECTION
		{
					  x = x + cos(o + (M_PI / 2))*value;
					  y = y + sin(o + (M_PI / 2))*value;
					  player->TeleportTo(mapid, x, y, z, o);
		}
			break;
		case 'r': // RIGHT DIRECTION
		{
					  x = x + cos(o - (M_PI / 2))*value;
					  y = y + sin(o - (M_PI / 2))*value;
					  player->TeleportTo(mapid, x, y, z, o);
		}
			break;
		case 'f':
		{
					x = x + cosf(o)*value;
					y = y + sinf(o)*value;
					player->TeleportTo(mapid, x, y, z, o);
		}
			break;
		case 'b':
		{
					x = x - cosf(o)*value;
					y = y - sinf(o)*value;
					player->TeleportTo(mapid, x, y, z, o);
		}
			break;
		case 'u':
			player->TeleportTo(mapid, x, y, z + value, o);
			break;
		case 'd':
			player->TeleportTo(mapid, x, y, z - value, o);
			break;
		case 'o':
		{
					o = Position::NormalizeOrientation((value * M_PI / 180.0f) + o);
					player->TeleportTo(mapid, x, y, z, o);
		}
			break;

		}

		return true;

	}

};

void AddSC_cs_legacy()
{
	new cs_legacy();
}
