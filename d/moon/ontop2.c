inherit ROOM;

void create ()
{
	set ("short", "玉女峰顶");
  	set ("long", @LONG
祥云光满，瑞霭香浮。在这冰天雪地里居然还有如此仙境。这里正是独立
云海，傲越千山的昆仑极顶。靠南似乎有一条下山的小路。靠北则有一圈
篱笆，围着几间精致的小屋，入口处有一株桂树(tree)。往东可望见一片
杏林。

LONG);
	set("item_desc", ([ 
		"tree" : "一株高耸入云的大桂树 。上面无数的桂花正散发出阵阵清香，不知道怎样才能采集到。",
	]));
  	set("objects", ([
  		__DIR__"obj/guishuzhi" : 2,
  		__DIR__"npc/wugang" : 1,
  		__DIR__"npc/yutu" : 1,
	]));
  	set("outdoors","moon");
  	set("exits", ([ 
  		"east" : __DIR__"yltw",
  		"west" : __DIR__"fabao-road1",
  		"north" : __DIR__"xiaoyuan",
  		"southdown" : __DIR__"neartop",
	]));
	setup();
}

void init()
{
	add_action("do_climb", "climb");
  	add_action("do_kan", "kan");
}

int do_climb(string arg)
{
	object wugang;
  	object me=this_player();
 
  	if( (!arg) || !((arg == "tree") || (arg == "桂树")))
		return notify_fail("爬什么？\n");
  	if( me->is_busy()) return notify_fail("你现在正忙着呢。");
  	if( me->query("kee") < (int)(me->query_maxkee()/3) )
  	{
    		me->receive_damage("kee",(int)me->query_maxkee()*20/100);
    		return notify_fail("你身子发虚，一头栽了下来，哎呀！\n");
	}
  	if( (int)me->query_skill("dodge", 1)<40 && (int)me->query_skill("moondance", 1) < 80)
        {
		message_vision("$N小心翼翼的往上爬了一点，觉得头晕眼花，就赶紧爬了下来．\n", me);
          	me->improve_skill("dodge", 40-me->query("str"));
          	tell_object(me, "你领悟出一些基本轻功方面的窍门。\n");
        }
      	else
        {
		message_vision("$N纵身往桂树上一跳，接着爬入树丛中不见了。\n", me);
          	me->move(__DIR__"tree1.c");
        }
	me->receive_damage("kee", (int)me->query_maxkee()*10/100);
  	return 1;
}

int do_kan(string arg)
{
  	object me=this_player();
  	object ob; 
  	object wugang;
  	if( (!arg) || !((arg == "tree") || (arg == "桂树")))
    		return notify_fail("你要砍什么？\n");
    	if( me->is_busy()) 
    		return notify_fail("你现在正忙着呢。");
   	if( !(ob = me->query_temp("weapon"))|| (string)ob->query("skill_type") != "axe")
    		return notify_fail("先去找把斧头吧！\n");
  	if( me->query("kee") < (int)(me->query_maxkee()/3))
    		return notify_fail("再砍下去手都要磨破了！\n");
  	if( !((string)me->query("family/family_name")=="月宫" )
  	 && objectp(wugang = present("wugang", environment(me))) && living(wugang) )
    	{
      		message_vision("吴刚拦道：此间并非戏耍之处，请勿骚扰我仙家清修!\n",me);
    	}
  	else
    	{
      		message_vision("$N朝桂树使劲儿砍了几下．\n", me);
      		if( (int)me->query_skill("unarmed", 1)< 50 )
        	{
          		me->improve_skill("unarmed", me->query("str"));
          		tell_object(me, "累了个臭死，你总算领悟出一些运劲使力方面的窍门。\n");
        	}
      		else 
      		{
			tell_object(me, "你试着砍了几下，不明白为什么有人会做这种傻事。\n"); 
		}
	}
  	me->receive_damage("kee", (int)me->query_maxkee()*10/100);
  	return 1;
}
