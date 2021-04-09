inherit __DIR__"r.c";

void create()
{
::create();
set("short","往昔");
set("number",9);
set("master","qianmian guai");
set("exits",([
        "up" : __DIR__"top2",
]));    
set("item_desc",([
        "up" : "上方雾气缭绕，你什么也看不清。\n",
]));
set("objects",([
      __DIR__"npc/other"  : 1,
      __DIR__"npc/other2" : 1+random(3),
      __DIR__"npc/moon2" : random(2),
      __DIR__"npc/fc2" : random(2),
      __DIR__"npc/hyd2" : random(2),
      __DIR__"npc/hell2" : random(2),
      __DIR__"npc/jjf2" : random(2),
      __DIR__"npc/baihua2" : random(2),
      __DIR__"npc/putuo2" : random(2),
      __DIR__"npc/fc2" : random(2),
]));
set("no_huicheng",1);
setup();
}               

int valid_leave(object me,string dir)
{
if ( !me->query("新任务/门派挑战/千面怪")
  || me->query("新任务/门派挑战/num")<9 )
         {
      return notify_fail("你挑战尚未成功，不能再往上走了！\n"); 
          }
return ::valid_leave(me,dir);
}
