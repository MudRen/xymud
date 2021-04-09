// news cmds
// by Doing
#include <ansi.h>
#include <combat.h> 
inherit F_CLEAN_UP;

int main(object me, string arg)
{

        if (! arg || arg == "" || arg == "all")
        {
                "/adm/daemons/newsd.c"->show_news(me, (arg != "all") ? 1 : 0);
                return 1;
        }

        if (sscanf(arg, "discard %s", arg))
        {
                "/adm/daemons/newsd.c"->do_discard(me, arg);
                return 1;
        }

        if (sscanf(arg, "post %s", arg))
        {
                "/adm/daemons/newsd.c"->do_post(me, arg);
                return 1;
        }

        "/adm/daemons/newsd.c"->do_read(me, arg);

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : news [next] | [<新闻编号>] | new | all

这条指令让你你可以阅读游戏中的新闻。所有的更新和消息都是通过
新闻发布的。

使用 new 参数可以让你阅读还没有读过的新闻。
使用 all 参数可以让你查看系统目前所有的新闻。

总站的巫师可以通过news post <标题>来发布新闻。news discard来
删除新闻。
HELP );
    return 1;
}

