inherit __DIR__"r.c";

void create()
{
::create();
set("short","无量");
set("number",13);
set("master","ao guang");
set("exits",([
        "up" : __DIR__"baihua",
]));    
set("item_desc",([
        "up" : "上方雾气缭绕，你什么也看不清。\n",
]));
set("objects",([
      __DIR__"npc/sea"  : 1,
      __DIR__"npc/sea2" : 4+random(3),
]));
setup();
}               

