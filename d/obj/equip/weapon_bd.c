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
	set("long", "玄武泪珠所化，能将%d级以下的挑战武器转化(change)成可召唤的武器。\n");
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
	str+= "(兵)";
	msg = query_title(query("level"));
	str = replace_string(str,"玄武石",msg+"玄武石");
	return str;
}

string weapon_short(object ob)
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
	if( armor->query("weapon_level")>query("level") )
		return err_msg(weapon_short(armor)+"品质太高，你需要"+query_title(armor->query("weapon_level"))+"以上品质的玄武石(兵)。\n");
		
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
		