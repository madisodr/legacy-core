/******************
 * Grimoire
 *
 * Author: Halcyon (Daniel Madison)
 * 
 * Desc - 
 */

#include "Language.h"
#include "legacy_defines.h" 
#include "ScriptMgr.h"
#include "ScriptPCH.h"
#include "Spell.h"

#define LEVEL_UP 47292
#define COIN 999116
#define UNCOMMON_REQUEST_COUNT 20

class Grimoire : public ItemScript
{
    public:
        Grimoire() : ItemScript("Grimoire"){}
        bool OnUse(Player* p, Item* item, SpellCastTargets const& /*targets*/) override
        {
            QueryResult result = WorldDatabase.PQuery("SELECT spell_id, cost FROM grimoire WHERE item='%u'", item->GetEntry());

            if(result)
            {
                Field* field = result->Fetch();
                uint32 spell = field[0].GetUInt32();
                uint32 cost = field[1].GetUInt32();

                SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spell);
                if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo, p))
                {
                    ChatHandler(p->GetSession()).PSendSysMessage(LANG_COMMAND_SPELL_BROKEN, spell);
                    ChatHandler(p->GetSession()).SetSentErrorMessage(true);
                    return false;
                }

                if(p->HasSpell(spell))
                {
                    ChatHandler(p->GetSession()).SendSysMessage(LANG_YOU_KNOWN_SPELL);
                    return false;
                }

                p->LearnSpell(spell, false);
                p->DestroyItemCount(item->GetEntry(), 1, true, true); 
            } 


            return true;
        } // bool OnUse
};


class item_requester : public CreatureScript
{
    public:
        item_requester() : CreatureScript("item_requester") {}

        bool OnGossipHello(Player* player, Creature* creature)
        {
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, "Requst an Item", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1, "", 0, true);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Nevermind.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            player->PlayerTalkClass->SendGossipMenu(284733, creature->GetGUID());

            return true;
        }

        bool OnGossipSelectCode(Player* player, Creature* /*creature*/, uint32 sender, uint32 action, const char* code)
        {
            player->PlayerTalkClass->ClearMenus();
            player->PlayerTalkClass->SendCloseGossip();

            if(action == GOSSIP_ACTION_INFO_DEF+2)
                return true;

            uint32 itemId = 0, cost = 0, iClass, quality;
            ChatHandler handler = ChatHandler(player->GetSession());

            if(atoi((char*) code) > 0)
                itemId = atoi((char*)code);

            if(itemId == COIN)
                return false;

            ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(itemId);
            if (!itemTemplate)
            {
                handler.PSendSysMessage("Invalid item entry");
                return false;
            }

            quality = itemTemplate->Quality;

            if(quality > ITEM_QUALITY_UNCOMMON)
            {
                ChatHandler(player->GetSession()).PSendSysMessage("You can't request items of this quality.");
                return false;
            }

            iClass = itemTemplate->Class;
            if(iClass == 2 || iClass == 4 || iClass == 6 || iClass == 15)
            {
                if(quality == ITEM_QUALITY_UNCOMMON)
                    cost = 30;

                if(GetItemRequests(player) > 0)
                    cost = 0;

                if(!player->HasItemCount(COIN, cost) && cost > 0)
                {
                    ChatHandler(player->GetSession()).PSendSysMessage("You don't have enough coins.");
                    return false;
                }

                if(CreateItem(player, itemId) == false)
                    return false;

                if(cost > 0)
                {
                    CharacterDatabase.PExecute("UPDATE character_requests SET amount = amount - 1 WHERE guid='%u'", player->GetGUIDLow());
                    player->DestroyItemCount(COIN, cost, true);
                }

                ChatHandler(player->GetSession()).PSendSysMessage("You have '%u' requests left on this character", GetItemRequests(player));
                return true;
            } else {
                ChatHandler(player->GetSession()).PSendSysMessage("You can't request this type of item.");
                return false;
            }
        }

        uint32 GetItemRequests(Player* player)
        {
            QueryResult result = CharacterDatabase.PQuery("SELECT amount FROM character_requests WHERE guid='%u'", player->GetGUIDLow());
            if(result)
            {
                Field* fields = result->Fetch();
                return fields[0].GetUInt32();
            } else
            {
                CharacterDatabase.PExecute("INSERT INTO character_requests (guid, amount) VALUES ('%u', '%u')", player->GetGUIDLow(), UNCOMMON_REQUEST_COUNT);
            }

            return 0;
        }

        bool CreateItem(Player* player, uint32 itemId)
        {
            ChatHandler handler = ChatHandler(player->GetSession());
            if(Item* item = Item::CreateItem(itemId, 1, player))
            {
                MailSender sender(MAIL_NORMAL, player->GetGUID().GetCounter(), MAIL_STATIONERY_GM);
                MailDraft draft("Item Request", "Your items, as requested.");

                SQLTransaction trans = CharacterDatabase.BeginTransaction();
                item->SaveToDB(trans);
                draft.AddItem(item);

                draft.SendMailTo(trans, MailReceiver(player, player->GetGUID().GetCounter()), sender);
                CharacterDatabase.CommitTransaction(trans);

                return true;
            }


            return false;
        }
};



void AddSC_grimoire()
{
    new Grimoire();
    new item_requester();
}
