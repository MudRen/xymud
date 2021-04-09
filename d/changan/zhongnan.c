#include <ansi.h>
inherit ROOM;

void create ()
{
        set ("short", "终南山口");
        set ("long", @LONG
终南山又称太乙山，距长安城八十多里，素有“锦秀巨屏拱长
安”之说。据传老子曾在山中讲经。这条大官道穿越终南山口，
两面秀峰入云，却无明显之路可以上山。
LONG);
        set("exits", ([
                "south" : __DIR__"broadway2",
                "north" : __DIR__"broadway1",
        ]));
        set("outdoors", 2);
        setup();
}

void init()
{
        add_action("do_enter","enter");
}

int do_enter()
{
        object who = this_player();
        if( userp(who) && who->query_temp("maze/40tupo")
         && time()>=who->query("maze/tupo-40")+1800
         && ( (who->query_level()==39&&who->query("combat_exp")>=16100000) ||wizardp(who) ) )
        {
                who->delete_temp("maze");
                who->dismiss_team(who);
                if( MAZE_D->enter_maze(who, "tupo40-5") )
                {
                        who->set("maze/tupo-40",time());
                        message_vision(HIC"\n$N"HIC"进入了土极之地"NOR YEL"终南幽谷"NOR HIC"。\n"NOR,who);
                        return 1;
                }
                else    return err_msg("你有些踌躇不前。\n");
        }
        else    return 0;
}

