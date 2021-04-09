inherit ROOM;
#include <ansi.h>

string *mark = ({
	"李白","紫霞仙子","白眉","镇元大仙","黄飞虎","西王母",
	"白发老人","阎罗王","大鹏明王","玉鼠精","观音菩萨",
	"菩提祖师","敖广","凝眸仙子",
});     

int do_list();

void create ()
{
	set("short", "战斗区");
	set("long","\n\n\n\n");
	set("no_quit",1);
	set("no_flee",1);
	set("alternative_die",1);
	set("channel_id","挑战任务");
     set("virtual_room",1);
	setup();
}

int is_tiaozhan(){return 1;}

int get_player(object who)
{
	int i;
	object *inv;
	if( !who )
		return 0;
	inv = all_inventory(who);
	for(i=0;i<sizeof(inv);i++)
		if( userp(inv[i]) )
			return 1;
	return 0;
}				
	
void alternative_die (object me)
{
	string log;
	object npc,ob,*inv;
	int i;
	if( !me )
		return;
	me->remove_all_killer();
	all_inventory()->remove_killer(me);
	if( userp(me) )
	{
		if( time()<me->query("mark/tiaozhan/last_die")+3600      	//假死时间没到
	     || me->query("combat_exp")<10000
	     || me->query("daoxing")<10000 
	     || !me->query("obstacle/reward") )
		{
			delete("alternative_die");
			me->set("mark/tiaozhan/last_out",time());
			me->die();
			log = sprintf("%s %s 因假死时间未到|WD不足，而在挑战地图 %s 中真死.\n",ctime(time()), me->query("id"), query("short") );
			log_file("挑战死亡记录",log);			   
			set("alternative_die",1);
			return;
		}
		me->set("mark/tiaozhan/last_die",time());	
		me->set("kee", 100);
		me->set("sen", 100);
		me->set("force",100);
		me->set("mana",100);
		me->clear_condition();
		me->delete_temp("no_move");
		me->set("eff_kee",me->query("max_kee"));
		me->set("eff_sen",me->query("max_sen"));
		me->add("combat_exp",-3000);
		me->add("daoxing",-3000);
		me->save();
		message_vision("\n$N「啪」的一声倒在地上，挣扎着抽动了几下就死了。\n",me);    
		message_vision ("地下传来崔判官的声音：门派切磋之争，不伤阳寿！\n",me);
		message_vision("\n一道青烟随之升起，$N在烟雾中挣扎着抽动了几下，又慢慢的站起来了。。。。\n",me); 
		message_vision ("\n崔判官将$N传回客栈。\n",me);
		me->set("mark/tiaozhan/last_out",time());
		if( !me->move("/d/city/kezhan") )
			me->move("/d/kaifeng/tieta");
		return;
	}		
//NPC
	if( !me->is_job() )
	{
		message_vision(HIY"\n金光一闪，$N"HIY"顿时化为灰灰。\n\n"NOR,me);    
		destruct(me);
		return;
	}
	ob = me->query_temp("last_damage_from");
	if( !ob || !userp(ob) || !living(ob) || !present(ob,environment(me)) )
	{
		message_vision("\n$N「啪」的一声倒在地上，挣扎着抽动了几下就死了。\n",me);    
		message_vision("\n一道青烟随之升起，$N在烟雾中挣扎着抽动了几下，又慢慢的站起来了。。。。\n",me);			  
		me->powerup(1);
		return;
	}
//MASTER	
	if( query("master")==me->query("id") )
	{
		npc = present("di zi",environment(me));
		if( npc && !userp(npc) && npc->is_job() )
		{
			me->command("say 先将门下弟子打败再说！");
			me->powerup(1);
			return;
		}

		message_vision("\n$N「啪」的一声倒在地上，挣扎着抽动了几下就死了。\n",me);      
		me->reward_ob(ob);
		destruct(me);
		return; 
	}			       
//DIZI	
	message_vision("\n$N「啪」的一声倒在地上，挣扎着抽动了几下就死了。\n",me);    
	me->reward_ob(ob);
	destruct(me);
	return;
}

int valid_leave(object who,string dir)
{
	int i;  
	if( who->is_fighting() )   
		return notify_fail("你停住了脚步专心备战。\n");
	if( get_player(who) )
		return notify_fail("你要先将身上的玩家放下。\n");
	i = query("number");
	if( !who->query("mark/tiaozhan/"+mark[i-1]) )
		return notify_fail("此关你尚未闯过，如何走得？\n");
	return ::valid_leave(who,dir);
}

int do_list()
{
	string *t,*k,tmp,str="";
	int i;  
	mapping kk,tt = ([
		"李白"		: "墨香",	
		"紫霞仙子"	: "前世",
		"白眉"		: "磨砺",
		"镇元大仙"	: "乾坤",
		"黄飞虎"	: "离火",
		"西王母"	: "昆仑",
		"白发老人"  : "功名",
		"阎罗王"	: "奖惩",
		"大鹏明王"	: "野望",
		"玉鼠精" 	: "地涌",
		"观音菩萨"  : "净土",
		"菩提祖师"  : "菩提",
		"敖广"	  	: "无量",		
		"凝眸仙子"  : "凝香",
	]);
	object me = this_player();
	kk = me->query("mark/tiaozhan");
	if( !kk || !mapp(kk) )
		return err_msg("你星月挑战尚未有建树。\n");

	str+= "星月挑战总共以下各关：\n";
	t = keys(tt);
	k = keys(kk);
	for(i=0;i<sizeof(mark);i++)
	{
		str+= sprintf("\t%20s",HIC+tt[mark[i]]+NOR);
		if( member_array(mark[i],k)==-1 )
			str+= "\t("HIR"未完成"NOR")\n";
		else    
			str+= "\t("HIY"已完成"NOR")\n";
	}	       
	if( 3600-time()+me->query("mark/tiaozhan/last_die")>0 )
		str+= "离下一次假死还有"+FINGER_D->age_string(3600-time()+me->query("mark/tiaozhan/last_die"))+"。\n";      
	if( me->query("combat_exp")<10000 || me->query("daoxing")<10000 )
		str+= HIY"你的武学、道行不足，在挑战地图内不受死亡保护。\n"NOR;
	tell_object(me,str);
	return 1;
}
	
void reset()
{
	int i;
	object *inv;
	if( query("master") && objectp(present(query("master"),this_object())) )
		return;
	tell_room(this_object(),"\n\n一声巨响，天地好似都在震动。。。。\n\n\n");
	inv = all_inventory();
	for(i=0;i<sizeof(inv);i++)
	{
		if( inv[i] && !inv[i]->is_fighting() 
		&& !inv[i]->is_job() && !wizardp(inv[i]) )
		{
			message_vision("一阵天旋地转中，$N脚下一滑，不见了踪影！\n\n",inv[i]);
			if( !userp(inv[i]) )
				destruct(inv[i]);
			else    
				MISC_D->random_capture(inv[i],1,1);
		}
	}
	::reset();
}

void init()
{
        if( get_player(this_player()) ){
             this_player()->move("/d/dntg/sky/beitian",2);
             tell_object(this_player(),"你要先将身上的玩家放下。\n"); 
             return;
        }
	add_action("do_list","list");
}
