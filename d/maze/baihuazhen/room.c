#include <ansi.h>
#include <combat.h>
#include "/cmds/std/valid_move.h"
inherit ROOM;
    
void create()
{
	set("short","花海");
	set("long",@LONG
走了也不知多久，风中突然传来一阵阵甜蜜的花香。这花香不是牡
丹，不是玫瑰，也不是梅，不是菊......这花香甜蜜得竟非世间所有。
LONG);		
        set("no_chuqiao",1);
        set("channel_id","【阵法】");
        set("alternative_die",1);
        set("任务",1);
        set("hell",1);
        setup();
}

string query_enter_file()
{
	string str = query("mazeobj");
	int idx;
	idx = strsrch(str, "/", -1);
	str = str[0..idx-1];
	str+= "/enter";
	return str;
}

int alternative_die(object who)
{
	string start;
	int i,lost;
        object target;
        if( !who )
                return 1;
	//无进入标识                
        if( userp(who) && !who->query_temp("maze/baihuazhen") )
                return 1;
        if( !userp(who) )
        {
        	who->set("no_corpse",1);
		return 1;
	}	
        //玩家死亡
        who->add_temp("maze/baihua_died",1);
        i = who->query_temp("maze/baihua_died");
        if( i<=0 ) i= 1;
        lost = 100;
        lost*= i;
        if( lost>10000 )
        	lost = 10000;
        if( lost>who->query("combat_exp") )
        	lost = who->query("combat_exp");
        if( lost>0 )
        {	
		who->add("combat_exp",-lost);
		tell_object(who,HIG"【百花阵】你损失了"+lost+"点武学。\n"NOR);
	}	
        lost = 100;
        lost*= i;
        if( lost>10000 )
        	lost = 10000;
	lost = lost/2;
        if( lost>who->query("daoxing") )
        	lost = who->query("daoxing");
        if( lost>0 )
        {	
		who->add("daoxing",-lost);
		tell_object(who,HIG"【百花阵】你损失了"+COMBAT_D->chinese_daoxing(lost)+"道行。\n"NOR);
	}
        who->powerup(0,1);
        who->save();
        start = query_enter_file();
        if( !start )
        	start = sprintf("/d/baihuagu/flower%d",1+random(6));
	if( file_size(start+".c")>0 )
        {
        	who->move(start);
		message("vision","\n\n【百花阵】花海翻腾，只见一道血肉模糊的人影跌将出来。。。。\n\n",environment(who),who);
		tell_object(who,"你伤势严重，退回到了起点。\n");
	}
	else
	{
		tell_object(who,HIG"【百花阵】副本地图已被销毁，你退出了副本地图。\n"NOR);
		who->delete_temp("maze");
		who->move(sprintf("/d/city/baihu-w%d",1+random(3)),2);
	}
        return 0;
}                       

void init()
{
	object map;
        add_action("do_cmds","",1);
        if( userp(this_player()) && !this_player()->query_temp("maze/baihuazhen_tu") )
        {
		map = new("/d/baihuagu/obj/map");
        	if( map->write_map(this_player()) )
        	{
        		if( map->move(this_player()) )
        		{
        			tell_object(this_player(),HIG"【百花阵】你得到了百花阵图。\n"NOR);
        			this_player()->set_temp("maze/baihuazhen_tu",1);
        		}
        		else	destruct(map);
        	}
        	else	destruct(map);
        }
}

int valid_leave(object who,string dir)
{
	int i;
	string *strs,file,arg;
	mapping exit;
	object npc;
	if( wizardp(who) && who->query("env/test") )
		return ::valid_leave(who,dir);
	if( !who->query_temp("maze/baihuazhen") )
        	return notify_fail("你是怎么混进来的？！\n");
        exit = query("exits");
        if( !exit || !mapp(exit) || undefinedp(exit[dir]) )
        	return ::valid_leave(who,dir);
        if( !valid_move(who) )
        	return ::valid_leave(who,dir);
 	if( who->query_temp("bhg_zhen")>0 
         && who->query_temp("bhg_zhen")%5==0 )
		return ::valid_leave(who,dir);        	
        exit = ([
                HIR"红玫瑰"NOR 	: "象征着热恋的红玫瑰，娇色欲滴，",
        	HIW"白玫瑰"NOR	: "象征着纯洁与高贵的白玫瑰，晶莹可爱，", 
        	HIM"粉风信子"NOR: "象征着倾慕与浪漫的粉色风信子，清丽芳香",
		HIG"情人草"NOR	: "象征着爱意永恒的情人草，状如云雾，蓬松轻盈，",
        	MAG"熏衣草"NOR	: "象征着等待爱情的熏衣草，紫色浪漫，花香柔和，", 
       		HIC"蝴蝶兰"NOR	: "象征着卿卿我我的蝴蝶兰，娇艳小巧，美丽别致，",
        	HIR"火百合"NOR	: "象征着热烈的爱的火红色百合，明艳灿烂，",
        	HIG"马蹄莲"NOR	: "象征着永结同心的马蹄莲，纯洁甘美，清秀挺拔，",
        	HIW"满天星"NOR	: "象征着纯洁的心的满天星楚楚动人，温柔多情，",
        	HIM"粉金鱼草"NOR: "象征着花好月圆的粉色金鱼草，活泼开朗，",
        	HIC"天堂鸟"NOR	: "象征着热恋中的情侣的天堂鸟，气质高贵，色彩瑰丽，",
        	HIB"勿忘我"NOR	: "象征着眷恋不舍的勿忘我,花姿不凋，花色不褪，",
        	HIY"黄康乃馨"NOR: "象征着长久的友谊的黄色康乃馨，雍容富丽，",
        	HIM"紫丁香"NOR	: "象征着初恋与羞涩的紫丁香，清新淡雅，惹人喜爱，",
        	MAG"紫郁金香"NOR: "象征着永不磨灭的爱情的紫色郁金香，典雅妩媚，", 
        ]);	
        strs = keys(exit);
        arg = strs[random(sizeof(strs))];
        arg = "忽然从花海中飘来一朵"+arg+"，只见这"+exit[arg]+"你不由心神陶醉其中。。。\n";
        i = 1+random(5);
        switch(random(20))
        {
        	case 9 :
        	case 1 : who->start_hunluan(i,arg);break;
        	case 2 :
        	case 8 : who->start_blind(i,arg);break;
        	case 3 :
        	case 7 : who->start_busy(i);break;
        	case 5 : who->start_no_move(i,arg);break;
        	default: return ::valid_leave(who,dir);
        }
        who->receive_damage("kee",who->query_maxkee()/(random(15)+35));
        who->receive_wound("kee",who->query_maxkee()/(random(15)+35));
        who->add_temp("bhg_zhen",1);
        if( random(who->query_temp("bhg_zhen"))>=2 )
        {
        	tell_object(who,arg);
        	who->delete_temp("bhg_zhen");
        	strs = ({"moon","baicaoxian","ningmou",});
        	file = "/d/baihuagu/npc/"+strs[random(sizeof(strs))];
        	npc = find_object(file);
        	if( !npc || !living(npc) )
        		npc = load_object(file);
        	if( npc && living(npc) )
        	{
        		tell_object(who,"\n花海一分，落英缤纷，但见"+npc->name()+"从中露出身影，对你发起了攻击！\n");
        		COMBAT_D->do_attack(npc,who,npc->query_temp("weapon"),TYPE_QUEST);
        	}	
        	return 2;
        }
        return notify_fail(arg);
}

int do_cmds(string arg)
{
        string *nocmds,verb = query_verb();
        nocmds = ({
                "zhenshens","huhuan","recall","zhaohuan",
                "move","maphere","map","exert","cast","perform",
        });
        if( member_array(verb,nocmds)==-1 )
                return 0;
        write("ok\n");
        return 1;
}