inherit __DIR__"r.c";

void create()
{
::create();
set("short","净土");
set("number",11);
set("master","guanyin pusa");
set("exits",([
        "up" : __DIR__"fc",
]));    
set("item_desc",([
        "up" : "上方雾气缭绕，你什么也看不清。\n",
]));
set("objects",([
      __DIR__"npc/putuo"  : 1,
      __DIR__"npc/putuo2" : 4+random(4),
]));
setup();
}               

