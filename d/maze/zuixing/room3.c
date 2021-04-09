#include <ansi.h>
inherit ROOM;

void create ()
{
	set ("short", "醉星楼二楼");
  	set ("long", @LONG
这里是醉星楼的一角，迎面就是一根巨大的柱子(zhuzi)。拐角
是一面玉石屏风，上绘嫦娥奔月的故事。
    现在空荡荡的，没有一个人影。
LONG);
	set("item_desc",([
		"zhuzi" : "一根巨大的柱子，撑起了醉星楼的一角，可千万别砍(chop)哦。\n",
	]));	
	setup();
}

void init()
{
	add_action("do_kan", "砍");
  	add_action("do_kan", "chop");
  	add_action("do_kan", "kan3"); 
}

void finish_zuixing(object me)
{
	if( !me )
		return;
	if( !me->query_temp("pendding/jjf_break") )
		return;
	if( me->query_temp("pendding/zuixing_break")!=4 )
		return;
	me->delete_temp("pendding");
	if( !me->is_knowing("jjf_breakxing") )
		me->set_knowing("jjf_breakxing",1);
	CHANNEL_D->do_channel(this_object(),"rumor","听说"HIY+me->name()+HIM"拆了醉星楼！"NOR);
	tell_object(me,HIY"【将军府】恭喜恭喜！你成功拆了醉星楼，你完成了将军府的祖师试炼任务！\n"NOR);
	me->set("shilian","jjf");
	me->move("/d/jjf/qilin2",2);
	message_vision("尉迟恭向$N道喜。\n",me);
	message_vision("尉迟恭说：虽说拆了他们也会重建，老夫就是出了这口气！\n",me);
	if( me->query_level()<50 )
		message_vision("尉迟恭说：我看这位"+RANK_D->query_respect(me)+"很对我的脾气，如想入我门下，尽管开口！\n",me);
}
 
int do_kan(string arg)
{
	string data;
	object me=this_player(), here=this_object(), ob;
  	int x,y,kar=me->query_kar();
 
  	if( (!arg || arg != "柱子") && (arg != "zhuzi" && arg!="pillar"))
    		return err_msg("你要从哪里下手？\n");
  	if( !(ob = me->query_temp("weapon")) )
    		return err_msg("没有顺手的家伙怎么拆得动？\n");
 	if( ob->query("skill_type")=="unarmed" )
 		return err_msg("没有顺手的家伙怎么拆得动？\n");
	if( query("breaked") )
    		return err_msg("柱子都塌了，还砍什么砍？\n");
    	if( me->is_busy() || me->is_fihgting() )
    		return err_msg("你现在正忙着呢。\n");
    	if( me->query("kee")<me->query_maxkee()/4 )
    		return err_msg("你现在太累了。\n");		
  	message_vision("$N用足了劲，将"+ob->name()+"抡圆了砸向彩楼的柱子！只见几片木片四散飞开。\n", me);
  	me->start_busy(1);
  	if( random(kar)>40 )
    	{
    		set("breaked",1);
    		x = query("maze/x");
    		y = query("maze/y");
    		data = x+"_"+y;
    		if( !me->query_temp("pendding/zx_"+data) )
    		{
    			me->set_temp("pendding/zx_"+data,1);	
    			me->add_temp("pendding/zuixing_break",1);
    		}	
    		arg = "只听一声巨响，柱子从中折断，";
      		if( me->query_temp("pendding/zuixing_break")==1 )
      			arg+= "整栋醉星楼传来一阵轰鸣之声，片刻之后声音才渐渐低去。\n";
      		else if( me->query_temp("pendding/zuixing_break")==2 )
      			arg+= "整栋醉星楼传来一阵轰鸣之声，一炷香的光阴之后声音才渐渐低去。\n";
      		else if( me->query_temp("pendding/zuixing_break")==3 )
      			arg+= "整栋醉星楼传来一阵轰鸣之声，很明显感到整栋楼有些倾斜！\n";
      		else	arg+= "整栋醉星楼轰鸣不绝，四下楼板纷纷落下，要塌了！\n";
      		message_vision("\n"+arg+"\n",me);
      		if( me->query_temp("pendding/zuixing_break")==4 )
		{
			finish_zuixing(me);
			return 1;
		}
      		set("long", @LONG
这里曾经是一间华丽无比的房间，但现在只剩一片废墟。几块烂木头
下面到处都是酒杯碗筷的碎片。
LONG);
		set("item_desc",([
			"zhuzi" : "早被人砍坏了，一片狼藉。。。。\n",
		]));
    	}
    	else	write("结果你累了一脖子的粗汗。。。。\n");
  	me->receive_damage("kee", (int)me->query_maxkee()/4);
  	return 1;
}
