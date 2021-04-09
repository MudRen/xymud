// rewritten by snowcat on 4/11/1997
// room: huoyan

inherit ROOM;

void create ()
{
  set ("short", "火焰山");
  set ("long", @LONG

火，火，火！！！

大火绵延八百里，四周寸草不生。据说当年太上老君的炼丹炉被蹬
翻，几块炉砖掉在此处，即化为火焰山。人一走进去既成烟灰，更
勿提东南西北。

LONG);

  set("exits", ([
        "westdown" : __DIR__"huoyan",
        "eastdown" : __DIR__"huoyan",
        "northup"  : __DIR__"huoyan",
        "southup"  : __DIR__"huoyan",
      ]));
  set("outdoors", "firemount");
  set("burning_mount",1);
  setup();
}

void burnt (object me)
{
	if( ! me)
    		return;
	if( environment(me) != this_object())
    		return;
	if( random(8) == 0)
  	{
    		message_vision("一股热浪袭来，将$N往上一抛，$N飞了出去！\n",me);
    		me->move(__DIR__"shanbian");
    		message_vision("$N冒着浓烟从山上滚了下来！\n",me);
		me->unconcious();
    		return;
  	}
  	else if( random(2) == 0)
  	{
    		object ob;
    		object *inv = all_inventory(me);
    		if( sizeof(inv) == 0)
      			return;
    		ob = inv[random(sizeof(inv))];
    		if( ob && !ob->query("no_get") 
    		 && ob->move(this_object()))
      		{
   			if(  ob->is_character() )
         		{
         			ob->revive(1);
         			message_vision("只见火焰一舔，$N身上的$n落将在地！\n",me,ob);
         		}
   			else  
   			{
        			message_vision("只见火焰一舔，$N的$n顿时化为灰烬！\n",me,ob);
          			destruct(ob);
         		}
         		return;
    		}
  	}
  	else 
  	{
    		switch (random(4))
    		{
      			case 0:{ message_vision("$N的头发冒起一股青烟！\n",me); break; }
      			case 1:{ message_vision("$N身上滋滋作响！\n",me); break; }
      			case 2:{ message_vision("$N的脸上膨起几个大水疱！\n",me); break; }
      			case 3:{ message_vision("$N发出一股焦味！\n",me); break; }
    		}
  	}
  	if(me->query("kee") > 15)
    		me->add("kee",-5-random(10));
  	if(me->query("sen") > 15)
    		me->add("sen",-5-random(10));
  	call_out ("burnt",random(5)+15,me);
}

void init()
{
	if( userp(this_player()) )
		call_out ("burnt",random(5)+15,this_player());
}

