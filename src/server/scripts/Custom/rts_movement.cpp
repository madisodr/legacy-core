#include "ScriptPCH.h"
#include "MoveSpline.h"
#include "MoveSplineInit.h"
#include "WaypointMovementGenerator.h"

#define PI 3.14159265

class rts_movement : public SpellScriptLoader 
{
    public:
        rts_movement() : SpellScriptLoader("rts_movement"){ }

        class rts_movement_SpellScript : public SpellScript
    {
        PrepareSpellScript(rts_movement_SpellScript);

        void HandleAfterCast()
        {
            if(GetCaster()->GetTypeId() != TYPEID_PLAYER || !GetCaster())
                return;

            Player* player = GetCaster()->ToPlayer();

            if(Creature* creature = (Creature*)player->GetSelectedUnit())
            {
                if(creature->GetTypeId() != TYPEID_UNIT)
                    return;

                const WorldLocation summonPos = *GetExplTargetDest();
                float x = summonPos.GetPositionX();
                float y = summonPos.GetPositionY();
                float z = summonPos.GetPositionZ();

                Movement::Location dest(x, y, z, 0.0f);
                Movement::MoveSplineInit init(creature);

                init.MoveTo(x,y,z);
                init.Launch();
            }
        }

        void Register()
        {
            AfterCast += SpellCastFn(rts_movement_SpellScript::HandleAfterCast);
        }
    };

        SpellScript* GetSpellScript() const
        {
            return new rts_movement_SpellScript();
        }
};

class rts_placement : public SpellScriptLoader 
{
    public:
        rts_placement() : SpellScriptLoader("rts_placement"){ }

        class rts_placement_SpellScript : public SpellScript
    {
        PrepareSpellScript(rts_placement_SpellScript);

        void HandleAfterCast()
        {
            if(GetCaster()->GetTypeId() != TYPEID_PLAYER || !GetCaster())
                return;

            Player* player = GetCaster()->ToPlayer();
            uint32 entry = player->getSavedCreatureId();
            Map* map = player->GetMap();
            const WorldLocation summonPos = *GetExplTargetDest();

            if(!sObjectMgr->GetCreatureTemplate(entry))
                return;

            Creature* creature = new Creature();
            if (!creature->Create(sObjectMgr->GenerateLowGuid(HIGHGUID_UNIT), map, player->GetPhaseMaskForSpawn(), entry, summonPos.GetPositionX(), summonPos.GetPositionY(), summonPos.GetPositionZ(), player->GetOrientation()))
            {
                delete creature;
                return;
            }

            creature->SaveToDB(map->GetId(), (1 << map->GetSpawnMode()), player->GetPhaseMaskForSpawn());

            uint32 db_guid = creature->GetDBTableGUIDLow();

            // current "creature" variable is deleted and created fresh new, otherwise old values might trigger asserts or cause undefined behavior
            creature->CleanupsBeforeDelete();
            delete creature;
            creature = new Creature();
            if (!creature->LoadCreatureFromDB(db_guid, map))
            {
                delete creature;
                return;
            }

            sObjectMgr->AddCreatureToGrid(db_guid, sObjectMgr->GetCreatureData(db_guid));
        }

        void Register()
        {
            AfterCast += SpellCastFn(rts_placement_SpellScript::HandleAfterCast);
        }
    };

        SpellScript* GetSpellScript() const
        {
            return new rts_placement_SpellScript();
        }
};

void AddSC_rts_movement()
{
    new rts_movement();
    new rts_placement();
}
