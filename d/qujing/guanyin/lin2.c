inherit ROOM;

void create ()
{
  set ("short", "林道");
  set ("long", @LONG

但见山林锦翠色，到处都是飞禽走兽，给你一种赏心悦目的
感觉。远远看到山凹里面有楼台影影，殿阁沉沉，
LONG);
 
  set("exits", ([
        "northeast"      : __DIR__"lin1",
        "west"   :  __DIR__"lin3",
      ]));

  set("outdoors", __DIR__);

  setup();
}

