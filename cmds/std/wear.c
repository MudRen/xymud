// wear.c

#include <ansi.h>

inherit F_CLEAN_UP;

int do_wear(object me, object ob);

int main(object me, string arg)
{
	object ob, *inv;
	int i, count;

	if( !arg ) return notify_fail("你要穿戴什么？\n");
	
	
	if(arg=="all") {
		inv = all_inventory(me);
		for(count=0, i=0; i<sizeof(inv); i++) {
			if( inv[i]->query("equipped") ) continue;
			if(do_wear(me, inv[i]) ) count ++;
		}
		write("Ok.\n");
		return 1;
	}

	if( !objectp(ob = present(arg, me)) )
		return notify_fail("你身上没有这样东西。\n");
			
	if( ob->query("equipped") )
		return notify_fail("你已经装备着了。\n");

	return do_wear(me, ob);
}

int do_wear(object me, object ob)
{
	string str;

	if( ob->query("owner_id") && ob->query("owner_id") != getuid(me) )   {
		destruct(ob);
		return notify_fail("下次别乱偷别人的东西。\n");
	}

	if( ob->query("No_Wear") )
		return notify_fail("这件衣服不能再穿了！\n");
	if( ob->query("breaked") )
		return notify_fail(ob->name()+"已经损坏了，需要修复。\n");
	if( ob->query("level")>me->query_level() )
		return notify_fail("你的等级不足"+ob->query("level")+"。\n");
	if( ob->query("female_only")
	&&	(string)me->query("gender") != "女性" )
		return notify_fail("这是女人的衣衫，你一个大男人也想穿，羞也不羞？\n");

	if( ob->wear() ) {
		if( !stringp(str = ob->query("wear_msg")) )
			switch( ob->query("armor_type") ) {
				case "cloth":
				case "armor":
				case "boots":
				case "surcoat":
					str = YEL "$N穿上一" + ob->query("unit") + "$n。\n" NOR;
					break;
				case "head":
				case "neck":
				case "wrists":
				case "finger":
				case "hands":
					str = YEL "$N戴上一" + ob->query("unit") + "$n。\n" NOR;
					break;
				case "waist":
					str = YEL "$N佩上一" + ob->query("unit") + ob->query("name") + "。\n" NOR;
					break;
				default:
					str = YEL "$N装备$n。\n" NOR;
			}
		if( !me->query("env/brief_message") )	
			message_vision(str, me, ob);
		else
		{
			str = replace_string(str,"$N","你");
			str = replace_string(str,"$n",ob->name());
			write(str);
		}	
		me->set_temp("last_time/wear",time());
		return 1;
	} else
		return 0;
}

int help(object me)
{
	write(@HELP
指令格式：wear|chuan <装备名称>
 
这个指令让你装备某件防具。
 
HELP
    );
    return 1;
}
