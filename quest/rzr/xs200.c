#include <ansi.h>
inherit __DIR__"rzr.c";

void valid_map_skill()
{
        map_skill("unarmed","cuixin-zhang");
        map_skill("force","ningxie-force");
        map_skill("spells","dengxian-dafa");
        map_skill("sword","bainiao-jian");
        map_skill("blade","bingpo-blade");
        map_skill("parry","bingpo-blade");
        map_skill("dodge","xiaoyaoyou");
        set("force_factor",50);
        set("mana_factor",query_skill("spells")/2);
}       


void setnames()
{
        set_name("段小淳",({"duan","shi"}));
        set("gender","男性");
        set("age",25);
        set("str",32);
        set("con",21);
        set("int",23);
        set("spi",20);
        set("cor",10);
        set("cps",10);
        set("kar",35);
        set("per",31);
}

void setskills()
{                 
        set("mp","xs");
        set("level",200);                

        set_skill("blade",200);
        set_skill("dodge",200);
        set_skill("force",200);
        set_skill("ningxie-force",200);
        set_skill("literate",200);
        set_skill("bainiao-jian",200);
        set_skill("parry",200);
        set_skill("xiaoyaoyou",200);
        set_skill("bingpo-blade",200);
        set_skill("spells",200);
        set_skill("sword",200);
        set_skill("pingfeng",200);
        set_skill("unarmed",200);
        set_skill("unarmed",200);
        set_skill("cuixin-zhang",200); 
        set_skill("dengxian-dafa",200);        
        set("max_kee",5000);
        set("max_sen",5000);
        
        create_family("大雪山",3,HIW"迷天邪圣"NOR);
        set("family/master_name","大鹏明王");
        set("family/master_id","dapeng mingwang");
}

void do_hit(object who)
{
        object weapon;
        reset_eval_cost();
        remove_call_out("do_hit");
        if( !who || !this_object()->is_fighting(who) )
                return;
        command("wield blade");
        weapon = query_temp("weapon");
        if( !weapon )
        {
        	add_temp("apply/karma",3000);
			weapon = carry_object(0,"blade",1);
			add_temp("apply/karma",-3000);
		}	
        command("wield blade");
        QUEST_D->randomPfm(this_object());
}

