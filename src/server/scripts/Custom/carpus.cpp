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

            Player* player = handler->GetSession()->GetPlayer();
            if(player->HasSelectedGameObject())
            {

                if(player->GetSelectedGameObject()->GetEntry() != GO_CARPUS_TELEPORTER)
                {
                    handler->SendSysMessage("The object you have selected is not a carpus object and can't be linked to the portal system.");
                    return false;
                }

                uint32 guid = player->GetSelectedGameObject()->GetGUIDLow();
                float x, y, z, ort;
                uint32 map;

                x = player->GetPositionX();
                y = player->GetPositionY();
                z = player->GetPositionZ();
                ort = player->GetOrientation();
                map = player->GetMapId();

                QueryResult result = WorldDatabase.PQuery("SELECT objectID FROM carpus_teleports WHERE objectID='%u'", guid);
                
                if(result)
                    WorldDatabase.PExecute("UPDATE carpus_teleports SET map='%u', x='%f', y='%f', z='%f', o='%f' WHERE objectID='%u'", map, x, y, z, ort, guid);
                else
                    WorldDatabase.PExecute("INSERT INTO carpus_teleports (objectID, map, x, y, z, o) VALUES (%u, %u, %f, %f, %f, %f)", guid, map, x, y, z, ort);

                handler->SendSysMessage("A link has been added at your location to the selected object.");
                return true;
            }

            handler->SendSysMessage("You didn't select an object. Run .gobject target first.");
            return false;
        }
};

class carpus_main : public GameObjectScript
{
    public:
        carpus_main() : GameObjectScript("carpus_main"){}

        bool OnGossipHello(Player* player, GameObject* go) 
        {
            uint32 guid = (uint32)go->GetGUIDLow();
            QueryResult result = WorldDatabase.PQuery("SELECT map, x, y, z, o FROM carpus_teleports WHERE objectID='%u' LIMIT 1", guid);
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
