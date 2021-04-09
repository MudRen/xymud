// buy.c
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string item, targ;
        object ob, owner;
        int price, afford,num;
        string fname,opfaname,faname=me->query("family/family_name");
        string* slist;
	
        if( this_player()->is_busy() )
		return notify_fail("你现在正忙着呢。\n");
	num=1;                	
	if(!arg)return notify_fail("指令格式：buy <某物> from <某人>\nbuy <某物> from <某人> for <数量>\n");
	if( sscanf(arg, "%s from %s for %d", item, targ,num)!=3)
		if( sscanf(arg, "%s from %s", item, targ)!=2)
                	return notify_fail("指令格式：buy <某物> from <某人>\nbuy <某物> from <某人> for <数量>\n");
	if(num<1)num=1;
	if(num>100)num=100;

        if( !objectp(owner = present(targ, environment(me))) )
                return notify_fail("你要跟谁买东西？\n");

	if( userp(owner) ) 
	{
                message_vision("$N想向$n购买「" + item + "」。\n", me, owner);
                notify_fail("对方好像不愿意跟你交易。\n");
                return 1;
        }
        
        if( (price = owner->buy_object(me, item)) == -1 ) return 1;
        if( price < 1 ) return 0;
/*
        fname=file_name(environment(me));
        slist=explode(fname,"/");
        opfaname=SHILI_D->query_family(slist[sizeof(slist)-2]);
        if((opfaname!="")&&(opfaname==faname)){
                message_vision("$n对$N说，由于贵门多年照顾，就收您一半的钱了.\n",me,owner);
                price=price/2;
        }
        if((opfaname!="")&&faname&&(FAMILYD->family_relation(opfaname,faname)==-1)){
                message_vision("$n对$N说，"+SHILI_D->query_master(opfaname)+"说了，卖给贵门派弟子的东西，价格都要翻倍。\n",me,owner);
                price=price*2;
        }
*/
	price=price*num;
	
	
	if( !me->check_pay(price) )
		return notify_fail("你的钱不够。\n");
	
	if(owner->complete_trade(me, num,item)) 
	{
		me->money_add(-price);
		return 1;
	} 
	else	return notify_fail("购买失败，可能你背包满了。\n");
}

int help(object me)
{
   write( @HELP
指令格式: buy <something> from <someone>

这一指令让你可以从某些人身上买到物品。
HELP
   );
   return 1;
}
