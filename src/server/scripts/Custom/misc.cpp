#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "GameObject.h"

#define SilverCoin 999116

class misc_legacy : public PlayerScript
{
    public:
        misc_legacy() : PlayerScript("misc_legacy"){}

        void SetGMSettings(Player* player)
        {
            if (CharacterDatabase.PQuery("SELECT guid FROM character_flying WHERE guid=%u", uint64(player->GetGUID())))
            {
                WorldPacket data(12);
                data.SetOpcode(SMSG_MOVE_SET_CAN_FLY);
                data << player->GetPackGUID();
                data << uint32(0);                                      // unknown
                player->SendMessageToSet(&data, true);
            }

            if (QueryResult display = CharacterDatabase.PQuery("SELECT morph FROM character_morph WHERE guid=%u", uint64(player->GetGUID())))
            {
                player->SetDisplayId(display->Fetch()[0].GetUInt32());
            }

            if (QueryResult Scale = CharacterDatabase.PQuery("SELECT scale FROM character_scale WHERE guid=%u", uint64(player->GetGUID())))
            {
                player->SetObjectScale(Scale->Fetch()[0].GetFloat());
            }

            if (QueryResult qrspeed = CharacterDatabase.PQuery("SELECT speed FROM character_speed WHERE guid=%u", uint64(player->GetGUID())))
            {
                float speed = qrspeed->Fetch()[0].GetFloat();
                player->SetSpeed(MOVE_WALK, speed, true);
                player->SetSpeed(MOVE_RUN, speed, true);
                player->SetSpeed(MOVE_SWIM, speed, true);
                player->SetSpeed(MOVE_FLIGHT, speed, true);
            }
        }

        void LearnLanguages(Player* player)
        {
            if (player->GetSkillValue(98) == 0)
                player->SetSkill(98, 1, 300, 300);

            if (!player->HasSpell(668))
                player->LearnSpell(668, false);
            if (player->GetSkillValue(109) == 0)
                player->SetSkill(109, 1, 300, 300);

            if (!player->HasSpell(669))
                player->LearnSpell(669, false);
        }

        void DetermineAndOrSendBladefist(Player* player)
        {
            QueryResult result = CharacterDatabase.PQuery("SELECT race, playerBytes FROM characters WHERE guid=%u", player->GetGUIDLow());
            if (!result)
                return;

            if (CharacterDatabase.PQuery("SELECT guid FROM character_bladefist WHERE guid=%u", player->GetGUIDLow()))
                return;

            Field* fields = result->Fetch();
            uint32 race = fields[0].GetUInt16();
            uint8 skin = fields[1].GetUInt8();

            if (race == 2 && skin == 2)
            {
                // from console show not existed sender
                MailSender sender(MAIL_NORMAL, 0, MAIL_STATIONERY_GM);

                // fill mail
                MailDraft draft("The Bladefist", "All members of the Shattered Hand clan own a Bladefist. You have been granted a generic Bladefist that you may replace at any point.\n\nIn conjunction,"
                        " you are being granted the D.E.H.T.A Trap Smasher that is by default available from Jepetto. Using this will make your weapon - the Bladefist - *always* appear.\n\n");

                SQLTransaction trans = CharacterDatabase.BeginTransaction();

                if (Item* item = Item::CreateItem(999119, 1, player))
                {
                    item->SetFlag(ITEM_FIELD_FLAGS, ITEM_FLAG_SOULBOUND);
                    item->SaveToDB(trans);                               // save for prevent lost at next mail load, if send fail then item will deleted
                    draft.AddItem(item);
                }
                if (Item* item = Item::CreateItem(999118, 1, player))
                {
                    item->SetFlag(ITEM_FIELD_FLAGS, ITEM_FLAG_SOULBOUND);
                    item->SaveToDB(trans);                               // save for prevent lost at next mail load, if send fail then item will deleted
                    draft.AddItem(item);
                }
                if (Item* item = Item::CreateItem(999117, 1, player))
                {
                    item->SetFlag(ITEM_FIELD_FLAGS, ITEM_FLAG_SOULBOUND);
                    item->SaveToDB(trans);                               // save for prevent lost at next mail load, if send fail then item will deleted
                    draft.AddItem(item);
                }
                if (Item* item = Item::CreateItem(35228, 1, player))
                {
                    item->SetFlag(ITEM_FIELD_FLAGS, ITEM_FLAG_SOULBOUND);
                    item->SaveToDB(trans);                               // save for prevent lost at next mail load, if send fail then item will deleted
                    draft.AddItem(item);
                }

                draft.SendMailTo(trans, MailReceiver(player, player->GetGUID().GetCounter()), sender);
                CharacterDatabase.CommitTransaction(trans);

                CharacterDatabase.PQuery("INSERT INTO character_bladefist VALUES (%u)", player->GetGUIDLow());
            }

        }

        void SendStarterItems(Player* player)
        {
            if (CharacterDatabase.PQuery("SELECT guid FROM character_starter WHERE guid=%u", player->GetGUIDLow()))
                return;

            uint8 race = player->getRace();

            MailSender sender(MAIL_NORMAL, 0, MAIL_STATIONERY_GM);

            MailDraft draft("Starter Items", "The Legacy Starter Packs and item tokens have been distributed to all players. You can redeem the token at any Jepetto NPC.");

            SQLTransaction trans = CharacterDatabase.BeginTransaction();

            if (Item* item = Item::CreateItem(32897, 1, player))
            {
                item->SetFlag(ITEM_FIELD_FLAGS, ITEM_FLAG_SOULBOUND);
                item->SaveToDB(trans);                               // save for prevent lost at next mail load, if send fail then item will deleted
                draft.AddItem(item);
            }

            switch (race)
            {
                case 1:
                    if (Item* item = Item::CreateItem(999120, 1, player))
                    {
                        item->SetFlag(ITEM_FIELD_FLAGS, ITEM_FLAG_SOULBOUND);
                        item->SaveToDB(trans);                               // save for prevent lost at next mail load, if send fail then item will deleted
                        draft.AddItem(item);
                    }
                    break;
                case 2:
                    if (Item* item = Item::CreateItem(999126, 1, player))
                    {
                        item->SetFlag(ITEM_FIELD_FLAGS, ITEM_FLAG_SOULBOUND);
                        item->SaveToDB(trans);                               // save for prevent lost at next mail load, if send fail then item will deleted
                        draft.AddItem(item);
                    }
                    break;
                case 3:
                    if (Item* item = Item::CreateItem(999122, 1, player))
                    {
                        item->SetFlag(ITEM_FIELD_FLAGS, ITEM_FLAG_SOULBOUND);
                        item->SaveToDB(trans);                               // save for prevent lost at next mail load, if send fail then item will deleted
                        draft.AddItem(item);
                    }
                    break;
                case 4:
                    if (Item* item = Item::CreateItem(999121, 1, player))
                    {
                        item->SetFlag(ITEM_FIELD_FLAGS, ITEM_FLAG_SOULBOUND);
                        item->SaveToDB(trans);                               // save for prevent lost at next mail load, if send fail then item will deleted
                        draft.AddItem(item);
                    }
                    break;
                case 5:
                    if (Item* item = Item::CreateItem(999132, 1, player))
                    {
                        item->SetFlag(ITEM_FIELD_FLAGS, ITEM_FLAG_SOULBOUND);
                        item->SaveToDB(trans);                               // save for prevent lost at next mail load, if send fail then item will deleted
                        draft.AddItem(item);
                    }
                    break;
                case 6:
                    if (Item* item = Item::CreateItem(999128, 1, player))
                    {
                        item->SetFlag(ITEM_FIELD_FLAGS, ITEM_FLAG_SOULBOUND);
                        item->SaveToDB(trans);                               // save for prevent lost at next mail load, if send fail then item will deleted
                        draft.AddItem(item);
                    }
                    break;
                case 7:
                    if (Item* item = Item::CreateItem(999123, 1, player))
                    {
                        item->SetFlag(ITEM_FIELD_FLAGS, ITEM_FLAG_SOULBOUND);
                        item->SaveToDB(trans);                               // save for prevent lost at next mail load, if send fail then item will deleted
                        draft.AddItem(item);
                    }
                    break;
                case 8:
                    if (Item* item = Item::CreateItem(999130, 1, player))
                    {
                        item->SetFlag(ITEM_FIELD_FLAGS, ITEM_FLAG_SOULBOUND);
                        item->SaveToDB(trans);                               // save for prevent lost at next mail load, if send fail then item will deleted
                        draft.AddItem(item);
                    }
                    break;
                case 9:
                    if (Item* item = Item::CreateItem(999134, 1, player))
                    {
                        item->SetFlag(ITEM_FIELD_FLAGS, ITEM_FLAG_SOULBOUND);
                        item->SaveToDB(trans);                               // save for prevent lost at next mail load, if send fail then item will deleted
                        draft.AddItem(item);
                    }
                    break;
                case 10:
                    if (Item* item = Item::CreateItem(999131, 1, player))
                    {
                        item->SetFlag(ITEM_FIELD_FLAGS, ITEM_FLAG_SOULBOUND);
                        item->SaveToDB(trans);                               // save for prevent lost at next mail load, if send fail then item will deleted
                        draft.AddItem(item);
                    }
                    break;
                case 11:
                    if (Item* item = Item::CreateItem(999124, 1, player))
                    {
                        item->SetFlag(ITEM_FIELD_FLAGS, ITEM_FLAG_SOULBOUND);
                        item->SaveToDB(trans);                               // save for prevent lost at next mail load, if send fail then item will deleted
                        draft.AddItem(item);
                    }
                    break;
                case 18:
                    if (Item* item = Item::CreateItem(999133, 1, player))
                    {
                        item->SetFlag(ITEM_FIELD_FLAGS, ITEM_FLAG_SOULBOUND);
                        item->SaveToDB(trans);                               // save for prevent lost at next mail load, if send fail then item will deleted
                        draft.AddItem(item);
                    }
                    break;
                case 20:
                    if (Item* item = Item::CreateItem(999125, 1, player))
                    {
                        item->SetFlag(ITEM_FIELD_FLAGS, ITEM_FLAG_SOULBOUND);
                        item->SaveToDB(trans);                               // save for prevent lost at next mail load, if send fail then item will deleted
                        draft.AddItem(item);
                    }
                    break;
            }

            draft.SendMailTo(trans, MailReceiver(player, player->GetGUID().GetCounter()), sender);
            CharacterDatabase.CommitTransaction(trans);

            CharacterDatabase.PQuery("INSERT INTO character_starter VALUES (%u)", player->GetGUIDLow());
        }

        void DraeneiHack(Player* player)
        {
            if (player->getRace() == 11)
            {
                /* Shadow Resistance */
                if (player->HasSpell(59541))
                    player->RemoveSpell(59541);
                if (player->HasSpell(59540))
                    player->RemoveSpell(59540);
                if (player->HasSpell(59539))
                    player->RemoveSpell(59539);
                if (player->HasSpell(59538))
                    player->RemoveSpell(59538);
                if (player->HasSpell(59536))
                    player->RemoveSpell(59536);
                if (player->HasSpell(59535))
                    player->RemoveSpell(59535);

                /* Gift of the Naaru */
                if (player->HasSpell(59548))
                    player->RemoveSpell(59548);
                if (player->HasSpell(59547))
                    player->RemoveSpell(59547);
                if (player->HasSpell(59545))
                    player->RemoveSpell(59545);
                if (player->HasSpell(59544))
                    player->RemoveSpell(59544);
                if (player->HasSpell(59543))
                    player->RemoveSpell(59543);
                if (player->HasSpell(28880))
                    player->RemoveSpell(28880);

                /* Heroic Presence */
                if (player->HasSpell(28878))
                    player->RemoveSpell(28878);
            }

            if (player->getRace() == 10)
            {
                if (player->getClass() == CLASS_ROGUE)
                    player->RemoveSpell(28730);
                else
                    player->RemoveSpell(25046);
            }
        }

        void LearnSkills(Player* player)
        {
            QueryResult skills = CharacterDatabase.PQuery("SELECT * FROM character_upt_skills WHERE guid = %u", player->GetGUIDLow());
            if (!skills)
                return;

            do
            {
                Field* fields = skills->Fetch();
                uint32 skill = fields[1].GetUInt32();
                uint32 minval = fields[2].GetUInt32();
                uint32 maxval = fields[3].GetUInt32();
                player->SetSkill(skill, player->HasSkill(skill) ? player->GetSkillStep(skill) : 1, minval, maxval);
            } while (skills->NextRow());
        }

        void Abbendum(Player* player, bool firstlogin)
        {
            if (CharacterDatabase.PQuery("SELECT * FROM abbendum where guid = %u", player->GetGUIDLow()))
                return;

            if (player->GetTotalPlayedTime() < 3600)
                return;

            if (firstlogin)
            {
                CharacterDatabase.PExecute("INSERT INTO abbendum VALUES (%u)", player->GetGUIDLow());
                return;
            }

            // from console show not existed sender
            MailSender sender(MAIL_NORMAL, 0, MAIL_STATIONERY_GM);

            // fill mail
            MailDraft draft("Silver Coins", "You are being retroactively awarded for your played time. For every hour you play, you are awarded 10 coins.");

            SQLTransaction trans = CharacterDatabase.BeginTransaction();

            if (floor(player->GetTotalPlayedTime() / 3600) * 10 > 200)
            {
                double stackcount = ceil((floor(player->GetTotalPlayedTime() / 3600) * 10 ) / 200);
                int remaining = floor(player->GetTotalPlayedTime() / 3600) * 10;
                for (int i = 0; i < stackcount; i++)
                {
                    if (remaining > 200)
                    {
                        Item* item = Item::CreateItem(SilverCoin, 200, player);
                        item->SetFlag(ITEM_FIELD_FLAGS, ITEM_FLAG_SOULBOUND);
                        item->SaveToDB(trans);                               // save for prevent lost at next mail load, if send fail then item will deleted
                        draft.AddItem(item);

                        remaining -= 200;
                    }
                    else
                    {
                        Item* item = Item::CreateItem(SilverCoin, remaining, player);
                        item->SetFlag(ITEM_FIELD_FLAGS, ITEM_FLAG_SOULBOUND);
                        item->SaveToDB(trans);                               // save for prevent lost at next mail load, if send fail then item will deleted
                        draft.AddItem(item);
                    }
                }

            }
            else
            {
                Item* item = Item::CreateItem(SilverCoin, floor(player->GetTotalPlayedTime() / 3600) * 10, player);
                item->SetFlag(ITEM_FIELD_FLAGS, ITEM_FLAG_SOULBOUND);
                item->SaveToDB(trans);                               // save for prevent lost at next mail load, if send fail then item will deleted
                draft.AddItem(item);
            }

            draft.SendMailTo(trans, MailReceiver(player, player->GetGUID().GetCounter()), sender);
            CharacterDatabase.CommitTransaction(trans);

            player->SetNextCoinTime(floor(player->GetTotalPlayedTime() / 3600) * 3600);

            CharacterDatabase.PExecute("INSERT INTO abbendum VALUES (%u)", player->GetGUIDLow());


        }

        void SendUPT(Player* player)
        {
            if (CharacterDatabase.PQuery("SELECT * FROM has_upt WHERE guid = %u", player->GetGUIDLow()))
                return;

            MailSender sender(MAIL_NORMAL, 0, MAIL_STATIONERY_GM);

            // fill mail
            MailDraft draft("Universal Progression Tool", "Use this tool to learn new animations.");

            SQLTransaction trans = CharacterDatabase.BeginTransaction();

            Item* item = Item::CreateItem(999150, 1, player);
            item->SetFlag(ITEM_FIELD_FLAGS, ITEM_FLAG_SOULBOUND);
            item->SaveToDB(trans);                               // save for prevent lost at next mail load, if send fail then item will deleted
            draft.AddItem(item);

            draft.SendMailTo(trans, MailReceiver(player, player->GetGUID().GetCounter()), sender);
            CharacterDatabase.CommitTransaction(trans);

            CharacterDatabase.PExecute("INSERT INTO has_upt VALUES (%u)", player->GetGUIDLow());
        }

        void LearnReputations(Player* player)
        {
            uint8 race = player->getRace();
            if (race == 1 || race == 3 || race == 4 || race == 7 || race == 11 || race == 20)
            {

                player->SetReputation(930, 999999); // Exodar
                player->SetReputation(49, 999999); // Night Watch
                player->SetReputation(72, 999999); // Stormwind
                player->SetReputation(69, 999999); // Darnassus
                player->SetReputation(47, 999999); // Ironforge
                player->SetReputation(54, 999999); // Gnomeregan Exiles

                player->SetReputation(76, -999999); // Orgrimmar
                player->SetReputation(81, -999999); // Thunder Bluff
                player->SetReputation(68, -999999); // Undercity
                player->SetReputation(911, -999999); // Silvermoon City
                player->SetReputation(530, -999999); // Darkspear Trolls

            }
            else if (race == 2 || race == 5 || race == 6 || race == 8 || race == 10 || race == 18)
            {
                player->SetReputation(930, -999999); // Exodar
                player->SetReputation(49, -999999); // Night Watch
                player->SetReputation(72, -999999); // Stormwind
                player->SetReputation(69, -999999); // Darnassus
                player->SetReputation(47, -999999); // Ironforge
                player->SetReputation(54, -999999); // Gnomeregan Exiles

                player->SetReputation(76, 999999); // Orgrimmar
                player->SetReputation(81, 999999); // Thunder Bluff
                player->SetReputation(68, 999999); // Undercity
                player->SetReputation(911, 999999); // Silvermoon City
                player->SetReputation(530, 999999); // Darkspear Trolls
            }
            else if (race == 9)
            {
                player->SetReputation(930, 999999); // Exodar
                player->SetReputation(49, 999999); // Night Watch
                player->SetReputation(72, 999999); // Stormwind
                player->SetReputation(69, 999999); // Darnassus
                player->SetReputation(47, 999999); // Ironforge
                player->SetReputation(54, 999999); // Gnomeregan Exiles
                player->SetReputation(76, 999999); // Orgrimmar
                player->SetReputation(81, 999999); // Thunder Bluff
                player->SetReputation(68, 999999); // Undercity
                player->SetReputation(911, 999999); // Silvermoon City
                player->SetReputation(530, 999999); // Darkspear Trolls
            }
        }

        /* hack city */
        void OnLogin(Player* player, bool firstlogin) override
        {
            SetGMSettings(player);
            LearnLanguages(player);
            //  LearnReputations(player);
            DetermineAndOrSendBladefist(player);
            SendStarterItems(player);
            SendUPT(player);
            if (player->getRace() == 11)
                DraeneiHack(player);
            Abbendum(player, firstlogin);

            player->ModifyMoney(999999999);

            if (player->GetMapId() == 725)
                player->RemoveByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_FFA_PVP);
            if (QueryResult Result = CharacterDatabase.PQuery("SELECT guid FROM character_deaths WHERE guid = %u", player->GetGUIDLow()))
            {
                player->SetExecuted(true);
                if (player->GetMapId() != 573)
                {
                    player->TeleportTo(573, 174.517395, -260.539032, 1.027144, 0.338673);
                    player->Whisper("Oops, where'd you go? Get back here...", LANG_COMMON, player, true);
                }
            }


        }

        /* hack city */
        void OnMapChanged(Player* player) override
        {
            if (player->GetMapId() == 725)
                player->RemoveByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_FFA_PVP);
            SetGMSettings(player);
            LearnLanguages(player);
            LearnSkills(player);
            if (player->getRace() == 11)
                DraeneiHack(player);
        }
};

class npc_armor_trainer : public CreatureScript
{
    public:
        npc_armor_trainer() : CreatureScript("npc_armor_trainer") {}

        bool OnGossipHello(Player* player, Creature* creature)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Learn Leather", GOSSIP_SENDER_MAIN, 5);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Learn Mail", GOSSIP_SENDER_MAIN, 10);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Learn Plate", GOSSIP_SENDER_MAIN, 15);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Learn All", GOSSIP_SENDER_MAIN, 20);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Exit", GOSSIP_SENDER_MAIN, 25);
            player->PlayerTalkClass->SendGossipMenu(724007, creature->GetGUID());

            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 actions)
        {
            player->PlayerTalkClass->ClearMenus();

            switch (actions)
            {
                case 5:
                    player->SetSkill(414, 1, 1, 1);
                    player->LearnSpell(9077, false);
                    break;
                case 10:
                    player->SetSkill(413, 1, 1, 1);
                    player->LearnSpell(8737, false);
                    break;
                case 15:
                    player->SetSkill(293, 1, 1, 1);
                    player->LearnSpell(750, false);
                    break;
                case 20:
                    player->SetSkill(414, 1, 1, 1);
                    player->LearnSpell(9077, false);
                    player->SetSkill(413, 1, 1, 1);
                    player->LearnSpell(8737, false);
                    player->SetSkill(293, 1, 1, 1);
                    player->LearnSpell(750, false);

                    break;
                case 25:
                    player->PlayerTalkClass->SendCloseGossip();
                    return true;
                    break;
            }

            player->PlayerTalkClass->SendCloseGossip();
            return true;
        }
};

class npc_scale : public CreatureScript
{
    public:
        npc_scale() : CreatureScript("npc_scale") {}

        bool OnGossipHello(Player* player, Creature* creature)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Scale - Tiny", GOSSIP_SENDER_MAIN, 5);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Scale - Small", GOSSIP_SENDER_MAIN, 10);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Scale - Reset", GOSSIP_SENDER_MAIN, 15);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Scale - Large", GOSSIP_SENDER_MAIN, 20);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Scale - Huge", GOSSIP_SENDER_MAIN, 25);
            player->PlayerTalkClass->SendGossipMenu(724007, creature->GetGUID());

            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 actions)
        {
            player->PlayerTalkClass->ClearMenus();

            float scale = 1;

            switch (actions)
            {
                case 5:
                    scale = 0.93;
                    break;
                case 10:
                    scale = 0.97;
                    break;
                case 15:
                    scale = 1;
                    break;
                case 20:
                    scale = 1.03;
                    break;
                case 25:
                    scale = 1.07;
                    break;
            }

            player->SetObjectScale(scale);
            CharacterDatabase.PExecute("INSERT INTO character_scale VALUES ('%u', '%f') ON DUPLICATE KEY UPDATE scale='%f'", player->GetGUIDLow(), scale, scale);
            player->PlayerTalkClass->SendCloseGossip();

            return true;
        }
};


class npc_spark_teleporter : public CreatureScript
{
    private:
        enum Grouping
        {
            /* Back */
            ON_GOSSIP_HELLO,

            /* Groups */
            Alliance,
            Horde,
            Neutral,

            /* Subgroups */
            A_Stormwind,
            A_Darnassus,
            A_Exodar,
            A_Ironforge,
            A_The_Hinterlands,
            A_Hillsbrad_Foothills,
            A_Alterac_Mountains,
            A_Tirisfal_Glades,
            A_Silverpine_Forest,
            A_Arathi_Highlands,
            A_Wetlands,
            A_Loch_Modan,
            A_Dun_Morogh,


            H_Orgrimmar,
            H_ThunderBluff,
            H_Undercity,
            H_Silvermoon,
            H_Eversong_Woods,
            H_Ghostlands,
            H_The_Hinterlands,
            H_Alterac_Mountains,
            H_Hillsbrad_Foothills,
            H_Tirisfal_Glades,
            H_Silverpine_Forest,
            H_Arathi_Highlands,


            N_Eastern_Plaguelands,
            N_Western_Plaguelands,
            N_Alterac_Mountains,
            N_The_Hinterlands,
            N_Searing_Gorge,

            N_CrystalsongForest,
            N_ZulDrak,
            N_StormPeaks,
            N_SholazarBasin,

            /* Locations */
            A_Stormwind_Trade,
            A_Stormwind_Entrance,
            A_Stormwind_Oldtown,

            A_Darnassus_Entrance,
            A_Darnassus_Cenarion,
            A_Darnassus_Temple,

            A_Exodar_Inn,
            A_Exodar_Entrance,
            A_Exodar_tmp,

            A_Theramore,
            A_Astranaar,
            A_Menethil_Harbor,

            H_Orgrimmar_Inn,
            H_Orgrimmar_Entrance,
            H_Orgrimmar_Honor,

            H_ThunderBluff_Entrance,
            H_ThunderBluff_Cairne,
            H_ThunderBluff_Spirit,

            H_Fairbreeze_Village,
            H_Sunstrider_Isle,
            H_Silvermoon_Entrance,
            H_Silvermoon_Court,
            H_Silvermoon_West,

            H_Suncrown_Village,
            H_Tranquillien,
            H_Goldenmist_Village,

            N_Lights_Hope_Chapel,
            N_Northpass_Tower,
            N_Crown_Guard_Tower,

            N_Hearthglen,
            N_Chillwind_Camp,
            N_Caer_Darrow,

            H_Crossroads,
            H_Tarren_Mill,
            H_Stonard,
            H_Camp_Mojache,

            N_Booty_Bay,
            N_Everlook,
            N_Gadgetzan,
            N_Kezan,
            N_Ratchet,

            H_Brill,
            A_Scarlet_Monastery,
            H_Undercity_Entrance,
            H_Undercity_Bank,
            H_Undercity_Apothecarium,

            A_Pyrewood_Village,
            A_Ambermill,
            H_The_Spelchur,

            H_Soferas_Naze,
            A_Corrahns_Dagger,
            N_Dalaran_Crater,

            A_Southshore,
            A_Hillsbrad_Fields,
            H_Tauren_Mill,

            A_Aerie_Peak,
            A_QuelDanil_Lodge,
            H_Revantusk_Village,

            A_Stromgarde_Keep,
            A_Refuge_Pointe,
            H_Hammerfall,

            A_Valley_Of_Kings,
            A_Thelsamar,
            A_Stonewrought_Dam,

            A_Kharanos,
            A_GolBolar_Quarry,
            A_Ironforge_Inn,
            A_Ironforge_Entrance,
            A_Ironforge_Mystic,

            N_Thorium_Point



        };

    public:
        npc_spark_teleporter() : CreatureScript("npc_spark_teleporter")  { }

        bool OnGossipHello(Player * player, Creature * creature)
        {
            if (player->IsExecuted())
            {
                player->PlayerTalkClass->SendGossipMenu(724010, creature->GetGUID());
                return true;
            }
            if (player->getRace() != 18)
            {
                if (player->GetTeam() == ALLIANCE || player->getRace() == 11)
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Alliance Locations", GOSSIP_SENDER_MAIN, Alliance);
                }
                if (player->GetTeam() == HORDE || player->getRace() == 11)
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Horde Locations", GOSSIP_SENDER_MAIN, Horde);
                }
            }

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Neutral Locations", GOSSIP_SENDER_MAIN, Neutral);
            player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());


            return true;
        }

        bool OnGossipSelect(Player * player, Creature * creature, uint32 sender, uint32 actions)
        {
            player->PlayerTalkClass->ClearMenus();
            if (sender != GOSSIP_SENDER_MAIN)
            {
                return false;
            }

            switch (actions)
            {
                case ON_GOSSIP_HELLO:
                    OnGossipHello(player, creature);
                    break;
                case Alliance:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, ON_GOSSIP_HELLO);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Stormwind", GOSSIP_SENDER_MAIN, A_Stormwind);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Darnassus", GOSSIP_SENDER_MAIN, A_Darnassus);
                    //player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Exodar", GOSSIP_SENDER_MAIN, A_Exodar);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Silverpine Forest", GOSSIP_SENDER_MAIN, A_Silverpine_Forest);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Tirisfal Glades", GOSSIP_SENDER_MAIN, A_Tirisfal_Glades);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "The Hinterlands", GOSSIP_SENDER_MAIN, A_The_Hinterlands);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Alterac Mountains", GOSSIP_SENDER_MAIN, A_Alterac_Mountains);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Arathi Highlands", GOSSIP_SENDER_MAIN, A_Arathi_Highlands);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Wetlands", GOSSIP_SENDER_MAIN, A_Wetlands);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Hillsbrad Foothills", GOSSIP_SENDER_MAIN, A_Hillsbrad_Foothills);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Loch Modan", GOSSIP_SENDER_MAIN, A_Loch_Modan);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Dun Morogh", GOSSIP_SENDER_MAIN, A_Dun_Morogh);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Astranaar", GOSSIP_SENDER_MAIN, A_Astranaar, "Are you sure you wish to begin in Astranaar?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Theramore", GOSSIP_SENDER_MAIN, A_Theramore, "Are you sure you wish to begin in Theramore?", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case Horde:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, ON_GOSSIP_HELLO);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Orgrimmar", GOSSIP_SENDER_MAIN, H_Orgrimmar);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Thunder Bluff", GOSSIP_SENDER_MAIN, H_ThunderBluff);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Eversong Woods", GOSSIP_SENDER_MAIN, H_Eversong_Woods);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ghostlands", GOSSIP_SENDER_MAIN, H_Ghostlands);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Silverpine Forest", GOSSIP_SENDER_MAIN, H_Silverpine_Forest);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Tirisfal Glades", GOSSIP_SENDER_MAIN, H_Tirisfal_Glades);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Hillsbrad Foothills", GOSSIP_SENDER_MAIN, H_Hillsbrad_Foothills);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Alterac Mountains", GOSSIP_SENDER_MAIN, H_Alterac_Mountains);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "The Hinterlands", GOSSIP_SENDER_MAIN, H_The_Hinterlands);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Stonard", GOSSIP_SENDER_MAIN, H_Stonard, "Are you sure you wish to begin in Stonard?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "The Crossroads", GOSSIP_SENDER_MAIN, H_Crossroads, "Are you sure you wish to begin in The Crossroads?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Camp Mojache", GOSSIP_SENDER_MAIN, H_Camp_Mojache, "Are you sure you wish to begin in Camp Mojache?", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case Neutral:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, ON_GOSSIP_HELLO);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Eastern Plaguelands", GOSSIP_SENDER_MAIN, N_Eastern_Plaguelands);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Western Plaguelands", GOSSIP_SENDER_MAIN, N_Western_Plaguelands);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Alterac Mountains", GOSSIP_SENDER_MAIN, N_Alterac_Mountains);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Searing Gorge", GOSSIP_SENDER_MAIN, N_Searing_Gorge);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Booty Bay", GOSSIP_SENDER_MAIN, N_Booty_Bay, "Are you sure you wish to begin in Booty Bay?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Gadgetzan", GOSSIP_SENDER_MAIN, N_Gadgetzan, "Are you sure you wish to begin in Gadgetzan?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Everlook", GOSSIP_SENDER_MAIN, N_Everlook, "Are you sure you wish to begin in Everlook?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Ratchet", GOSSIP_SENDER_MAIN, N_Ratchet, "Are you sure you wish to begin in Ratchet?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Kezan", GOSSIP_SENDER_MAIN, N_Kezan, "Are you sure you wish to begin in the island of Kezan?", 0, 0);

                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case A_Stormwind:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, Alliance);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Stormwind Entrance", GOSSIP_SENDER_MAIN, A_Stormwind_Entrance, "Are you sure you wish to begin in Stormwind Entrance?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Stormwind Inn", GOSSIP_SENDER_MAIN, A_Stormwind_Trade, "Are you sure you wish to begin in the The Gilded Rose?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Old Town", GOSSIP_SENDER_MAIN, A_Stormwind_Oldtown, "Are you sure you wish to begin in the Pig and Whistle Tavern?", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case A_Ironforge:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, Alliance);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Ironforge Entrance", GOSSIP_SENDER_MAIN, A_Ironforge_Entrance, "Are you sure you wish to begin in Ironforge Entrance?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Ironforge Tavern", GOSSIP_SENDER_MAIN, A_Ironforge_Inn, "Are you sure you wish to begin in the The Stonefire Tavern?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "The Mystic Ward", GOSSIP_SENDER_MAIN, A_Ironforge_Mystic, "Are you sure you wish to begin in the Mystic Ward?", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case A_Darnassus:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, Alliance);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Darnassus Entrance", GOSSIP_SENDER_MAIN, A_Darnassus_Entrance, "Are you sure you wish to begin in Darnassus Entrance?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "The Cenarion Enclave", GOSSIP_SENDER_MAIN, A_Darnassus_Cenarion, "Are you sure you wish to begin in the Cenarion Enclave?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "The Temple of the Moon", GOSSIP_SENDER_MAIN, A_Darnassus_Temple, "Are you sure you wish to begin in the Temple of the Moon?", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case H_Orgrimmar:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, Horde);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Orgrimmar Entrance", GOSSIP_SENDER_MAIN, H_Orgrimmar_Entrance, "Are you sure you wish to begin in Orgrimmar Entrance?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Gryshka's Inn", GOSSIP_SENDER_MAIN, H_Orgrimmar_Inn, "Are you sure you wish to begin in Gryshka's Inn?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Valley of Honor", GOSSIP_SENDER_MAIN, H_Orgrimmar_Honor, "Are you sure you wish to begin in The Valley of Honor?", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case H_ThunderBluff:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, Horde);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Thunderbluff Entrance", GOSSIP_SENDER_MAIN, H_ThunderBluff_Entrance, "Are you sure you wish to begin in Thunderbluff Entrance?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "The Spirit Rise", GOSSIP_SENDER_MAIN, H_ThunderBluff_Spirit, "Are you sure you wish to begin in the Spirit Rise?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Chieftain's Bluff", GOSSIP_SENDER_MAIN, H_ThunderBluff_Cairne, "Are you sure you wish to begin in the Chieftain's Bluff?", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case H_Eversong_Woods:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, Horde);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Fairbreeze Village", GOSSIP_SENDER_MAIN, H_Fairbreeze_Village, "Are you sure you wish to begin in Fairbreeze Village?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Sunstrider Isle", GOSSIP_SENDER_MAIN, H_Sunstrider_Isle, "Are you sure you wish to begin in Sunstrider Isle?", 0, 0);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Silvermoon", GOSSIP_SENDER_MAIN, H_Silvermoon);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case H_Ghostlands:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, Horde);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Suncrown Village", GOSSIP_SENDER_MAIN, H_Suncrown_Village, "Are you sure you wish to begin in Suncrown Village?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Tranquillien", GOSSIP_SENDER_MAIN, H_Tranquillien, "Are you sure you wish to begin in Tranquillien", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Goldenmist Village", GOSSIP_SENDER_MAIN, H_Goldenmist_Village, "Are you sure you wish to begin in Goldenmist Village", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case H_Silvermoon:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, H_Eversong_Woods);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Silvermoon Entrance", GOSSIP_SENDER_MAIN, H_Silvermoon_Entrance, "Are you sure you wish to begin in Silvermoon Entrance?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Western Silvermoon", GOSSIP_SENDER_MAIN, H_Silvermoon_West, "Are you sure you wish to begin in Western Silvermoon?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "The Court of the Sun", GOSSIP_SENDER_MAIN, H_Silvermoon_Court, "Are you sure you wish to begin in The Court of the Sun?", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case H_Undercity:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, H_Tirisfal_Glades);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Undercity Entrance", GOSSIP_SENDER_MAIN, H_Undercity_Entrance, "Are you sure you wish to begin in Undercity Entrance?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "The Trade Quarter", GOSSIP_SENDER_MAIN, H_Undercity_Bank, "Are you sure you wish to begin in The Trade Quarter?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "The Apothecarium", GOSSIP_SENDER_MAIN, H_Undercity_Apothecarium, "Are you sure you wish to begin in The Apothecarium?", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case N_Eastern_Plaguelands:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, Neutral);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Light's Hope Chapel", GOSSIP_SENDER_MAIN, N_Lights_Hope_Chapel, "Are you sure you wish to begin in Light's Hope Chapel?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Northpass Tower", GOSSIP_SENDER_MAIN, N_Northpass_Tower, "Are you sure you wish to begin in Northpass Tower?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Crown Guard Tower", GOSSIP_SENDER_MAIN, N_Crown_Guard_Tower, "Are you sure you wish to begin in Crown Guard Tower?", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case N_Western_Plaguelands:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, Neutral);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Hearthglen", GOSSIP_SENDER_MAIN, N_Hearthglen, "Are you sure you wish to begin in Hearthglen?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Chillwind Point", GOSSIP_SENDER_MAIN, N_Chillwind_Camp, "Are you sure you wish to begin in Chillwind Point?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Caer Darrow", GOSSIP_SENDER_MAIN, N_Caer_Darrow, "Are you sure you wish to begin in Caer Darrow?", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case A_Tirisfal_Glades:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, Alliance);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Scarlet Monastery", GOSSIP_SENDER_MAIN, A_Scarlet_Monastery, "Are you sure you wish to begin in Scarlet Monastery?", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case H_Tirisfal_Glades:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, Horde);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "The Undercity", GOSSIP_SENDER_MAIN, H_Undercity);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Brill", GOSSIP_SENDER_MAIN, H_Brill, "Are you sure you wish to begin in Brill?", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case A_Silverpine_Forest:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, Alliance);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Pyrewood Village", GOSSIP_SENDER_MAIN, A_Pyrewood_Village, "Are you sure you wish to begin in Pyrewood Village?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Ambermill", GOSSIP_SENDER_MAIN, A_Ambermill, "Are you sure you wish to begin in Ambermill?", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case H_Silverpine_Forest:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, Horde);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "The Sepulcher", GOSSIP_SENDER_MAIN, H_The_Spelchur, "Are you sure you wish to begin in The Spelchur?", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case A_Alterac_Mountains:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, Alliance);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Corrahn's Dagger", GOSSIP_SENDER_MAIN, A_Corrahns_Dagger, "Are you sure you wish to begin in Corrahn's Dagger?", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case N_Alterac_Mountains:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, Neutral);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Dalaran Crater", GOSSIP_SENDER_MAIN, N_Dalaran_Crater, "Are you sure you wish to begin in Dalaran Crater?", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case H_Alterac_Mountains:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, Horde);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Sofera's Naze", GOSSIP_SENDER_MAIN, H_Soferas_Naze, "Are you sure you wish to begin in Sofera's Naze?", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case A_Hillsbrad_Foothills:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, Alliance);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Southshore", GOSSIP_SENDER_MAIN, A_Southshore, "Are you sure you wish to begin in Southshore?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Hillsbrad Fields", GOSSIP_SENDER_MAIN, A_Hillsbrad_Fields, "Are you sure you wish to begin in Hillsbrad Fields?", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case H_Hillsbrad_Foothills:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, Horde);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Tarren Mill", GOSSIP_SENDER_MAIN, H_Tarren_Mill, "Are you sure you wish to begin in Tarren Mill?", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case A_The_Hinterlands:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, Alliance);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Aerie Peak", GOSSIP_SENDER_MAIN, A_Aerie_Peak, "Are you sure you wish to begin in Aerie Peak?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Quel'Danil Lodge", GOSSIP_SENDER_MAIN, A_QuelDanil_Lodge, "Are you sure you wish to begin in Quel'Danil Lodge?", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case H_The_Hinterlands:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, Horde);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Revantusk Village", GOSSIP_SENDER_MAIN, H_Revantusk_Village, "Are you sure you wish to begin in Revantusk Village?", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case A_Arathi_Highlands:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, Alliance);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Stromgarde Keep", GOSSIP_SENDER_MAIN, A_Stromgarde_Keep, "Are you sure you wish to begin in Stromgarde Keep?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Refuge Pointe", GOSSIP_SENDER_MAIN, A_Refuge_Pointe, "Are you sure you wish to begin in Refuge Pointe?", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case H_Arathi_Highlands:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, Horde);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Hammerfall", GOSSIP_SENDER_MAIN, H_Hammerfall, "Are you sure you wish to begin in Hammerfall?", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case A_Wetlands:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, Alliance);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Menethil Harbour", GOSSIP_SENDER_MAIN, A_Menethil_Harbor, "Are you sure you wish to begin in Menethil Harbour?", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case A_Loch_Modan:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, Alliance);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Valley of Kings", GOSSIP_SENDER_MAIN, A_Valley_Of_Kings, "Are you sure you wish to begin in Valley Of Kings?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Stonewrought Dam", GOSSIP_SENDER_MAIN, A_Stonewrought_Dam, "Are you sure you wish to begin in Stonewrought Dam?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Thelsamar", GOSSIP_SENDER_MAIN, A_Thelsamar, "Are you sure you wish to begin in Thelsamar?", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case A_Dun_Morogh:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, Alliance);
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Ironforge", GOSSIP_SENDER_MAIN, A_Ironforge);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Kharanos", GOSSIP_SENDER_MAIN, A_Kharanos, "Are you sure you wish to begin in Kharanos?", 0, 0);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Gol'Bolar Quarry", GOSSIP_SENDER_MAIN, A_GolBolar_Quarry, "Are you sure you wish to begin in Gol'Bolar Quarry?", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case N_Searing_Gorge:
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Back", GOSSIP_SENDER_MAIN, Neutral);
                    player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TAXI, "Thorium Point", GOSSIP_SENDER_MAIN, N_Thorium_Point, "Are you sure you wish to begin in Thorium Point?", 0, 0);
                    player->PlayerTalkClass->SendGossipMenu(724006, creature->GetGUID());
                    break;
                case A_Stormwind_Entrance:
                    player->TeleportTo(0, -9085.154297, 418.603882, 92.402603, 0.628370);
                    break;
                case A_Stormwind_Trade:
                    player->TeleportTo(0, -8859.068359, 660.534851, 96.924789, 5.317941);
                    break;
                case A_Stormwind_Oldtown:
                    player->TeleportTo(0, -8639.614258, 421.210419, 102.816566, 2.180277);
                    break;
                case A_Ironforge_Inn:
                    player->TeleportTo(0, -4847.864746, -878.805664, 501.659454, 3.912365);
                    break;
                case A_Ironforge_Mystic:
                    player->TeleportTo(0, -4680.815430, -934.320801, 501.658875, 5.331579);
                    break;
                case A_Ironforge_Entrance:
                    player->TeleportTo(0, -5034.275391, -818.499634, 495.128265, 5.368489);
                    break;
                case A_Darnassus_Temple:
                    player->TeleportTo(1, 9708.125977, 2525.262695, 1335.689331, 0.025073);
                    break;
                case A_Darnassus_Cenarion:
                    player->TeleportTo(1, 10121.045898, 2519.825195, 1324.782715, 1.818918);
                    break;
                case A_Darnassus_Entrance:
                    player->TeleportTo(1, 9984.053711, 1953.985352, 1325.743530, 1.523608);
                    break;
                case A_Theramore:
                    player->TeleportTo(1, -3593.071045, -4319.344238, 7.183995, 3.836976);
                    break;
                case A_Astranaar:
                    player->TeleportTo(1, 2831.892578, -241.772278, 106.310349, 4.012125);
                    break;
                case A_Menethil_Harbor:
                    player->TeleportTo(0, -3792.055664, -785.844116, 9.412722, 1.642145);
                    break;
                case H_Orgrimmar_Entrance:
                    player->TeleportTo(1, 1334.622559, -4373.814941, 26.195023, 0.123267);
                    break;
                case H_Orgrimmar_Honor:
                    player->TeleportTo(1, 2124.310059, -4730.936523, 50.210594, 5.768704);
                    break;
                case H_Orgrimmar_Inn:
                    player->TeleportTo(1, 1622.151978, -4433.279785, 11.812630, 2.777118);
                    break;
                case H_ThunderBluff_Entrance:
                    player->TeleportTo(1, -1339.793457, 176.661682, 57.721725, 0.249600);
                    break;
                case H_ThunderBluff_Spirit:
                    player->TeleportTo(1, -999.668518, 253.027939, 138.063950, 1.036572);
                    break;
                case H_ThunderBluff_Cairne:
                    player->TeleportTo(1, -1203.532593, -11.234323, 168.565170, 4.634479);
                    break;
                case H_Silvermoon_Entrance:
                    player->TeleportTo(530, 9342.620117, -7277.465820, 14.261377, 6.264054);
                    break;
                case H_Silvermoon_Court:
                    player->TeleportTo(530, 9846.542969, -7293.169922, 26.139175, 2.177627);
                    break;
                case H_Silvermoon_West:
                    player->TeleportTo(530, 9524.172852, -6844.225586, 16.492395, 1.165933);
                    break;
                case H_Suncrown_Village:
                    player->TeleportTo(530, 7945.047363, -7211.743652, 135.328049, 5.23312);
                    break;
                case H_Tranquillien:
                    player->TeleportTo(530, 7630.244629, -6814.267578, 79.890450, 3.310178);
                    break;
                case H_Goldenmist_Village:
                    player->TeleportTo(530, 7830.355469, -6231.920898, 20.549596, 0.601339);
                    break;
                case H_Undercity_Entrance:
                    player->TeleportTo(0, 1900.830322, 238.207077, 54.512180, 3.137046);
                    break;
                case H_Undercity_Bank:
                    player->TeleportTo(0, 1631.732422, 240.887131, -43.102367, 3.195163);
                    break;
                case H_Undercity_Apothecarium:
                    player->TeleportTo(0, 1503.685303, 334.006012, -60.087688, 2.362625);
                    break;
                case H_Stonard:
                    player->TeleportTo(0, -10460.382812, -3199.938721, 20.178350, 4.660134);
                    break;
                case H_Tarren_Mill:
                    player->TeleportTo(0, 11.762218, -708.797791, 73.247490, 3.240730);
                    break;
                case H_Camp_Mojache:
                    player->TeleportTo(1, -4329.782715, -7.060944, 57.980293, 2.071621);
                    break;
                case H_Crossroads:
                    player->TeleportTo(1, -506.378296, -2790.562012, 91.666641, 0.889805);
                    break;
                case H_Sunstrider_Isle:
                    player->TeleportTo(530, 10347.748047, -6356.338867, 33.137711, 4.821285);
                    break;
                case H_Fairbreeze_Village:
                    player->TeleportTo(530, 8733.591797, -6674.619141, 69.534744, 2.624523);
                    break;
                case N_Booty_Bay:
                    player->TeleportTo(0, -14285.243164, 556.442139, 8.838202, 4.240738);
                    break;
                case N_Gadgetzan:
                    player->TeleportTo(1, -7084.374023, -3738.187988, 8.547241, 4.786827);
                    break;
                case N_Everlook:
                    player->TeleportTo(1, 6736.21875, -4602.038574, 720.501465, 4.157516);
                    break;
                case N_Ratchet:
                    player->TeleportTo(1, -1038.403564, -3667.173096, 23.869135, 6.031826);
                    break;
                case N_Kezan:
                    player->TeleportTo(25, -8250.459961, 1458.238159, 41.080536, 2.196520);
                    break;
                case N_Lights_Hope_Chapel:
                    player->TeleportTo(0, 2280.286377, -5275.759766, 82.056244, 4.784036);
                    break;
                case N_Northpass_Tower:
                    player->TeleportTo(0, 3164.075195, -4333.938477, 133.557968, 4.869642);
                    break;
                case N_Crown_Guard_Tower:
                    player->TeleportTo(0, 1867.073975, -3681.382812, 155.860214, 4.394477);
                    break;
                case N_Hearthglen:
                    player->TeleportTo(0, 2727.770508, -1678.721802, 127.799606, 1.103645);
                    break;
                case N_Chillwind_Camp:
                    player->TeleportTo(0, 814.794434, -1472.514771, 72.835983, 6.164248);
                    break;
                case N_Caer_Darrow:
                    player->TeleportTo(0, 991.790894, -2507.916016, 59.333805, 6.075013);
                    break;
                case H_Brill:
                    player->TeleportTo(0, 2279.907959, 408.576324, 33.872205, 4.882988);
                    break;
                case A_Scarlet_Monastery:
                    player->TeleportTo(0, 2782.611084, -705.640808, 129.004211, 0.122698);
                    break;
                case A_Pyrewood_Village:
                    player->TeleportTo(0, -344.942810, 1394.348511, 30.234087, 1.754752);
                    break;
                case A_Ambermill:
                    player->TeleportTo(0, -195.538483, 1177.499878, 63.407730, 6.200099);
                    break;
                case H_The_Spelchur:
                    player->TeleportTo(0, 548.771179, 1457.717041, 104.187775, 2.266829);
                    break;
                case H_Soferas_Naze:
                    player->TeleportTo(0, 318.133606, -852.636414, 134.716614, 3.148761);
                    break;
                case A_Corrahns_Dagger:
                    player->TeleportTo(0, -12.791600, -553.372986, 152.259003, 6.026770);
                    break;
                case N_Dalaran_Crater:
                    player->TeleportTo(0, 1.193335, 242.375549, 44.032848, 0.296975);
                    break;
                case A_Southshore:
                    player->TeleportTo(0, -732.213135, -548.417263, 20.127022, 3.054591);
                    break;
                case A_Hillsbrad_Fields:
                    player->TeleportTo(0, -664.190796, 40.346756, 46.973232, 6.164337);
                    break;
                case A_Aerie_Peak:
                    player->TeleportTo(0, 201.177994, -2096.780029, 116.466003, 5.452650);
                    break;
                case A_QuelDanil_Lodge:
                    player->TeleportTo(0, 174.412704, -2815.934326, 111.012062, 0.688218);
                    break;
                case H_Revantusk_Village:
                    player->TeleportTo(0, -480.238464, -4521.651855, 13.025707, 3.464514);
                    break;
                case A_Stromgarde_Keep:
                    player->TeleportTo(0, -1574.529175, -1789.899780, 67.218399, 1.745639);
                    break;
                case A_Refuge_Pointe:
                    player->TeleportTo(0, -1196.028809, -2657.192627, 45.235466, 1.371804);
                    break;
                case H_Hammerfall:
                    player->TeleportTo(0, -1086.989258, -3553.717041, 49.838737, 0.112798);
                    break;
                case A_Valley_Of_Kings:
                    player->TeleportTo(0, -5870.587402, -2557.521484, 307.286560, 3.950142);
                    break;
                case A_Stonewrought_Dam:
                    player->TeleportTo(0, -4716.983398, -3420.970703, 310.257111, 1.974002);
                    break;
                case A_Thelsamar:
                    player->TeleportTo(0, -5405.503906, -2890.239990, 342.464447, 5.292311);
                    break;
                case A_GolBolar_Quarry:
                    player->TeleportTo(0, -5649.320801, -1515.694580, 398.111603, 4.092218);
                    break;
                case A_Kharanos:
                    player->TeleportTo(0, -5597.310059, -483.398010, 396.980988, 3.175660);
                    break;
                case N_Thorium_Point:
                    player->TeleportTo(0, -6494.724798, -1133.742798, 307.243988, 4.027842);
                    break;
            }
        }

};

void AddSC_misc()
{
    new misc_legacy();
    new npc_spark_teleporter();
    new npc_armor_trainer();
    new npc_scale();
}
