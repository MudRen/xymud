inherit ROOM; 
#include <ansi.h>

string random_msg();

void create() 
{ 
        set("short", "洞内"); 
        set("long", @LONG
这里是山洞深处，四周四壁之上刻满了古朴繁杂的符文。洞内弥漫着
一个清幽的药香。
    山洞正中，摆放着一个香蒲，它的前方是一个巨大的药炉(lu)。
    由于此地深临地心，有大神通牵引地底熔浆之火，故洞内不显地
寒，反而让人觉得如临春夏。
LONG
); 
	set("no_magic",1);
        set("no_fight",1);
        set("exits", ([ 
                "south" :__DIR__"maze/exit",
                "out"   : "/d/changan/nanyue",
        ]));
	set("channel_id","引气入体");
	set("item_desc", ([
                "lu": "一个巨大的药炉，还能运作，如果将药放(put)进去，说不定还能炼丹(liandan)。\n",
                "out" : "一个小型的传送阵，站在上面，会立时将人传送出去。\n",
	]));                
        setup();
}

void init()
{
	if( this_player()->query_temp("maze/tupo20-2") )
	{
		add_action("do_put","put");
		add_action("do_lian","liandan");
	}	
}

int valid_leave(object who,string dir)
{
	if( dir=="out" )
	{
		if( who->query_level()<20 )
			return notify_fail("机缘难得，你现在就想离开了？\n");
	}
	return ::valid_leave(who,dir);
}

int do_put(string arg)
{
	object ob,me = this_player();
	
	if( !arg || (!wizardp(me) && me->query_level()!=19) )
		return 0;
	if( sscanf(arg,"%s in lu",arg)!=1 )
		return err_msg("这里没有这样东西。\n");
	ob = present(arg,me);
	if( !ob || userp(ob) )
		return err_msg("你身上没有"+arg+"。\n");
	arg = ob->query("name");	
	if( query("yao/"+arg) )
		return err_msg("药炉内你已经放了一株"+ob->name()+"了。\n");
	message_vision("$N将一株$n丢入药炉中。\n",me,ob);
	set("yao/"+arg,1);
	destruct(ob);
	return 1;
}

void finish(object me,int fail)
{
	remove_call_out("finish");
	tell_room(this_object(),"\n药香越来越浓郁起来。\n");
	if( !me || !present(me,this_object()) 
	 || (!wizardp(me) && me->query_level()!=19) )
		return;
	if( random(me->query_kar())<5 )
	{
		call_out("finish",2+random(3),me,fail);
		return;
	}
	message_vision("\n成了！\n",me);
	me->start_busy(5);
	message_vision("$N急不可耐上前掀开炉盖。\n",me);
	if( fail>0 )
	{
		message_vision("\n结果因为药材放错，整味丹药算是毁了，$N只炼了粒灰不溜秋的丸子出来，气得甩手就丢在一旁。\n\n",me);
		delete("yao");
		return;
	}
	if( wizardp(me) 
         || (me->query_level()==19) ) 
	 {
		if( me->level_up() )
		{
			CHANNEL_D->do_channel(this_object(),"rumor","听说"+me->name()+HIM"成功炼出了「"HIY"炼体丹"HIM"」！"NOR);
			tell_object(me,HIY"【系统】你成功炼出了「"HIM"炼体丹"HIY"」，你对天气元气的感悟加深了。\n"NOR);
			tell_object(me,HIG"【系统】你的等级提升了"HIR"1"HIG"级。\n"NOR);
			CHAR_D->setup_char( me );
			UPDATE_D->check_user(me,1);
			me->powerup(0,1);
			me->set_temp("login_data/time", time());
			me->set_temp("login_data/exp", 0);
			me->save();
		}
	}	
}

int do_lian(string arg)
{
	int i;
	string *need,*now;
	mapping yao;
	object me = this_player();
	int fail = 0;

	if( !me->query_temp("maze/tupo20-2") )	
		return 0;
	yao = query("yao");
	if( !yao || !mapp(yao) || sizeof(yao)<1 )
		return err_msg("药炉中是空的。\n");
	if( me->is_busy() )
		return err_msg("你现在正忙着呢。\n");	
		
	need = me->query_temp("tupo20/yao");
	now = keys(yao);
	if( sizeof(need)!=sizeof(now) )
		fail = 1;
	else
	{
		for(i=0;i<sizeof(now);i++)
		{
			if( member_array(now[i],need)==-1 )
			{
				fail = 1;
				break;
			}
		}
	}
	message_vision("\n$N关上炉盖。\n",me);
	me->start_busy(5);
	message_vision("只见药炉上光华一闪，炉身上道符游动，牵动阵法，地底顿时涌起一层地火，烈焰卷动，须臾间便有一股药香传出。\n",me);
	remove_call_out("finish");
	call_out("finish",2+random(3),me,fail);
	return 1;
}
	
