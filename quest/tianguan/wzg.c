inherit __DIR__"r.c";

void create()
{
::create();
set("short","乾坤");
set("number",4);
set("master","zhenyuan daxian");
set("exits",([
        "up" : __DIR__"hyd",
]));    
set("item_desc",([
        "up" : "上方雾气缭绕，你什么也看不清。\n",
]));
set("objects",([
      __DIR__"npc/wzg"  : 1,
      __DIR__"npc/wzg2" : 3+random(4),
]));
setup();
}               

