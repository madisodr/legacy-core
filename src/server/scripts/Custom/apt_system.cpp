#include "ScriptPCH.h"
#include "MapManager.h"
#include "Language.h"
#include "GameObject.h"
#include "ObjectAccessor.h"
#include "PetAI.h"
#include "Pet.h"


/******************************************************
 * SQL CODE
 * INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (897, 'spell_place_apt');
 * 
 * CREATE TABLE `apt_item_objects` (`itemEntry` mediumint(8) NOT NULL, `objectEntry` mediumint(8) NOT NULL , PRIMARY KEY (`itemEntry`))
 *
 *
 * TODO make item have bool isApt()
 *      if is APT, when item is deleted
 *          delete object linked to item
 **/

class item_script_apt : public ItemScript
{
    public:
        static uint32 entryId;
        static uint32 itemGuid;
        static const WorldLocation* summonPos;
        uint32 lastcast;

        item_script_apt() : ItemScript("item_script_apt") {}

        bool OnUse(Player* player, Item* item, SpellCastTargets const& targets) override
        {
            if (player->GetMapId() == 725 || player->GetMapId() == 573)
            {
                ChatHandler(player->GetSession()).SendSysMessage("You may not spawn an APT in this zone.");
                return false;
            }
            itemGuid = item->GetGUIDLow();
            entryId = item->GetEntry();
            summonPos = targets.GetDstPos();
            player->CastSpell(player, 29173, true);

            return true;
        }
};

uint32 item_script_apt::entryId = 0;
uint32 item_script_apt::itemGuid = 0;
const WorldLocation* item_script_apt::summonPos = new WorldLocation();

class spell_place_apt : public SpellScriptLoader
{
    public:
        spell_place_apt() : SpellScriptLoader("spell_place_apt") { }

        class spell_place_apt_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_place_apt_SpellScript);

        void HandleAfterCast()
        {
            if(GetCaster()->GetTypeId() != TYPEID_PLAYER || !GetCaster())
                return;

            Player* player = GetCaster()->ToPlayer();
            const WorldLocation* summonPos = item_script_apt::summonPos;

            QueryResult result = WorldDatabase.PQuery("SELECT objectEntry FROM apt_item_objects WHERE itemEntry = '%u'", item_script_apt::entryId);
            if(!result)
                return;

            Field* fields = result->Fetch();
            uint32 objectEntry = fields[0].GetUInt32();

            result = WorldDatabase.PQuery("SELECT objectGuid FROM apt_placed_objects WHERE itemID = '%u'", item_script_apt::itemGuid);
            if(result)
            {
                Field* field = result->Fetch();
                uint32 objectGuid = field[0].GetUInt32();
                if(GameObjectData const* gameObjectData = sObjectMgr->GetGOData(objectGuid))
                {
                    GameObject* object = ChatHandler(player->GetSession()).GetObjectGlobalyWithGuidOrNearWithDbGuid(objectGuid, gameObjectData->id);
                    remove(player, object);
                }
            }
            else
                place(player, summonPos->GetPositionX(), summonPos->GetPositionY(), summonPos->GetPositionZ(), player->GetOrientation(), player->GetPhaseMaskForSpawn(), objectEntry); 
        }
        void Register() override
        {
            AfterCast += SpellCastFn(spell_place_apt_SpellScript::HandleAfterCast);
        }

    };

        SpellScript* GetSpellScript() const override
        {
            return new spell_place_apt_SpellScript();
        }

        static void remove(Player* player, GameObject* object)
        {
            if (!player || !object)
                return;

            if (!object)
                return;

            // ADD IN THE CHECKS FOR OWNERSHIP
            ObjectGuid ownerGuid = object->GetOwnerGUID();
            if (ownerGuid)
            {
                Unit* owner = ObjectAccessor::GetUnit(*player, ownerGuid);
                if (!owner || !ownerGuid.IsPlayer())
                {
                    ChatHandler(player->GetSession()).PSendSysMessage(LANG_COMMAND_DELOBJREFERCREATURE, ownerGuid.GetCounter(), object->GetGUIDLow());
                    ChatHandler(player->GetSession()).SetSentErrorMessage(true);
                    return;
                }
                owner->RemoveGameObject(object, false);
            }

            QueryResult result = WorldDatabase.PQuery("DELETE FROM apt_placed_objects WHERE objectGuid='%u'", object->GetGUIDLow());
            object->SetRespawnTime(0);
            object->Delete();
            object->DeleteFromDB();


        }

        static GameObject* place(Player* player, float x, float y, float z, float o, uint32 phase, uint32 guid)
        {
            // e = !move && entry or move && guid (entryorguid
            if (!player || !guid)
                return NULL;


            phase = 1;

            const GameObjectTemplate* objectInfo = sObjectMgr->GetGameObjectTemplate(guid);

            if(player->GetDistance(x, y, z) > 20)
            {
                ChatHandler(player->GetSession()).PSendSysMessage("You cant place that object so far away.");
                ChatHandler(player->GetSession()).SetSentErrorMessage(true);
                return NULL;
            }

            if (!objectInfo)
            {
                ChatHandler(player->GetSession()).PSendSysMessage(LANG_GAMEOBJECT_NOT_EXIST, guid);
                ChatHandler(player->GetSession()).SetSentErrorMessage(true);
                return NULL;
            }

            if (objectInfo->displayId && !sGameObjectDisplayInfoStore.LookupEntry(objectInfo->displayId))
            {
                // sLog->outErrorDb("Gameobject (Entry %u GoType: %u) have invalid displayId (%u), not spawned.", e, objectInfo->type, objectInfo->displayId);
                ChatHandler(player->GetSession()).PSendSysMessage(LANG_GAMEOBJECT_HAVE_INVALID_DATA, guid);
                ChatHandler(player->GetSession()).SetSentErrorMessage(true);
                return NULL;
            }

            Map* map = player->GetMap();
            if(player->GetMapId() == 608)
            {
                ChatHandler(player->GetSession()).PSendSysMessage("Stop! Not so fast. No placing APTs in here.");
                ChatHandler(player->GetSession()).SetSentErrorMessage(true);
                return NULL;
            }

            GameObject* object = new GameObject;
            uint32 guidLow = sObjectMgr->GenerateLowGuid(HIGHGUID_GAMEOBJECT);

            if (!object->Create(guidLow, objectInfo->entry, map, phase, x, y, z, o, 0.0f, 0.0f, 0.0f, 0.0f, 0, GO_STATE_READY))
            {
                delete object;
                return NULL;
            }

            object->SaveToDB(map->GetId(), (1 << map->GetSpawnMode()), phase);

            if (!object->LoadGameObjectFromDB(guidLow, map))
            {
                delete object;
                return NULL;
            }

            // STORE THE ITEM_INSTANCE THAT WAS USED TO SPAWN THIS ITEM!!!

            sObjectMgr->AddGameobjectToGrid(guidLow, sObjectMgr->GetGOData(guidLow));

            QueryResult result = WorldDatabase.PQuery("INSERT INTO apt_placed_objects VALUES('%u', '%u')", item_script_apt::itemGuid, guidLow);
            result = WorldDatabase.PQuery("INSERT INTO legacy_gameobject VALUES ('%u', '1', '0', '%u')", guidLow, player->GetGUIDLow());

            return object;
        }
};
/*
class PlayerHook : public PlayerScript
{
public:
    PlayerHook() : PlayerScript("playerhook") {}

    void OnDelete(ObjectGuid guid, uint32 accountid) override
    {
        if (QueryResult result = WorldDatabase.PQuery("SELECT * FROM legacy_gameobject WHERE owner = %u", uint64(guid)))
        {
            do
            {
                Field* fields = result->Fetch();
                GameObject* object;
                uint32 guidLow = fields[0].GetUInt32();
                if (GameObjectData const* gameObjectData = sObjectMgr->GetGOData(guidLow))
                {
                    object = ChatHandler(sWorld->FindSession(accountid)).GetObjectGlobalyWithGuidOrNearWithDbGuid(guidLow, gameObjectData->id);

                    object->SetRespawnTime(0);
                    object->Delete();
                    object->DeleteFromDB();
                }
                else
                {
                    QueryResult result = WorldDatabase.PQuery("DELETE FROM apt_placed_objects WHERE objectGuid='%u'", object->GetGUIDLow());
                    continue;
                }

            } while (result->NextRow());
        }
    }
};

*/
void AddSC_apt_system()
{
    new item_script_apt();
    new spell_place_apt();
}

