#include "ScriptMgr.h"
#include "TargetedMovementGenerator.h"

class hector_handler : public PlayerScript
{

    public:
        hector_handler() : PlayerScript("hector_handler"){
        }

        void hector_unsummon(Player* player)
        {
 
            player->PlayerTalkClass->SendCloseGossip();

            if(player->getMountPlaced() != NULL)
            {
                player->getMountPlaced()->ToTempSummon()->UnSummon();
                player->setMountPlaced(NULL);
            }
        }

        void OnMount(Player* player)
        {
            hector_unsummon(player);
        }

        void OnDismount(Player* player, uint32 entry)
        {
            QueryResult result =  WorldDatabase.PQuery("SELECT summon_entry FROM mount_template WHERE entry='%u'", entry);

            std::cout << "\n" << entry << "\n";

            if(!result)
                return;

            Field* fields = result->Fetch();


            TempSummon* mount = player->SummonCreature(fields[0].GetUInt32(), player->GetPositionX() + 5, player->GetPositionY() + 5, player->GetPositionZ());

            player->setMountPlaced(mount);
            player->getMountPlaced()->GetMotionMaster()->MoveFollow(player, PET_FOLLOW_DIST, mount->GetFollowAngle());

        }

        void OnLogout(Player* player)
        {
            hector_unsummon(player);
        }
};

class hector : public CreatureScript
{

    public:
        hector() : CreatureScript("hector"){
        }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if(player == creature->ToTempSummon()->GetSummoner())
            {

                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Dismiss", GOSSIP_SENDER_MAIN, 5);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Stay",    GOSSIP_SENDER_MAIN, 10);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Follow",  GOSSIP_SENDER_MAIN, 15);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Check Storage",  GOSSIP_SENDER_MAIN, 20);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Exit",    GOSSIP_SENDER_MAIN, 25);
                player->PlayerTalkClass->SendGossipMenu(1, creature->GetGUID());
            }

            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 actions)
        {

            player->PlayerTalkClass->ClearMenus();

            switch(actions)
            {
                case 5: // dismiss
                    if(player->getMountPlaced() != NULL)
                    {
                        creature->ToTempSummon()->UnSummon();
                        player->setMountPlaced(NULL);
                    }

                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case 10: // stay
                    if(player->getMountPlaced() != NULL)
                    {
                        creature->SetPosition(creature->GetPositionX(), creature->GetPositionY(), creature->GetPositionZ(), creature->GetOrientation());
                        creature->GetMotionMaster()->MovementExpired(true);
                    }
                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case 15: // follow
                    if( player->getMountPlaced() != NULL)
                        creature->GetMotionMaster()->MoveFollow(player, PET_FOLLOW_DIST, creature->GetFollowAngle());

                    player->PlayerTalkClass->SendCloseGossip();
                    break;
                case 20: // check storage
                    player->PlayerTalkClass->SendCloseGossip();
                    player->GetSession()->SendShowBank(player->GetGUID());
                case 25: // exit
                    break;
            }

            player->PlayerTalkClass->SendCloseGossip();
            return true;
        }
};

void AddSC_hector()
{
    new hector();
    new hector_handler();
}
