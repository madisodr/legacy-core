//#include "ScriptMgr.h"
//#include "ScriptedGossip.h"
#include "ScriptPCH.h"
#include "Log.h"/*
#include "Player.h"
#include "Item.h"
#include <cstring>*/

/***********************************
* Galenus - Legacy Death System
**/

#define GOSSIP_ITEM_1   "|cff00ff00|TInterface\\icons\\Ability_Hunter_Assassinate:60|t|r Execute"
#define GOSSIP_ITEM_2   "|cff00ff00|TInterface\\icons\\Spell_Holy_PainSupression:60|t|r Injure"
#define GOSSIP_ITEM_3   "|cff00ff00|TInterface\\icons\\Ability_Rogue_Sprint:60|t|r Set Free"
#define GOSSIP_ITEM_4   "|cff00ff00|TInterface\\icons\\Achievement_BG_Xkills_AVgraveyard:60|t|r Revive"
#define INJURE_ITEM_1   "|cff00ff00|TInterface\\icons\\Ability_Warrior_Disarm:60|t|r Break arm"
#define INJURE_ITEM_2   "|cff00ff00|TInterface\\icons\\Spell_Nature_Slow:60|t|r Break leg"
#define INJURE_ITEM_3   "|cff00ff00|TInterface\\icons\\Spell_Frost_Stun:60|t|r Knock out"
#define INJURE_ITEM_4   "|cff00ff00|TInterface\\icons\\Ability_Warrior_Trauma:60|t|r Beat up"
#define RETURN          "|cff00ff00|TInterface\\icons\\Trade_Engineering:60|t|r Main Menu"
#define EXIT            "|cff00ff00|TInterface\\icons\\Trade_Engineering:60|t|r Exit"
#define DIED_TEXT       "Don't worry. Our death zone is.. inconclusive. If you release, you will be resurrected where you are."
#define EXECUTED_TEXT   "On release spirit, your corpse will be left at its location, and you will be teleported to the Purgatory."

class galenus : public ItemScript
{
public:
	galenus() : ItemScript("galenus"){ }

	bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/) override
	{

        if(player->IsInCombat())
        {
            ChatHandler(player->GetSession()).PSendSysMessage("You can't use this item right now.");
            return false;
        }

		player->PlayerTalkClass->ClearMenus();
		player->ADD_GOSSIP_ITEM(10, GOSSIP_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1); //Execute
		player->ADD_GOSSIP_ITEM(10, GOSSIP_ITEM_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2); //Injure
		player->ADD_GOSSIP_ITEM(10, GOSSIP_ITEM_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3); //Release
		   player->ADD_GOSSIP_ITEM(10, EXIT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);

		player->PlayerTalkClass->SendGossipMenu(724008, item->GetGUID());

		return true;
	}

	bool OnGossipSelect(Player* player, Item* item, uint32 /*sender*/, uint32 action) override
	{
		player->PlayerTalkClass->ClearMenus();

		switch (action)
		{
		case GOSSIP_ACTION_INFO_DEF + 1: // Execute Player - Version 1
			HandleExecute(player);
			player->PlayerTalkClass->SendCloseGossip();
			break;
		case GOSSIP_ACTION_INFO_DEF + 2: // Injure Menu
			player->ADD_GOSSIP_ITEM(10, "Back", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
			player->ADD_GOSSIP_ITEM(10, INJURE_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6); //Break Arm
			player->ADD_GOSSIP_ITEM(10, INJURE_ITEM_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7); //Break Leg
			player->ADD_GOSSIP_ITEM(10, INJURE_ITEM_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8); //Mind-Numbing
			player->ADD_GOSSIP_ITEM(10, INJURE_ITEM_4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9); //Restrict Gear
			//   player->ADD_GOSSIP_ITEM(10, RETURN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+10);
			player->PlayerTalkClass->SendGossipMenu(724009, item->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 3: // Set a player free
			HandleRelease(player);
			player->PlayerTalkClass->SendCloseGossip();
			break;
        case GOSSIP_ACTION_INFO_DEF + 5: // Exit
            player->PlayerTalkClass->SendCloseGossip();
            break;
		case GOSSIP_ACTION_INFO_DEF + 6: // Break arm
			HandleBreakArm(player);
			player->PlayerTalkClass->SendCloseGossip();
			break;
		case GOSSIP_ACTION_INFO_DEF + 7: // Break leg
			HandleBreakLeg(player);
			player->PlayerTalkClass->SendCloseGossip();
			break;
		case GOSSIP_ACTION_INFO_DEF + 8: // Knock out
			HandleKnockOut(player);
			player->PlayerTalkClass->SendCloseGossip();
			break;
		case GOSSIP_ACTION_INFO_DEF + 9: // Beat up
			HandleBeatUp(player);
			player->PlayerTalkClass->SendCloseGossip();
			break;
		case GOSSIP_ACTION_INFO_DEF + 10:
			player->PlayerTalkClass->ClearMenus();
			//     player->ADD_GOSSIP_ITEM(10, "Welcome to the death menu. Choose your actions carefully, for they do concern life and death.", GOSSIP_SENDER_MAIN, 0);
			player->ADD_GOSSIP_ITEM(10, GOSSIP_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1); //Execute
			player->ADD_GOSSIP_ITEM(10, GOSSIP_ITEM_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2); //Injure
			player->ADD_GOSSIP_ITEM(10, GOSSIP_ITEM_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3); //Release
			player->ADD_GOSSIP_ITEM(10, EXIT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);

			player->PlayerTalkClass->SendGossipMenu(724008, item->GetGUID());
			break;
		}

		return true;
	}

	bool HandleExecute(Player* p)
	{
		Player* victim = p->GetSelectedPlayer();

		if (!victim) {
			ChatHandler(p->GetSession()).SendSysMessage("You don't have a player selected.");
			return true;
		}

		if (p == victim) {
			ChatHandler(p->GetSession()).SendSysMessage("O, that this too too solid flesh would melt, thaw, and resolve itself into a dew, or that the Everlasting had not fixed his canon 'gainst self-slaughter.");
			return true;
		}
		if (victim->HasAura(STUN) && !p->HasAura(24647)) {
			ChatHandler(p->GetSession()).PSendSysMessage("You have executed '%s'.", victim->GetName().c_str());
			ChatHandler(victim->GetSession()).PSendSysMessage("You have been executed by '%s'.", p->GetName().c_str());
			ChatHandler(victim->GetSession()).SendSysMessage(EXECUTED_TEXT);
			victim->SetExecuted(true);
			victim->Kill(victim, false);
			CharacterDatabase.PExecute("INSERT INTO character_deaths (guid, `by`) VALUES (%u, '%s')", victim->GetGUIDLow(), p->GetName().c_str());
		}
		else {
			ChatHandler(p->GetSession()).PSendSysMessage("You cannot kill a player unless they are stunned.");
			return false;
		}

		return true;
	}

	void HandleBreakArm(Player* p){
		Player* victim = p->GetSelectedPlayer();

		if (!victim || p == victim)
		{
			ChatHandler(p->GetSession()).PSendSysMessage("You don't have a player selected.");
			return;
		}

		if (victim->HasAura(STUN) && !p->HasAura(STUN))
		{
			victim->RemoveAura(STUN);
			if (!victim->HasAura(BROKEN_ARM))
				victim->AddAura(BROKEN_ARM, victim);
			if (victim->HasAura(BROKEN_LEG))
				victim->RemoveAura(BROKEN_LEG);
			if (Aura* sick = victim->GetAura(BROKEN_ARM, victim->GetGUID()))
				sick->SetDuration((6 * HOUR)*IN_MILLISECONDS);

			ChatHandler(victim->GetSession()).PSendSysMessage("You have had your arm broken by '%s'.", p->GetName().c_str());
			ChatHandler(p->GetSession()).PSendSysMessage("You have broken '%s''s arm!", victim->GetName().c_str());
		}
	}

	void HandleBreakLeg(Player* p){
		Player* victim = p->GetSelectedPlayer();

		if (!victim || p == victim)
		{
			ChatHandler(p->GetSession()).PSendSysMessage("You don't have a player selected.");
			return;
		}

		if (victim->HasAura(STUN) && !p->HasAura(STUN))
		{
			victim->RemoveAura(STUN);
			// victim->CastSpell(victim, BROKEN_LEG, true); // Rez sickness - PLACE HOLDER
			if (!victim->HasAura(BROKEN_LEG))
				victim->AddAura(BROKEN_LEG, victim);
			if (victim->HasAura(BROKEN_ARM))
				victim->RemoveAura(BROKEN_ARM);
			if (Aura* sick = victim->GetAura(BROKEN_LEG, victim->GetGUID()))
				sick->SetDuration((6 * HOUR)*IN_MILLISECONDS);

			ChatHandler(victim->GetSession()).PSendSysMessage("You have had your leg broken by '%s'.", p->GetName().c_str());
			ChatHandler(p->GetSession()).PSendSysMessage("You have broken '%s''s leg!", victim->GetName().c_str());

		}
	}

	void HandleKnockOut(Player* p){
		ChatHandler(p->GetSession()).SendSysMessage("Sorry, this ability is disabled due to a bug.");
		return;
		Player* victim = p->GetSelectedPlayer();

		if (!victim || p == victim)
		{
			ChatHandler(p->GetSession()).PSendSysMessage("You don't have a player selected.");
			return;
		}

		if (victim->HasAura(STUN) && !p->HasAura(STUN))
		{
			victim->RemoveAura(STUN);
			victim->AddAura(CONCUSSION, victim);
			if (Aura* sick = victim->GetAura(CONCUSSION, victim->GetGUID()))
				sick->SetDuration((6 * HOUR)*IN_MILLISECONDS);


			ChatHandler(victim->GetSession()).PSendSysMessage("You have been knocked the fuck out by '%s'.", p->GetName().c_str());
			ChatHandler(p->GetSession()).PSendSysMessage("You knocked the fuck out of '%s'!", victim->GetName().c_str());
		}
	}

	void HandleBeatUp(Player* p){
		ChatHandler(p->GetSession()).SendSysMessage("Sorry, this ability is disabled due to a bug.");
		return;
		Player* victim = p->GetSelectedPlayer();

		if (!victim || p == victim)
		{
			ChatHandler(p->GetSession()).PSendSysMessage("You don't have a player selected.");
			return;
		}

		if (victim->HasAura(STUN) && !p->HasAura(24647))
		{
			victim->RemoveAura(STUN);
			victim->AddAura(BLOODSTAIN, victim);
			if (Aura* sick = victim->GetAura(CONCUSSION, victim->GetGUID()))
				sick->SetDuration((6 * HOUR)*IN_MILLISECONDS);

			ChatHandler(victim->GetSession()).PSendSysMessage("You got yo ass whooped by '%s'.", p->GetName().c_str());
			ChatHandler(p->GetSession()).PSendSysMessage("You whooped '%s''s ass", victim->GetName().c_str());

		}
	}

	void HandleRelease(Player* p)
	{
		Player* victim = p->GetSelectedPlayer();

    	if (!victim)
		{
			ChatHandler(p->GetSession()).PSendSysMessage("You don't have a player selected.");
			return;
		}

		if (p == victim)
		{
			ChatHandler(p->GetSession()).PSendSysMessage("You can not release yourself.");
			return;
		}

		if (victim->HasAura(STUN) && !p->HasAura(24647))
		{
			victim->RemoveAura(STUN);
			ChatHandler(p->GetSession()).PSendSysMessage("You've set %s free.", victim->GetName().c_str());
			ChatHandler(victim->GetSession()).PSendSysMessage("You've been set free by %s.", p->GetName().c_str());
		}
	}

};

void AddSC_galenus()
{
	new galenus();
}
