//
// file: globals.h
//
// This file is #included in all objects automatically by the driver.
// (See config file of driver)

//// #pragma save_binary

// 统一 busy 的返回信息。
#define BUSY_MESSAGE		"你现在忙得很，无法做任何事情。\n"
#define SYS_BUSY		"系统忙碌中……请您稍候……\n"

// 受保护的年龄
#define PROTECT_AGE		16

#define TOPTEN_RICH     "/topten/rich.o"
#define TOPTEN_PKER     "/topten/pker.o"
#define TOPTEN_EXP      "/topten/exp.o"
#define TOPTEN_DAOXING  "/topten/daoxing.o"
#define TOPTEN_SHEN1    "/topten/shen1.o"
#define TOPTEN_SHEN2    "/topten/shen2.o"
#define TOPTEN_neili    "/topten/neili.o"
#define TOPTEN_PER1     "/topten/per1.o"
#define TOPTEN_PER2     "/topten/per2.o"
#define TOPTEN_AGE      "/topten/age.o"
#define TOPTEN_POTENTIAL "/topten/potential.o"
#define RICH_B          "十大富人"
#define PKER_B          "十大恶人"
#define EXP_B           "十大武林高手"
#define DAOXING_B	"十大得道真仙"
#define POTENTIAL_B	"十大潜在高手"
#define SHEN1_B         "十大魔头"
#define SHEN2_B         "十大法力高手"
#define neili_B         "十大内力高手"
#define PER1_B          "十大白马王子"
#define PER2_B          "十大梦中情人"
#define AGE_B           "十大老不死"
#define TOPTEN_D        "/adm/daemons/toptend"

// Directories
#define COMMAND_DIR		"/cmds/"
#define CONFIG_DIR		"/adm/etc/"
#define DATA_DIR		"/data/"
#define HELP_DIR		"/doc/"
#define LOG_DIR			"/log/"
#define BACKUP_DIR      "/backup/"
#define DUMP_DIR		"/backup/"
#define ARCHETYEP_DIR   "/d/obj/archetype/"

// Daemons
#define ALIAS_D			"/adm/daemons/aliasd"
#define CHANNEL_D		"/adm/daemons/channeld"
#define CHAR_D			"/adm/daemons/chard"
#define CHINESE_D		"/adm/daemons/chinesed"
#define COMBAT_D		"/adm/daemons/combatd"
#define COMMAND_D		"/adm/daemons/cmd_d"
#define CONVERT_D		"/adm/daemons/convertd"
#define EMOTE_D			"/adm/daemons/emoted"
#define FINGER_D		"/adm/daemons/fingerd"
#define INQUIRY_D		"/adm/daemons/inquiryd"
#define LOGIN_D			"/adm/daemons/logind"
#define CPU_D       		"/adm/daemons/cpud"
#define MISC_D		  	"/adm/daemons/miscd"
#define MONITOR_D		"/adm/daemons/monitord"
#define NATURE_D		"/adm/daemons/natured"
#define NEWS_D			"/adm/daemons/newsd"
#define NPC_D     		"/adm/daemons/npcd"	//生成npc
#define OBSTACLE_D  		"/adm/daemons/obstacled"
#define PROFILE_D		"/adm/daemons/profiled"
#define RANK_D			"/adm/daemons/rankd"
#define SECURITY_D		"/adm/daemons/securityd"
#define XYJTIME_D   		"/adm/daemons/xyjtimed.c"
#define SPELL_D		  	"/adm/daemons/spelld"
#define MONEY_D     		"/adm/daemons/moneyd"
#define UPDATE_D		"/adm/daemons/updated"
#define VIRTUAL_D		"/adm/daemons/virtuald.c"
#define WEAPON_D		"/adm/daemons/weapond"
#define BAN_D		  	"/adm/daemons/band.c"
#define TASK_D                "/adm/daemons/questd"
#define COLOR_D     		"/adm/daemons/colord"
#define FINANCE_D		"/adm/daemons/finance_d"
#define QUEST_D         	"/adm/daemons/questd"
#define NAME_D	    		"/adm/daemons/named.c"
#define ROBOT_D	    		"/adm/daemons/robotd.c"
#define CODE_D			"/adm/daemons/coded.c"
#define FAMILY_D		"/adm/daemons/familyd.c"
#define REMOVE_D		"/adm/daemons/removed.c"
#define VRM_SERVER		"/adm/daemons/vrm_server.c"
#define MAZE_D			"/adm/daemons/mazed.c"
//add By snowtu 方便以后写任务用的
#define GIFT_D 			"/adm/daemons/giftd.c"
#define COMBINE_D      		"/adm/daemons/combined.c"
#define BJTIME_CMD	        "/cmds/usr/bjtime.c"
#define TITLE_D			"/adm/daemons/titled.c"
#define MOD_D			"/adm/daemons/modd.c"

#define CLASS_D(x)		("/daemon/class/" + x)
#define SKILL_D(x)		("/daemon/skill/" + x)
#define CONDITION_D(x)		("/daemon/condition/" + x)
#define INVOCATION_D(x)		("/obj/npc/" + x) //护法调用的NPC

#define BOOK_OBJ		"/d/obj/book/"
#define WEAPON_DIR		"/d/obj/weapon/"
#define ARMOR_DIR		"/d/obj/armor/"

#define BOOK_OB			"/d/obj/book/"
#define WEAPON_OB		"/d/obj/weapon/"
#define ARMOR_OB		"/d/obj/armor/"

#define WEAPON_OBJ(type,name)	("/d/obj/weapon/"+type+"/"+name)
#define ARMOR_OBJ(type,name)	("/d/obj/armor/"+type+"/"+name)

#define FABAO			"/obj/fabao.c"
#define COIN_OB			"/obj/money/coin"
#define CORPSE_OB		"/obj/corpse"
#define LOGIN_OB		"/obj/login"
#define SIMUL_EFUN_OB		"/adm/obj/simul_efun"
#define MASTER_OB		"/adm/obj/master"
#define MAILBOX_OB		"/obj/mailbox"
#define SILVER_OB		"/obj/money/silver"
#define USER_OB			"/obj/user"
#define VOID_OB			"/obj/void"
#define TEMP_OB			"/obj/tempy"

// Inheritable Standard Objects

#define BANK			"/std/room/bank"
#define SALESROOM		"/std/room/salesroom"
#define HOCKSHOP		"/std/room/hockshop"
#define BULLETIN_BOARD		"/std/bboard"
#define BBS_BOARD		"/std/bbsboard"
#define BOOK			"/std/book"
#define CHARACTER		"/std/char"
#define CLASS_GUILD		"/std/room/class_guild"
#define COMBINED_ITEM		"/std/item/combined"
#define EQUIP			"/std/equip"
#define FORCE			"/std/force"
#define ITEM			"/std/item"
#define LIQUID			"/std/liquid"
#define MONEY			"/std/money"
#define F_MASTER		"/std/char/master.c"
#define NPC			"/std/char/npc"
#define BOSS			"/std/char/boss"
#define NPC_SAVE		"/std/char/npcsave"
#define POWDER			"/std/medicine/powder"
#define QUEST			"/std/quest"
#define ROOM			"/std/room"
#define SKILL			"/std/skill"
#define SSERVER			"/std/sserver"
#define SUPER_NPC		"/std/char/super_npc"
#define HUFA			"/std/char/hufa"
// User IDs
#define ROOT_UID		"Root"
#define BACKBONE_UID		"Backbone"

// Features
#define F_ACTION		"/feature/action.c"
#define F_ALIAS			"/feature/alias.c"
#define F_APPRENTICE		"/feature/apprentice.c"
#define F_ATTACK		"/feature/attack.c"
#define F_ATTRIBUTE		"/feature/attribute.c"
#define F_AUTOLOAD		"/feature/autoload.c"
#define F_CLEAN_UP		"/feature/clean_up.c"
#define F_COMMAND		"/feature/command.c"
#define F_CONDITION		"/feature/condition.c"
#define F_DAMAGE		"/feature/damage.c"
#define F_DBASE			"/feature/dbase.c"
#define F_EDIT			"/feature/edit.c"
#define F_FOOD			"/feature/food.c"
#define F_LIQUID		"/feature/liquid.c"
#define F_ENCODING		"/feature/encoding.c"
#define F_EQUIP			"/feature/equip.c"
#define F_FINANCE		"/feature/finance.c"
#define F_LIQUID		"/feature/liquid.c"
#define F_MESSAGE		"/feature/message.c"
#define F_MORE			"/feature/more.c"
#define F_MOVE			"/feature/move.c"
#define F_NAME			"/feature/name.c"
#define F_ONEOWNER		"/feature/oneowner.c"

#define F_SAVE			"/feature/save.c"
#define F_BACKUP		"/feature/backup.c"
#define F_SKILL			"/feature/skill.c"
#define F_TEAM			"/feature/team.c"
#define F_TREEMAP		"/feature/treemap.c"
#define F_UNIQUE		"/feature/unique.c"
#define F_VENDOR		"/feature/vendor.c"
#define F_VENDOR_SALE		"/feature/vendor_sale.c"


// Profiling switches
//
// If you changed any of these defines, you'll need reboot to make it
// in effect.

#define PROFILE_COMMANDS
#undef PROFILE_COMMANDS
