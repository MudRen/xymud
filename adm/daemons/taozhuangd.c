//套装模块
#include <dbase.h>
#include <ansi.h>
#include <mudlib.h>

inherit F_DBASE;

mapping all_stats = ([
	"attack"	: "命中率",
    "strength"	: "后天体格",
	"courage"       : "后天胆识",
    "intelligence"  : "后天悟性",
    "spirituality"  : "后天灵性",
    "composure"     : "后天定力",
    "personality"   : "后天容貌",
    "constitution"  : "后天根骨",
    "karma"         : "后天福缘",
    "force_recover" : "吸气效果追加",
    "fofce_refresh"	: "凝神效果追加",
    "add_damage2"	: "法术伤害追加",
    "add_damage"	: "物理伤害追加",
    "add_armor"	: "物理防御追加",
    "add_armor2"	: "法术防御追加",
    "redamage_kee_damage" 	  : "气血伤害反弹",
    "redamage_eff_kee_damage" : "气血损失反弹",
    "redamage_sen_damage"	  : "精神伤害反弹",
    "redamage_eff_sen_damage" : "精神损失反弹",
    "receive_curing_kee"	  : "气血治疗追加",
    "receive_heal_kee"	  : "气血恢复追加",
    "receive_curing_sen"	  : "精神治疗追加",
    "receive_heal_sen"	  : "精神恢复追加",
    "add_busy"	: "僵直效果追加",
    "reduce_busy"	: "僵直效果减少率",
    "healup_kee"	: "气血自动恢复",
    "healup_sen"	: "精神自动恢复",
    "healup_force"	: "内力自动恢复",
    "healup_mana"	: "法力自动恢复",
    "cast_succ"		: "法术命中附加",
    "cast_dodge"	: "法术闪避附加",
    "no_cast_redamage" : "抵消法术反弹",
    "cast_redamage" : "法术反弹附加",
    "ad_eff_kee"	: "自动治疗气血",
    "ad_kee"		: "自动恢复气血",
    "ad_eff_sen"	: "自动治疗精神",
    "ad_sen"		: "自动恢复精神",
    "ad_force"		: "自动回复内力",
    "ad_mana"		: "自动回复法力",
]);

void create()
{
        seteuid(getuid());
        message("channel:sys", WHT"┋系统┋套装组合精灵启动。\n"NOR, users());
}
/*
// 根据套装部件和持有部件者打印部件信息
// 应用于look.c
string print_mod_stats(object obj, object owner)
{
	class eqmod mod_stats;
	string modnum, *mod_file, *mod_name, *eq_files, *keys_stats;
	mapping stats;
	int i;
	string msg, str, eq_str;
	
	// 初始化资料
	modnum = obj->query("mod");
	msg = "";
	mod_stats = new(class eqmod);
	// 读取套装资料
	mod_stats = load_one_mod(modnum);
	// 检查合法性
	if (check_one_mod(mod_stats))
	{
		msg = sprintf("╭━━━━━━━━╮\n");
		mod_file = mod_stats->file;
		mod_name = mod_stats->name;
		eq_files = owner->query_temp("modfiles_"+modnum);
		if ( !pointerp(eq_files) )
			eq_files = ({ });
		for (i=0;i<sizeof(mod_file);i++)
		{
			eq_str = "  ";
			if (member_array(mod_file[i], eq_files) != -1)
				eq_str = WHT"√"NOR;
			if (base_name(obj) == mod_file[i])
				if (obj->query_temp("mod_eq"))
					eq_str = HIR"√"NOR;
				else
					eq_str = RED"×"NOR;
			str = sprintf("┃%s%-14s"NOR"┃\n",eq_str, filter_color(mod_name[i]));
			str = replace_string(str, filter_color(mod_name[i]), mod_name[i] );
			msg += str;
		}
		msg += sprintf("╰━━━━━━━━╯\n");
		if ( (int)owner->query_temp("modamount_"+modnum) == sizeof(mod_file) )
			eq_str = HIR;
		else
			eq_str = YEL;
		msg += sprintf(" %-s(%s%d/%d"NOR")\n",
			mod_stats->modname,
			eq_str,
			(int)owner->query_temp("modamount_"+modnum),
			sizeof(mod_file));
		msg += sprintf("%s╭━━━━━━━━╮"NOR"\n", eq_str);
		stats = mod_stats->stats;
		keys_stats = keys(stats);
		for (i=0;i<sizeof(keys_stats);i++)
		{
			if (get_chinese(keys_stats[i]) != "")
			{
				str = sprintf("%4s +%-10d",get_chinese(keys_stats[i]), stats[keys_stats[i]]);
				msg += sprintf("%s┃"NOR"%|16s%s┃"NOR"\n", eq_str, str, eq_str);
			}
		}
		msg += sprintf("%s╰━━━━━━━━╯"NOR"\n", eq_str);
	}
	return msg;
}

// 为属性名称匹配中文
string get_chinese(string stats)
{
	string msg, *keys;
	keys = keys(all_stats);
	if (member_array(stats, keys) != -1)
		msg = all_stats[stats];
	else
		msg = "";
	return msg;
}

// 根据检查一个套装是否合法，即是否存在，如果套装数据还是初始化数据，就是不存在。
int check_one_mod(class eqmod mod_stats)
{
	if( mod_stats->modnum == "" )
		return 0;
	if( mod_stats->modname == "" )
		return 0;
	if( !(sizeof(mod_stats->file)) )
		return 0;
	if( !(sizeof(mod_stats->name)) )
		return 0;
	if( !(mod_stats->stats) )
		return 0;
	return 1;
}

// 根据序号查找套装数据
class eqmod load_one_mod(string modnum)
{
	string filename, this_file;

	object ob;
	class eqmod item;
	string *field, modname, modfile, modstats;
	int i;
	mapping stats;
	string stats_key;
	int stats_value;
	
	item = new(class eqmod);

	// 0001-0999位于"/adm/etc/mod_eq/newbie.mod"
	if ( modnum[0] == '0' && strlen(modnum) == 4)
		filename = MOD_EQ+"newbie.mod";
	
	// 初始化一个空的套装文件
	item->modnum = "";
	item->modname = "";
	item->file = ({});
	item->name = ({});

	// 文件为空。返回空值。
	if(!stringp(filename) || file_size(filename) < 0)
		return item;
	this_file = read_file(filename);
	
	// 根据套装序号查找序号所在文件表，查找匹配套装数据
	// modname 	套装名字
	// modfile	套装文件表
	// modstats	套装属性表
	sscanf( this_file, "%*s<"+modnum+">\n%s\n~\n%s\n~\n%s\n</"+modnum+">%*s", modname, modfile, modstats );
	
	item->modnum = modnum;
	item->modname = modname;

	// 解析文件表，填入文件名称和套装部件中文名字。	
	field = explode(modfile, "\n");
	if( sizeof(field) < 2 )		// 少于2个就不称之为套装了。
		return item;
	for (i=0;i<sizeof(field);i++)
	{
		ob = new(field[i]);
		if(!ob)
			return 0;
		item->file += ({ field[i] });
		item->name += ({ ob->query("name") });
	}

	// 解析属性表，填入属性关键字和套装属性。	
	field = explode(modstats, "\n");
	// stats_key	属性关键字
	// stats_value	属性值
	stats = ([ ]);
	for (i=0;i<sizeof(field);i++)
	{
		sscanf( field[i], "%s %d", stats_key, stats_value );
		stats[stats_key] = stats_value;
	}
	item->stats = stats;
	
	return item;
}

// 装备套装部件
// ob套装部件 owner装备者
void equip_mod(object ob, object owner)
{
	string modnum, file;
	class eqmod mod_stats;
	string *modfiles;
	
	mapping stats, applied_prop;
	int i;
	string *apply;
	
	modnum = ob->query("mod");
	mod_stats = new(class eqmod);
	// 读取套装资料
	mod_stats = load_one_mod(modnum);
	// 检查合法性
	if (!check_one_mod(mod_stats))
		return;
	// 检查套装部件ob是否是套装里的一件
	file = base_name(ob);
	if (member_array(file, mod_stats->file) == -1)
		return;
	
	// 标记套装件数
	owner->add_temp("modamount_"+modnum,1);
	// 标记套装文件
	modfiles = owner->query_temp("modfiles_"+modnum);
	if ( pointerp(modfiles) )
		modfiles += ({ file });
	else
		modfiles = ({ file });
	owner->set_temp("modfiles_"+modnum,modfiles);
	// 装备的套装设置标记
	ob->set_temp("mod_eq",1);
	
	// 如果onwer身上装备的套装件数未达到套装总件数时，不赋予onwer套装属性
	if ((int)owner->query_temp("modamount_"+modnum) < sizeof(mod_stats->file))
		return;
	// 读取套装附加属性
	stats = mod_stats->stats;
	apply = keys(stats);
	applied_prop = owner->query_temp("apply");
	if( !mapp(applied_prop) ) 
		applied_prop = ([]);
	for(i = 0; i<sizeof(apply); i++)
		if( undefinedp(applied_prop[apply[i]]) )
			applied_prop[apply[i]] = stats[apply[i]];
		else
			applied_prop[apply[i]] += stats[apply[i]];
	owner->set_temp("apply", applied_prop);
}
// 卸下套装部件
// ob套装部件 owner装备者
void unequip_mod(object ob, object owner)
{
	string modnum, file;
	class eqmod mod_stats;
	string *modfiles;
	
	mapping stats, applied_prop;
	int i;
	string *apply;
	
	modnum = ob->query("mod");
	mod_stats = new(class eqmod);
	// 读取套装资料
	mod_stats = load_one_mod(modnum);
	// 检查合法性
	if (!check_one_mod(mod_stats))
		return;
	// 检查套装部件ob是否是套装里的一件
	file = base_name(ob);
	if (member_array(file, mod_stats->file) == -1)
		return;
	
	// 标记套装件数
	owner->add_temp("modamount_"+modnum,-1);
	if ((int)owner->query_temp("modamount_"+modnum)<0)
		owner->delete_temp("modamount_"+modnum);
	// 标记套装文件
	modfiles = owner->query_temp("modfiles_"+modnum);
	if ( pointerp(modfiles) )
		modfiles -= ({ file });
	else
		modfiles = ({ });
	owner->set_temp("modfiles_"+modnum,modfiles);
	// 删除装备套装部件标记
	ob->delete_temp("mod_eq");

	// 如果onwer身上装备的套装件数+1未达到套装总件数时，
	// 因为没附加过套装属性，所以不需要执行删除onwer套装属性
	if (((int)owner->query_temp("modamount_"+modnum) + 1) < sizeof(mod_stats->file))
		return;
	// 读取套装附加属性
	stats = mod_stats->stats;
	apply = keys(stats);
	applied_prop = owner->query_temp("apply");
	for(i = 0; i<sizeof(apply); i++)
		applied_prop[apply[i]] -= stats[apply[i]];
}
*/