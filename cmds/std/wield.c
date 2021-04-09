// wield.c

inherit F_CLEAN_UP;

int do_wield(object me, object ob);

int main(object me, string arg)
{
	object ob, *inv;
	int i, count;

	if( !arg ) return notify_fail("你要装备什么武器？\n");

	if(arg=="all") {
		inv = all_inventory(me);
		for(count=0, i=0; i<sizeof(inv); i++) {
			if( inv[i]->query("equipped") ) continue;
			if(do_wield(me, inv[i]) ) count ++;
		}
		write("Ok.\n");
		return 1;
	}

	if( !objectp(ob = present(arg, me)) )
		return notify_fail("你身上没有这样东西。\n");

	if( ob->query("equipped") )
		return notify_fail("你已经装备着了。\n");

	return do_wield(me, ob);
}

int do_wield(object me, object ob)
{
	string str;

    	if( ob->query("owner_id") && ob->query("owner_id") != getuid(me) )   
    	{
		destruct(ob);
		return notify_fail("下次别乱偷别人的东西。\n");
	}
	if( me->query_temp("No_Wield") )
		return notify_fail("你原形已现，不可再持兵器！\n");
	if( ob->query("breaked") )
		return notify_fail(ob->name()+"已经损坏了，需要修复。\n");
	if( ob->query("level")>me->query_level() )
		return notify_fail("你的等级不足"+ob->query("level")+"。\n");
	if( ob->wield() ) 
	{
		if( !stringp(str = ob->query("wield_msg")) )
			str = "$N装备$n作武器。\n";
		if( !me->query("env/brief_message") )	
			message_vision(str, me, ob);
		else
		{
			str = replace_string(str,"$N","你");
			str = replace_string(str,"$n",ob->name());
			write(str);
		}			
		return 1;
	} 
	else	return 0;
}

int help(object me)
{
	write(@HELP
指令格式：wield|zhuangbei <装备名称>
 
这个指令让你装备某件物品作武器, 你必需要拥有这样物品.
 
HELP
    );
    return 1;
}
