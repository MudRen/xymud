#include <ansi.h>
inherit NPC;
inherit F_SAVE;

int is_rzr(){ return 1; }

nosave int can_save = 1;

string query_save_file() 
{
        int sk;
        string mp,id = query("id");
        if( !id )
                return 0;
        mp = query("mp");
        if( !mp ) mp = "none";
        sk = query("level");
        if( !sk || sk<=0 )
                sk = 120;                       
        return sprintf("/data/npc/rzr/%c/%s_%s%d",id[0],id,mp,sk);
}

int save()
{
        if( !can_save )
                return 0;
        return ::save();
}
        
void reload()
{
        if(clonep()) 
        {
                if(sizeof(filter_array(children(base_name(this_object())),(:clonep:)))>1) 
                {
                        can_save=0;
                        call_out("self_destroy",1);
                        return;
                }
        }
        if( clonep() && can_save) 
        { 
                if(!restore())
                        log_file("npc_save",sprintf("Failed to restore %s(%s).\n",this_object()->query("id"),base_name(this_object())));
        }   
}

void valid_map_skill()
{
        set("force_factor",query_skill("force")/2);
        set("mana_factor",query_skill("spells")/2);
}       

void setskills() { return; }
void setnames() { return; }

void create()
{
        int wx;
        seteuid(getuid()); 
        set("name","RZR"); 
        setnames();
        set("channel_id","人造人系统");
        set("wiz_test",1);
        set("任务",1);
        setskills();                 
        wx = query_skill("force",1);
        wx = wx/10*wx*wx;
        set("combat_exp",wx);
        set("daoxing",wx);
        wx = query("level")*30/2;
        set("max_force",wx);
        set("force",wx*2);
        set("max_mana",wx);
        set("mana",wx*2);
        set("maximum_force",wx);
        set("maximum_mana",wx);
        setup();
        reload();
        set("chat_chance",20);
        set("chat_msg", ({
                (: random_move :),  
        }));
        valid_map_skill();
		add_temp("apply/karma",3000);
        carry_object(0,"shoes",1)->wear();
        carry_object(0,"pifeng",1)->wear();
        carry_object(0,"armor",1)->wear();
        carry_object(0,"kui",1)->wear();
        carry_object(0,"ring",1)->wear();
        carry_object(0,"neck",1)->wear();
        carry_object(0,"sword",1)->wield();
        carry_object(0,"blade",1);
        add_temp("apply/karma",-3000);
		set("env/wimpy",30);
        powerup(0,1);
}

void do_hit(object who) { return; }

void unconcious()
{
        can_save = 0;
        ::unconcious();
}

void heart_beat() 
{
        int i,period;
        object target,me = this_object();
        if( !environment() ) 
                return; 

        if( !query_temp("stime") )   set_temp("stime",time());
        if( !is_fighting() && time()>query_temp("stime")+500 ) {
                   delete_temp("last_damage_from");
                   die();
                   return;
        }
        if( query("force")<100 ) 
        { 
                if( query("kee")<=0 || query("eff_kee")<=0 ) 
                {
                        die(); 
                        return; 
                } 
                if( query("sen")<0 || query("eff_sen")<=0 ) 
                { 
                        unconcious(); 
                        return; 
                } 
        }
        if( query("eff_kee") < query("max_kee") )
                QUEST_D->addEffKee(me);
        if( query("kee") < query("eff_kee") )
                QUEST_D->addKee(me);
        if( query("sen") < query("eff_sen") )
                QUEST_D->addSen(me);
        if( query("eff_sen") < query("max_sen") )
                QUEST_D->addEffSen(me);
        if( me->is_busy() &&  !me->is_fighting() ) 
        {
                me->start_busy(1,10000);
                me->interrupt_me(me,"不动"); 
                me->reset_action(); 
        }
        if( !me->is_fighting() )
        {
                if( query("force")<query("max_force")*2
                 && !environment()->query("no_fight")
                 && !environment()->query("no_magic")
                 && time()>query_temp("last_dazuo")+300 
                 && !query_temp("pending/exercise") )
                {
                        set_temp("last_dazuo",time());
                        i = query("max_force")*2-query("force");
                        i/= (query_skill("force",1)/10);
                        if( i<100 )
                                i = 100;
                        if( i>query("kee")/2 )
                                i = query("kee")/2;
                        command("exercise "+i);
                }

                if( query("mana")<query("max_mana")*2
                 && !environment()->query("no_fight")
                 && !environment()->query("no_magic")
                 && time()>query_temp("last_mingsi")+300 
                 && !query_temp("pending/meditate") )
                {
                        set_temp("last_mingsi",time());
                        i = query("max_mana")*2-query("mana");
                        i/= (query_skill("spells",1)/10);
                        if( i<100 )
                                i = 100;
                        if( i>query("sen")/2 )
                                i = query("sen")/2;
                        command("meditate "+i);
                }
        }
        else
        {
                set("force_factor",10);
                target = SSERVER->offensive_target(me);
                if( target && !COMBAT_D->playerp(target) && query("force")<query("max_force")*2 )   add("force",300+random(500));
                if( target && living(me) )
                        do_hit(target);         
        }
                
        me->update_age();
        if (living(me))
        {
                period = time()-(int) query("last_save");
                if (period < 0 || period > 15 * 60)
                {
                        string msg;
                        if( !me->save() )
                                msg = "由于数据异常，本次存盘失败";
                        else    msg = "已经自动存盘";
                        set("last_save", time());
                        CHANNEL_D->do_channel(this_object(),"sys","人造人档案"+msg);
                }
        }       
        ::heart_beat();
}

void die()
{
        QUEST_D->powerup(this_object());
        can_save = 1;
        save();
        message_vision("\n\n$N离开了游戏。\n",this_object());
        destruct(this_object());
}

int random_move()
{
        if( environment()->is_ymdh() )
                return ::random_move();
        else    return 0;
}       

void init()
{
        if( environment()
         && environment()->is_ymdh() 
         && !this_object()->is_fighting() 
         && userp(this_player()) 
         && !this_object()->is_busy() )
                kill_ob(this_player());
        ::init();
}

