#include <ansi.h>
inherit ROOM;

string *fo = ({
		"楞严经","华严经","药师经","圆觉经","僧伽吒经",
		"无量寿经","佛本行经","佛遗教经","妙法莲华经",
		"佛说盂兰盆经",
});
string *dao = ({
		"黃庭经","朝天宝懺","通玄真经","老君西升经",
		"元始无量度人上品妙经","南华真经",
		"三论元旨","道德经","太乙救苦天尊",
		"阴符经","文始真经","灵官经",
});

string check_me()
{
	string str,*q1,*q2;
	int i;
	object who = this_player();
	if( !who->query_temp("pending/quest") )
		return 0;
	if( !arrayp(q1 = who->query_temp("maze/xiaoyan_fojing"))
	 || sizeof(q1)<1 )
		return 0;
	if( !arrayp(q2 = who->query_temp("maze/xiaoyan_daojing"))
	 || sizeof(q2)<1 )
		return 0;
	str = "一方霞光闪耀的书架，以玉石雕刻而成，虽小巧玲珑，却也给人以灵气澎湃的感觉。\n";
	str+= "书架分两层，上层是佛经，依次摆放着：\n  ";
	for(i=0;i<sizeof(q1);i++)
	{
		str+= q1[i];
		if( i<sizeof(q1)-1 )
			str+= "、";
		if( i%5==4 )
			str+="\n  ";	
	}
	str+= "\n下面那层则摆着道经，依次是：\n  ";
	for(i=0;i<sizeof(q2);i++)
	{
		str+= q2[i];
		if( i<sizeof(q2)-1 )
			str+= "、";
		if( i%5==4 )
			str+="\n  ";
				
	}
	str+= "\n每本经籍位置有些古怪，似乎可以推(tui)一下。\n";
	str+= "书架一旁则有数行娟秀的小字(zi)。\n";
	return str;
}

string tell_me()
{
	object who = this_player();
	if( who->query_temp("maze/xiaoyan_zi") )
		return (who->query_temp("maze/xiaoyan_zi"));
	return 0;	
}
    
void create()
{
	set("short","小雁塔副本");
        set("channel_id","小雁塔副本");
        set("alternative_die",1);
        set("item_desc",([
                "shu jia" : (: check_me :),
		"zi"  : (: tell_me :),
	]));
        setup();
}

void alternative_die(object who)
{
	int i,lost;
        object target;
        string file;
        if( !who )
                return;
	//无进入标识                
        if( userp(who) && !who->query_temp("maze/xiaoyan") )
        {
                set("alternative_die",0);
                who->die();
                set("alternative_die",1);
                return;
        }
//        message_vision ("\n$N「啪」的一声倒在地上，挣扎着抽动了几下就死了。\n\n",who);          
        if( !userp(who) )
        {
                target = who->query_temp("last_damage_from");
                who->clear_condition();
                if( target && present(target,this_object()) 
                 && ( wizardp(target)
                   || (target->query_level()>24&&target->query_level()<30)) ) 
                        who->reward_ob(target);
                if( who )  destruct(who);
                return;                         
        }
        //玩家死亡
        who->powerup(0,1);
        file = sprintf("/data/maze/%s/xiaoyan-ta/enter.c",who->query("id"));
        if( file_size(file)>0 )
        {
        	who->move(file,2);
		message_vision("\n\n一干沙弥七手八脚将血肉模糊的$N抬了过来。一旁的法明长老慌忙赶紧上前，抢救了半天，才把$N从鬼门关救了回来。。。。\n\n",who);
	}
	else
	{
		tell_object(who,HIG"【副本】小雁塔：地图已被销毁，你退出了副本地图。\n"NOR);
		who->delete_temp("maze");
		who->move(sprintf("/d/city/baihu-w%d",1+random(3)),2);
	}
        return;
}                       

void init()
{
	object me = this_player();
	if( userp(me) )
	{
        	add_action("do_cmds","",1);
        	add_action("do_tui","tui");
        	add_action("do_tui","push");
        	if( !me->query_temp("maze/xiaoyan_type")
        	 && !query("type_set") )
        	{
        		if( random(2) )
        			me->set_temp("maze/xiaoyan_type","kill");
        		else	me->set_temp("maze/xiaoyan_type","quest");	
        		set("type_set",1);
        	}
        }
}

void create_guai(object who)
{
	object guai;
	int i;
	if( !who || !living(who) 
	 || !present(who,this_object()) )
	 	return;
	i = 1+random(2);
	message_vision("\n忽然一阵脚步传来，从甬道深处跑出"+chinese_number(i)+"个汉子，不由分说，朝着$N就展开了攻击！\n",who);
	while(i--)
	{
		guai = new("/d/maze/xiaoyan-ta/npc/guai");
		if( guai->move(this_object()) )
			guai->kill_ob(who);
		else
		{
			if( guai ) destruct(guai);
			continue;
		}	
	}
}

void init_quest(object who)
{
	string q1,q2,an1,an2,*quest1,*quest2,str,*tian,*di,*ff,*dd,temp;
	int i;
	if( !who || !living(who) 
	 || !present(who,this_object()) )
	 	return;
	tian = ({ "甲","乙","丙","丁","戊","己","庚","辛","壬","癸", });	
	di = ({ "子","丑","寅","卯","辰","巳","午","未","申","酉","戌","亥",});	
	quest1 = quest2 = ({});
	ff =  fo;
	dd =  dao;
	for(i=0;i<sizeof(fo);i++)
	{
		temp = ff[random(sizeof(ff))];
		ff-= ({temp});
		quest1+= ({temp});
	}
	for(i=0;i<sizeof(dao);i++)
	{
		temp = dd[random(sizeof(dd))];
		dd-= ({temp});
		quest2+= ({temp});
	}
	i = random(10);
	an1 = quest1[i];
	q1 = tian[i];
	i = random(12);
	an2 = quest2[i];
	q2 = di[i];
	who->set_temp("maze/xiaoyan_a1",an1);
	who->set_temp("maze/xiaoyan_a2",an2);
	str = "一行娟秀的小字写道：\n";
	str+= "此间洞府为余藏书之所，余好以天干谈佛，以地支论道。\n";
	str+= "今日余心血来潮，以「"+q1+q2+"」为此地通行密语。\n";
	who->set_temp("maze/xiaoyan_zi",str);
	who->set_temp("maze/xiaoyan_fojing",quest1);
	who->set_temp("maze/xiaoyan_daojing",quest2);
	who->set_temp("pending/quest",1);
        message_vision(HIC"霞光一闪，凭空忽然出现了一个玉石书架(shu jia)，正好挡住了你的去路。\n"NOR,who);
	who->start_busy(1);
}

void create_quest(object who)
{
	if( !who || !living(who) 
	 || !present(who,this_object()) )
	 	return;
	if( !who->query_temp("maze/xiaoyan_zi") 
	 && who->query_temp("maze/xiaoyan_type")=="quest" )
	 	init_quest(who); 		 	
}

int valid_leave(object who,string dir)
{
	if( !who->query_temp("maze/xiaoyan") )
        	return notify_fail("你是怎么混进来的？！\n");
        if( who->query_temp("pending/quest") )
        	return notify_fail("眼前那霞光阵阵的玉石书架(jia)挡住了你的去路。\n");
	if( !who->query_temp("maze/xiaoyan_type") )
        	return ::valid_leave(who,dir);
        switch(who->query_temp("maze/xiaoyan_type"))
        {
        	case "kill" :
        		create_guai(who);
        		who->delete_temp("maze/xiaoyan_type");
        		return 2;
        	case "quest":
        		create_quest(who);
        		return 2;
        	default	: return ::valid_leave(who,dir);
        }	
}

int do_cmds(string arg)
{
        string *nocmds,verb = query_verb();
        nocmds = ({
                "zhenshens","huhuan","recall","move","maphere","map",
        });
        if( member_array(verb,nocmds)==-1 )
                return 0;
        write("ok\n");
        return 1;
}

int do_tui(string arg)
{
	object who = this_player();
	if( !who->query_temp("maze/xiaoyan_zi") 
	 || who->query_temp("maze/xiaoyan_type")!="quest" )
	 	return 0;
	if( !arg )
	 	return err_msg("你推了推书架，却是啥反应也没有。\n");
	if( member_array(arg,fo)==-1 
	 && member_array(arg,dao)==-1 )
	 	return err_msg("你要推哪本书？\n");
        if( arg!=who->query_temp("maze/xiaoyan_a1") && arg!=who->query_temp("maze/xiaoyan_a2") )
                  return 1;
	message_vision("$N将书架上的【"HIY+arg+NOR"】摆正了一下。\n",who);
	if( arg==who->query_temp("maze/xiaoyan_a1") )
		who->set_temp("maze/jiguan1",1);
	if( arg==who->query_temp("maze/xiaoyan_a2") )
		who->set_temp("maze/jiguan2",1);
	if( who->query_temp("maze/jiguan1")
	 && who->query_temp("maze/jiguan2") )
	{	 
		message_vision("\n\n“嘎嘣”一声，书架上传出一阵机括之声，霞光一闪，书架渐渐淡去。。。。\n\n",who);
		who->delete_temp("maze/xiaoyan_type");
		who->delete_temp("maze/jiguan2");
		who->delete_temp("maze/jiguan1");
		who->delete_temp("maze/xiaoyan_zi");
		who->delete_temp("maze/xiaoyan_a1");
		who->delete_temp("maze/xiaoyan_a2");
		who->delete_temp("maze/xiaoyan_fojing");
		who->delete_temp("maze/xiaoyan_daojing");
		who->delete_temp("pending/quest");
		tell_object(who,HIG"前方已通，赶紧走吧。\n"NOR);
	}
	else	message_vision("书架上霞光一闪，结果什么反应也没有。\n",who);
	return 1;
}
