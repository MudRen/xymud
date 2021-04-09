#include <ansi.h>
inherit ROOM;
    
void create()
{
        set("short","始皇陵一层副本");
        set("channel_id","始皇陵一层副本");
        set("alternative_die",1);
        set("item_desc",([
                "west" : "这里黑布隆冬的，你看不清楚。\n",
                "east" : "这里黑布隆冬的，你看不清楚。\n",
                "north" : "这里黑布隆冬的，你看不清楚。\n",
                "south" : "这里黑布隆冬的，你看不清楚。\n",
        ])); 
        set("guai1",2+random(3));
        set("guai2",1+random(2));
        set("guai3",random(2)); 
        setup();
}

void alternative_die(object who)
{
        int i,lost;
        object target;
        string file,msg;
        if( !who )
                return;
        if( !userp(who) )
        {
                target = who->query_temp("last_damage_from");
                who->clear_condition();
                if( target && present(target,this_object()) 
                 && (target->query_level()<40||wizardp(target)) )
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
        message_vision("\n"HIW"$N"HIW"跌跌撞撞的向外逃去。\n"NOR,who);  
        
        lost = 5000;
        lost = lost*9/10+random(lost/10);
        if( who->query("combat_exp")<lost )
                who->set("combat_exp",0);
        else    who->add("combat_exp",-lost);
        tell_object(who,HIR"【副本】始皇陵一层：你身负重伤，损失了"HIY+lost+""HIR"点武学经验。"NOR"\n");
        
        lost = 1000;
        lost = lost*9/10+random(lost/10);
        if( who->query("daoxing")<lost )
                who->set("daoxing",0);
        else    who->add("daoxing",-lost);
        tell_object(who,HIR"【副本】始皇陵一层：你身负重伤，损失了"HIY+COMBAT_D->chinese_daoxing(lost)+""HIR"道行。"NOR"\n");
        
        lost = 1000;
        lost = lost*9/10+random(lost/10);
        if( who->query("potential")-who->query("learned_points")<lost )
                who->set("potential",who->query("learned_points"));
        else    who->add("potential",-lost);
        tell_object(who,HIR"【副本】始皇陵一层：你身负重伤，损失了"HIY+lost+""HIR"点修为潜能。"NOR"\n");
        if( target )
        {
                CHANNEL_D->do_channel(this_object(),"rumor",who->name(1)+"在始皇陵一层被 "HIY+COLOR_D->clean_color( (stringp(target->query("title"))?target->query("title"):"") +target->name() )+HIM"打得身负重伤。"NOR);
                if( target->is_boss() )
                        log_file("长安始皇陵001",time()+"#"+who->query("name")+"("+capitalize(who->query("id"))+")于 始皇陵一层 被"+COLOR_D->clean_color( (stringp(target->query("title"))?target->query("title"):"") +target->name() )+" 所伤。\n");
        }
                
        who->set("kee",100);
        who->set("eff_kee",100);
        who->set("sen",100);
        who->set("eff_sen",100);
        who->set("force",0);
        who->set("mana",0);
        
        file = sprintf("/d/eastway/guandao%d",1+random(3));
        who->move(file,2);
        message_vision("\n"HIW"$N"HIW"跌跌撞撞的从始皇陵中逃了出来。\n\n"NOR,who);
        who->delete_temp("maze");
        who->set("maze/qingling",time());
        return;
}                       

void init()
{
        if( userp(this_player()) )
        {
                add_action("do_cmds","",1);
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

void create_guai(object who,int type)
{
        object guai;
        if( !who || !living(who) 
         || type<1 || type>3 )
                return;
        switch(type)
        {
                case 1 : 
                        if( query("guai1")<=0 ) return;
                        guai = new("/d/maze/qingling-1/npc/jiangshi-1");
                        break;  
                case 2 :
                        if( query("guai2")<=0 ) return;
                        guai = new("/d/maze/qingling-1/npc/jiangshi-2");
                        break;  
                default :
                        if( query("guai3")<=0 ) return;
                        guai = new("/d/maze/qingling-1/npc/jiangshi-3");
                        break;  
        }
        if( !guai )
                return;
        if( !guai->information(who) )
        {
                if( guai ) destruct(guai);
                return;
        }
        message_vision(HIR"\n从一旁跳出一个僵尸！\n"NOR,who);
        guai->move(this_object());
        guai->kill_ob(who);
        who->fight_ob(who);     
        switch(type)
        {
                case 1 : add("guai1",-1);break;
                case 2 : add("guai2",-1);break;
                default :add("guai3",-1);break;
        }
}

int valid_leave(object who,string dir)
{
        object guai;
        if( !userp(who) )
                return ::valid_leave(who,dir);
        if( who->is_fighting() )
                return notify_fail("你现在正忙着呢。\n");
        if( present("jiang shi",this_object()) )
                return notify_fail("僵尸拉住了你的去路。\n");
                
        if( query("guai1")<=0
         && query("guai2")<=0
         && query("guai3")<=0 )
                return ::valid_leave(who,dir);
                
        if( query("guai1")>0 )  
        {
                create_guai(who,1);
                if( random(6)==0 )
                        create_guai(who,2);
                if( random(10)==0 )
                        create_guai(who,3);
        }
        if( query("guai2")>0 )
        {
                create_guai(who,2);
                if( random(6)==0 )
                        create_guai(who,3);
        }                               
        if( query("guai3")>0 )
                create_guai(who,3);
        
        return notify_fail("深处好似传来一阵异响，你警惕的停住了脚步。\n");
}
