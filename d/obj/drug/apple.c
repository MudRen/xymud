#include <ansi.h>
inherit ITEM;
int do_eat(string);
void init()
{
      add_action("do_eat","eat");
}
void create()
{
    set_name("苹果",({"ping guo", "apple"}));
    if (clonep())
        set_default_object(__FILE__);
     else {
        set("unit","个");
        set("long", "这是一个苹果。\n");
        set("value", 2000);
        set("drug_type", "补品");
     }
     setup();
}
int do_eat(string arg)
{
   object me = this_player();
    if (arg!="ping guo" && arg!="apple") return 0;
   else {
   me->save();
   }
message_vision("$N吃下一个苹果，气色看起来好多了。\n",
     me);
   destruct(this_object());
   return 1;
}


