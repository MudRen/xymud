inherit __DIR__"r.c";

void create()
{
::create();
set("short","功名");
set("number",7);
set("master","lao ren");
set("exits",([
        "up" : __DIR__"hell",
]));    
set("item_desc",([
        "up" : "上方雾气缭绕，你什么也看不清。\n",
]));
set("objects",([
      __DIR__"npc/jjf"  : 1,
      __DIR__"npc/jjf2" : 4+random(4),
]));
setup();
}  