// Room: some place in 西牛贺洲
// inside2.c
#include <ansi.h>
inherit ROOM;

void create ()
{
  set ("short", "讲经堂");
  set ("long", @LONG

这里是三星洞的讲经堂，平时道士们便在这里讲经说法。若是
有什么大事，也在这里集会商议。左右整整齐齐地放着四五十
个软垫，也坐了一二十个道士。
LONG);

  set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"houlang1.c",
  "southdown" : __DIR__"inside1.c",
]));
  set("objects", ([ /* sizeof() == 2 */
  __DIR__"npc/xiao" : 1,
  __DIR__"npc/yunyang" : 1,
]));
  set("valid_startroom", 1);

  setup();
}

void init()
{
	add_action("do_hear","hear");
}

int do_hear()
{
	object me=this_player();
  	if( !query("jiangjing") || (string)me->query("family/family_name")!="方寸山三星洞" )
     		return 0;
	if(me->is_busy())
      		return notify_fail("你正忙着呢。\n");
      	if( me->query("kee")<30 || me->query("sen")<30 )
      		return notify_fail("你现在太累了。\n");
	if(me->query("faith")<10 )
		return notify_fail("你的师门贡献不够。\n");
	tell_object(me,"你在旁闻听，若有所悟，不禁眉花眼笑。\n");
  	me->start_busy(5);
   	me->improve_skill("dao",1+random(me->query_spi()+me->query_int())/2);
   	me->improve_skill("wuxiangforce",1+random(me->query_spi()+me->query_int())/2);
	me->add("faith",-10);
	me->receive_damage("kee",20);
   	me->receive_damage("sen",20);
  	return 1;
}

int valid_leave(object me, string dir)
{
        if (dir == "up" ) {
        if (objectp(present("master yunyang", environment(me)))) {
	if((string)me->query("family/family_name")=="方寸山三星洞") {
		if((int)me->query("family/generation") < 2) {
			me->set("family/generation", 2);
			me->set("title", "方寸山三星洞第二代弟子");
		}
	if((string)me->query("family/master_name")=="菩提祖师") {
		me->set("pending/kick_out",1);
	}
	return ::valid_leave(me, dir);
	}
        return notify_fail("云阳真人说道：祖师清修，少见外人，您还是请回吧！\n");
	}
	}
        return ::valid_leave(me, dir);
}

