#include "ScriptMgr.h"
#include "Player.h"
#include "GameObject.h"

enum CarpusGOs
{
    GO_CARPUS_TELEPORTER = 540120
};

class carpus_commandscript : public CommandScript
{
    public:
        carpus_commandscript() : CommandScript("carpus_commandscript"){}

        ChatCommand* GetCommands() const 
        {

            static ChatCommand carpusCommandTable[] =
            {
                { "link",   rbac::RBAC_PERM_COMMAND_CARPUS_LINK, true,  &HandleLinkCommand, "", NULL},
                { NULL,     0,                                   false, NULL,               "", NULL}
            };

            static ChatCommand commandTable[] =
            {
                { "carpus", SEC_MODERATOR, true,  NULL, "", carpusCommandTable},
                { NULL,     0,             false, NULL, "", NULL}
            };

            return commandTable;
        }

        static bool HandleLinkCommand(ChatHandler* handler, const char* args)
        {
            if(!args)
                return false;

            Player* player = handler->GetSession()->GetPlayer();

            char* id = handler->extractKeyFromLink((char*)args, "Hgameobject");
            if(!id)
                return false;

            uint32 guid = atoi(id);
            if(!guid)
                return false;

            char const* ccount = strtok(NULL, " ");
            int32 count = 0;
            if(ccount)
                count = strtol(ccount, NULL, 10);

            if(count < 0)
                return false;

            float x, y, z, ort;
            uint32 map;

            if(GameObjectData const* goData = sObjectMgr->GetGOData(guid))
            {
                if(goData->id == GO_CARPUS_TELEPORTER)
                {
                    x = player->GetPositionX();
                    y = player->GetPositionY();
                    z = player->GetPositionZ();
                    ort = player->GetOrientation();
                    map = player->GetMapId();
                }
            }

            QueryResult result = WorldDatabase.PQuery("SELECT objectID FROM carpus_teleports WHERE objectID='%u' && portNum='%u'", guid, count);
            if(result)
                WorldDatabase.PExecute("UPDATE carpus_teleports SET map='%u', x='%f', y='%f', z='%f', o='%f' WHERE objectID='%u' && portNum='%u'", map, x, y, z, ort, guid, count);
            else
                WorldDatabase.PExecute("INSERT INTO carpus_teleports (objectID, map, x, y, z, o, portNum) VALUES (%u, %u, %f, %f, %f, %f, %u)", guid, map, x, y, z, ort, count);

            return true;
        }
};

class carpus_main : public GameObjectScript
{
    public:
        carpus_main() : GameObjectScript("carpus_main"){}

        bool OnGossipHello(Player* player, GameObject* go) 
        {
            uint32 guid = (uint32)go->GetGUIDLow();
            QueryResult result = WorldDatabase.PQuery("SELECT map, x, y, z, o FROM carpus_teleports WHERE objectID='%u' ORDER BY RAND() LIMIT 1", guid);
            if(!result)
                return false;

            Field* fields = result->Fetch();

            uint32 map = fields[0].GetUInt32();
            float x = fields[1].GetFloat();
            float y = fields[2].GetFloat();
            float z = fields[3].GetFloat();
            float o = fields[4].GetFloat();

            player->TeleportTo(map, x, y, z, o);

            return true;
        }
};

void AddSC_carpus_script()
{
    new carpus_main();
    new carpus_commandscript();
}
