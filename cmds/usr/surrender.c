// surrender.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;

	if( me->query("gin")<1 )
		return notify_fail("你的活力不足了。\n");        
        if( !me->is_fighting() )
                return notify_fail("投降？现在没有人在打你啊....？\n");
        if( me->is_busy() )
                return notify_fail("你正忙着呢，不能投降。\n"); 

        ob = me->query_temp("last_opponent");
        if( objectp(ob) && living(ob) && ob->is_killing(me->query("id")) ) 
        {
                if( ob!=me->query("rulaitask/guai") 
                 && me->query("rulaitask/kind")!="劝" )
                {                
                        message_vision(HIW"$N"HIW"向$n"HIW"求饶，但是$n"HIW"大声说道："+ RANK_D->query_rude(me) + "废话少说，纳命来！\n"NOR, me, ob);
                        return 1;
                }
                if( !ob->accept_surrender(me) )
                {                
                        message_vision(HIW"$N"HIW"向$n"HIW"求饶，但是$n"HIW"大声说道："+ RANK_D->query_rude(me) + "废话少说，纳命来！\n"NOR, me, ob);
                        return 1;
                }
        }
        me->add("gin",-1);
	me->remove_all_enemy();
        if( ob && objectp(ob) && living(ob) && ob->is_killing(me->query("id")) )
                ob->remove_killer(me);
        message_vision( HIW "\n$N"HIW"说道：「不打了，不打了，我投降....。」\n\n" NOR, me);
        if( me && ob && userp(me) && !userp(ob) )
		ob->combat_lose(me);
        if( me && ob && userp(ob) && !userp(me) )
		me->combat_win(ob);		        
        return 1;
}
int help(object me)
{
  write(@HELP
指令格式 : surrender
 
这个指令可以让你向敌人投降而终止战斗。

*此命令将消耗1点活力。 
HELP
    );
    return 1;
}
 

