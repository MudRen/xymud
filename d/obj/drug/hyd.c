// cracked by vikee 2/09/2002   vikee@263.net
// huanyang.c 还阳丹
#include <ansi.h>
inherit ITEM;

int do_eat(string);
void init();

void init()
{
add_action("do_eat", "eat");
}

void create()
{
set_name(HIG "还阳丹" NOR, ({"huanyang dan", "dan"}));
set_weight(20);
set("unit", "粒");
set("long", "一粒还阳丹，据说有起死回生之效。\n");
set("value", 100000);
set("no_get", "嘿嘿，做梦吧! \n");
set("no_drop","这么宝贵的还阳丹，哪能乱扔! \n");
set("no_give","这么宝贵的还阳丹，哪能乱扔! \n");
set("no_put","这么宝贵的还阳丹，哪能乱扔! \n");
set("is_monitored", 1);
setup();
}

int do_eat(string arg)
{
object victim = this_player();

if ( !arg || !id(arg))
        return notify_fail("你要吃什么？\n");
victim->add("combat_exp", (int)victim->query("combat_exp") / 40);
/*
if( (int)victim->query("potential") > (int)victim->query("learned_points"))
        victim->add("potential",(int)victim->query("potential") - (int)victim->query("learned_points") );
*/
victim->skill_death_recover();
victim->add("daoxing",victim->query("death/dx_loss"));
victim->save();
if( userp(victim) ) log_file("RECOVER", sprintf("%s(%s) Got recovered on %s.\n", victim->name(1), geteuid(victim), ctime(time()) ) );
message_vision(HIG "\n$N吃下一粒还阳丹，硬是从白无常那里逃脱，捡回了一条小命。\n\n" NOR, victim);
destruct(this_object());
return 1;
}
