inherit __DIR__"r.c";

void create()
{
::create();
set("short","野望");
set("number",9);
set("master","dapeng mingwang");
set("exits",([
         "up" : __DIR__"wdd",
]));    
set("item_desc",([
        "up" : "上方雾气缭绕，你什么也看不清。\n",
        "west" : "上方雾气缭绕，你什么也看不清。\n",
]));
set("objects",([
      __DIR__"npc/xs"  : 1,
      __DIR__"npc/xs2" : 4+random(3),
]));
setup();
}               

