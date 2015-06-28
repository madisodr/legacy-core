#include "ScriptMgr.h"
#include "ScriptPCH.h"
#include "ObjectMgr.h"
#include "MapManager.h"
#include "Language.h"
#include "Chat.h"
#include "Group.h"
#include "Player.h"
#include "WorldSession.h"
#include "World.h"

#include <time.h>
#include <string>


/**********************************************
 * Euclid AI
 * |
 *  -> includes Pythagoras
 *
 * CONFIG_EUCLID_ON
 * CONFIG_EUCLID_PERCENT
 * CONFIG_EUCLID_DANGER
 * CONFIG_PYTHAGORAS
 * CONFIG_APOLLONIUS
 *
 * gameobjects for armor drops
 *     Chest: 508596
 *     Pants: 508598
 *     Helm: 193200
 *     Boots: 508591
 *     Shoulders: 508421
 *
 *
 * PylonNPC - 99100
 ***********************************************/
#define T_WAVE 10000 // in miliseconds - turn into config option
#define PYLONID 99100 // pylon npc spawn entry
#define PRECENT 1

class euclid : public CreatureScript
{
    public:
        euclid() : CreatureScript("euclid") {}

        struct euclidAI : public ScriptedAI
    {
        euclidAI(Creature* creature) : ScriptedAI(creature){}

        uint32 m_dsTimer;
        uint32 spawnPrecent;
        uint32 radius;

        std::vector<uint32> creatures, resources;
        std::vector<GameObject*> resourceSpawns;
        
        void Reset()
        {
            m_dsTimer = T_WAVE;
        }

        uint32 calculateWaveLimit()
        {
            return uint32(sWorld->GetMaxActiveSessionCount() * (float)(spawnPrecent / 100));
        } // calculateWaveLimit()

        void UpdateAI(uint32 uiDiff)
        {

            if (sWorld->getBoolConfig(CONFIG_EUCLID_ON))
            {
                if(uiDiff > m_dsTimer)
                {
                    spawnWave(15);
                    Reset();
                }
                else
                    m_dsTimer -= uiDiff;
            }
        } // UpdateAI(uint32 uiDiff)

        void loadNPCs()
        {
            Field* fields;
            QueryResult result = WorldDatabase.PQuery("SELECT npcEntry FROM euclid_npcs WHERE guid='%u'", me->GetGUIDLow());

            creatures.clear();

            if(!result)
                return;

            do
            {
                fields = result->Fetch();
                creatures.push_back(fields[0].GetUInt32());
            } while (result->NextRow());
        } // loadNPCs()

        void loadResources()
        {
            Field* fields;
            QueryResult result = WorldDatabase.PQuery("SELECT objEntry FROM euclid_resources WHERE guid='%u'", me->GetGUIDLow());

            resources.clear();

            if(!result)
                return;

            do
            {
                fields = result->Fetch();
                resources.push_back(fields[0].GetUInt32());
            } while (result->NextRow());
        } // loadResources()

        void loadRadius()
        {
            Field* fields;
            QueryResult result = WorldDatabase.PQuery("SELECT radius FROM euclid_radius WHERE guid='%u'", me->GetGUIDLow());

            if(!result)
                radius = 400;
            else
                radius = result->Fetch()[0].GetUInt32();
        }

        void spawnWave(uint32 wavesize)
        {
            int32 randNpc = 0, randResc = 0;
            loadNPCs();
            loadResources();
            loadRadius();
            int32 angle, dist;

            srand(time(NULL));

            if(creatures.size() > 0)
            {
                for(uint32 i = 0; i < wavesize; i++)
                {
                    angle = rand() % 720;
                    angle = angle - 360;

                    dist = rand() % radius;

                    if(dist < 20)
                        dist += 40;

                    float pointX = me->GetPositionX() + (dist * cos(angle*M_PI/180));
                    float pointY = me->GetPositionY() + (dist * sin(angle*M_PI/180));
                    float pointZ = me->GetMap()->GetHeight(pointX, pointY, me->GetPositionZ(), true, 10000.0f);

                    randNpc = rand() % creatures.size();
                    std::string text = "Spawning npc;" + std::to_string(randNpc);
                    me->SummonCreature(creatures[randNpc], pointX, pointY, pointZ, angle, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, T_WAVE);
                }
            }

            if(resources.size() > 0)
            {

                for(uint32 i = 0; i < resourceSpawns.size(); i++)
                {
                    me->GetMap()->RemoveFromMap(resourceSpawns[i], true);
                }

                resourceSpawns.clear();

                for(uint32 i = 0; i < wavesize; i++)
                {
                    angle = rand() % 720;
                    angle = angle - 360;

                    dist = rand() % radius;
                    if(dist < 20)
                        dist += 40;

                    float pointX = me->GetPositionX() + (dist * cos(angle*M_PI/180));
                    float pointY = me->GetPositionY() + (dist * sin(angle*M_PI/180));
                    float pointZ = me->GetMap()->GetHeight( pointX, pointY, me->GetPositionZ(), true, 10000.0f);
                    
                    randResc = rand() % resources.size();

                    GameObject* obj = me->SummonGameObject(resources[randResc], pointX, pointY, pointZ, angle, 0, 0, sin(angle/2), cos(angle/2), 0);
                    resourceSpawns.push_back(obj);
                }
            }
            //Spawn Resource Wave
        } // spawnWave(uint32 wavesize)

    }; // struct euclidAI

        CreatureAI* GetAI(Creature* creature) const 
        {
            return new euclidAI(creature);
        }

};

class cs_euclid : public CommandScript
{
    public:
        cs_euclid() : CommandScript("cs_euclid"){}

        ChatCommand* GetCommands() const
        {
            static ChatCommand euclidRemoveTable[] =
            { 
                { "npc",        SEC_MODERATOR,  false, &HandleRemoveNPCCommand,     "", NULL },
                { "resource",   SEC_MODERATOR,  false, &HandleRemoveResourceCommand,   "", NULL },
                { NULL,         0,              false, NULL,                        "", NULL }
            };

            static ChatCommand euclidAddTable[] =
            { 
                { "npc",        SEC_MODERATOR,  false, &HandleAddNPCCommand,        "", NULL },
                { "resource",   SEC_MODERATOR,  false, &HandleAddResourceCommand,   "", NULL },
                { NULL,         0,              false, NULL,                        "", NULL }
            };

            static ChatCommand euclidCommandTable[] =
            {
                { "add",        SEC_MODERATOR,   true,  NULL,           "", euclidAddTable },
                { "remove",     SEC_MODERATOR,   true,  NULL,        "", euclidRemoveTable },
                { "size"  ,     SEC_MODERATOR,   false, &HandleSizeCommand,       "", NULL },
                { "info",       SEC_MODERATOR,   false, &HandlePylonInfoCommand,  "", NULL },
                { NULL,         0,               false, NULL,                     "", NULL }
            };

            static ChatCommand commandTable[] =
            {
                { "euclid",     SEC_MODERATOR,      true, NULL,       "", euclidCommandTable },
                { NULL,         0,               false, NULL,                  "", NULL }
            };

            return commandTable;
        }

        static bool HandleSizeCommand(ChatHandler* handler, const char* args)
        {
            if(!*args)
                return false;

            uint32 size = atoi((char*)args);

            if(size < 1)
            {
                handler->SendSysMessage(LANG_BAD_VALUE);
                handler->SetSentErrorMessage(true);
                return false;
            }

            Creature* node = handler->getSelectedCreature();
            if(!node || node->GetEntry() != PYLONID)
            {
                handler->SendSysMessage(LANG_SELECT_CREATURE);
                handler->SetSentErrorMessage(true);
                return false;
            }

            uint32 guid = node->GetGUIDLow();

            QueryResult result = WorldDatabase.PQuery("SELECT radius FROM euclid_radius WHERE guid='%u'", guid);
            if(result)
                WorldDatabase.PExecute("UPDATE euclid_radius SET radius='%u' WHERE guid='%u'", size, guid);
            else
                WorldDatabase.PExecute("INSERT INTO euclid_radius VALUES ('%u', '%u')", guid, size);

            handler->PSendSysMessage("Size of Node %u has been set too %u", guid, size);

        }

        static bool HandleRemoveNPCCommand(ChatHandler* handler, const char* args){
            if(!*args)
                return false;

            Creature* node = handler->getSelectedCreature();
            if (!node || node->GetEntry() != PYLONID)
            {
                handler->SendSysMessage(LANG_SELECT_CREATURE);
                handler->SetSentErrorMessage(true);
                return false;
            }

            char* charID = handler->extractKeyFromLink((char*)args, "Hcreature_entry");
            if (!charID)
                return false;

            uint32 id  = atoi(charID);

            CreatureTemplate const* creatureTemplate = sObjectMgr->GetCreatureTemplate(id);
            if (!creatureTemplate)
                return false;


            WorldDatabase.PExecute("DELETE FROM euclid_npcs WHERE guid='%u'", id);
            handler->PSendSysMessage("%s has been removed from node %u", creatureTemplate->Name.c_str(), node->GetGUIDLow());

            return true;
        }

        static bool HandleRemoveResourceCommand(ChatHandler* handler, const char* args){
            if(!*args)
                return false;

            Creature* node = handler->getSelectedCreature();
            if (!node || node->GetEntry() != PYLONID)
            {
                handler->SendSysMessage(LANG_SELECT_CREATURE);
                handler->SetSentErrorMessage(true);
                return false;
            }

            char* id = handler->extractKeyFromLink((char*)args, "Hgameobject_entry");
            if (!id)
                return false;

            uint32 objectId = atol(id);
            if (!objectId)
                return false;

            const GameObjectTemplate* objectInfo = sObjectMgr->GetGameObjectTemplate(objectId);

            if (!objectInfo)
            {
                handler->PSendSysMessage(LANG_GAMEOBJECT_NOT_EXIST, objectId);
                handler->SetSentErrorMessage(true);
                return false;
            }

            WorldDatabase.PExecute("DELETE FROM euclid_resources WHERE guid='%u'", objectId);
            handler->PSendSysMessage("%s has been removed from node %u", objectInfo->name.c_str(), node->GetGUIDLow());

            return true;
        }

        static bool HandleAddNPCCommand(ChatHandler* handler, const char* args){
            if(!*args)
                return false;

            Creature* node = handler->getSelectedCreature();
            if (!node || node->GetEntry() != PYLONID)
            {
                handler->SendSysMessage(LANG_SELECT_CREATURE);
                handler->SetSentErrorMessage(true);
                return false;
            }

            char* charID = handler->extractKeyFromLink((char*)args, "Hcreature_entry");
            if (!charID)
                return false;

            uint32 id  = atoi(charID);
            CreatureTemplate const* creatureTemplate = sObjectMgr->GetCreatureTemplate(id);

            if(!creatureTemplate)
                return false;

            WorldDatabase.PExecute("INSERT INTO euclid_npcs VALUES ('%u', '%u')", node->GetGUIDLow(), id);
            handler->PSendSysMessage("%s has been added to node %u", creatureTemplate->Name.c_str(), node->GetGUIDLow());

            return true;
        }


        static bool HandleAddResourceCommand(ChatHandler* handler, const char* args)
        {
            if(!*args)
                return false;

            Creature* node = handler->getSelectedCreature();
            if (!node || node->GetEntry() != PYLONID)
            {
                handler->SendSysMessage(LANG_SELECT_CREATURE);
                handler->SetSentErrorMessage(true);
                return false;
            }

            char* id = handler->extractKeyFromLink((char*)args, "Hgameobject_entry");
            if (!id)
                return false;

            uint32 objectId = atol(id);
            if (!objectId)
                return false;

            const GameObjectTemplate* objectInfo = sObjectMgr->GetGameObjectTemplate(objectId);

            if (!objectInfo)
            {
                handler->PSendSysMessage(LANG_GAMEOBJECT_NOT_EXIST, objectId);
                handler->SetSentErrorMessage(true);
                return false;
            }			

            WorldDatabase.PExecute("INSERT INTO euclid_resources VALUES ('%u', '%u')", node->GetGUIDLow(), objectId);
            handler->PSendSysMessage("%s has been added to node %u", objectInfo->name.c_str(), node->GetGUIDLow());

            return true;
        }

        static bool HandleEuclidViewCommand(ChatHandler* handler, const char* args){
            // Whether the NPCs for the pylons are visible or not to a player
            // arguments is on or off
            return true;
        }
        static bool HandlePylonInfoCommand(ChatHandler* handler, const char* args){ 
            // list npcs
            // list resources
            // id number
            // distance
            // danger level
            return true; 
        }
};

void AddSC_euclid()
{
    new euclid();
    new cs_euclid();
}

