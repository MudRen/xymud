// cracked by vikee 2/09/2002   vikee@263.net
// halt.c

#include "/doc/help.h"
inherit SSERVER;

int main(object me, string arg)
{
        object target;
        if( !me->is_fighting() )
                return notify_fail("你现在并没有在战斗。\n");
        target = offensive_target(me);          
        me->remove_all_killer();
        message_vision("$N用巫师的神力停止了这场打斗。\n", me);
        if( target && !userp(target) )
                target->powerup(0,1);
        write("Ok.\n");
        return 1;
}

int help(object me)
{
   write(@HELP
指令格式: ss

可以停止所有与你有关的战斗。
HELP
   );
   return 1;
}

