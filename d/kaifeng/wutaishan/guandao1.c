// Room: /u/dragon/kaifengadd/kf2.c

inherit ROOM;

void create()
{
	set("short", "官道");
	set("long", @LONG
        

　　一条宽阔的大道，贯穿南北，直同边关。

LONG);
  set("exits", ([
        "south" : __DIR__"guandao",
        "north" : __DIR__"guandao2",
      ]));

  set("outdoors", __DIR__);

  setup();
  
}


