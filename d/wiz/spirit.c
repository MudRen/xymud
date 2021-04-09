// by night
// fid 修改

inherit ROOM;
#include <ansi.h>
void create ()
{
  set ("short", HIY"精灵楼"NOR);
  set ("long", @LONG
由夜精灵所筑，临窗的地上铺著猩红毛毯，楼阁正面设著大红金钱
蟒靠背，石青金钱蟒引枕，秋香色金钱蟒大条褥。两边设一对梅花式
红漆小几，几上茗琬瓶花俱备，还有一个翡翠所造的箱子。
LONG);

  	set("exits", ([
        "east" : __DIR__"entrance",
//        "down" : __DIR__"kezhan",
      ]));
  	set("objects", ([
        	__DIR__"npc/spirit" :  1,
      ]));
  	set("no_fight", 1);
   	set("no_magic", 1);

  setup();
}
void init()
{
    add_action("block_cmd", "", 1);
}

int block_cmd(string args)
{
string verb;
verb = query_verb();

    if (verb == "kill") return 1; 
    if (verb == "bian") return 1; 
    if (verb == "ji") return 1; 
    if (verb == "xiudao") return 1;
    if (verb == "exert") return 1;
    return 0;
}

