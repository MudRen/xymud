//Cracked by Roath
inherit ROOM;
#include <room.h>
void create ()
{
  set ("short", "青石崖");
  set ("long", @LONG

蓬莱岛上风光秀丽，当真是好去处！高崖上视野开阔，远望四周，
把蓬莱景色看的清清楚楚。远处大海如明镜般平整。山崖上长有
无数异草，飘着淡淡香气。
LONG);
  set("exits", ([ /* sizeof() == 3 */
//  "south" : __DIR__"road1",
]));
        set("outdoors", 1);
  setup();
}
void grass_grow()
{
        object grass;
        seteuid(getuid());
        if(grass=new("/d/obj/drug/qiongcao")){
                grass->move(this_object());
                grass->invocation();
        }
        return;
}


void init()
{
   object cao;
    object me=this_player();
   if (!cao=present("qiong cao",environment(me)) )
     {
        grass_grow();
        return ;
     }
   return ;
}   
        


