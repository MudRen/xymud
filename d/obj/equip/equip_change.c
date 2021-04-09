//装备升级
#include <ansi.h>
inherit COMBINED_ITEM;

void setup(){}

void create()
{
	set_name("冲灵石",({"bao shi","shi","stone",}));
	if(clonep()) 
		set_default_object(__FILE__); 
	set("base_unit", "颗");
	set("unit","些");
	set("long", "霞光横溢的宝石，用它可以改善(improve)装备升级次数增加%d次。\n");
	set("value", 0);
    	set("level",1);
    	set("changed",1);
    	setup();
    	set_amount(1);
}

void init()
{
	add_action("do_change","improve");
}

string long()
{
	string str = ::long();
	return sprintf(str,query("level"));
}

string query_title(int v)
{
	v*= 10;
	if( v<=10 )
		return "凡品";
	else if( v<=20 )	
		return "下品";
	else if( v<=30 )	
		return "中品";
	else if( v<=40 )	
		return "上品";
	else	return "珍品";
}	

string name()
{
	string msg,str = ::name();
	if( query("level")<=0 )
		return "无效的"+str;
	msg = query_title(query("level"));
	return msg+str;
}

string armor_short(object ob)
{
	string str;
	if( !ob )
		return "";
	str = ob->name(1);
	str = COLOR_D->clean_color(str);
	//sscanf(str,"%s(%*s",str);
	return str;
}

int do_change(string arg)
{
	int now,max,v,p,pp;
	object obj,me = this_player();

	if( !arg || !present(this_object(),me) )
		return 0;
	obj = present(arg,me);
	if( !obj )
		return err_msg("你身上没有"+arg+"。\n");		
	if( !obj->query("armor_type") && !obj->query("skill_type") )
		return err_msg(armor_short(obj)+"不能升级。\n");
	if( query("level")<=0 || !query("owner_id") || query("owner_id")!=me->query("id") )
		return err_msg(name()+"好似失去了效果。\n");	
	if( !obj->query("armor_prop") && !obj->query("weapon_prop") )
		return err_msg(armor_short(obj)+"没有升级的价值。\n");	
	if( obj->query("equipped") )
		return err_msg("你要先卸除"+armor_short(obj)+"。\n");

	max = obj->query("level");
	max = max/9+1;
	if( max>5 )
		max = 5; 
	v = query("level");			
	if( obj->query("max_level")+v>max )
		return err_msg(armor_short(obj)+"已经没有成长的可能了。\n");

	if( !intp(now=obj->query("base_level"))
	 || now<1 )
	{	 
		now = obj->query("level");
		obj->set("base_level",now);
	}

	write(HIC"你将"+name()+HIC"在"+armor_short(obj)+HIC"上轻轻摩擦。\n"NOR);
	
	p = (200-now)/36;
	pp = random(p);
	if( wizardp(me) )
		write( sprintf("now=%d p=%d pp=%d\n",now,p,pp) );
	if( pp==0 )
	{
		write(HIC+name()+HIC"发出一阵微弱的霞光。\n"NOR);	
		write(HIC"霞光闪了几闪，结果什么反应也没有。\n"NOR);
		write(HIR"【系统】"+armor_short(obj)+HIR"品质提高失败。\n"NOR);
	}
	else
	{
		obj->add("max_level",v);
		write(HIC+name()+HIC"发出一阵炫目的霞光。\n"NOR);
		write(HIG"【系统】"+armor_short(obj)+HIG"品质提高了！\n"NOR);
		if( obj->save() )
			write(HIR"【系统】"+armor_short(obj)+"保存成功。"NOR"\n");
		else	write(HIR"【系统】注意：未绑定的装备可能会因各种可能而消失，在未绑定之前，可以存在长安钱庄的"HIY"仓库"HIR"里。"NOR"\n");
	}	
	if( query_amount()>1 )
		add_amount(-1);
	else	destruct(this_object());
	return 1;
}
		