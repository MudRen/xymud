// create by smile 12/8/1998
// 白骨洞，白骨精的栖息地
#include <ansi.h>

inherit ROOM;

void create ()
{
  set ("short", "白骨洞");
  set ("long", @LONG
   [1;37m
        $$$                  $$$$$$$$$$$ 
       $ $                   $$       $$           $$$    $$$$$$$$$$$$$$$
      $ $                    $$$$$$   $$            $ $   $$$$$$$$$$$$$$$
     $ $$$$$$$$$$$$$         $$  $$   $$             $$$  $ $         $ $
     $ $$$$$$$$$$$$$     $$$$$$$$$$$$$$$$$$$$             $ $  $$$$$  $ $
     $ $         $ $     $$                $$       $$$   $ $  $$$$$  $ $
     $ $$$$$$$$$$$ $         $$$$$$$$$$$$            $ $  $ $         $ $
     $ $$$$$$$$$$$ $         $ $      $ $             $$$ $ $ $$$$$$$ $ $
     $ $         $ $         $ $$$$$$$$ $                 $ $ $ $ $ $ $ $
     $ $$$$$$$$$$$ $         $ $      $ $             $$$ $ $ $ $$$ $ $ $
     $$$$$$$$$$$$$$$         $ $$$$$$$$ $            $ $  $ $ $$$$$$$ $ $
                             $$$     $$$$           $$$   $$$       $-$ $
                                                          $$$        $$$$
[2;37;0m
      洞里往外呼呼的冒着黑烟，随风飘来阵阵腥味，熏得你直想呕吐。洞门边上
    堆着几个骷髅，想必是一些被洞内妖精吃掉的过往行人的死后所留残骸。
    
LONG);

  set("exits", ([
        "southdown"   : __DIR__"dongting",
      ]));
  set("outdoors", __DIR__);

  setup();
}

void init()
{
  add_action("do_enter","enter");
}

int do_enter(string arg)  //enter baigudong,must dx>100y,and mana>1800
{
    object me;
  if(!arg) return notify_fail("你想进什么？\n");  
  if(arg!="dong"&&arg!="hole"&&arg!="洞"&&arg!="白骨洞")
      return notify_fail("你想进什么？\n");  

      me = this_player();
   message_vision("[1;33m$N深吸了一口气，捏住鼻子，往白骨洞冲了过去。[2;37;0m\n",me);
   if(me->query("obstacle/baigudong")!="done")
    {
   if(me->query_temp("obstacle/baigudong_yao_killed")!="done"||
      me->query_level()<40||me->query_maxmana()<1800)
     {
       message_vision("[1;31m$N冲到洞口，突然一阵黑烟滚过,夹杂着一股熏人腥气。\n$N惊叫一声，昏倒在地上!\n[2;37;0m",me);
       me->unconcious();
       return 1;
     }
    };
   message_vision("[1;35m缭绕的黑烟一碰到$N，顿时四散而去\n[1;36m$N一脚踏进白骨洞![2;37;0m\n",me);
     me->move(__DIR__"dongnei"); 
  return 1;     
}
