// huandian.c 鲜花店
// modified by amy&&jingxue for xycq 2004/4/15

inherit ROOM;
#include <room.h>
#include <ansi.h>

void create()
        {
        set("short", HIM"枚眼盈盈"NOR);
        set("long", HIG"山是眼波横，眼是眉峰聚。借问行人去哪边，眉眼盈盈处。\n"NOR);
        set("exits", ([
                "down" : __DIR__"eastseashore",
//"up": __DIR__"huadian1",
        ]));
        set("objects", ([
                "d/wiz/flower/npc/flowerseller":1,
        ]) );
        set("no_fight",1);
        set("no_sleep",1);
        setup();
}
void init()
{
        add_action("do_fight", "fight");
        add_action("do_kill", "kill");
        add_action("do_steal", "steal");
        add_action("do_cast", "cast");
        add_action("do_ji","ji");
        add_action("do_throw","throw");
        add_action("do_perform","perform");
        add_action("do_exert","exert");
        add_action("do_bid","bid");
}
void die()
{
        return;
}

int do_fight(string arg)
{
        object who = this_player();
        message_vision("$N准备跟小枚儿比划比划，结果被一群官兵上来麻利的把$N捆了个结实，押着丢到水里喂鱼去了。\n",who);
        who->move("/d/changan/inwater");
        return 1;
}

int do_kill(string arg)
{
        object who = this_player();
        message_vision("$N刚准备行刺小枚儿，不料旁边闪出一群大内侍卫来。$N吓的胆都破了，\n连忙对着小枚儿鞠了个躬，结果还是被侍卫胖揍一顿，扔到水里喂鱼去了。\n",who);
        who->move("/d/changan/inwater");
        return 1;
}
int do_perform(string arg)
{
        object who = this_player();
        message_vision("$N猪蹄又发痒了，结果被小枚儿一个佛山无影脚踹到一边去了。\n",who);
        who->move("/d/city/center");
        return 1;
}
int do_cast(string arg)
{
        object who = this_player();
        message_vision("$N对着小枚儿结结巴巴的念了几句咒语，小枚儿立马给了$N一个大嘴巴。\n",who);
        return 1;
}
int do_exert(string arg)
{
        object who = this_player();
        message_vision("$N想用内功，但总觉得运不起气来。\n",who);
        return 1;
}
int do_steal(string arg)
{
        object who = this_player();
        message_vision("$N想偷东西，但总是有贼心没贼胆。\n",who);
        return 1;
}
int do_ji(string arg)
{
        object who = this_player();
        message_vision("$N想祭法宝，前思后想，还是没敢。\n",who);
        return 1;
}
int do_throw(string arg)
{
        object who = this_player();
        message_vision("$N掏出暗器，看了看武功高强的小枚儿，信心不足，又把暗器收了起来。\n",who);
        return 1;
}
int do_bid(string arg)
{
       object who = this_player();
       message_vision("$N想买店，看看是小枚儿开的，就没敢盘。\n",who);
      return 1;
}

int valid_leave(object me, string dir)
{
           //temp access for future wiz.

if( dir=="up" && !wizardp(me) )
                  return notify_fail("这是tmt大人刚刚做的房间，还是测试阶段。\n");
          return ::valid_leave(me, dir);
}
