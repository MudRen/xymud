#include <ansi.h>
inherit ROOM;

string *gg = ({
	"yg-baihuagu","yg-dragon","yg-moon","yg-putuo",
	"yg-shushan","yg-wudidong","yg-xueshan",
});	
   
void create()
{
        set("short","建木遗迹副本");
        set("channel_id","建木遗迹副本");
        set("alternative_die",1);
        set("item_desc",([
                "west" : "叠叠松涛，阵阵树摇。\n",
                "east" : "叠叠松涛，阵阵树摇。\n",
                "north" : "叠叠松涛，阵阵树摇。\n",
                "south" : "叠叠松涛，阵阵树摇。\n",
        ])); 
        setup();
}

void alternative_die(object who)
{
        object target;
        string file,msg;
        if( !who )
                return;
        if( !userp(who) )
        {
                target = who->query_temp("last_damage_from");
                who->clear_condition();
                if( target && present(target,this_object()) 
                 && ( (target->query_level()==39&&target->query("combat_exp")>=16100000) ||wizardp(target) ) )
                        who->reward_ob(target);
                else    message_vision(HIY"$N"HIY"「啪」的一声倒在地上，挣扎着抽动了几下就死了。\n"NOR,who);
                if( who )  destruct(who);
                return;                         
        }
        //玩家死亡
        target = who->query_temp("last_damage_from");
        
        who->powerup(0,1);
        if( random(2) )
                msg = COMBAT_D->status_msg((1+random(5))*10);
        else    msg = COMBAT_D->eff_status_msg((1+random(5))*10);
        message_vision(NOR"\n( $N"+msg+NOR")\n",who);
        message_vision("\n"HIC"$N"HIC"身子一歪，直接从悬崖边跌落下去，幸亏有大机缘，在半空被一根烂草挡了一下，方才性命无忧。\n"NOR,who);  
        file = sprintf("/data/maze/%c/%s/tupo40-2/enter.c",who->query("id")[0],who->query("id"));
        if( file_size(file)>0 )
        	who->move(file,2);
	else
	{
		tell_object(who,HIG"【副本】建木遗迹：地图已被销毁，你退出了副本地图。\n"NOR);
		who->delete_temp("maze");
		who->move("/d/moon/tree2",2);
	}
	                
        who->set("kee",100);
        who->set("eff_kee",100);
        who->set("sen",100);
        who->set("eff_sen",100);
        who->set("force",0);
        who->set("mana",0);
        
        who->set("maze/tupo-40",time());
        return;
}                       

void init()
{
        if( userp(this_player()) )
        {
        	this_player()->add_temp("maze/road",1);
                add_action("do_cmds","",1);
                add_action("do_drop","drop");
        }
}

int do_drop(string arg)
{
	return ("/d/city/droproom.c")->do_main(arg);
}

int do_cmds(string arg)
{
        string *nocmds,verb = query_verb();
        nocmds = ({
                "recall","move","maphere","map",
        });
        if( member_array(verb,nocmds)==-1 )
                return 0;
        write("ok\n");
        return 1;
}

int valid_leave(object who,string dir)
{
	int i,lvl,k;
        object guai;
        if( !userp(who) )
                return ::valid_leave(who,dir);
        if( who->is_fighting() )
                return notify_fail("你现在正忙着呢。\n");
                
        if( query("create") )
                return ::valid_leave(who,dir);
	if( who->query_temp("maze/road")%5!=0 )
		return ::valid_leave(who,dir);
	i = 2+random(2)+random(2);
	k = 0;
	while(i--)
	{
		guai = new("/d/maze/tupo40-2/npc/"+ gg[random(sizeof(gg))] );
		if( who->query_temp("maze/road")>30 )
			lvl = ({5,4})[random(2)];
		else if( who->query_temp("maze/road")>25 )
			lvl = ({4,5,4,4})[random(4)];
		else if( who->query_temp("maze/road")>20 )
			lvl = ({2,3,3,4})[random(4)];
		else if( who->query_temp("maze/road")>15 )
			lvl = ({1,2,2,3})[random(4)];
		else if( who->query_temp("maze/road")>10 )
			lvl = ({1,1,1,2})[random(4)];
		else	lvl = 1;
		guai->remove_all();
		guai->init_name(lvl);
		guai->init_texing();
		if( guai->move(this_object()) )
		{
			message_vision(HIG"\n树木一阵晃动，从里面走出一个奇形怪状的怪物！\n"NOR,who);
			k++;
		}
		else if( guai )
			destruct(guai);
	}
	set("create",1);
	if( k>0 )
		return notify_fail("你不由疑惑的停住了脚步。\n");
	return ::valid_leave(who,dir);	
}