#include <ansi.h>
inherit __DIR__"enchase.c";

void create_enchase()
{
	set_name(HIR"冲冠一怒为红颜"NOR,({"chongguan hongyan",}));
	set("need_mana",0);
	set("weapon_level",1);
}

int in_jiezi(){ return 1;}

int is_combine_item(){ return 0;}

nosave int do_enchase(object who,object obj){ return 0;}

string long()
{
	string long = "这是一枚神奇的灵石，它可以提升可召唤类武器的等级。\n";
	
	long+= "要求";
	long+= HIM"  武器："+query("weapon_level")+"级\n"NOR;
	long+= "效果";
	long+= HIR"  升级武器：将等级<9的可召唤类武器提升一级\n"NOR;
	long+= "提示";
	long+= HIC"  升级命令：shengji <武器名称>\n"NOR;
	return long;
}

void init()
{
	add_action("do_sheng","shengji");
}

int err_msg(string arg)
{
	write(arg);
	return 1;
}

int do_sheng(string arg)
{
	object ob,me = this_player();
	
	if( !arg )
		return 0;
	ob = present(arg,me);
	if( !ob )
		return err_msg("你身上没有"+arg+"。\n");
	if( !ob->is_zhaohuan() )
		return err_msg(ob->query("name")+"不是可召唤类武器。\n");
	if( ob->query("owner_id")!=me->query("id") )
		return err_msg(ob->query("name")+"不是你的专属武器。\n");
	if( ob->query("weapon_level")>=9 )
		return err_msg(ob->query("name")+"已不能通过"+query("name")+"来升级。\n");
	if( me->is_busy() )	
		return err_msg("你现在正忙着呢。\n");
	
	write("你对"+ob->query("name")+"使用了"+query("name")+"。\n");
	me->start_busy(1);
	ob->level_up();
	if( query_amount()<2 )
		destruct(this_object());
	else	add_amount(-1);	
	return 1;
}						
		
					