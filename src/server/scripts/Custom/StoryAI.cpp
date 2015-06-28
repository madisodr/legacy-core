#include "StoryAI.h"
#include "Player.h"
#include "StoryscriptMgr.h"
#include "Spell.h"

int StoryAI::Permissible(const Creature* creature)
{
	if (creature->isCivilian() || creature->IsNeutralToAll())
		return PERMIT_BASE_REACTIVE;

	return PERMIT_BASE_NO;
}

void StoryAI::UpdateAI(uint32 diff)
{
	if (disabledai)
	{
		if (!UpdateVictim())
		{
			return;
		}

		DoMeleeAttackIfReady();
	}

	/* Let's process data. processed becomes false whenever the storyscript is.
	P.S: Should probably move this to initialize AI. In seperate blocks atm due to conception levels*/
	if (processed == true)
	{
		TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "HasSpells if block.");

		// if has spells
			// For every StoryScriptSpell within StoryScriptList
				// if StorySpell->Validation
					// add to realqueue.
		// if has movements
			// dec storyscriptmove
			// For every StoryScriptMove within StoryScriptMoveList
				// if StoryScriptMove->Validation
					// add to realqueue.
		// if has chat
			// For every StoryScriptChat within StoryScriptChatList
				// if StoryScriptChat->Validation
					// add to realqueue.

		TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "Processed finish block.");
		processed = false;
	}

	/**********************
	**** Out of combat ****
	***********************/
	if (!UpdateVictim())
	{
		return;
	}
	/*******************
	**** In combat *****
	********************
	* Rationalization of algorithm:
	*
	* We have a list of spells located in st->GetSpellListByGuid(me->getguidlow()).
	* We use this as a framework for our to-do list. Whenever an action is completed,
	* the UpdateSpells funciton is called to refresh the Spell List. The algorithm below
	* l
	********************/

	/* What do we do with this AI State? */
	if (st->HasSpells(me->GetGUIDLow()))
	{
		//TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "WE ARE INSIDE THE SPELLQUEUE BLOCK.");

		/* First, handle cooldowns. */
		if (globalCooldown >= diff)
		{
			TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "GCD! REMAINING: %u", globalCooldown);
			globalCooldown -= diff;
			for (CreatureSpellCooldowns::iterator itr = me->m_CreatureSpellCooldowns.begin(); itr != me->m_CreatureSpellCooldowns.end(); itr++)
			{
				if (itr->second >= diff)
					itr->second -= diff;
				else
					me->m_CreatureSpellCooldowns.erase(itr->first);
			}
			return;
		}
		else
		{
			globalCooldown = 0;
		}
		if (!UpdateSpells())
		{
			DoMeleeAttackIfReady();
			return;
		}

		SpellInfo const* sinfo = sSpellMgr->GetSpellInfo(43039);

		const SpellInfo* spellinfo = sSpellMgr->GetSpellInfo(_spellQueue.front()->GetSpellId());
		switch (int8 type = _spellQueue.front()->GetType())
		{
			case STORYSCRIPT_SPELL_MAINTAIN_ME:
				TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "CASTING MAINTAIN ON ME.");
				me->CastSpell(me->getVictim(), _spellQueue.front()->GetSpellId(), false);
				globalCooldown = 1500; // 1.5 seconds
				return;
			case STORYSCRIPT_SPELL_MAINTAIN_TARGET:
				TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "CASTING MAINTAIN ON TARGET.");
				if (!me->getVictim()->HasAura(_spellQueue.front()->GetSpellId()))
				{
					me->CastSpell(me->getVictim(), _spellQueue.front()->GetSpellId(), false);
					me->resetAttackTimer();
					globalCooldown = 1500;
					return;
				}
				return;
			case STORYSCRIPT_SPELL_PRIMARY:
				TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "CASTING PRIMARY.");
				DoCast(me->getVictim(), _spellQueue.front()->GetSpellId(), false);
				me->m_CreatureSpellCooldowns[_spellQueue.front()->GetSpellId()] = time(NULL) + spellinfo->GetRecoveryTime();
				me->resetAttackTimer();
				globalCooldown = 1500;
				return;
			case STORYSCRIPT_SPELL_SECONDARY:
				if (!me->HasSpellCooldown(_spellQueue.front()->GetSpellId()))
				{
					TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "CASTING SECONDARY.");
					me->CastSpell(me->getVictim(), _spellQueue.front()->GetSpellId(), false);
					me->resetAttackTimer();
					globalCooldown = 1500;
				}
				return;
			case STORYSCRIPT_SPELL_FILLER:
				/* Is it an actual spell? */
				if (_spellQueue.front()->GetSpellId() != -1)
				{
					SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(_spellQueue.front()->GetSpellId());

					//me->m_CombatDistance = 30.0f;
					//me->m_SightDistance = 30.0f;

					if (me->HasUnitState(UNIT_STATE_CASTING))
						return;

					if (me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SILENCED))
						return;

					if (me->HasCategoryCooldown(spellInfo->Id))
						return;

					if (me->IsWithinCombatRange(me->getVictim(), spellInfo->GetMaxRange()) && !me->HasSpellCooldown(spellInfo->Id))
					{
						TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "CASTING FILLER.");
						me->CastSpell(me->getVictim(), spellInfo->Id, false);
						//me->resetAttackTimer();
						return;
					}
				}
				return;
			case STORYSCRIPT_SPELL_AUTO:
				TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "CASTING AUTO.");
				if (!me->HasSpellCooldown(_spellQueue.front()->GetSpellId()))
				{
					me->CastSpell(me->getVictim(), _spellQueue.front()->GetSpellId(), false);
					me->resetAttackTimer();
				}
				globalCooldown = 1500;
				return;
			default:
				TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "WARNING! UNRECOGNIZED STORYSCRIPT SPELL TYPE! INVESTIGATE IMMEDIATELY!");
				return;
		}
	}
	else
	{
		DoMeleeAttackIfReady();
		//AttackStart(me->getVictim());
	}
}

void StoryAI::Reset()
{
	InitializeAI();
}

void StoryAI::AttackStart(Unit* victim)
{
	if (_spellQueue.empty() && init)
	{
		if (victim && me->Attack(victim, true))
			me->GetMotionMaster()->MoveChase(victim);
	}
	else
		AttackStartCaster(victim, 30.0f);
}

bool StoryAI::UpdateSpells()
{
	if (!init)
		init = true;
	if (!_spellQueue.empty())
	{
		_spellQueue.clear();
		if (!_spellQueue.empty())
			TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "VECTOR NOT EMPTY!!");
	}
	StoryScriptSpellList& SpellList = st->GetSpellListByGuid(me->GetGUIDLow());

	for (int i = 0; i != SpellList.size(); i++)
		Temporary(i, SpellList);

	if (_spellQueue.empty())
	{
		TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "SPELLQUEUE EMPTY. =/");
		return false;
	}

	return true;
}

void StoryAI::Temporary(uint32 range, StoryScriptSpellList& SpellList)
{
	for (StoryScriptSpellList::iterator itr = SpellList.begin(); itr != SpellList.end(); itr++)
	{
		const SpellInfo* spelldata = sSpellMgr->GetSpellInfo(itr->second->GetSpellId());
		if (!spelldata)
		{
			TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "SPELL INVALID! %u", itr->second->GetSpellId());
			continue;
		}

		if (itr->second->IsActive() && itr->second->GetType() == range)
		{
			if (range == STORYSCRIPT_SPELL_MAINTAIN_ME)
			{
				if (me->HasAura(itr->second->GetSpellId()) || !HasEnoughMana(spelldata) || globalCooldown > 0)
					continue;
				else
					TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "me");
			}

			if (range == STORYSCRIPT_SPELL_MAINTAIN_TARGET)
			{
				if (!me->getVictim() || me->getVictim()->HasAura(itr->second->GetSpellId()) || !HasEnoughMana(spelldata) || globalCooldown > 0)
					continue;
				TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "target");
			}
			if (range == STORYSCRIPT_SPELL_PRIMARY)
			{
				if (!HasEnoughMana(spelldata) || me->HasSpellCooldown(spelldata->Id) || globalCooldown > 0)
				{
					continue;
				}
				TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "primary");
			}

			if (range == STORYSCRIPT_SPELL_SECONDARY)
			{
				if (!HasEnoughMana(spelldata) || me->HasSpellCooldown(itr->second->GetSpellId()) || globalCooldown > 0)
					continue;
				TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "secondary");
			}
			if (range == STORYSCRIPT_SPELL_FILLER)
			{
				if (me->HasSpellCooldown(itr->second->GetSpellId()) || globalCooldown > 0 || !HasEnoughMana(spelldata))
				{
					continue;
				}
				
				TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "filler", itr->second->GetSpellId(), globalCooldown);
			}
			if (range == STORYSCRIPT_SPELL_AUTO)
			{
				/* No requirements. */
			}
			//_spellQueue.insert(std::pair<uint8, StoryScriptSpell*>(itr->second->GetType(), itr->second));
			//_spellQueue.insert(std::pair<uint8, StoryScriptSpell*>(itr->second->GetType(), itr->second));
			TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "%u INSERTED INTO SPELLQUEUE.", spelldata->Id);
			_spellQueue.insert(_spellQueue.end(), itr->second);
		}
	}
}

void StoryAI::SpellInterrupted(uint32 spellid, uint32 unTimeMs)
{
	TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "%u", unTimeMs);
	TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "%u", unTimeMs);
	TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "%u", unTimeMs);
	TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "%u", unTimeMs);
	TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "%u", unTimeMs);
	TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "%u", unTimeMs);
}

bool StoryAI::HasEnoughMana(SpellInfo const* spelldata)
{
	uint32 calc = ((float)spelldata->ManaCostPercentage / 100) * me->GetCreateMana();
	//TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "cost: %u", calc);
	TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "CURRENT MANA: %u", me->GetPower(POWER_MANA));
	TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "id: %u spell costs: %u, %u, %u", spelldata->Id, spelldata->ManaCost, (uint32)(((float)spelldata->ManaCostPercentage / 100) * me->GetCreateMana()), spelldata->ManaCostPerlevel*me->getLevel());
	if (spelldata->ManaCost > me->GetPower(POWER_MANA))
	{
		TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "FIRST");
		return false;
	}
	if ((uint32)(((float)spelldata->ManaCostPercentage / 100) * me->GetCreateMana()) > me->GetPower(POWER_MANA))
	{
		TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "SECOND");
		return false;
	}
	if (spelldata->ManaCostPerlevel*me->getLevel() > me->GetPower(POWER_MANA))
	{
		TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "THIRD");
		return false;
	}
	TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "Spell %u passed without incident.", spelldata->Id);
	return true;
}

/*bool DoSpellAttackIfReady(uint32 spell)
{

	if (me->HasUnitState(UNIT_STATE_CASTING) || !me->isAttackReady())
		return true;

	SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spell);
	
	if (me->IsWithinCombatRange(me->getVictim(), spellInfo->GetMaxRange(false)))
	{
		me->CastSpell(me->getVictim(), spell, false);
		me->resetAttackTimer();
		return true;
	}

	return false;
}*/

void StoryAI::EnterCombat(Unit* who)
{
	me->MonsterSay("Foo", LANG_UNIVERSAL, 0);
}
/*
void StoryAI::DoMeleeAttackIfReady()
{
	if (me->HasUnitState(UNIT_STATE_CASTING))
		return;

	Unit* victim = me->getVictim();
	//Make sure our attack is ready and we aren't currently casting before checking distance
	if (me->isAttackReady() && me->IsWithinMeleeRange(victim))
	{
		me->AttackerStateUpdate(victim);
		me->resetAttackTimer();
	}

	if (me->haveOffhandWeapon() && me->isAttackReady(OFF_ATTACK) && me->IsWithinMeleeRange(victim))
	{
		me->AttackerStateUpdate(victim, OFF_ATTACK);
		me->resetAttackTimer(OFF_ATTACK);
	}
}
*/
void StoryAI::InitializeAI()
{
	std::vector<StoryScriptSpell*> _spellQueue;
	me->m_CreatureSpellCooldowns.clear();
	me->m_CreatureCategoryCooldowns.clear();
	init = false;

	int storyid = sStoryScriptMgr->FindStoryByCreatureGuid(me->GetGUIDLow());

	if (storyid == 0)
	{
		TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "WARNING! CREATURE %u HAS FAILED STORYSCRIPT VALIDATION!", me->GetGUIDLow());
		disabledai = true;
	}
	else
	{
		st = sStoryScriptMgr->GetStoryScript(storyid);
		TC_LOG_ERROR(LOG_FILTER_GAMEEVENTS, "WARNING! CREATURE %u HAS PASSED STORYSCRIPT VALIDATION!", me->GetGUIDLow());
		disabledai = false;
	}

	running = false;
	processed = true;
}