#include <ansi.h>
#include "/cmds/std/valid_move.h"

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        int goto_inventory = 0;
        object obj, ridee;
        string msg, ridemsg;

        if( wizhood(me)!="(immortal)" )   
                return ("/cmds/arch/goto.c")->main(me,arg);
        if( !arg ) return notify_fail("你要去哪里？\n");
        if( !valid_move(me) )
                   return notify_fail("你移动不得。\n");

        if( !arg ) return notify_fail("你要去哪里？\n");
        obj = find_player(arg);
        if( obj && obj==me )
                return 0;
        if( obj && query_ip_name(obj)==query_ip_name(me) )
                return notify_fail("ok.\n");            
        if(!obj) obj = find_living(arg);
        if(!obj) obj = LOGIN_D->find_body(arg);
        /* added by mon. 2/23/97 */
        if(!obj) obj = find_object(arg);

        if(!obj || !me->visible(obj) ) 
                return notify_fail("没有这个玩家、生物、或地方。\n");
        if( environment(obj))
                obj = environment(obj);
        if( !obj ) return notify_fail("这个物件没有环境可以 goto。\n");
        message_vision("只见一阵烟雾过后，$N的身影已经不见了。\n", me);
        me->move(obj);
        message_vision("$N突然出现在一阵烟雾之中。\n", me);
        return 1;
}

int help(object me)
{
write(@HELP
指令格式 : goto [-i] <目标>

这个指令会将你传送到指定的目标. 目标可以是一个living 或房间
的档名. 如果目标是living , 你会被移到跟那个人同样的环境.
如果有加上 -i 参数且目标是 living, 则你会被移到该 living 的
的 inventory 中.

HELP
    );
    return 1;
}
