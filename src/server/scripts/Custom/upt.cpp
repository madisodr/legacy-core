#include "ScriptPCH.h"
#include "Log.h"
#include "SharedDefines.h"

#define SilverCoin 999116

class item_script_upt : public ItemScript
{
    public:
        enum Options
        {

            ON_GOSSIP_HELLO,
            /*** Groups ****/
            AnimationsNActions,
            Arcane,
            DarkNShadow,
            Fire,
            IceNWater,
            HolyLightNDivine,
            ArmorNProficiencies,
            Nature,
            ElementalNShaman,
            ItemRequest,

            /*** Individual spells ****/
            /* Animations & Actions */
            AA_Weapon_Swing = 35041,
            AA_Combat_Stance,
            AA_Kick = 42908,
            AA_Punch = 57543,
            AA_Hold_Rifle = 16723,
            AA_Man_Down = 12218,
            AA_Run_Away = 8225,
            AA_Shield_Block = 42906,
            AA_Throw_Javelin = 62778,
            AA_Chop_Tree = 62990,
            AA_Apollo_Leash = 61857,
            AA_Cosmetic_Enchant_Cast = 60888,

            /* Arcane */
            A_Arcane_Explosion_Visual = 35426,
            A_Cosmetic_Azure_Manashaper_Channel = 59069,
            A_Cosmetic_Teleport_Effect = 52096,
            A_Evil_Teleport_Visual_Only = 61456,
            A_Evocation_Visual_Only = 32477,
            A_Wyrmrest_Arcane_Beam = 55840,
            A_Arcane_Channeling_Effect = 39550,
            A_Arcane_Channeling = 54219,
            A_Cosmetic_Arcane_Shield = 46933,
            A_Proximity_Mine_Visual = 49311,
            A_Ethereal_Ring = 40952,

            /* Dark & Shadow */
            DS_Dark_Ritual_Channel = 67040,
            DS_Destroy_Soul = 74086,
            DS_Dispersion = 47218,
            DS_Entropius_Cosmetic_Spawn = 46223,
            DS_Power_Ball_Visual = 54139,
            DS_Bloodmyst_Channeling = 30946,
            DS_Wave_Beam = 6061,
            DS_Blackfathom_Channeling = 8734,
            DS_Shadow_Channeling = 51733,
            DS_Feathery_Explosion = 39180,
            DS_Heart_Beam = 54988,
            DS_Fel_Crystal = 44374,
            DS_Sphere_Purple = 56075,
            DS_Food_Poisoning = 28528,
            DS_Animal_Feed = 29918,
            DS_Raise_Dead = 69431,
            DS_Soul_Separation = 46695,

            /* Fire */
            F_Bombing_Run = 40162,
            F_Cosmetic_New_Fire_Beam_Channel = 45576,
            F_Cosmetic_Wintergrasp_Victory_Aura = 60044,
            F_Find_Opening_Visual = 45964,
            F_Hellfire_Warder_Channel_Visual = 33827,
            F_Fire_Channeling = 21392,
            F_Fire_Channeling_Two = 45579,
            F_Twin_Waves = 42328,
            F_Split_Four_Ways = 42331,
            F_Burning_Felguard_Spawn = 16074,
            F_Red_Wyrmrest_Beam = 55824,

            /* Ice & Water */
            IW_Crystal_Spike_Pre_Visual = 50442,
            IW_Ice_Spear_Visual = 75498,
            IW_Frostbolt_Volley = 29923,
            IW_Pure_Water = 8384,
            IW_Frost_Channeling = 75427,
            IW_Frost_Channeling_Two = 45846,
            IW_Cone_Cold = 43066,

            /* Holy Light & Divine */
            HLD_Holy_Strength = 67371,
            HLD_Holy_Zone_Visual = 70571,
            HLD_Speak = 39838,
            HLD_Sprinkle_Holy_Water = 57806,
            HLD_Holy_Channeling_Two = 51361,
            HLD_Sacred_Shield = 70491,
            HLD_Sphere_Visual = 56102,
            HLD_Bronze_Wyrmrest_Beam = 55841,
            HLD_Hammer_Righteous = 54423,
            HLD_Lightning_Visual = 56915,
            HLD_Summon_Holy_Mount_Visual = 31726,

            /* Armor & Proficiencies */
            AP_Leather,
            AP_Leather_Skill = 414,
            AP_Mail,
            AP_Mail_Spell = 8737,
            AP_Mail_Skill = 413,
            AP_Plate,
            AP_Plate_Spell = 750,
            AP_Plate_Skill = 293,

            /* Nature */
            N_Nature_Channeling = 13236,
            N_Nature_Channeling_Two = 28892,
            N_Green_Wyrmrest_Beam = 55838,
            N_Morthis_Tranquility = 40128,
            N_Nature_Wave = 51365,
            N_Noblegarden_Bunny = 61710,


            /* Elemental & Shaman */
            ES_Earth_Explosion = 42373,
            ES_Call_Lightning = 37964,
            ES_Fire_Visual = 73119,
            ES_Death_Visual = 57555,
            ES_Boom_Visual = 35341,
            ES_Water_Elemental_Visual = 32995,
            ES_Cyclone_Fall = 59838,
            ES_Sandstorm = 68802,
            ES_Boomerang_Lightning_Bolt = 36312
        };

        item_script_upt() : ItemScript("item_script_upt") { }

        bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/) override
        {
            player->PlayerTalkClass->ClearMenus();
            player->ADD_GOSSIP_ITEM(10, "Animations & Actions", GOSSIP_SENDER_MAIN, AnimationsNActions);
            player->ADD_GOSSIP_ITEM(10, "Arcane", GOSSIP_SENDER_MAIN, Arcane);
            player->ADD_GOSSIP_ITEM(10, "Dark & Shadow", GOSSIP_SENDER_MAIN, DarkNShadow);
            player->ADD_GOSSIP_ITEM(10, "Fire", GOSSIP_SENDER_MAIN, Fire);
            player->ADD_GOSSIP_ITEM(10, "Ice & Water", GOSSIP_SENDER_MAIN, IceNWater);
            player->ADD_GOSSIP_ITEM(10, "Holy Light & Divine", GOSSIP_SENDER_MAIN, HolyLightNDivine);
            player->ADD_GOSSIP_ITEM(10, "Armor Proficiencies", GOSSIP_SENDER_MAIN, ArmorNProficiencies);
            player->ADD_GOSSIP_ITEM(10, "Nature", GOSSIP_SENDER_MAIN, Nature);
            player->ADD_GOSSIP_ITEM(10, "Elemental & Shaman", GOSSIP_SENDER_MAIN, ElementalNShaman);
            player->ADD_GOSSIP_ITEM(10, "Item Requesting", GOSSIP_SENDER_MAIN, ItemRequest);

            player->PlayerTalkClass->SendGossipMenu(724008, item->GetGUID());

            return true;
        }

        bool OnGossipSelectCode(Player* player, Item* item, uint32 sender, uint32 action, const char* code)
        {
            player->PlayerTalkClass->ClearMenus();
            uint32 itemId;
            if(code > 0)
                itemId = atoi((char*)code);

            ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(itemId);
            if (!itemTemplate)
            {
                ChatHandler(player->GetSession()).PSendSysMessage(LANG_COMMAND_ITEMIDINVALID, itemId);
                handler->SetSentErrorMessage(true);
                return false;
            }

            if(itemTemplate->Quality > ITEM_QUALITY_UNCOMMON)
            {
                ChatHandler(player->GetSession()).PSendSysMessage("You can't request this quality item.");
                return false;
            }

            if(sender == GOSSIP_SENDER_MAIN)
            {
                switch (action)
                {
                    case IR_Common:
                        if(itemTemplate->Quality <= ITEM_QUALITY_NORMAL)
                        {
                            CreateItem(player, itemId);
                            return true;
                        }
                        break;
                    case IR_Uncommon:
                        if(GetItemRequests(player) <= 0)
                        {
                            ChatHandler(player->GetSession()).PSendSysMessage("You can't request anymore items");
                            return false;
                        }

                        if(itemTemplate->Quality == ITEM_QUALITY_UNCOMMON && CheckHasEnough(player, 30))
                        {
                            if(CreateItem(player, itemId) == false)
                                return false;

                            CharacterDatabase.DirectExecute("UPDATE character_request SET amount = amount - 1 WHERE guid='%u'", player->GetGUIDLow());
                            player->DestroyItemCount(SilverCoin, 30, true);

                            ChatHandler(player->GetSession()).PSendSysMessage("You have '%u' requests left on this character", GetItemRequests(player));

                            return true;
                        }

                        break;
                }
            }
        }

        uint32 GetItemRequests(Player* player)
        {
            QueryResult result = CharacterDatabase.PQuery("SELECT amount FROM legacy_character WHERE guid='%u'", player->GetGUIDLow());
            if(result)
            {
                Field* fields = result->Fetch();
                return fields[0].GetUInt32();
            }
        }

        bool CreateItem(Player* player, uint32 itemId)
        {

            Item* item;

            if(item->Create(sObjectMgr->GenerateLowGuid(HIGHGUID_ITEM), itemId, player) == false)
                return false;

            MailSender toSend(MAIL_NORMAL, player->GetGUIDLow(), MAIL_STATIONERY_GM);
            SQLTransaction trans = CharacterDatabase.BeginTransaction();
            item->SaveToDB(trans);

            MailDraft mailDraft("Item Request", "Your item, as requested.");
            mailDraft.AddItem(item);
            mailDraft.SendMailTo(trans, MailReceiver(player), toSend);
            CharacterDatabase.CommitTransaction(trans);
            return true;
        }

        bool OnGossipSelect(Player* player, Item* item, uint32 /*sender*/, uint32 action) override
        {
            player->PlayerTalkClass->ClearMenus();

            switch (action)
            {
                case ON_GOSSIP_HELLO:
                    player->PlayerTalkClass->ClearMenus();
                    player->ADD_GOSSIP_ITEM(10, "Animations & Actions", GOSSIP_SENDER_MAIN, AnimationsNActions);
                    player->ADD_GOSSIP_ITEM(10, "Arcane", GOSSIP_SENDER_MAIN, Arcane);
                    player->ADD_GOSSIP_ITEM(10, "Dark & Shadow", GOSSIP_SENDER_MAIN, DarkNShadow);
                    player->ADD_GOSSIP_ITEM(10, "Fire", GOSSIP_SENDER_MAIN, Fire);
                    player->ADD_GOSSIP_ITEM(10, "Ice & Water", GOSSIP_SENDER_MAIN, IceNWater);
                    player->ADD_GOSSIP_ITEM(10, "Holy Light & Divine", GOSSIP_SENDER_MAIN, HolyLightNDivine);
                    player->ADD_GOSSIP_ITEM(10, "Armor Proficiencies", GOSSIP_SENDER_MAIN, ArmorNProficiencies);
                    player->ADD_GOSSIP_ITEM(10, "Nature", GOSSIP_SENDER_MAIN, Nature);
                    player->ADD_GOSSIP_ITEM(10, "Elemental & Shaman", GOSSIP_SENDER_MAIN, ElementalNShaman);
                    player->ADD_GOSSIP_ITEM(10, "Item Requesting", GOSSIP_SENDER_MAIN, ItemRequest);

                    player->PlayerTalkClass->SendGossipMenu(724008, item->GetGUID());
                    break;
                case AnimationsNActions:
                    player->ADD_GOSSIP_ITEM(10, "Back", GOSSIP_SENDER_MAIN, ON_GOSSIP_HELLO);

                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Weapon Swing (20 silver)", GOSSIP_SENDER_MAIN, AA_Weapon_Swing, "Are you sure you wish to purchase this spell?", 2000, false);
                    //player->ADD_GOSSIP_ITEM(10, "Combat Stance", GOSSIP_SENDER_MAIN, AA_Combat_Stance);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Kick (20 silver)", GOSSIP_SENDER_MAIN, AA_Kick, "Are you sure you wish to purchase this spell?", 2000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Punch (unarmed attack) (20 silver)", GOSSIP_SENDER_MAIN, AA_Punch, "Are you sure you wish to purchase this spell?", 2000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Hold Rifle (20 silver)", GOSSIP_SENDER_MAIN, AA_Hold_Rifle, "Are you sure you wish to purchase this spell?", 2000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Man Down! (Splurt out blood) (30 silver)", GOSSIP_SENDER_MAIN, AA_Man_Down, "Are you sure you wish to purchase this spell?", 3000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Run away! (Fears yourself) (30 silver)", GOSSIP_SENDER_MAIN, AA_Run_Away, "Are you sure you wish to purchase this spell?", 3000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Shield Block (20 silver)", GOSSIP_SENDER_MAIN, AA_Shield_Block, "Are you sure you wish to purchase this spell?", 2000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Throw Javelin (Requires a throwing weapon) (15 silver)", GOSSIP_SENDER_MAIN, AA_Throw_Javelin, "Are you sure you wish to purchase this spell?", 1500, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Chop Tree (10 silver)", GOSSIP_SENDER_MAIN, AA_Chop_Tree, "Are you sure you wish to purchase this spell?", 1000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Apollo's Leash (Attaches a rope to the target) (16 silver)", GOSSIP_SENDER_MAIN, AA_Apollo_Leash, "Are you sure you wish to purchase this spell?", 1500, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Cosmetic Enchanting Cast (15 silver)", GOSSIP_SENDER_MAIN, AA_Cosmetic_Enchant_Cast, "Are you sure you wish to purchase this spell?", 1500, false);


                    player->PlayerTalkClass->SendGossipMenu(724008, item->GetGUID());

                    break;

                case Arcane:
                    player->ADD_GOSSIP_ITEM(10, "Back", GOSSIP_SENDER_MAIN, ON_GOSSIP_HELLO);

                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Arcane Explosion Visual (expanding dome of blue light) (30 silver)", GOSSIP_SENDER_MAIN, A_Arcane_Explosion_Visual, "Are you sure you wish to purchase this spell?", 3000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Cosmetic Azure Manashaper Channel (turn blue, channel arcane) (40 silver)", GOSSIP_SENDER_MAIN, A_Cosmetic_Azure_Manashaper_Channel, "Are you sure you wish to purchase this spell?", 4000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Cosmetic Teleport Effect (40 silver)", GOSSIP_SENDER_MAIN, A_Cosmetic_Teleport_Effect, "Are you sure you wish to purchase this spell?", 4000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Evil Teleport Visual Only (20 silver)", GOSSIP_SENDER_MAIN, A_Evil_Teleport_Visual_Only, "Are you sure you wish to purchase this spell?", 2000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Evocation Visual Only (20 silver)", GOSSIP_SENDER_MAIN, A_Evocation_Visual_Only, "Are you sure you wish to purchase this spell?", 2000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Wyrmrest Arcane Beam (40 silver)", GOSSIP_SENDER_MAIN, A_Wyrmrest_Arcane_Beam, "Are you sure you wish to purchase this spell?", 4000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Arcane Channeling Effect (20 silver)", GOSSIP_SENDER_MAIN, A_Arcane_Channeling_Effect, "Are you sure you wish to purchase this spell?", 2000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Arcane Channeling (25 silver)", GOSSIP_SENDER_MAIN, A_Arcane_Channeling, "Are you sure you wish to purchase this spell?", 2500, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Cosmetic Arcane Shield (30 silver)", GOSSIP_SENDER_MAIN, A_Cosmetic_Arcane_Shield, "Are you sure you wish to purchase this spell?", 3000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Proximity Mine Visual (100 silver)", GOSSIP_SENDER_MAIN, A_Proximity_Mine_Visual, "Are you sure you wish to purchase this spell?", 10000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Ethereal Ring (100 silver)", GOSSIP_SENDER_MAIN, A_Ethereal_Ring, "Are you sure you wish to purchase this spell?", 10000, false);
                    //player->ADD_GOSSIP_ITEM(10, "Evocation Visual Only", GOSSIP_SENDER_MAIN, A_Evocation_Visual_Only);

                    player->PlayerTalkClass->SendGossipMenu(724008, item->GetGUID());

                    break;
                case DarkNShadow:
                    player->ADD_GOSSIP_ITEM(10, "Back", GOSSIP_SENDER_MAIN, ON_GOSSIP_HELLO);

                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Dark Ritual Channel (20 silver)", GOSSIP_SENDER_MAIN, DS_Dark_Ritual_Channel, "Are you sure you wish to purchase this spell?", 2000, false);
                    //player->ADD_GOSSIP_ITEM(10, "Destroy Soul (Dark Holy Nova)", GOSSIP_SENDER_MAIN, DS_Destroy_Soul);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Dispersion (20 silver)", GOSSIP_SENDER_MAIN, DS_Dispersion, "Are you sure you wish to purchase this spell?", 2000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Entropius Cosmetic Spawn (ball of shadow, expands) (30 silver)", GOSSIP_SENDER_MAIN, DS_Entropius_Cosmetic_Spawn, "Are you sure you wish to purchase this spell?", 3000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Power Ball Visual (40 silver)", GOSSIP_SENDER_MAIN, DS_Power_Ball_Visual, "Are you sure you wish to purchase this spell?", 4000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Bloodmyst Dark Channeling (35 silver)", GOSSIP_SENDER_MAIN, DS_Bloodmyst_Channeling, "Are you sure you wish to purchase this spell?", 3500, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Wave Beam (30 silver)", GOSSIP_SENDER_MAIN, DS_Wave_Beam, "Are you sure you wish to purchase this spell?", 3000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Blackfathom Channeling (20 silver)", GOSSIP_SENDER_MAIN, DS_Blackfathom_Channeling, "Are you sure you wish to purchase this spell?", 2000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Shadow Channeling (20 silver)", GOSSIP_SENDER_MAIN, DS_Shadow_Channeling, "Are you sure you wish to purchase this spell?", 2000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Flash Feathery Explosion Visual (100 silver)", GOSSIP_SENDER_MAIN, DS_Feathery_Explosion, "Are you sure you wish to purchase this spell?", 10000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Heart Beam Visual (50 silver)", GOSSIP_SENDER_MAIN, DS_Heart_Beam, "Are you sure you wish to purchase this spell?", 5000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Fel Crystal Cosmetic (20 silver)", GOSSIP_SENDER_MAIN, DS_Fel_Crystal, "Are you sure you wish to purchase this spell?", 2000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Sphere Visual (Purple) (50 silver)", GOSSIP_SENDER_MAIN, DS_Sphere_Purple, "Are you sure you wish to purchase this spell?", 5000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Troll Food Poisoning (30 silver)", GOSSIP_SENDER_MAIN, DS_Food_Poisoning, "Are you sure you wish to purchase this spell?", 3000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Captured Animal Feed Visual (20 silver)", GOSSIP_SENDER_MAIN, DS_Animal_Feed, "Are you sure you wish to purchase this spell?", 2000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Raise Dead (50 silver)", GOSSIP_SENDER_MAIN, DS_Raise_Dead, "Are you sure you wish to purchase this spell?", 5000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Soul Separation (30 silver)", GOSSIP_SENDER_MAIN, DS_Soul_Separation, "Are you sure you wish to purchase this spell?", 3000, false);

                    player->PlayerTalkClass->SendGossipMenu(724008, item->GetGUID());

                    break;

                case Fire:

                    player->ADD_GOSSIP_ITEM(10, "Back", GOSSIP_SENDER_MAIN, ON_GOSSIP_HELLO);

                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Bombing Run (30 silver)", GOSSIP_SENDER_MAIN, F_Bombing_Run, "Are you sure you wish to purchase this spell?", 3000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Cosmetic New Fire Beam Channel (Mouth) (turn red, channel flame) (50 silver)", GOSSIP_SENDER_MAIN, F_Cosmetic_New_Fire_Beam_Channel, "Are you sure you wish to purchase this spell?", 5000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Hellfire Warder Channel Visual (channel flames, red rune circles) (30 silver)", GOSSIP_SENDER_MAIN, F_Hellfire_Warder_Channel_Visual, "Are you sure you wish to purchase this spell?", 3000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Fire Channeling (20 silver)", GOSSIP_SENDER_MAIN, F_Fire_Channeling, "Are you sure you wish to purchase this spell?", 2000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Fire Channeling (Option Two) (20 silver)", GOSSIP_SENDER_MAIN, F_Fire_Channeling_Two, "Are you sure you wish to purchase this spell?", 2000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Twin Waves (Fireball) (40 silver)", GOSSIP_SENDER_MAIN, F_Twin_Waves, "Are you sure you wish to purchase this spell?", 4000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Split Four Ways (Fireball) (40 silver)", GOSSIP_SENDER_MAIN, F_Split_Four_Ways, "Are you sure you wish to purchase this spell?", 4000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Burning Felguard Spawn (25 silver)", GOSSIP_SENDER_MAIN, F_Burning_Felguard_Spawn, "Are you sure you wish to purchase this spell?", 2500, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Red Wyrmrest Beam (100 silver)", GOSSIP_SENDER_MAIN, F_Red_Wyrmrest_Beam, "Are you sure you wish to purchase this spell?", 10000, false);

                    player->PlayerTalkClass->SendGossipMenu(724008, item->GetGUID());
                    break;

                case IceNWater:

                    player->ADD_GOSSIP_ITEM(10, "Back", GOSSIP_SENDER_MAIN, ON_GOSSIP_HELLO);

                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Crystal Spike Pre Visual (50 silver)", GOSSIP_SENDER_MAIN, IW_Crystal_Spike_Pre_Visual, "Are you sure you wish to purchase this spell?", 5000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Ice Spear Visual (20 silver)", GOSSIP_SENDER_MAIN, IW_Ice_Spear_Visual, "Are you sure you wish to purchase this spell?", 2000, false);
                    //player->ADD_GOSSIP_ITEM(10, "Frostbolt Volley", GOSSIP_SENDER_MAIN, IW_Frostbolt_Volley);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Pure Water (burst of water, demon sommuning effect) (20 silver)", GOSSIP_SENDER_MAIN, IW_Pure_Water, "Are you sure you wish to purchase this spell?", 2000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Frost Channeling (20 silver)", GOSSIP_SENDER_MAIN, IW_Frost_Channeling, "Are you sure you wish to purchase this spell?", 2000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Frost Channeling (Option Two) (30 silver)", GOSSIP_SENDER_MAIN, IW_Frost_Channeling_Two, "Are you sure you wish to purchase this spell?", 3000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Cone of Cold (30 silver)", GOSSIP_SENDER_MAIN, IW_Cone_Cold, "Are you sure you wish to purchase this spell?", 3000, false);

                    player->PlayerTalkClass->SendGossipMenu(724008, item->GetGUID());
                    break;
                case HolyLightNDivine:
                    player->ADD_GOSSIP_ITEM(10, "Back", GOSSIP_SENDER_MAIN, ON_GOSSIP_HELLO);

                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Holy Zone Visual (50 silver)", GOSSIP_SENDER_MAIN, HLD_Holy_Zone_Visual, "Are you sure you wish to purchase this spell?", 5000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Speak! (holy bolt) (20 silver)", GOSSIP_SENDER_MAIN, HLD_Speak, "Are you sure you wish to purchase this spell?", 2000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Holy Channeling (20 silver)", GOSSIP_SENDER_MAIN, HLD_Holy_Channeling_Two, "Are you sure you wish to purchase this spell?", 2000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Sacred Shield Visual (30 silver)", GOSSIP_SENDER_MAIN, HLD_Sacred_Shield, "Are you sure you wish to purchase this spell?", 3000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Sphere Visual (Blue) (50 silver)", GOSSIP_SENDER_MAIN, HLD_Sphere_Visual, "Are you sure you wish to purchase this spell?", 5000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Bronze Wyrmrest Beam (100 silver)", GOSSIP_SENDER_MAIN, HLD_Bronze_Wyrmrest_Beam, "Are you sure you wish to purchase this spell?", 10000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Hammer of the Righteous (30 silver)", GOSSIP_SENDER_MAIN, HLD_Hammer_Righteous, "Are you sure you wish to purchase this spell?", 3000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Random Lightning Visual Effect (40 silver)", GOSSIP_SENDER_MAIN, HLD_Lightning_Visual, "Are you sure you wish to purchase this spell?", 4000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Summon Holy Mount Visual (30 silver)", GOSSIP_SENDER_MAIN, HLD_Summon_Holy_Mount_Visual, "Are you sure you wish to purchase this spell?", 3000, false);

                    //player->ADD_GOSSIP_ITEM(10, "Sprinkle Holy Water (25 silver)", GOSSIP_SENDER_MAIN, HLD_Sprinkle_Holy_Water);

                    player->PlayerTalkClass->SendGossipMenu(724008, item->GetGUID());
                    break;
                case Nature:
                    player->ADD_GOSSIP_ITEM(10, "Back", GOSSIP_SENDER_MAIN, ON_GOSSIP_HELLO);

                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Nature Channeling (20 silver)", GOSSIP_SENDER_MAIN, N_Nature_Channeling, "Are you sure you wish to purchase this spell?", 2000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Nature Channeling (Option Two) (20 silver)", GOSSIP_SENDER_MAIN, N_Nature_Channeling_Two, "Are you sure you wish to purchase this spell?", 2000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Green Wyrmrest Beam (100 silver)", GOSSIP_SENDER_MAIN, N_Green_Wyrmrest_Beam, "Are you sure you wish to purchase this spell?", 10000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Morthis Tranquility Channel (70 silver)", GOSSIP_SENDER_MAIN, N_Morthis_Tranquility, "Are you sure you wish to purchase this spell?", 7000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Nature Wave (50 silver)", GOSSIP_SENDER_MAIN, N_Nature_Wave, "Are you sure you wish to purchase this spell?", 5000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Noblegarden Bunny Visual (20 silver)", GOSSIP_SENDER_MAIN, N_Noblegarden_Bunny, "Are you sure you wish to purchase this spell?", 2000, false);


                    player->PlayerTalkClass->SendGossipMenu(724008, item->GetGUID());
                    break;
                case ElementalNShaman:
                    player->ADD_GOSSIP_ITEM(10, "Back", GOSSIP_SENDER_MAIN, ON_GOSSIP_HELLO);

                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Earth Explosion (30 silver)", GOSSIP_SENDER_MAIN, ES_Earth_Explosion, "Are you sure you wish to purchase this spell?", 3000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Cosmetic Call Lightning (20 silver)", GOSSIP_SENDER_MAIN, ES_Call_Lightning, "Are you sure you wish to purchase this spell?", 2000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Fire Visual (30 silver)", GOSSIP_SENDER_MAIN, ES_Fire_Visual, "Are you sure you wish to purchase this spell?", 3000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Twisted Visage Death Visual (20 silver)", GOSSIP_SENDER_MAIN, ES_Death_Visual, "Are you sure you wish to purchase this spell?", 2000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Boom Visual (50 silver)", GOSSIP_SENDER_MAIN, ES_Boom_Visual, "Are you sure you wish to purchase this spell?", 5000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Water Elemental Impact Visual (15 silver)", GOSSIP_SENDER_MAIN, ES_Water_Elemental_Visual, "Are you sure you wish to purchase this spell?", 1500, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Cyclone Fall (30 silver)", GOSSIP_SENDER_MAIN, ES_Cyclone_Fall, "Are you sure you wish to purchase this spell?", 3000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Sandstorm (70 silver)", GOSSIP_SENDER_MAIN, ES_Sandstorm, "Are you sure you wish to purchase this spell?", 7000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Boomerang Lightning Bolt (15 silver)", GOSSIP_SENDER_MAIN, ES_Boomerang_Lightning_Bolt, "Are you sure you wish to purchase this spell?", 1500, false);

                    player->PlayerTalkClass->SendGossipMenu(724008, item->GetGUID());
                    break;

                case ArmorNProficiencies:
                    player->ADD_GOSSIP_ITEM(10, "Back", GOSSIP_SENDER_MAIN, ON_GOSSIP_HELLO);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Leather (20 silver)", GOSSIP_SENDER_MAIN, AP_Leather, "Are you sure you wish to purchase this spell?", 2000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Mail (30 silver)", GOSSIP_SENDER_MAIN, AP_Mail, "Are you sure you wish to purchase this spell?", 3000, false);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Plate (40 silver)", GOSSIP_SENDER_MAIN, AP_Plate, "Are you sure you wish to purchase this spell?", 4000, false);

                    player->PlayerTalkClass->SendGossipMenu(724008, item->GetGUID());
                    break;
                case ItemRequest:
                    player->ADD_GOSSIP_ITEM(10, "Back", GOSSIP_SENDER_MAIN, ON_GOSSIP_HELLO);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Common & Junk", GOSSIP_SENDER_MAIN, IR_Common, "Item ID", 0, true);
                    player->ADD_GOSSIP_ITEM_EXTENDED(10, "Uncommon (Green)", GOSSIP_SENDER_MAIN, IR_Uncommon, "Item ID", 0, true);
                case AA_Weapon_Swing:
                    if (!CheckHasEnough(player, 20))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 20, AA_Weapon_Swing);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                    /*
                       case AA_Combat_Stance:
                       if (!CheckHasEnough(player, 1))
                       {
                       player->PlayerTalkClass->SendCloseGossip();
                       return false;
                       }
                       TryLearnSpell(player, 1, AA_Combat_Stance);
                       player->PlayerTalkClass->SendCloseGossip();
                       break;
                       */
                case AA_Kick:
                    if (!CheckHasEnough(player, 20))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 20, AA_Kick);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case AA_Punch:
                    if (!CheckHasEnough(player, 20))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 20, AA_Punch);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case AA_Hold_Rifle:
                    if (!CheckHasEnough(player, 20))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 20, AA_Hold_Rifle);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case AA_Man_Down:
                    if (!CheckHasEnough(player, 30))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 30, AA_Man_Down);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case AA_Run_Away:
                    if (!CheckHasEnough(player, 30))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 30, AA_Run_Away);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case AA_Shield_Block:
                    if (!CheckHasEnough(player, 20))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 20, AA_Shield_Block);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case AA_Throw_Javelin:
                    if (!CheckHasEnough(player, 15))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 15, AA_Throw_Javelin);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case AA_Chop_Tree:
                    if (!CheckHasEnough(player, 10))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 10, AA_Chop_Tree);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case AA_Apollo_Leash:
                    if (!CheckHasEnough(player, 15))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 15, AA_Apollo_Leash);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case AA_Cosmetic_Enchant_Cast:
                    if (!CheckHasEnough(player, 15))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 15, AA_Cosmetic_Enchant_Cast);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;

                    /* End Animations and Actions */

                case A_Arcane_Explosion_Visual:
                    if (!CheckHasEnough(player, 30))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 30, A_Arcane_Explosion_Visual);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case A_Cosmetic_Azure_Manashaper_Channel:
                    if (!CheckHasEnough(player, 40))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 40, A_Cosmetic_Azure_Manashaper_Channel);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case A_Cosmetic_Teleport_Effect:
                    if (!CheckHasEnough(player, 40))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 40, A_Cosmetic_Teleport_Effect);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case A_Evil_Teleport_Visual_Only:
                    if (!CheckHasEnough(player, 20))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 20, A_Evil_Teleport_Visual_Only);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case A_Wyrmrest_Arcane_Beam:
                    if (!CheckHasEnough(player, 40))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 40, A_Wyrmrest_Arcane_Beam);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case A_Arcane_Channeling_Effect:
                    if (!CheckHasEnough(player, 20))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 20, A_Arcane_Channeling_Effect);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case A_Arcane_Channeling:
                    if (!CheckHasEnough(player, 25))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 25, A_Arcane_Channeling);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case A_Cosmetic_Arcane_Shield:
                    if (!CheckHasEnough(player, 30))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 30, A_Cosmetic_Arcane_Shield);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case A_Proximity_Mine_Visual:
                    if (!CheckHasEnough(player, 100))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 100, A_Proximity_Mine_Visual);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case A_Ethereal_Ring:
                    if (!CheckHasEnough(player, 100))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 100, A_Ethereal_Ring);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;

                    /* End Arcane */

                case DS_Dark_Ritual_Channel:
                    if (!CheckHasEnough(player, 20))
                        return true;
                    TryLearnSpell(player, 20, DS_Dark_Ritual_Channel);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                    /*case DS_Destroy_Soul:
                      if (!CheckHasEnough(player, 10))
                      return true;
                      TryLearnSpell(player, 10, DS_Destroy_Soul);
                      player->PlayerTalkClass->SendCloseGossip();
                      break; */
                case DS_Dispersion:
                    if (!CheckHasEnough(player, 20))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 20, DS_Dispersion);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case DS_Entropius_Cosmetic_Spawn:
                    if (!CheckHasEnough(player, 30))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 30, DS_Entropius_Cosmetic_Spawn);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case DS_Power_Ball_Visual:
                    if (!CheckHasEnough(player, 40))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 40, DS_Power_Ball_Visual);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case DS_Bloodmyst_Channeling:
                    if (!CheckHasEnough(player, 35))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 35, DS_Bloodmyst_Channeling);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case DS_Wave_Beam:
                    if (!CheckHasEnough(player, 30))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 30, DS_Wave_Beam);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case DS_Blackfathom_Channeling:
                    if (!CheckHasEnough(player, 20))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 20, DS_Blackfathom_Channeling);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case DS_Shadow_Channeling:
                    if (!CheckHasEnough(player, 20))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 20, DS_Shadow_Channeling);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case DS_Feathery_Explosion:
                    if (!CheckHasEnough(player, 100))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 100, DS_Feathery_Explosion);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case DS_Heart_Beam:
                    if (!CheckHasEnough(player, 50))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 50, DS_Heart_Beam);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case DS_Fel_Crystal:
                    if (!CheckHasEnough(player, 20))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 20, DS_Fel_Crystal);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case DS_Sphere_Purple:
                    if (!CheckHasEnough(player, 50))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 50, DS_Sphere_Purple);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case DS_Food_Poisoning:
                    if (!CheckHasEnough(player, 30))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 30, DS_Food_Poisoning);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case DS_Animal_Feed:
                    if (!CheckHasEnough(player, 20))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 20, DS_Animal_Feed);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case DS_Raise_Dead:
                    if (!CheckHasEnough(player, 50))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 50, DS_Raise_Dead);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case DS_Soul_Separation:
                    if (!CheckHasEnough(player, 30))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 30, DS_Soul_Separation);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;

                    /* End Dark and Shadow */

                case F_Bombing_Run:
                    if (!CheckHasEnough(player, 30))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 30, F_Bombing_Run);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case F_Cosmetic_New_Fire_Beam_Channel:
                    if (!CheckHasEnough(player, 50))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 50, F_Cosmetic_New_Fire_Beam_Channel);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case F_Hellfire_Warder_Channel_Visual:
                    if (!CheckHasEnough(player, 30))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 30, F_Hellfire_Warder_Channel_Visual);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case F_Fire_Channeling:
                    if (!CheckHasEnough(player, 20))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 20, F_Fire_Channeling);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case F_Fire_Channeling_Two:
                    if (!CheckHasEnough(player, 20))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 20, F_Fire_Channeling_Two);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case F_Twin_Waves:
                    if (!CheckHasEnough(player, 40))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 40, F_Twin_Waves);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case F_Split_Four_Ways:
                    if (!CheckHasEnough(player, 40))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 40, F_Split_Four_Ways);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case F_Burning_Felguard_Spawn:
                    if (!CheckHasEnough(player, 25))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 25, F_Burning_Felguard_Spawn);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case F_Red_Wyrmrest_Beam:
                    if (!CheckHasEnough(player, 100))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 100, F_Red_Wyrmrest_Beam);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;

                    /* End Fire */

                case IW_Crystal_Spike_Pre_Visual:
                    if (!CheckHasEnough(player, 50))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 50, IW_Crystal_Spike_Pre_Visual);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case IW_Ice_Spear_Visual:
                    if (!CheckHasEnough(player, 20))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 20, IW_Ice_Spear_Visual);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case IW_Pure_Water:
                    if (!CheckHasEnough(player, 20))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 20, IW_Pure_Water);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case IW_Frost_Channeling:
                    if (!CheckHasEnough(player, 20))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 20, IW_Frost_Channeling);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case IW_Frost_Channeling_Two:
                    if (!CheckHasEnough(player, 30))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 30, IW_Frost_Channeling_Two);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case IW_Cone_Cold:
                    if (!CheckHasEnough(player, 30))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 30, IW_Cone_Cold);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;

                    /* End Ice and Water */

                case HLD_Holy_Zone_Visual:
                    if (!CheckHasEnough(player, 50))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 50, HLD_Holy_Zone_Visual);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case HLD_Speak:
                    if (!CheckHasEnough(player, 20))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 20, HLD_Speak);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case HLD_Holy_Channeling_Two:
                    if (!CheckHasEnough(player, 20))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 20, HLD_Holy_Channeling_Two);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case HLD_Sacred_Shield:
                    if (!CheckHasEnough(player, 30))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 30, HLD_Sacred_Shield);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case HLD_Sphere_Visual:
                    if (!CheckHasEnough(player, 50))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 50, HLD_Sphere_Visual);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case HLD_Bronze_Wyrmrest_Beam:
                    if (!CheckHasEnough(player, 100))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 100, HLD_Bronze_Wyrmrest_Beam);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case HLD_Hammer_Righteous:
                    if (!CheckHasEnough(player, 30))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 30, HLD_Hammer_Righteous);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case HLD_Lightning_Visual:
                    if (!CheckHasEnough(player, 40))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 40, HLD_Lightning_Visual);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case HLD_Summon_Holy_Mount_Visual:
                    if (!CheckHasEnough(player, 30))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 30, HLD_Summon_Holy_Mount_Visual);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;

                    /* End Holy Light and Divine */

                case N_Nature_Channeling:
                    if (!CheckHasEnough(player, 20))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 20, N_Nature_Channeling);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case N_Nature_Channeling_Two:
                    if (!CheckHasEnough(player, 20))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 20, N_Nature_Channeling_Two);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case N_Green_Wyrmrest_Beam:
                    if (!CheckHasEnough(player, 100))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 100, N_Green_Wyrmrest_Beam);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case N_Morthis_Tranquility:
                    if (!CheckHasEnough(player, 70))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 70, N_Morthis_Tranquility);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case N_Nature_Wave:
                    if (!CheckHasEnough(player, 50))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 50, N_Nature_Wave);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case N_Noblegarden_Bunny:
                    if (!CheckHasEnough(player, 20))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 20, N_Noblegarden_Bunny);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;

                    /* End Nature */

                case ES_Earth_Explosion:
                    if (!CheckHasEnough(player, 30))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 30, ES_Earth_Explosion);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case ES_Call_Lightning:
                    if (!CheckHasEnough(player, 20))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 20, ES_Call_Lightning);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case ES_Fire_Visual:
                    if (!CheckHasEnough(player, 30))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 30, ES_Fire_Visual);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case ES_Death_Visual:
                    if (!CheckHasEnough(player, 20))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 20, ES_Death_Visual);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case ES_Boom_Visual:
                    if (!CheckHasEnough(player, 50))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 50, ES_Boom_Visual);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case ES_Water_Elemental_Visual:
                    if (!CheckHasEnough(player, 15))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 15, ES_Water_Elemental_Visual);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case ES_Cyclone_Fall:
                    if (!CheckHasEnough(player, 30))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 30, ES_Cyclone_Fall);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case ES_Sandstorm:
                    if (!CheckHasEnough(player, 70))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 70, ES_Sandstorm);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case ES_Boomerang_Lightning_Bolt:
                    if (!CheckHasEnough(player, 15))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 15, ES_Boomerang_Lightning_Bolt);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;

                    /* End Elemental and Shaman */

                case AP_Leather:
                    if (!CheckHasEnough(player, 20))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    if (player->HasSkill(AP_Leather_Skill))
                    {
                        ChatHandler(player->GetSession()).SendSysMessage("You already know how to wear leather.");
                    }
                    else
                    {
                        player->SetSkill(AP_Leather_Skill, 1, 1, 1);
                        CharacterDatabase.PQuery("INSERT INTO character_upt_skills VALUES (%u, %u, %u, %u)", player->GetGUIDLow(), AP_Leather_Skill, 1, 1);
                        CharacterDatabase.PQuery("INSERT INTO upt_purchases VALUES ('skill', %u, %u)", AP_Leather_Skill, player->GetGUIDLow());
                        player->DestroyItemCount(SilverCoin, 20, true);
                    }
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case AP_Mail:
                    if (!CheckHasEnough(player, 30))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 30, AP_Mail_Spell, AP_Mail_Skill, 2);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case AP_Plate:
                    if (!CheckHasEnough(player, 40))
                    {
                        player->PlayerTalkClass->SendCloseGossip();
                        return false;
                    }
                    TryLearnSpell(player, 40, AP_Plate_Spell, AP_Plate_Skill, 2);
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
            }

            return true;
        }


        bool CheckHasEnough(Player* player, uint32 cost)
        {
            if (player->HasItemCount(SilverCoin, cost))
                return true;
            else
            {
                ChatHandler(player->GetSession()).SendSysMessage("You do not have enough coins.");
                return false;
            }
        }

        void TryLearnSpell(Player* player, uint32 cost, uint32 spell, uint32 skill = 0, uint8 type = 1)
        {
            ChatHandler handler = ChatHandler(player->GetSession());
            if (player->HasSpell(spell))
            {
                if (skill)
                {
                    if (player->HasSkill(skill))
                    {
                        handler.SendSysMessage("You already own the spell and skill.");
                    }
                    else
                    {
                        switch (type)
                        {
                            case 1: // weapon skills
                                {
                                    player->SetSkill(skill, 1, 400, 400);
                                    CharacterDatabase.PQuery("INSERT INTO character_upt_skills VALUES (%u, %u, %u, %u)", player->GetGUIDLow(), skill, 400, 400);
                                    break;
                                }
                            case 2: // proficiencies
                                {
                                    player->SetSkill(skill, 1, 1, 1);
                                    CharacterDatabase.PQuery("INSERT INTO character_upt_skills VALUES (%u, %u, %u, %u)", player->GetGUIDLow(), skill, 1, 1);
                                }
                            case 3: //language
                                {
                                    player->SetSkill(skill, 1, 300, 300);
                                    CharacterDatabase.PQuery("INSERT INTO character_upt_skills VALUES (%u, %u, %u, %u)", player->GetGUIDLow(), skill, 300, 300);
                                }
                        }
                        player->DestroyItemCount(SilverCoin, cost, true);
                        CharacterDatabase.PQuery("INSERT INTO upt_purchases VALUES ('skill', %u, %u)", skill, player->GetGUIDLow());
                    }
                }
                else
                {
                    handler.SendSysMessage("You already own the spell.");
                }
            }
            else if (skill)
            {
                if (!player->HasSkill(skill))
                {
                    switch (type)
                    {
                        case 1: // weapon skills
                            {
                                player->SetSkill(skill, 1, 400, 400);
                                CharacterDatabase.PQuery("INSERT INTO character_upt_skills VALUES (%u, %u, %u, %u)", player->GetGUIDLow(), skill, 400, 400);
                                break;
                            }
                        case 2: // proficiencies
                            {
                                player->SetSkill(skill, 1, 1, 1);
                                CharacterDatabase.PQuery("INSERT INTO character_upt_skills VALUES (%u, %u, %u, %u)", player->GetGUIDLow(), skill, 1, 1);
                            }
                        case 3: //language
                            {
                                player->SetSkill(skill, 1, 300, 300);
                                CharacterDatabase.PQuery("INSERT INTO character_upt_skills VALUES (%u, %u, %u, %u)", player->GetGUIDLow(), skill, 300, 300);
                            }
                    }
                    CharacterDatabase.PQuery("INSERT INTO upt_purchases VALUES ('skill', %u, %u)", skill, player->GetGUIDLow());
                }

                player->LearnSpell(spell, false);
                player->DestroyItemCount(SilverCoin, cost, true);
                CharacterDatabase.PQuery("INSERT INTO upt_purchases VALUES ('spell', %u, %u)", spell, player->GetGUIDLow());
            }
            else
            {
                player->LearnSpell(spell, false);
                player->DestroyItemCount(SilverCoin, cost, true);
                CharacterDatabase.PQuery("INSERT INTO upt_purchases VALUES ('spell', %u, %u)", spell, player->GetGUIDLow());
            }
        }
};

void AddSC_upt()
{
    new item_script_upt();
}


