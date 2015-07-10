/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptLoader.h"
#include "World.h"

// spells
void AddSC_deathknight_spell_scripts();
void AddSC_druid_spell_scripts();
void AddSC_generic_spell_scripts();
void AddSC_hunter_spell_scripts();
void AddSC_mage_spell_scripts();
void AddSC_paladin_spell_scripts();
void AddSC_priest_spell_scripts();
void AddSC_rogue_spell_scripts();
void AddSC_shaman_spell_scripts();
void AddSC_warlock_spell_scripts();
void AddSC_warrior_spell_scripts();
void AddSC_quest_spell_scripts();
void AddSC_item_spell_scripts();
void AddSC_holiday_spell_scripts();

void AddSC_SmartScripts();

//Commands
void AddSC_account_commandscript();
void AddSC_achievement_commandscript();
void AddSC_ahbot_commandscript();
void AddSC_arena_commandscript();
void AddSC_ban_commandscript();
void AddSC_bf_commandscript();
void AddSC_cast_commandscript();
void AddSC_character_commandscript();
void AddSC_cheat_commandscript();
void AddSC_debug_commandscript();
void AddSC_deserter_commandscript();
void AddSC_disable_commandscript();
void AddSC_event_commandscript();
void AddSC_gm_commandscript();
void AddSC_go_commandscript();
void AddSC_gobject_commandscript();
void AddSC_group_commandscript();
void AddSC_guild_commandscript();
void AddSC_honor_commandscript();
void AddSC_instance_commandscript();
void AddSC_learn_commandscript();
void AddSC_lfg_commandscript();
void AddSC_list_commandscript();
void AddSC_lookup_commandscript();
void AddSC_message_commandscript();
void AddSC_misc_commandscript();
void AddSC_mmaps_commandscript();
void AddSC_modify_commandscript();
void AddSC_npc_commandscript();
void AddSC_pet_commandscript();
void AddSC_quest_commandscript();
void AddSC_rbac_commandscript();
void AddSC_reload_commandscript();
void AddSC_reset_commandscript();
void AddSC_send_commandscript();
void AddSC_server_commandscript();
void AddSC_tele_commandscript();
void AddSC_ticket_commandscript();
void AddSC_titles_commandscript();
void AddSC_wp_commandscript();

#ifdef SCRIPTS
//world
void AddSC_areatrigger_scripts();
void AddSC_emerald_dragons();
void AddSC_generic_creature();
void AddSC_go_scripts();
void AddSC_guards();
void AddSC_item_scripts();
void AddSC_npc_professions();
void AddSC_npc_innkeeper();
void AddSC_npcs_special();
void AddSC_npc_taxi();
void AddSC_achievement_scripts();
void AddSC_action_ip_logger();

//eastern kingdoms
void AddSC_alterac_valley();                 //Alterac Valley
//void ADDSC_boss_balinda();
//void ADDSC_boss_drekthar();
//void ADDSC_boss_galvangar();
//void ADDSC_boss_vanndar();
void AddSC_blackrock_depths();               //Blackrock Depths
//void ADDSC_boss_ambassador_flamelash();
//void ADDSC_boss_anubshiah();
//void ADDSC_boss_draganthaurissan();
//void ADDSC_boss_general_angerforge();
//void ADDSC_boss_gorosh_the_dervish();
//void ADDSC_boss_grizzle();
//void ADDSC_boss_high_interrogator_gerstahn();
//void ADDSC_boss_magmus();
//void ADDSC_boss_moira_bronzebeard();
//void ADDSC_boss_tomb_of_seven();
void AddSC_instance_blackrock_depths();
//void ADDSC_boss_drakkisath();                //Blackrock Spire
//void ADDSC_boss_halycon();
//void ADDSC_boss_highlordomokk();
//void ADDSC_boss_mothersmolderweb();
//void ADDSC_boss_overlordwyrmthalak();
//void ADDSC_boss_shadowvosh();
//void ADDSC_boss_thebeast();
//void ADDSC_boss_warmastervoone();
//void ADDSC_boss_quatermasterzigris();
//void ADDSC_boss_pyroguard_emberseer();
//void ADDSC_boss_gyth();
//void ADDSC_boss_rend_blackhand();
//void ADDSC_boss_gizrul_the_slavener();
//void ADDSC_boss_urok_doomhowl();
//void ADDSC_boss_lord_valthalak();
void AddSC_instance_blackrock_spire();
//void ADDSC_boss_razorgore();                 //Blackwing lair
//void ADDSC_boss_vaelastrasz();
//void ADDSC_boss_broodlord();
//void ADDSC_boss_firemaw();
//void ADDSC_boss_ebonroc();
//void ADDSC_boss_flamegor();
//void ADDSC_boss_chromaggus();
//void ADDSC_boss_nefarian();
void AddSC_instance_blackwing_lair();
void AddSC_deadmines();                      //Deadmines
void AddSC_instance_deadmines();
//void ADDSC_boss_mr_smite();
void AddSC_gnomeregan();                     //Gnomeregan
void AddSC_instance_gnomeregan();
//void ADDSC_boss_attumen();                   //Karazhan
//void ADDSC_boss_curator();
//void ADDSC_boss_maiden_of_virtue();
//void ADDSC_boss_shade_of_aran();
//void ADDSC_boss_malchezaar();
//void ADDSC_boss_terestian_illhoof();
//void ADDSC_boss_moroes();
//void ADDSC_bosses_opera();
//void ADDSC_boss_netherspite();
void AddSC_instance_karazhan();
void AddSC_karazhan();
//void ADDSC_boss_nightbane();
//void ADDSC_boss_felblood_kaelthas();         // Magister's Terrace
//void ADDSC_boss_selin_fireheart();
//void ADDSC_boss_vexallus();
//void ADDSC_boss_priestess_delrissa();
void AddSC_instance_magisters_terrace();
void AddSC_magisters_terrace();
//void ADDSC_boss_lucifron();                  //Molten core
//void ADDSC_boss_magmadar();
//void ADDSC_boss_gehennas();
//void ADDSC_boss_garr();
//void ADDSC_boss_baron_geddon();
//void ADDSC_boss_shazzrah();
//void ADDSC_boss_golemagg();
//void ADDSC_boss_sulfuron();
//void ADDSC_boss_majordomo();
//void ADDSC_boss_ragnaros();
void AddSC_instance_molten_core();
void AddSC_instance_ragefire_chasm();        //Ragefire Chasm
void AddSC_the_scarlet_enclave();            //Scarlet Enclave
void AddSC_the_scarlet_enclave_c1();
void AddSC_the_scarlet_enclave_c2();
void AddSC_the_scarlet_enclave_c5();
//void ADDSC_boss_arcanist_doan();             //Scarlet Monastery
//void ADDSC_boss_azshir_the_sleepless();
//void ADDSC_boss_bloodmage_thalnos();
//void ADDSC_boss_headless_horseman();
//void ADDSC_boss_herod();
//void ADDSC_boss_high_inquisitor_fairbanks();
//void ADDSC_boss_houndmaster_loksey();
//void ADDSC_boss_interrogator_vishas();
//void ADDSC_boss_scorn();
void AddSC_instance_scarlet_monastery();
//void ADDSC_boss_mograine_and_whitemane();
//void ADDSC_boss_darkmaster_gandling();       //Scholomance
//void ADDSC_boss_death_knight_darkreaver();
//void ADDSC_boss_theolenkrastinov();
//void ADDSC_boss_illuciabarov();
//void ADDSC_boss_instructormalicia();
//void ADDSC_boss_jandicebarov();
//void ADDSC_boss_kormok();
//void ADDSC_boss_lordalexeibarov();
//void ADDSC_boss_lorekeeperpolkelt();
//void ADDSC_boss_rasfrost();
//void ADDSC_boss_theravenian();
//void ADDSC_boss_vectus();
//void ADDSC_boss_kirtonos_the_herald();
void AddSC_instance_scholomance();
void AddSC_shadowfang_keep();                //Shadowfang keep
void AddSC_instance_shadowfang_keep();
//void ADDSC_boss_magistrate_barthilas();      //Stratholme
//void ADDSC_boss_maleki_the_pallid();
//void ADDSC_boss_nerubenkan();
//void ADDSC_boss_cannon_master_willey();
//void ADDSC_boss_baroness_anastari();
//void ADDSC_boss_ramstein_the_gorger();
//void ADDSC_boss_timmy_the_cruel();
//void ADDSC_boss_postmaster_malown();
//void ADDSC_boss_baron_rivendare();
//void ADDSC_boss_dathrohan_balnazzar();
//void ADDSC_boss_order_of_silver_hand();
void AddSC_instance_stratholme();
void AddSC_stratholme();
void AddSC_sunken_temple();                  // Sunken Temple
void AddSC_instance_sunken_temple();
void AddSC_instance_sunwell_plateau();       //Sunwell Plateau
//void ADDSC_boss_kalecgos();
//void ADDSC_boss_brutallus();
//void ADDSC_boss_felmyst();
//void ADDSC_boss_eredar_twins();
//void ADDSC_boss_muru();
//void ADDSC_boss_kiljaeden();
void AddSC_sunwell_plateau();
//void ADDSC_boss_archaedas();                 //Uldaman
//void ADDSC_boss_ironaya();
void AddSC_uldaman();
void AddSC_instance_uldaman();
void AddSC_instance_the_stockade();          //The Stockade
//void ADDSC_boss_akilzon();                   //Zul'Aman
//void ADDSC_boss_halazzi();
//void ADDSC_boss_hex_lord_malacrass();
//void ADDSC_boss_janalai();
//void ADDSC_boss_nalorakk();
//void ADDSC_boss_zuljin();
void AddSC_instance_zulaman();
void AddSC_zulaman();
//void ADDSC_boss_jeklik();                    //Zul'Gurub
//void ADDSC_boss_venoxis();
//void ADDSC_boss_marli();
//void ADDSC_boss_mandokir();
//void ADDSC_boss_gahzranka();
//void ADDSC_boss_thekal();
//void ADDSC_boss_arlokk();
//void ADDSC_boss_jindo();
//void ADDSC_boss_hakkar();
//void ADDSC_boss_grilek();
//void ADDSC_boss_hazzarah();
//void ADDSC_boss_renataki();
//void ADDSC_boss_wushoolay();
void AddSC_instance_zulgurub();

//void AddSC_alterac_mountains();
void AddSC_arathi_highlands();
void AddSC_blasted_lands();
void AddSC_burning_steppes();
void AddSC_duskwood();
void AddSC_eastern_plaguelands();
void AddSC_ghostlands();
void AddSC_hinterlands();
void AddSC_isle_of_queldanas();
void AddSC_loch_modan();
void AddSC_redridge_mountains();
void AddSC_silverpine_forest();
void AddSC_stormwind_city();
void AddSC_stranglethorn_vale();
void AddSC_swamp_of_sorrows();
void AddSC_tirisfal_glades();
void AddSC_undercity();
void AddSC_western_plaguelands();
void AddSC_wetlands();

//kalimdor
void AddSC_blackfathom_deeps();              //Blackfathom Depths
//void ADDSC_boss_gelihast();
//void ADDSC_boss_kelris();
//void ADDSC_boss_aku_mai();
void AddSC_instance_blackfathom_deeps();
void AddSC_hyjal();                          //CoT Battle for Mt. Hyjal
//void ADDSC_boss_archimonde();
void AddSC_instance_mount_hyjal();
void AddSC_hyjal_trash();
//void ADDSC_boss_rage_winterchill();
//void ADDSC_boss_anetheron();
//void ADDSC_boss_kazrogal();
//void ADDSC_boss_azgalor();
//void ADDSC_boss_captain_skarloc();           //CoT Old Hillsbrad
//void ADDSC_boss_epoch_hunter();
//void ADDSC_boss_lieutenant_drake();
void AddSC_instance_old_hillsbrad();
void AddSC_old_hillsbrad();
//void ADDSC_boss_aeonus();                    //CoT The Black Morass
//void ADDSC_boss_chrono_lord_deja();
//void ADDSC_boss_temporus();
void AddSC_the_black_morass();
void AddSC_instance_the_black_morass();
//void ADDSC_boss_epoch();                     //CoT Culling Of Stratholme
//void ADDSC_boss_infinite_corruptor();
//void ADDSC_boss_salramm();
//void ADDSC_boss_mal_ganis();
//void ADDSC_boss_meathook();
void AddSC_culling_of_stratholme();
void AddSC_instance_culling_of_stratholme();
void AddSC_instance_dire_maul();             //Dire Maul
//void ADDSC_boss_celebras_the_cursed();       //Maraudon
//void ADDSC_boss_landslide();
//void ADDSC_boss_noxxion();
//void ADDSC_boss_ptheradras();
void AddSC_instance_maraudon();
//void ADDSC_boss_onyxia();                    //Onyxia's Lair
void AddSC_instance_onyxias_lair();
//void ADDSC_boss_tuten_kash();                 //Razorfen Downs
//void ADDSC_boss_mordresh_fire_eye();
//void ADDSC_boss_glutton();
//void ADDSC_boss_amnennar_the_coldbringer();
void AddSC_razorfen_downs();
void AddSC_instance_razorfen_downs();
void AddSC_razorfen_kraul();                 //Razorfen Kraul
void AddSC_instance_razorfen_kraul();
//void ADDSC_boss_kurinnaxx();                 //Ruins of ahn'qiraj
//void ADDSC_boss_rajaxx();
//void ADDSC_boss_moam();
//void ADDSC_boss_buru();
//void ADDSC_boss_ayamiss();
//void ADDSC_boss_ossirian();
void AddSC_instance_ruins_of_ahnqiraj();
//void ADDSC_boss_cthun();                     //Temple of ahn'qiraj
//void ADDSC_boss_viscidus();
//void ADDSC_boss_fankriss();
//void ADDSC_boss_huhuran();
void AddSC_bug_trio();
//void ADDSC_boss_sartura();
//void ADDSC_boss_skeram();
//void ADDSC_boss_twinemperors();
//void ADDSC_boss_ouro();
void AddSC_npc_anubisath_sentinel();
void AddSC_instance_temple_of_ahnqiraj();
void AddSC_wailing_caverns();                //Wailing caverns
void AddSC_instance_wailing_caverns();
//void ADDSC_boss_zum_rah();                   //Zul'Farrak
void AddSC_zulfarrak();
void AddSC_instance_zulfarrak();

void AddSC_ashenvale();
void AddSC_azshara();
void AddSC_azuremyst_isle();
void AddSC_bloodmyst_isle();
//void ADDSC_boss_azuregos();
void AddSC_darkshore();
void AddSC_desolace();
void AddSC_durotar();
void AddSC_dustwallow_marsh();
void AddSC_felwood();
void AddSC_feralas();
void AddSC_moonglade();
void AddSC_mulgore();
void AddSC_orgrimmar();
void AddSC_silithus();
void AddSC_stonetalon_mountains();
void AddSC_tanaris();
void AddSC_teldrassil();
void AddSC_the_barrens();
void AddSC_thousand_needles();
void AddSC_thunder_bluff();
void AddSC_ungoro_crater();
void AddSC_winterspring();

// Northrend

//void ADDSC_boss_slad_ran();
//void ADDSC_boss_moorabi();
//void ADDSC_boss_drakkari_colossus();
//void ADDSC_boss_gal_darah();
//void ADDSC_boss_eck();
void AddSC_instance_gundrak();

// Azjol-Nerub - Azjol-Nerub
//void ADDSC_boss_krik_thir();
//void ADDSC_boss_hadronox();
//void ADDSC_boss_anub_arak();
void AddSC_instance_azjol_nerub();

// Azjol-Nerub - Ahn'kahet
//void ADDSC_boss_elder_nadox();
//void ADDSC_boss_taldaram();
//void ADDSC_boss_amanitar();
//void ADDSC_boss_jedoga_shadowseeker();
//void ADDSC_boss_volazj();
void AddSC_instance_ahnkahet();

// Drak'Tharon Keep
//void ADDSC_boss_trollgore();
//void ADDSC_boss_novos();
//void ADDSC_boss_king_dred();
//void ADDSC_boss_tharon_ja();
void AddSC_instance_drak_tharon_keep();

//void ADDSC_boss_argent_challenge();      //Trial of the Champion
//void ADDSC_boss_black_knight();
//void ADDSC_boss_grand_champions();
void AddSC_instance_trial_of_the_champion();
void AddSC_trial_of_the_champion();
//void ADDSC_boss_anubarak_trial();        //Trial of the Crusader
//void ADDSC_boss_faction_champions();
//void ADDSC_boss_jaraxxus();
//void ADDSC_boss_northrend_beasts();
//void ADDSC_boss_twin_valkyr();
void AddSC_trial_of_the_crusader();
void AddSC_instance_trial_of_the_crusader();
//void ADDSC_boss_anubrekhan();            //Naxxramas
//void ADDSC_boss_maexxna();
//void ADDSC_boss_patchwerk();
//void ADDSC_boss_grobbulus();
//void ADDSC_boss_razuvious();
//void ADDSC_boss_kelthuzad();
//void ADDSC_boss_loatheb();
//void ADDSC_boss_noth();
//void ADDSC_boss_gluth();
//void ADDSC_boss_sapphiron();
//void ADDSC_boss_four_horsemen();
//void ADDSC_boss_faerlina();
//void ADDSC_boss_heigan();
//void ADDSC_boss_gothik();
//void ADDSC_boss_thaddius();
void AddSC_instance_naxxramas();
//void ADDSC_boss_magus_telestra();        //The Nexus Nexus
//void ADDSC_boss_anomalus();
//void ADDSC_boss_ormorok();
//void ADDSC_boss_keristrasza();
void AddSC_instance_nexus();
//void ADDSC_boss_drakos();                //The Nexus The Oculus
//void ADDSC_boss_urom();
//void ADDSC_boss_varos();
//void ADDSC_boss_eregos();
void AddSC_instance_oculus();
void AddSC_oculus();
//void ADDSC_boss_malygos();              // The Nexus: Eye of Eternity
void AddSC_instance_eye_of_eternity();
//void ADDSC_boss_sartharion();            //Obsidian Sanctum
void AddSC_obsidian_sanctum();
void AddSC_instance_obsidian_sanctum();
//void ADDSC_boss_bjarngrim();             //Ulduar Halls of Lightning
//void ADDSC_boss_loken();
//void ADDSC_boss_ionar();
//void ADDSC_boss_volkhan();
void AddSC_instance_halls_of_lightning();
//void ADDSC_boss_maiden_of_grief();       //Ulduar Halls of Stone
//void ADDSC_boss_krystallus();
//void ADDSC_boss_sjonnir();
void AddSC_instance_halls_of_stone();
void AddSC_halls_of_stone();
//void ADDSC_boss_auriaya();               //Ulduar Ulduar
//void ADDSC_boss_flame_leviathan();
//void ADDSC_boss_ignis();
//void ADDSC_boss_razorscale();
//void ADDSC_boss_xt002();
//void ADDSC_boss_kologarn();
//void ADDSC_boss_assembly_of_iron();
//void ADDSC_boss_general_vezax();
//void ADDSC_boss_mimiron();
//void ADDSC_boss_hodir();
//void ADDSC_boss_freya();
//void ADDSC_boss_yogg_saron();
//void ADDSC_boss_algalon_the_observer();
void AddSC_instance_ulduar();

// Utgarde Keep - Utgarde Keep
//void ADDSC_boss_keleseth();
//void ADDSC_boss_skarvald_dalronn();
//void ADDSC_boss_ingvar_the_plunderer();
void AddSC_instance_utgarde_keep();
void AddSC_utgarde_keep();

// Utgarde Keep - Utgarde Pinnacle
//void ADDSC_boss_svala();
//void ADDSC_boss_palehoof();
//void ADDSC_boss_skadi();
//void ADDSC_boss_ymiron();
void AddSC_instance_utgarde_pinnacle();

// Vault of Archavon
//void ADDSC_boss_archavon();
//void ADDSC_boss_emalon();
//void ADDSC_boss_koralon();
//void ADDSC_boss_toravon();
void AddSC_instance_vault_of_archavon();

//void ADDSC_boss_cyanigosa();             //Violet Hold
//void ADDSC_boss_erekem();
//void ADDSC_boss_ichoron();
//void ADDSC_boss_lavanthor();
//void ADDSC_boss_moragg();
//void ADDSC_boss_xevozz();
//void ADDSC_boss_zuramat();
void AddSC_instance_violet_hold();
void AddSC_violet_hold();
void AddSC_instance_forge_of_souls();   //Forge of Souls
void AddSC_forge_of_souls();
//void ADDSC_boss_bronjahm();
//void ADDSC_boss_devourer_of_souls();
void AddSC_instance_pit_of_saron();     //Pit of Saron
void AddSC_pit_of_saron();
//void ADDSC_boss_garfrost();
//void ADDSC_boss_ick();
//void ADDSC_boss_tyrannus();
void AddSC_instance_halls_of_reflection();   // Halls of Reflection
void AddSC_halls_of_reflection();
//void ADDSC_boss_falric();
//void ADDSC_boss_marwyn();
//void ADDSC_boss_lord_marrowgar();       // Icecrown Citadel
//void ADDSC_boss_lady_deathwhisper();
//void ADDSC_boss_icecrown_gunship_battle();
//void ADDSC_boss_deathbringer_saurfang();
//void ADDSC_boss_festergut();
//void ADDSC_boss_rotface();
//void ADDSC_boss_professor_putricide();
//void ADDSC_boss_blood_prince_council();
//void ADDSC_boss_blood_queen_lana_thel();
//void ADDSC_boss_valithria_dreamwalker();
//void ADDSC_boss_sindragosa();
//void ADDSC_boss_the_lich_king();
void AddSC_icecrown_citadel_teleport();
void AddSC_instance_icecrown_citadel();
void AddSC_icecrown_citadel();
void AddSC_instance_ruby_sanctum();      // Ruby Sanctum
void AddSC_ruby_sanctum();
//void ADDSC_boss_baltharus_the_warborn();
//void ADDSC_boss_saviana_ragefire();
//void ADDSC_boss_general_zarithrian();
//void ADDSC_boss_halion();

void AddSC_dalaran();
void AddSC_borean_tundra();
void AddSC_dragonblight();
void AddSC_grizzly_hills();
void AddSC_howling_fjord();
void AddSC_icecrown();
void AddSC_sholazar_basin();
void AddSC_storm_peaks();
void AddSC_wintergrasp();
void AddSC_zuldrak();
void AddSC_crystalsong_forest();
void AddSC_isle_of_conquest();

// Outland

// Auchindoun - Auchenai Crypts
//void ADDSC_boss_shirrak_the_dead_watcher();
//void ADDSC_boss_exarch_maladaar();
void AddSC_instance_auchenai_crypts();

// Auchindoun - Mana Tombs
//void ADDSC_boss_pandemonius();
//void ADDSC_boss_nexusprince_shaffar();
void AddSC_instance_mana_tombs();

// Auchindoun - Sekketh Halls
//void ADDSC_boss_darkweaver_syth();
//void ADDSC_boss_talon_king_ikiss();
//void ADDSC_boss_anzu();
void AddSC_instance_sethekk_halls();

// Auchindoun - Shadow Labyrinth
//void ADDSC_boss_ambassador_hellmaw();
//void ADDSC_boss_blackheart_the_inciter();
//void ADDSC_boss_grandmaster_vorpil();
//void ADDSC_boss_murmur();
void AddSC_instance_shadow_labyrinth();

// Black Temple
void AddSC_black_temple();
//void ADDSC_boss_illidan();
//void ADDSC_boss_shade_of_akama();
//void ADDSC_boss_supremus();
//void ADDSC_boss_gurtogg_bloodboil();
//void ADDSC_boss_mother_shahraz();
//void ADDSC_boss_reliquary_of_souls();
//void ADDSC_boss_teron_gorefiend();
//void ADDSC_boss_najentus();
//void ADDSC_boss_illidari_council();
void AddSC_instance_black_temple();

// Coilfang Reservoir - Serpent Shrine Cavern
//void ADDSC_boss_fathomlord_karathress();
//void ADDSC_boss_hydross_the_unstable();
//void ADDSC_boss_lady_vashj();
//void ADDSC_boss_leotheras_the_blind();
//void ADDSC_boss_morogrim_tidewalker();
void AddSC_instance_serpentshrine_cavern();
//void ADDSC_boss_the_lurker_below();

// Coilfang Reservoir - The Steam Vault
//void ADDSC_boss_hydromancer_thespia();
//void ADDSC_boss_mekgineer_steamrigger();
//void ADDSC_boss_warlord_kalithresh();
void AddSC_instance_steam_vault();

// Coilfang Reservoir - The Slave Pens
void AddSC_instance_the_slave_pens();
//void ADDSC_boss_mennu_the_betrayer();
//void ADDSC_boss_rokmar_the_crackler();
//void ADDSC_boss_quagmirran();

// Coilfang Reservoir - The Underbog
void AddSC_instance_the_underbog();
//void ADDSC_boss_hungarfen();
//void ADDSC_boss_the_black_stalker();

// Gruul's Lair
//void ADDSC_boss_gruul();
//void ADDSC_boss_high_king_maulgar();
void AddSC_instance_gruuls_lair();
//void ADDSC_boss_broggok();                   //HC Blood Furnace
//void ADDSC_boss_kelidan_the_breaker();
//void ADDSC_boss_the_maker();
void AddSC_instance_blood_furnace();
//void ADDSC_boss_magtheridon();               //HC Magtheridon's Lair
void AddSC_instance_magtheridons_lair();
//void ADDSC_boss_grand_warlock_nethekurse();  //HC Shattered Halls
//void ADDSC_boss_warbringer_omrogg();
//void ADDSC_boss_warchief_kargath_bladefist();
void AddSC_instance_shattered_halls();
//void ADDSC_boss_watchkeeper_gargolmar();     //HC Ramparts
//void ADDSC_boss_omor_the_unscarred();
//void ADDSC_boss_vazruden_the_herald();
void AddSC_instance_ramparts();
void AddSC_arcatraz();                       //TK Arcatraz
//void ADDSC_boss_zereketh_the_unbound();
//void ADDSC_boss_dalliah_the_doomsayer();
//void ADDSC_boss_wrath_scryer_soccothrates();
//void ADDSC_boss_harbinger_skyriss();
void AddSC_instance_arcatraz();
//void ADDSC_boss_high_botanist_freywinn();    //TK Botanica
//void ADDSC_boss_laj();
//void ADDSC_boss_warp_splinter();
//void ADDSC_boss_thorngrin_the_tender();
//void ADDSC_boss_commander_sarannis();
void AddSC_instance_the_botanica();
//void ADDSC_boss_alar();                      //TK The Eye
//void ADDSC_boss_kaelthas();
//void ADDSC_boss_void_reaver();
//void ADDSC_boss_high_astromancer_solarian();
void AddSC_instance_the_eye();
void AddSC_the_eye();
//void ADDSC_boss_gatewatcher_iron_hand();     //TK The Mechanar
//void ADDSC_boss_gatewatcher_gyrokill();
//void ADDSC_boss_nethermancer_sepethrea();
//void ADDSC_boss_pathaleon_the_calculator();
//void ADDSC_boss_mechano_lord_capacitus();
void AddSC_instance_mechanar();

void AddSC_blades_edge_mountains();
//void ADDSC_boss_doomlordkazzak();
//void ADDSC_boss_doomwalker();
void AddSC_hellfire_peninsula();
void AddSC_nagrand();
void AddSC_netherstorm();
void AddSC_shadowmoon_valley();
void AddSC_shattrath_city();
void AddSC_terokkar_forest();
void AddSC_zangarmarsh();

// Events
void AddSC_event_childrens_week();

// Pets
void AddSC_deathknight_pet_scripts();
void AddSC_generic_pet_scripts();
void AddSC_hunter_pet_scripts();
void AddSC_mage_pet_scripts();
void AddSC_priest_pet_scripts();
void AddSC_shaman_pet_scripts();

// battlegrounds

// outdoor pvp
void AddSC_outdoorpvp_ep();
void AddSC_outdoorpvp_hp();
void AddSC_outdoorpvp_na();
void AddSC_outdoorpvp_si();
void AddSC_outdoorpvp_tf();
void AddSC_outdoorpvp_zm();

// player
void AddSC_chat_log();
void AddSC_action_ip_logger();

#endif

void AddScripts()
{
    AddSpellScripts();
    AddSC_SmartScripts();
    AddCommandScripts();
#ifdef SCRIPTS
    AddWorldScripts();
    AddEasternKingdomsScripts();
    AddKalimdorScripts();
    AddOutlandScripts();
    AddNorthrendScripts();
    AddEventScripts();
    AddPetScripts();
    AddBattlegroundScripts();
    AddOutdoorPvPScripts();
    AddCustomScripts();
#endif
}

void AddSpellScripts()
{
    AddSC_deathknight_spell_scripts();
    AddSC_druid_spell_scripts();
    AddSC_generic_spell_scripts();
    AddSC_hunter_spell_scripts();
    AddSC_mage_spell_scripts();
    AddSC_paladin_spell_scripts();
    AddSC_priest_spell_scripts();
    AddSC_rogue_spell_scripts();
    AddSC_shaman_spell_scripts();
    AddSC_warlock_spell_scripts();
    AddSC_warrior_spell_scripts();
    AddSC_quest_spell_scripts();
    AddSC_item_spell_scripts();
    AddSC_holiday_spell_scripts();
}

void AddCommandScripts()
{
    AddSC_account_commandscript();
    AddSC_achievement_commandscript();
    AddSC_ahbot_commandscript();
    AddSC_arena_commandscript();
    AddSC_ban_commandscript();
    AddSC_bf_commandscript();
    AddSC_cast_commandscript();
    AddSC_character_commandscript();
    AddSC_cheat_commandscript();
    AddSC_debug_commandscript();
    AddSC_deserter_commandscript();
    AddSC_disable_commandscript();
    AddSC_event_commandscript();
    AddSC_gm_commandscript();
    AddSC_go_commandscript();
    AddSC_gobject_commandscript();
    AddSC_group_commandscript();
    AddSC_guild_commandscript();
    AddSC_honor_commandscript();
    AddSC_instance_commandscript();
    AddSC_learn_commandscript();
    AddSC_lookup_commandscript();
    AddSC_lfg_commandscript();
    AddSC_list_commandscript();
    AddSC_message_commandscript();
    AddSC_misc_commandscript();
    AddSC_mmaps_commandscript();
    AddSC_modify_commandscript();
    AddSC_npc_commandscript();
    AddSC_quest_commandscript();
    AddSC_pet_commandscript();
    AddSC_rbac_commandscript();
    AddSC_reload_commandscript();
    AddSC_reset_commandscript();
    AddSC_send_commandscript();
    AddSC_server_commandscript();
    AddSC_tele_commandscript();
    AddSC_ticket_commandscript();
    AddSC_titles_commandscript();
    AddSC_wp_commandscript();
}

void AddWorldScripts()
{
#ifdef SCRIPTS
    AddSC_areatrigger_scripts();
    AddSC_emerald_dragons();
    AddSC_generic_creature();
    AddSC_go_scripts();
    AddSC_guards();
    AddSC_item_scripts();
    AddSC_npc_professions();
    AddSC_npc_innkeeper();
    AddSC_npcs_special();
    AddSC_npc_taxi();
    AddSC_achievement_scripts();
    AddSC_chat_log(); // location: scripts\World\chat_log.cpp
    // To avoid duplicate code, we check once /*ONLY*/ if logging is permitted or not.
    if (sWorld->getBoolConfig(CONFIG_IP_BASED_ACTION_LOGGING))
        AddSC_action_ip_logger(); // location: scripts\World\action_ip_logger.cpp
#endif
}

void AddEasternKingdomsScripts()
{
#ifdef SCRIPTS
    AddSC_alterac_valley();                 //Alterac Valley
    //ADDSC_boss_balinda();
    //ADDSC_boss_drekthar();
    //ADDSC_boss_galvangar();
    //ADDSC_boss_vanndar();
    AddSC_blackrock_depths();               //Blackrock Depths
    //ADDSC_boss_ambassador_flamelash();
    //ADDSC_boss_anubshiah();
    //ADDSC_boss_draganthaurissan();
    //ADDSC_boss_general_angerforge();
    //ADDSC_boss_gorosh_the_dervish();
    //ADDSC_boss_grizzle();
    //ADDSC_boss_high_interrogator_gerstahn();
    //ADDSC_boss_magmus();
    //ADDSC_boss_moira_bronzebeard();
    //ADDSC_boss_tomb_of_seven();
    AddSC_instance_blackrock_depths();
    //ADDSC_boss_drakkisath();                //Blackrock Spire
    //ADDSC_boss_halycon();
  //ADDSC_boss_highlordomokk();
  //ADDSC_boss_mothersmolderweb();
  //ADDSC_boss_overlordwyrmthalak();
  //ADDSC_boss_shadowvosh();
  //ADDSC_boss_thebeast();
  //ADDSC_boss_warmastervoone();
  //ADDSC_boss_quatermasterzigris();
  //ADDSC_boss_pyroguard_emberseer();
  //ADDSC_boss_gyth();
  //ADDSC_boss_rend_blackhand();
  //ADDSC_boss_gizrul_the_slavener();
  //ADDSC_boss_urok_doomhowl();
  //ADDSC_boss_lord_valthalak();
    AddSC_instance_blackrock_spire();
  //ADDSC_boss_razorgore();                 //Blackwing lair
  //ADDSC_boss_vaelastrasz();
  //ADDSC_boss_broodlord();
  //ADDSC_boss_firemaw();
  //ADDSC_boss_ebonroc();
  //ADDSC_boss_flamegor();
  //ADDSC_boss_chromaggus();
  //ADDSC_boss_nefarian();
    AddSC_instance_blackwing_lair();
    AddSC_deadmines();                      //Deadmines
  //ADDSC_boss_mr_smite();
    AddSC_instance_deadmines();
    AddSC_gnomeregan();                     //Gnomeregan
    AddSC_instance_gnomeregan();
  //ADDSC_boss_attumen();                   //Karazhan
  //ADDSC_boss_curator();
  //ADDSC_boss_maiden_of_virtue();
  //ADDSC_boss_shade_of_aran();
  //ADDSC_boss_malchezaar();
  //ADDSC_boss_terestian_illhoof();
  //ADDSC_boss_moroes();
  //ADDSC_bosses_opera();
  //ADDSC_boss_netherspite();
    AddSC_instance_karazhan();
    AddSC_karazhan();
  //ADDSC_boss_nightbane();
  //ADDSC_boss_felblood_kaelthas();         // Magister's Terrace
  //ADDSC_boss_selin_fireheart();
  //ADDSC_boss_vexallus();
  //ADDSC_boss_priestess_delrissa();
    AddSC_instance_magisters_terrace();
    AddSC_magisters_terrace();
  //ADDSC_boss_lucifron();                  //Molten core
  //ADDSC_boss_magmadar();
  //ADDSC_boss_gehennas();
  //ADDSC_boss_garr();
  //ADDSC_boss_baron_geddon();
  //ADDSC_boss_shazzrah();
  //ADDSC_boss_golemagg();
  //ADDSC_boss_sulfuron();
  //ADDSC_boss_majordomo();
  //ADDSC_boss_ragnaros();
    AddSC_instance_molten_core();
    AddSC_instance_ragefire_chasm();        //Ragefire Chasm
    AddSC_the_scarlet_enclave();            //Scarlet Enclave
    AddSC_the_scarlet_enclave_c1();
    AddSC_the_scarlet_enclave_c2();
    AddSC_the_scarlet_enclave_c5();
  //ADDSC_boss_arcanist_doan();             //Scarlet Monastery
  //ADDSC_boss_azshir_the_sleepless();
  //ADDSC_boss_bloodmage_thalnos();
  //ADDSC_boss_headless_horseman();
  //ADDSC_boss_herod();
  //ADDSC_boss_high_inquisitor_fairbanks();
  //ADDSC_boss_houndmaster_loksey();
  //ADDSC_boss_interrogator_vishas();
  //ADDSC_boss_scorn();
    AddSC_instance_scarlet_monastery();
  //ADDSC_boss_mograine_and_whitemane();
  //ADDSC_boss_darkmaster_gandling();       //Scholomance
  //ADDSC_boss_death_knight_darkreaver();
  //ADDSC_boss_theolenkrastinov();
  //ADDSC_boss_illuciabarov();
  //ADDSC_boss_instructormalicia();
  //ADDSC_boss_jandicebarov();
  //ADDSC_boss_kormok();
  //ADDSC_boss_lordalexeibarov();
  //ADDSC_boss_lorekeeperpolkelt();
  //ADDSC_boss_rasfrost();
  //ADDSC_boss_theravenian();
  //ADDSC_boss_vectus();
  //ADDSC_boss_kirtonos_the_herald();
    AddSC_instance_scholomance();
    AddSC_shadowfang_keep();                //Shadowfang keep
    AddSC_instance_shadowfang_keep();
  //ADDSC_boss_magistrate_barthilas();      //Stratholme
  //ADDSC_boss_maleki_the_pallid();
  //ADDSC_boss_nerubenkan();
  //ADDSC_boss_cannon_master_willey();
  //ADDSC_boss_baroness_anastari();
  //ADDSC_boss_ramstein_the_gorger();
  //ADDSC_boss_timmy_the_cruel();
  //ADDSC_boss_postmaster_malown();
  //ADDSC_boss_baron_rivendare();
  //ADDSC_boss_dathrohan_balnazzar();
  //ADDSC_boss_order_of_silver_hand();
    AddSC_instance_stratholme();
    AddSC_stratholme();
    AddSC_sunken_temple();                  // Sunken Temple
    AddSC_instance_sunken_temple();
    AddSC_instance_sunwell_plateau();       //Sunwell Plateau
  //ADDSC_boss_kalecgos();
  //ADDSC_boss_brutallus();
  //ADDSC_boss_felmyst();
  //ADDSC_boss_eredar_twins();
  //ADDSC_boss_muru();
  //ADDSC_boss_kiljaeden();
    AddSC_sunwell_plateau();
    AddSC_instance_the_stockade();          //The Stockade
  //ADDSC_boss_archaedas();                 //Uldaman
  //ADDSC_boss_ironaya();
    AddSC_uldaman();
    AddSC_instance_uldaman();
  //ADDSC_boss_akilzon();                   //Zul'Aman
  //ADDSC_boss_halazzi();
  //ADDSC_boss_hex_lord_malacrass();
  //ADDSC_boss_janalai();
  //ADDSC_boss_nalorakk();
  //ADDSC_boss_zuljin();
    AddSC_instance_zulaman();
    AddSC_zulaman();
  //ADDSC_boss_jeklik();                    //Zul'Gurub
  //ADDSC_boss_venoxis();
  //ADDSC_boss_marli();
  //ADDSC_boss_mandokir();
  //ADDSC_boss_gahzranka();
  //ADDSC_boss_thekal();
  //ADDSC_boss_arlokk();
  //ADDSC_boss_jindo();
  //ADDSC_boss_hakkar();
  //ADDSC_boss_grilek();
  //ADDSC_boss_hazzarah();
  //ADDSC_boss_renataki();
  //ADDSC_boss_wushoolay();
    AddSC_instance_zulgurub();

    //AddSC_alterac_mountains();
    AddSC_arathi_highlands();
    AddSC_blasted_lands();
    AddSC_burning_steppes();
    AddSC_duskwood();
    AddSC_eastern_plaguelands();
    AddSC_ghostlands();
    AddSC_hinterlands();
    AddSC_isle_of_queldanas();
    AddSC_loch_modan();
    AddSC_redridge_mountains();
    AddSC_silverpine_forest();
    AddSC_stormwind_city();
    AddSC_stranglethorn_vale();
    AddSC_swamp_of_sorrows();
    AddSC_tirisfal_glades();
    AddSC_undercity();
    AddSC_western_plaguelands();
    AddSC_wetlands();
#endif
}

void AddKalimdorScripts()
{
#ifdef SCRIPTS
    AddSC_blackfathom_deeps();              //Blackfathom Depths
  //ADDSC_boss_gelihast();
  //ADDSC_boss_kelris();
  //ADDSC_boss_aku_mai();
    AddSC_instance_blackfathom_deeps();
    AddSC_hyjal();                          //CoT Battle for Mt. Hyjal
  //ADDSC_boss_archimonde();
    AddSC_instance_mount_hyjal();
    AddSC_hyjal_trash();
  //ADDSC_boss_rage_winterchill();
  //ADDSC_boss_anetheron();
  //ADDSC_boss_kazrogal();
  //ADDSC_boss_azgalor();
  //ADDSC_boss_captain_skarloc();           //CoT Old Hillsbrad
  //ADDSC_boss_epoch_hunter();
  //ADDSC_boss_lieutenant_drake();
    AddSC_instance_old_hillsbrad();
    AddSC_old_hillsbrad();
  //ADDSC_boss_aeonus();                    //CoT The Black Morass
  //ADDSC_boss_chrono_lord_deja();
  //ADDSC_boss_temporus();
    AddSC_the_black_morass();
    AddSC_instance_the_black_morass();
  //ADDSC_boss_epoch();                     //CoT Culling Of Stratholme
  //ADDSC_boss_infinite_corruptor();
  //ADDSC_boss_salramm();
  //ADDSC_boss_mal_ganis();
  //ADDSC_boss_meathook();
    AddSC_culling_of_stratholme();
    AddSC_instance_culling_of_stratholme();
    AddSC_instance_dire_maul();             //Dire Maul
  //ADDSC_boss_celebras_the_cursed();       //Maraudon
  //ADDSC_boss_landslide();
  //ADDSC_boss_noxxion();
  //ADDSC_boss_ptheradras();
    AddSC_instance_maraudon();
  //ADDSC_boss_onyxia();                    //Onyxia's Lair
    AddSC_instance_onyxias_lair();
  //ADDSC_boss_tuten_kash();                //Razorfen Downs
  //ADDSC_boss_mordresh_fire_eye();
  //ADDSC_boss_glutton();
  //ADDSC_boss_amnennar_the_coldbringer();
    AddSC_razorfen_downs();
    AddSC_instance_razorfen_downs();
    AddSC_razorfen_kraul();                 //Razorfen Kraul
    AddSC_instance_razorfen_kraul();
  //ADDSC_boss_kurinnaxx();                 //Ruins of ahn'qiraj
  //ADDSC_boss_rajaxx();
  //ADDSC_boss_moam();
  //ADDSC_boss_buru();
  //ADDSC_boss_ayamiss();
  //ADDSC_boss_ossirian();
    AddSC_instance_ruins_of_ahnqiraj();
  //ADDSC_boss_cthun();                     //Temple of ahn'qiraj
  //ADDSC_boss_viscidus();
  //ADDSC_boss_fankriss();
  //ADDSC_boss_huhuran();
    AddSC_bug_trio();
  //ADDSC_boss_sartura();
  //ADDSC_boss_skeram();
  //ADDSC_boss_twinemperors();
  //ADDSC_boss_ouro();
    AddSC_npc_anubisath_sentinel();
    AddSC_instance_temple_of_ahnqiraj();
    AddSC_wailing_caverns();                //Wailing caverns
    AddSC_instance_wailing_caverns();
  //ADDSC_boss_zum_rah();                   //Zul'Farrak
    AddSC_zulfarrak();
    AddSC_instance_zulfarrak();

    AddSC_ashenvale();
    AddSC_azshara();
    AddSC_azuremyst_isle();
    AddSC_bloodmyst_isle();
  //ADDSC_boss_azuregos();
    AddSC_darkshore();
    AddSC_desolace();
    AddSC_durotar();
    AddSC_dustwallow_marsh();
    AddSC_felwood();
    AddSC_feralas();
    AddSC_moonglade();
    AddSC_mulgore();
    AddSC_orgrimmar();
    AddSC_silithus();
    AddSC_stonetalon_mountains();
    AddSC_tanaris();
    AddSC_teldrassil();
    AddSC_the_barrens();
    AddSC_thousand_needles();
    AddSC_thunder_bluff();
    AddSC_ungoro_crater();
    AddSC_winterspring();
#endif
}

void AddOutlandScripts()
{
#ifdef SCRIPTS
    // Auchindoun - Auchenai Crypts
  //ADDSC_boss_shirrak_the_dead_watcher();
  //ADDSC_boss_exarch_maladaar();
    AddSC_instance_auchenai_crypts();

    // Auchindoun - Mana Tombs
  //ADDSC_boss_pandemonius();
  //ADDSC_boss_nexusprince_shaffar();
    AddSC_instance_mana_tombs();

    // Auchindoun - Sekketh Halls
  //ADDSC_boss_darkweaver_syth();
  //ADDSC_boss_talon_king_ikiss();
  //ADDSC_boss_anzu();
    AddSC_instance_sethekk_halls();

    // Auchindoun - Shadow Labyrinth
  //ADDSC_boss_ambassador_hellmaw();
  //ADDSC_boss_blackheart_the_inciter();
  //ADDSC_boss_grandmaster_vorpil();
  //ADDSC_boss_murmur();
    AddSC_instance_shadow_labyrinth();

    // Black Temple
    AddSC_black_temple();
  //ADDSC_boss_illidan();
  //ADDSC_boss_shade_of_akama();
  //ADDSC_boss_supremus();
  //ADDSC_boss_gurtogg_bloodboil();
  //ADDSC_boss_mother_shahraz();
  //ADDSC_boss_reliquary_of_souls();
  //ADDSC_boss_teron_gorefiend();
  //ADDSC_boss_najentus();
  //ADDSC_boss_illidari_council();
    AddSC_instance_black_temple();

    // Coilfang Reservoir - Serpent Shrine Cavern
  //ADDSC_boss_fathomlord_karathress();
  //ADDSC_boss_hydross_the_unstable();
  //ADDSC_boss_lady_vashj();
  //ADDSC_boss_leotheras_the_blind();
  //ADDSC_boss_morogrim_tidewalker();
    AddSC_instance_serpentshrine_cavern();
  //ADDSC_boss_the_lurker_below();

    // Coilfang Reservoir - The Steam Vault
    AddSC_instance_steam_vault();
  //ADDSC_boss_hydromancer_thespia();
  //ADDSC_boss_mekgineer_steamrigger();
  //ADDSC_boss_warlord_kalithresh();

    // Coilfang Reservoir - The Slave Pens
    AddSC_instance_the_slave_pens();
  //ADDSC_boss_mennu_the_betrayer();
  //ADDSC_boss_rokmar_the_crackler();
  //ADDSC_boss_quagmirran();

    // Coilfang Reservoir - The Underbog
    AddSC_instance_the_underbog();
  //ADDSC_boss_hungarfen();
  //ADDSC_boss_the_black_stalker();

    // Gruul's Lair
  //ADDSC_boss_gruul();
  //ADDSC_boss_high_king_maulgar();
    AddSC_instance_gruuls_lair();
  //ADDSC_boss_broggok();                   //HC Blood Furnace
  //ADDSC_boss_kelidan_the_breaker();
  //ADDSC_boss_the_maker();
    AddSC_instance_blood_furnace();
  //ADDSC_boss_magtheridon();               //HC Magtheridon's Lair
    AddSC_instance_magtheridons_lair();
  //ADDSC_boss_grand_warlock_nethekurse();  //HC Shattered Halls
  //ADDSC_boss_warbringer_omrogg();
  //ADDSC_boss_warchief_kargath_bladefist();
    AddSC_instance_shattered_halls();
  //ADDSC_boss_watchkeeper_gargolmar();     //HC Ramparts
  //ADDSC_boss_omor_the_unscarred();
  //ADDSC_boss_vazruden_the_herald();
    AddSC_instance_ramparts();
    AddSC_arcatraz();                       //TK Arcatraz
  //ADDSC_boss_zereketh_the_unbound();
  //ADDSC_boss_dalliah_the_doomsayer();
  //ADDSC_boss_wrath_scryer_soccothrates();
  //ADDSC_boss_harbinger_skyriss();
    AddSC_instance_arcatraz();
  //ADDSC_boss_high_botanist_freywinn();    //TK Botanica
  //ADDSC_boss_laj();
  //ADDSC_boss_warp_splinter();
  //ADDSC_boss_thorngrin_the_tender();
  //ADDSC_boss_commander_sarannis();
    AddSC_instance_the_botanica();
  //ADDSC_boss_alar();                      //TK The Eye
  //ADDSC_boss_kaelthas();
  //ADDSC_boss_void_reaver();
  //ADDSC_boss_high_astromancer_solarian();
    AddSC_instance_the_eye();
    AddSC_the_eye();
  //ADDSC_boss_gatewatcher_iron_hand();     //TK The Mechanar
  //ADDSC_boss_gatewatcher_gyrokill();
  //ADDSC_boss_nethermancer_sepethrea();
  //ADDSC_boss_pathaleon_the_calculator();
  //ADDSC_boss_mechano_lord_capacitus();
    AddSC_instance_mechanar();

    AddSC_blades_edge_mountains();
  //ADDSC_boss_doomlordkazzak();
  //ADDSC_boss_doomwalker();
    AddSC_hellfire_peninsula();
    AddSC_nagrand();
    AddSC_netherstorm();
    AddSC_shadowmoon_valley();
    AddSC_shattrath_city();
    AddSC_terokkar_forest();
    AddSC_zangarmarsh();
#endif
}

void AddNorthrendScripts()
{
#ifdef SCRIPTS
  //ADDSC_boss_slad_ran();               //Gundrak
  //ADDSC_boss_moorabi();
  //ADDSC_boss_drakkari_colossus();
  //ADDSC_boss_gal_darah();
  //ADDSC_boss_eck();
    AddSC_instance_gundrak();

    // Azjol-Nerub - Ahn'kahet
  //ADDSC_boss_elder_nadox();
  //ADDSC_boss_taldaram();
  //ADDSC_boss_amanitar();
  //ADDSC_boss_jedoga_shadowseeker();
  //ADDSC_boss_volazj();
    AddSC_instance_ahnkahet();

    // Azjol-Nerub - Azjol-Nerub
  //ADDSC_boss_krik_thir();
  //ADDSC_boss_hadronox();
  //ADDSC_boss_anub_arak();
    AddSC_instance_azjol_nerub();

    // Drak'Tharon Keep
  //ADDSC_boss_trollgore();
  //ADDSC_boss_novos();
  //ADDSC_boss_king_dred();
  //ADDSC_boss_tharon_ja();
    AddSC_instance_drak_tharon_keep();

  //ADDSC_boss_argent_challenge();      //Trial of the Champion
  //ADDSC_boss_black_knight();
  //ADDSC_boss_grand_champions();
    AddSC_instance_trial_of_the_champion();
    AddSC_trial_of_the_champion();
  //ADDSC_boss_anubarak_trial();        //Trial of the Crusader
  //ADDSC_boss_faction_champions();
  //ADDSC_boss_jaraxxus();
    AddSC_trial_of_the_crusader();
  //ADDSC_boss_twin_valkyr();
  //ADDSC_boss_northrend_beasts();
    AddSC_instance_trial_of_the_crusader();
  //ADDSC_boss_anubrekhan();            //Naxxramas
  //ADDSC_boss_maexxna();
  //ADDSC_boss_patchwerk();
  //ADDSC_boss_grobbulus();
  //ADDSC_boss_razuvious();
  //ADDSC_boss_kelthuzad();
  //ADDSC_boss_loatheb();
  //ADDSC_boss_noth();
  //ADDSC_boss_gluth();
  //ADDSC_boss_sapphiron();
  //ADDSC_boss_four_horsemen();
  //ADDSC_boss_faerlina();
  //ADDSC_boss_heigan();
  //ADDSC_boss_gothik();
  //ADDSC_boss_thaddius();
    AddSC_instance_naxxramas();
  //ADDSC_boss_magus_telestra();        //The Nexus Nexus
  //ADDSC_boss_anomalus();
  //ADDSC_boss_ormorok();
  //ADDSC_boss_keristrasza();
    AddSC_instance_nexus();
  //ADDSC_boss_drakos();                //The Nexus The Oculus
  //ADDSC_boss_urom();
  //ADDSC_boss_varos();
  //ADDSC_boss_eregos();
    AddSC_instance_oculus();
    AddSC_oculus();
  //ADDSC_boss_malygos();              // The Nexus: Eye of Eternity
    AddSC_instance_eye_of_eternity();
  //ADDSC_boss_sartharion();            //Obsidian Sanctum
    AddSC_obsidian_sanctum();
    AddSC_instance_obsidian_sanctum();
  //ADDSC_boss_bjarngrim();             //Ulduar Halls of Lightning
  //ADDSC_boss_loken();
  //ADDSC_boss_ionar();
  //ADDSC_boss_volkhan();
    AddSC_instance_halls_of_lightning();
  //ADDSC_boss_maiden_of_grief();       //Ulduar Halls of Stone
  //ADDSC_boss_krystallus();
  //ADDSC_boss_sjonnir();
    AddSC_instance_halls_of_stone();
    AddSC_halls_of_stone();
  //ADDSC_boss_auriaya();               //Ulduar Ulduar
  //ADDSC_boss_flame_leviathan();
  //ADDSC_boss_ignis();
  //ADDSC_boss_razorscale();
  //ADDSC_boss_xt002();
  //ADDSC_boss_general_vezax();
  //ADDSC_boss_assembly_of_iron();
  //ADDSC_boss_kologarn();
  //ADDSC_boss_mimiron();
  //ADDSC_boss_hodir();
  //ADDSC_boss_freya();
  //ADDSC_boss_yogg_saron();
  //ADDSC_boss_algalon_the_observer();
    AddSC_instance_ulduar();

    // Utgarde Keep - Utgarde Keep
  //ADDSC_boss_keleseth();
  //ADDSC_boss_skarvald_dalronn();
  //ADDSC_boss_ingvar_the_plunderer();
    AddSC_instance_utgarde_keep();
    AddSC_utgarde_keep();

    // Utgarde Keep - Utgarde Pinnacle
  //ADDSC_boss_svala();
  //ADDSC_boss_palehoof();
  //ADDSC_boss_skadi();
  //ADDSC_boss_ymiron();
    AddSC_instance_utgarde_pinnacle();

    // Vault of Archavon
  //ADDSC_boss_archavon();
  //ADDSC_boss_emalon();
  //ADDSC_boss_koralon();
  //ADDSC_boss_toravon();
    AddSC_instance_vault_of_archavon();

  //ADDSC_boss_cyanigosa();             //Violet Hold
  //ADDSC_boss_erekem();
  //ADDSC_boss_ichoron();
  //ADDSC_boss_lavanthor();
  //ADDSC_boss_moragg();
  //ADDSC_boss_xevozz();
  //ADDSC_boss_zuramat();
    AddSC_instance_violet_hold();
    AddSC_violet_hold();
    AddSC_instance_forge_of_souls();   //Forge of Souls
    AddSC_forge_of_souls();
  //ADDSC_boss_bronjahm();
  //ADDSC_boss_devourer_of_souls();
    AddSC_instance_pit_of_saron();      //Pit of Saron
    AddSC_pit_of_saron();
  //ADDSC_boss_garfrost();
  //ADDSC_boss_ick();
  //ADDSC_boss_tyrannus();
    AddSC_instance_halls_of_reflection();   // Halls of Reflection
    AddSC_halls_of_reflection();
  //ADDSC_boss_falric();
  //ADDSC_boss_marwyn();
  //ADDSC_boss_lord_marrowgar();        // Icecrown Citadel
  //ADDSC_boss_lady_deathwhisper();
  //ADDSC_boss_icecrown_gunship_battle();
  //ADDSC_boss_deathbringer_saurfang();
  //ADDSC_boss_festergut();
  //ADDSC_boss_rotface();
  //ADDSC_boss_professor_putricide();
  //ADDSC_boss_blood_prince_council();
  //ADDSC_boss_blood_queen_lana_thel();
  //ADDSC_boss_valithria_dreamwalker();
  //ADDSC_boss_sindragosa();
  //ADDSC_boss_the_lich_king();
    AddSC_icecrown_citadel_teleport();
    AddSC_instance_icecrown_citadel();
    AddSC_icecrown_citadel();
    AddSC_instance_ruby_sanctum();      // Ruby Sanctum
    AddSC_ruby_sanctum();
  //ADDSC_boss_baltharus_the_warborn();
  //ADDSC_boss_saviana_ragefire();
  //ADDSC_boss_general_zarithrian();
  //ADDSC_boss_halion();

    AddSC_dalaran();
    AddSC_borean_tundra();
    AddSC_dragonblight();
    AddSC_grizzly_hills();
    AddSC_howling_fjord();
    AddSC_icecrown();
    AddSC_sholazar_basin();
    AddSC_storm_peaks();
    AddSC_wintergrasp();
    AddSC_zuldrak();
    AddSC_crystalsong_forest();
    AddSC_isle_of_conquest();
#endif
}

void AddEventScripts()
{
#ifdef SCRIPTS
    AddSC_event_childrens_week();
#endif
}

void AddPetScripts()
{
#ifdef SCRIPTS
    AddSC_deathknight_pet_scripts();
    AddSC_generic_pet_scripts();
    AddSC_hunter_pet_scripts();
    AddSC_mage_pet_scripts();
    AddSC_priest_pet_scripts();
    AddSC_shaman_pet_scripts();
#endif
}

void AddOutdoorPvPScripts()
{
#ifdef SCRIPTS
    AddSC_outdoorpvp_ep();
    AddSC_outdoorpvp_hp();
    AddSC_outdoorpvp_na();
    AddSC_outdoorpvp_si();
    AddSC_outdoorpvp_tf();
    AddSC_outdoorpvp_zm();
#endif
}

void AddBattlegroundScripts()
{
#ifdef SCRIPTS
#endif
}

#ifdef SCRIPTS
/* This is where custom scripts' loading functions should be declared. */
	void AddSC_carpus_script();
	void AddSC_misc();
	void AddSC_cs_legacy();
    void AddSC_galenus();
    void AddSC_apt_system();
    void AddSC_upt();
    void AddSC_grimoire();
    void AddSC_hector();
#endif

void AddCustomScripts()
{
#ifdef SCRIPTS
    /* This is where custom scripts should be added. */
	AddSC_carpus_script();
	AddSC_misc();
	AddSC_cs_legacy();
    AddSC_galenus();
    AddSC_apt_system();
    AddSC_upt();
    AddSC_grimoire();
    AddSC_hector();
#endif
}
