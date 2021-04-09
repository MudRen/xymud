// created by snowcat 12/2/1997

inherit ROOM;

void create ()
{
  set ("short", "南门");
  set ("long", @LONG

长长的城墙由石条砌就，城门外的护城河已几乎干涸，正中是
一座城楼，设有两扇护铜甲硬木城门，铺有一双行石板大道，
通向城内外。

LONG);

  set("exits", ([
        "north"    : __DIR__"jiedao8",
        "south"    : __DIR__"dalu10",
      ]));
  set("objects", ([
        __DIR__"npc/junshi"    : 2,
      ]));
  set("outdoors",__DIR__"");
  setup();
}

int valid_leave (object who, string dir)
{
  if (! interactive (who) &&
      dir == "south")
    return 0;
  return ::valid_leave(who,dir);
}
