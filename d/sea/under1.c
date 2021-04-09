//under1.c

inherit ROOM;

void create ()
{
  set ("short", "海底");
  set ("long", @LONG

到了一个水中世界。海面上波浪汹涌，这里却静得出奇。一群群银
色的小鱼在蓝色的海水中游来游去，脚下是色彩斑斓的珊湖礁，其
中白色的珊瑚连成一线，如一条白云铺成的道路。
LONG);

  set("water", 1);
  set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/yecha" : 2,
]));
  set("exits", ([ /* sizeof() == 2 */
  "up" : "d/changan/eastseashore",
  "east" : __DIR__"under2",
]));
//      
        set("water", 1);
//  
        setup();
}

