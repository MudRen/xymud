#include <ansi.h>
inherit COMBINED_ITEM;

nosave mapping at = ([
	"strength"	: "体格",
	"courage" 	: "胆识",
	"intelligence"	: "悟性",
	"spirituality"	: "灵性",
	"composure"	: "定力",
	"personality"	: "容貌",
	"constitution"	: "根骨",
	"karma"		: "福缘",
	"damage"	: "攻击",
	"armor"		: "防御",
	"armor_vs_spells" : "法术防御",
	"armor_vs_force"  : "内功防御",
	"attack"	: "命中",
]);	
	 
nosave mapping at2 = ([
	"healup_kee"	: "气血恢复速度",
	"healup_sen"	: "精神恢复速度",
	"healup_force"	: "内力恢复速度",
	"healup_mana"	: "法力恢复速度",
	"remove_kee_damage" : "抵消气血减少",
	"remove_sen_damage" : "抵消精神减少",
	"remove_eff_kee_damage" : "抵消气血损伤",
	"remove_eff_sen_damage" : "抵消精神损伤",
	"redamage_kee"	: "反弹气血减少",
	"redamage_sen"	: "反弹精神减少",
	"redamage_eff_kee" : "反弹气血损伤",
	"redamage_eff_sen" : "反弹精神损伤",
]);	

protected void create_enchase(){}

void setup(){}

void create()
{
	set_name("enchanse item",({"enchanse item",}));
	set("base_weight",10);
	set("base_unit","颗");
	set("unit","些");
	create_enchase();                
    	set_amount(1);
        setup();
}

int is_combine_item(){ return 1;}	

int can_ronghe(){ return 1;}

protected int query_need_mana()
{
	return query("need_mana");
}

protected int update_obj(object who,object obj,string type)
{
	int i;
	string *data;
	mapping ench;
	
	if( !who || !obj || !type || !living(who) )
		return 0;
	if( type!="weapon" && type!="armor" )
		return 0;
	
	ench = query(type);
	if( !ench || !mapp(ench) )
	{
		tell_object(who,obj->query("name")+"是个假货，请联系巫师。\n");
		return 0;
	}
	data = keys(ench);
	for(i=0;i<sizeof(data);i++)
	{
		if( type=="weapon" )
			obj->add("weapon_prop/"+data[i],ench[data[i]]);
		else	obj->add("armor_prop/"+data[i],ench[data[i]]);
	}
	if( query_amount()>1 )
		add_amount(-1);
	else	destruct(this_object());
	return 1;
}

protected int do_enchase(object who,object obj)
{
	if( !who || !living(who) )
		return 0;
	if( !obj )
	{
		tell_object(who,"你要镶嵌到什么上面去？\n");
		return 0;
	}
	if( !obj->query("weapon_prop")
	 && !obj->query("armor_prop") )
	{
		tell_object(who,"你只能镶嵌到武器或防具上。\n");
		return 0;
	}
	if( obj->query("equipped") )
	{
		tell_object(who,"需要将"+obj->query("name")+"先卸除了。\n");
		return 0;
	}
	
	if( obj->query("weapon_prop") )
		return update_obj(who,obj,"weapon");
	else	return update_obj(who,obj,"armor");	
}

string long()
{
	int i;
	mapping data;
	string *msg,tmp,str,long = "这是一%s神奇的%s，它可以镶嵌在武器或防具上。\n";
	
	str = query("name");
	i = strlen(str);
	str = sprintf("%s",str[(i-2)..(i-1)]);
	
	if( str=="石" )  str = "灵石";
	else	str =  str+"石";
	
	long = sprintf(long,query("base_unit"),str);
	
	long+= "要求  ";
	long+= HIM"  防具："+query("armor_level")+"级"NOR;
	long+= HIM"  武器："+query("weapon_level")+"级\n"NOR;
	long+= "消耗  ";
	long+= HIR"  灵力："+query("need_mana")+"点\n"NOR;
	long+= "效果 \n";
	data = query("armor");
	if( data && mapp(data) )
	{
		msg = keys(data);
		for(i=0;i<sizeof(msg);i++)
		{
			if( member_array(msg[i],keys(at))!=-1 )
				long+= HIC"\t镶嵌防具："+at[msg[i]]+HIY""+(data[msg[i]]>0?"+":"-")+data[msg[i]]+"\n"NOR;
			else if( is_chinese(to_chinese(msg[i])) )
				long+= HIC"\t镶嵌防具："+to_chinese(msg[i])+"有效等级"+HIY""+(data[msg[i]]>0?"+":"-")+data[msg[i]]+"\n"NOR;
			else if ( sscanf(msg[i],"ad_%s",tmp)
			       && is_chinese(to_chinese(tmp)) )
				long+= HIC"\t镶嵌防具："+to_chinese(tmp)+"技能等级"+HIY""+(data[msg[i]]>0?"+":"-")+data[msg[i]]+"\n"NOR;
			else if( member_array(msg[i],keys(at2))!=-1 )				
				long+= HIC"\t镶嵌防具："+at2[msg[i]]+HIY""+(data[msg[i]]>0?"+":"-")+data[msg[i]]+"%\n"NOR;				
		}
	}	
	data = query("weapon");
	if( data && mapp(data) )
	{
		msg = keys(data);
		for(i=0;i<sizeof(msg);i++)
		{
			if( member_array(msg[i],keys(at))!=-1 )
				long+= HIG"\t镶嵌武器："+at[msg[i]]+HIY""+(data[msg[i]]>0?"+":"-")+data[msg[i]]+"\n"NOR;
			else if( is_chinese(to_chinese(msg[i])) )
				long+= HIG"\t镶嵌武器："+to_chinese(msg[i])+"有效等级"+HIY""+(data[msg[i]]>0?"+":"-")+data[msg[i]]+"\n"NOR;
			else if ( sscanf(msg[i],"ad_%s",tmp)
			       && is_chinese(to_chinese(tmp)) )
				long+= HIG"\t镶嵌武器："+to_chinese(tmp)+"技能等级"+HIY""+(data[msg[i]]>0?"+":"-")+data[msg[i]]+"\n"NOR;
			else if( member_array(msg[i],keys(at2))!=-1 )				
				long+= HIG"\t镶嵌武器："+at2[msg[i]]+HIY""+(data[msg[i]]>0?"+":"-")+data[msg[i]]+"%\n"NOR;				
		}
	}	
	return long;
}

int in_jiezi(){ return 1;}