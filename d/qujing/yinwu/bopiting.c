// created by snowcat 12/2/1997

inherit ROOM;

void create ()
{
  set ("short", "剥皮亭");
  set ("long", @LONG

山洞里一座六角石亭，亭子上爬满蔓草青苔，亭内有石桌石椅
石凳。北面有通道引向后园，东面是天井，西面是中堂，东南
边有一洞穴入口。

LONG);

  set("exits", ([
        "north"    : __DIR__"houyuan",
        "west"    : __DIR__"zhong",
        "east"    : __DIR__"tianjing",
        "southeast"    : __DIR__"rouku",
      ]));
  set("objects", ([
        __DIR__"npc/yaojing" : 2,
      ]));
  setup();
}
