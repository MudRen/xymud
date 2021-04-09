//武器升级
#include <ansi.h>
inherit COMBINED_ITEM;

void setup(){}

void create()
{
	set_name("玄武石",({"xuanwu shi","shi","stone",}));
	if(clonep()) 
		set_default_object(__FILE__); 
	set("base_unit", "颗");
	set("unit","些");
	set("long", "玄武泪珠所化，能将可召唤的%d级武器升级(shengji)。\n");
	set("value", 0);
    set("no_put",1);
    //set("no_give",1);
    set("no_get",1);
    set("level",10);
    set("changed",1);
    setup();
    set_amount(1);
}

void init()
{
	add_action("do_change","shengji");
}

string long()
{
	string str = ::long();
	return sprintf(str,query("level"));
}

string query_title(int v)
{
	if( v<=10 )
		return "凡品";
	else if( v<=30 )	
		return "下品";
	else if( v<=50 )	
		return "中品";
	else if( v<=100 )	
		return "上品";
	else if( v<=300 )	
		return "极品";
	else if( v<=500 )	
		return "仙品";
	else
		return "神级";
}	

string short()
{
	string msg,str = ::short();
	str+= "(武)";
	msg = query_title(query("level"));
	str = replace_string(str,"玄武石",msg+"玄武石");
	return str;
}

string armor_short(object ob)
{
	string str;
	if( !ob )
		return "";
	str = ob->short();
	str = COLOR_D->clean_color(str);
	//sscanf(str,"%s(%*s",str);
	return str;
}

int do_change(string arg)
{
	mapping prop,my_data;
	string *precent,*tmp;
	int i,k,j;
	mixed type;
	object armor,me = this_player();

	if( !arg || !present(this_object(),me) )
		return 0;
	armor = present(arg,me);
	if( !armor )
		return err_msg("你身上没有"+arg+"。\n");		
		
	if( !armor->is_zhaohuan() )
		return err_msg(armor_short(armor)+"不是可召唤的武器，不能升级。\n");
	if( armor->query("equipped") )
		return err_msg("你要先卸除"+armor_short(armor)+"。\n");		
	if( !armor->query("skill_type")
	 || !armor->query("weapon_level") )
		return err_msg(armor_short(armor)+"不是武器。\n");
	if( armor->query("weapon_level")>query("level") )
		return err_msg(armor_short(armor)+"品质太高，你需要"+query_title(armor->query("weapon_level"))+"以上品质的玄武石(玄)。\n");

	write(HIG"【武器升级】"+armor_short(armor)+HIG"升级成功！\n"NOR);
	my_data = armor->query("weapon_prop");
	tmp = keys(my_data);
	if( tmp && arrayp(tmp) )
	{
		prop = ([
			"attack"		: "命中率",
	        "strength"      : "后天体格",
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
       		"add_armor"		: "物理防御追加",
	       	"add_armor2"	: "法术防御追加",
    	  	"redamage_kee_damage" 	  : "气血伤害反弹",
       		"redamage_eff_kee_damage" : "气血损失反弹",
	       	"redamage_sen_damage"	  : "精神伤害反弹",
    	   	"redamage_eff_sen_damage" : "精神损失反弹",
       		"receive_curing_kee"	  : "气血治疗追加",
	       	"receive_heal_kee"	  	  : "气血恢复追加",
    	   	"receive_curing_sen"	  : "精神治疗追加",
       		"receive_heal_sen"	  	  : "精神恢复追加",
			"add_busy"		: "僵直效果追加",
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
		precent = ({
			"add_armor","add_armor2","force_recover","fofce_refresh",
			"redamage_kee_damage","redamage_eff_kee_damage",
			"redamage_sen_damage","redamage_eff_sen_damage", 
			"healup_kee","healup_sen","healup_force","healup_mana",
			"receive_heal_sen","receive_heal_kee","receive_heal_eff_kee",
			"receive_heal_eff_sen","cast_succ","no_cast_redamage","cast_dodge",    
			"cast_redamage","ad_eff_kee","ad_kee","ad_eff_sen","ad_sen",
			"ad_force","ad_mana",  
		});		
		j = sizeof(tmp);
		j = random(j);
		
		for(i=0;i<j;i++)
		{
			type = tmp[i];
			if( !stringp(type) || type=="damage" )
				continue;
			if( my_data[type]>100 )
				continue;			
			k = random(2)+random(armor->query("weapon_level")/50);
			if( member_array(type,precent)!=-1 )
				k = k/2;
			if( k>0 )
			{
				my_data[type]+= k;
				if( !undefinedp(prop[type]) )
				{
					if( member_array(type,precent)!=-1 )
						write(HIG"【武器升级】"+armor_short(armor)+HIG"的 "HIR+prop[type]+HIG" 属性增加了"HIR+k+"% "HIG"。\n"NOR);
					else
						write(HIG"【武器升级】"+armor_short(armor)+HIG"的 "HIR+prop[type]+HIG" 属性增加了"HIR+k+" "HIG"点。\n"NOR);	
				}
				else if( file_size(SKILL_D(type+".c"))!=-1 )
					write(HIG"【武器升级】"+armor_short(armor)+HIG"的 "HIR+to_chinese(type)+"有效等级"+HIG" 属性增加了"HIR+k+HIG" 点。\n"NOR);
				else if( sscanf(type,"ad_%s",type) )
				{
					if( file_size(SKILL_D(type+".c"))!=-1 )
						write(HIG"【武器升级】"+armor_short(armor)+HIG"的 "HIR+to_chinese(type)+"技能等级"+HIG" 属性增加了"HIR+k+HIG" 点。\n"NOR);
					else
						write(HIG"【武器升级】"+armor_short(armor)+HIG"的 "HIR+type+HIG" 属性增加了"HIR+k+HIG" 点。\n"NOR);	
				}
				else	write(HIG"【武器升级】"+armor_short(armor)+HIG"的 "HIR+type+HIG" 属性增加了"HIR+k+HIG" 点。\n"NOR);	
			}	
		}
	}
	armor->add("weapon_level",1);	
	k = random(2)+random(armor->query("weapon_level")/5);
	k = k/2;
	if(k<1)
		k = 1;
	if( k>0 )
	{
		armor->add("weapon_prop/damage",k);
		write(HIG"【武器升级】"+armor_short(armor)+HIG"的伤害增加了 "HIR+k+" 点"HIG"。\n"NOR);
	}
	armor->save();
	if( query_amount()>1 )
		add_amount(-1);
	else	
		destruct(this_object());
	return 1;
}
		