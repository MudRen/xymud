inherit __DIR__"r.c";

void create()
{
::create();
set("short","地涌");
set("number",10);
set("master","yu shu");
set("exits",([
         "up" : __DIR__"putuo",
]));    
set("item_desc",([
        "up" : "上方雾气缭绕，你什么也看不清。\n",
        "west" : "上方雾气缭绕，你什么也看不清。\n",
]));
set("objects",([
      __DIR__"npc/wdd"  : 1,
      __DIR__"npc/wdd2" : 4+random(3),
]));
setup();
}               

