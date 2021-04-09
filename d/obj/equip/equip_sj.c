//装备升级
#include <ansi.h>
inherit COMBINED_ITEM;

void setup(){}

void create()
{
	set_name("升级宝石",({"bao shi","shi","stone",}));
	if(clonep()) 
		set_default_object(__FILE__); 
	set("base_unit", "颗");
	set("unit","些");
	set("long", "霞光横溢的宝石，用它可以升级(shengji)%d级以下的装备。\n");
	set("value", 0);
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
		return "先天";
}	

string name()
{
	string msg,str = ::name();
	if( !query("type") )
		return "无效的"+str;
	if( query("type")=="weapon" )
		str = "金芒石";
	else	str = "厚土石";		
	msg = query_title(query("level"));
	return msg+str;
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
	mapping my_data,base_data;
	string *tmp,*base_prop,str,str2;
	int i,k,j;
	mixed type;
	object obj,me = this_player();
	mapping equip_apply_prop  = ("/cmds/std/look.c")->query_euqip_look1();
	mapping equip_apply_prop2 = ("/cmds/std/look.c")->query_euqip_look2();   

	if( !arg || !present(this_object(),me) )
		return 0;
	obj = present(arg,me);
	if( !obj )
		return err_msg("你身上没有"+arg+"。\n");		
	if( !obj->query("armor_type") && !obj->query("skill_type") )
		return err_msg(armor_short(obj)+"不能升级。\n");
	if( query("level")<=0 || !query("type") || !query("owner_id") )
		return err_msg(name()+"好似失去了效果。\n");	
	if( obj->query("level")>query("level") )
		return err_msg(armor_short(obj)+"品质太高，你需要"+query_title(obj->query("level"))+"以上品质的升级宝石。\n");
	if( !obj->query("armor_prop") && !obj->query("weapon_prop") )
		return err_msg(armor_short(obj)+"没有升级的价值。\n");	
	if( obj->query("max_level")+obj->query("base_level")<=obj->query("level") )
		return err_msg(armor_short(obj)+"已经没有成长的可能了。\n");
	if( query("from") )
	{
		if( !obj->query("from") || obj->query("from")!=query("from") )
			return err_msg(name()+"只能升级出自【"+query("from")+"】的装备。\n");
	}		
	if( obj->query("equipped") )
		return err_msg("你要先卸除"+armor_short(obj)+"。\n");

	write(HIG"【系统】"+armor_short(obj)+HIG"升级成功！\n"NOR);
	if( obj->query("skill_type") && obj->query("weapon_prop") )
	{
		my_data = obj->query("weapon_prop");
		base_data = ("/d/obj/nweapon/newweapon.c")->equip_base(obj);
	}
	else
	{
		my_data = obj->query("armor_prop");	
		base_data = ("/d/obj/narmor/newcloth.c")->equip_base(obj);
	}
	base_prop = keys(base_data);
		
	tmp = keys(my_data);
	if( tmp && arrayp(tmp) )
	{
		j = sizeof(tmp);
		j = random(j);
		for(i=0;i<j;i++)
		{
			type = tmp[i];
			if( !stringp(type) || member_array(type,base_prop)!=-1 )
				continue;
			if( my_data[type]>100 )
				continue;			
			k = random(2)+random(obj->query("level")/10)/3;
			if( member_array(type,keys(equip_apply_prop2))!=-1 )
				k = k/2;
			if( k>0 )
			{
				my_data[type]+= k;
				
				if( !undefinedp(equip_apply_prop[type]) )
					str = equip_apply_prop[type];
				else if( !undefinedp(equip_apply_prop2[type]) )	
					str = equip_apply_prop2[type];
				else
				{
					str = type;
					if( is_chinese(to_chinese(str)) )
						str = to_chinese(str)+"有效等级";
					else if( sscanf(str,"ad_%s",str2) )
					{
						if( is_chinese(to_chinese(str2)) )
							str = to_chinese(str2)+"技能等级";
					}
				}
				write(HIG"【系统】"+armor_short(obj)+HIG"的 "HIY+str+HIG" 增加了"HIR+k+HIG" 点。\n"NOR);	
			}	
		}
	}
	obj->add("level",1);	
	for(i=0;i<sizeof(base_prop);i++)
	{
		k = base_data[base_prop[i]]+obj->query("level")/3;
		k = k/5+random(k/5);
		if( k<1 ) k = 1;
		if( obj->query("skill_type") && obj->query("weapon_prop") )
			obj->add("weapon_prop/"+base_prop[i],k);
		else	obj->add("armor_prop/"+base_prop[i],k);
		
		if( !undefinedp(equip_apply_prop[base_prop[i]]) )
			str = equip_apply_prop[base_prop[i]];
		else if( !undefinedp(equip_apply_prop2[base_prop[i]]) )	
			str = equip_apply_prop2[base_prop[i]];
		else
		{
			str = base_prop[i];
			if( is_chinese(to_chinese(str)) )
				str = to_chinese(str)+"有效等级";
			else if( sscanf(str,"ad_%s",str2) )
			{
				if( is_chinese(to_chinese(str2)) )
					str = to_chinese(str2)+"技能等级";
			}
		}	
		write(HIG"【系统】"+armor_short(obj)+HIG"的 "HIY+str+HIG" 增加了 "HIR+k+" 点"HIG"。\n"NOR);
	}
	if( obj->save() )
		write(HIR"【系统】"+armor_short(obj)+"保存成功。"NOR"\n");
	else	write(HIR"【系统】注意：未绑定的装备可能会因各种可能而消失，在未绑定之前，可以存在长安钱庄的"HIY"仓库"HIR"里。"NOR"\n");
	if( query_amount()>1 )
		add_amount(-1);
	else	destruct(this_object());
	return 1;
}
		