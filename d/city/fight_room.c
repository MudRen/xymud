#include <ansi.h>
inherit ROOM;

void create() 
{
        set("short","静室");
        set("long","这里是拳盖三省范青屏范老爷子专门为%s准备的修炼之所。\n在这里战斗是不轮死伤的。");
        set("exits",([
                "out" : "/d/city/wuguanzhong",
        ]));
        set("alternative_die",1);
        set("no_clean_up",0);
}

void dest()
{
        destruct(this_object());
}

void _dest()
{
        remove_call_out("dest");
        call_out("dest",3+random(5));
}
        
void reset()
{
if( !objectp(this_object()) )   return;
if( !query("owner_id") )  return;
if( !present(query("owner_id"),this_object()) 
  || time()>query("start_time")+1800 )
        destruct(this_object());
}

int valid_leave(object who,string dir)
{
        if( who==query("owner") && dir=="out" )
        {
                tell_object(who,"你修炼完毕，朝外走去。\n");
                _dest();
                return 1;
        }
        return ::valid_leave(who,dir);
}                       

void alternative_die(object me)
{
        me->remove_all_killer();
        all_inventory(environment(me))->remove_killer(me);
        if( userp(me) && me->query("id")!=query("owner_id") )
        {
                set("alternative_die",0);
                me->die();      
                set("alternative_die",1);
                return;
        }
        me->set("kee",100);
        me->set("eff_kee",me->query("max_kee"));
        me->set("sen",100);
        me->set("eff_sen",me->query("max_sen"));
        me->set("force",me->query("max_force")/2);
        me->set("mana",me->query("max_mana")/2);
        me->set_temp("fight_job_lost",time());
        message_vision(HIR"\n\n$N"HIR"战罢多时，感觉浑身乏力，不由双脚一软，摔了个元宝磕~~~幸好屁股还是两瓣。。。。\n"NOR,me);
}

void init()
{
        if( this_player()==query("owner") && !query("start_time") )
                 set("start_time",time());
        add_action("do_none","",1);
        add_action("do_look","look");
}

int do_look(string arg)
{
        if( !arg && ("/cmds/std/look.c")->main(this_player(),arg) )
        {
                write(HIM"\t\t还有剩余时间"+(1800-(time()-query("start_time")))+"秒。\n"NOR);
                return 1;
        }
        return 0;
}

int do_none()
{
        string verb = query_verb();
        if( strsrch(verb,"ji")!=-1 
         || strsrch(verb,"cast")!=-1 
         || strsrch(verb,"move")!=-1   
         || strsrch(verb,"quit")!=-1 )
        {
                write("\n");
                return 1;
        }
        return 0;
}
