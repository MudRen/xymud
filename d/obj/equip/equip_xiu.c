//装备升级
#include <ansi.h>
inherit COMBINED_ITEM;

void setup(){}

void create()
{
	set_name("坎水石",({"bao shi","shi","stone",}));
	if(clonep()) 
		set_default_object(__FILE__); 
	set("base_unit", "颗");
	set("unit","些");
	set("long", "霞光横溢的宝石，用它可以修复(xiu)被损坏的装备。\n");
	set("value", 0);
    	set("level",10);
    	set("changed",1);
    	setup();
    	set_amount(1);
}

void init()
{
	add_action("do_change","xiu");
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
	object obj,me = this_player();

	if( !arg || !present(this_object(),me) )
		return 0;
	obj = present(arg,me);
	if( !obj )
		return err_msg("你身上没有"+arg+"。\n");		
	if( !obj->query("armor_type") && !obj->query("skill_type") )
		return err_msg(armor_short(obj)+"不能修复。\n");
	if( !obj->query("breaked") )
		return err_msg(armor_short(obj)+"不需要修复。\n");
	if( obj->query("equipped") )
		return err_msg("你要先卸除"+armor_short(obj)+"。\n");
	if( me->query("mana")<100 )
		return err_msg("你的法力不够了。\n");
	
	me->add("mana",-100);	
	write(HIC"你将"+name()+HIC"在"+armor_short(obj)+HIC"上轻轻摩擦。\n"NOR);
	write(HIC+name()+HIC"发出一阵微弱的霞光。\n"NOR);
	if( random(me->query_maxmana())<50 )
		write("结果什么反应也没用。\n");
	else	
	{
		write(HIC+armor_short(obj)+HIC"渐渐恢复了灵气。\n"NOR);
		obj->delete("breaked");
		obj->save();
	}
	if( query_amount()>1 )
		add_amount(-1);
	else	destruct(this_object());
	return 1;
}