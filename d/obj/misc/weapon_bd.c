//绑定石
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
	set("long", "玄武泪珠所化，能将下线不掉的武器转化(change)成可召唤的武器。\n");
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
	add_action("do_change","change");
}

string short()
{
	string str = ::short();
	str+= "(兵)";
	return str;
}

int do_change(string arg)
{
	mapping my_data;
	string *ars;
	int i;
	object obj,armor,me = this_player();
	if( !arg )
		return 0;
	if( !present(this_object(),me) )
		return 0;
	armor = present(arg,me);
	if( !armor )
		return err_msg("你身上没有"+arg+"。\n");
	if( !armor->query("changed") )
		return err_msg(armor->name()+"无法绑定。\n");
	if( armor->is_zhaohuan() )
		return err_msg(armor->name()+"无法绑定。\n");
	if( armor->query("equipped") )
		return err_msg("你要先卸除"+armor->name()+"。\n");		
	if( !armor->query("skill_type")
	 || !armor->query("weapon_level") )
		return err_msg(armor->name()+"不是武器。\n");
	my_data = armor->query_entire_dbase();
	obj = new("/obj/weapon");
	obj->set("owner_id",me->query("id"));
	ars = keys(my_data);
	for(i=0;i<sizeof(ars);i++)
	{
		if( !ars[i] || ars[i]=="changed" )
			continue;
		obj->set(ars[i],my_data[ars[i]]);
	}
	obj->set("shorts",armor->short());
	obj->set("ids",armor->parse_command_id_list());	
	obj->set_name(armor->query("name"),obj->query("ids"));
	obj->setup();
	if( !obj->move(me) )
	{
		destruct(obj);
		return err_msg("你背包满了。\n");
	}	
	if( obj->to_save() )
	{
		destruct(armor);
		me->save();
		me->start_busy(1);
		write(obj->short()+"变更完毕。\n");
		if( query_amount()>1 )
			add_amount(-1);
		else	
			destruct(this_object());
		return 1;
	}
	else
	{
		destruct(obj);
		write("变更失败。\n");
		me->start_busy(1);
		return 1;
	}
}
		