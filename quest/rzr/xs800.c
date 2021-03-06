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
        set("force_factor",120);
        set("mana_factor",query_skill("spells")/2);
}       


void setnames()
{
        set_name("段闰休",({"duan","shi"}));
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
        set("level",800);                

        set_skill("blade",800);
        set_skill("dodge",800);
        set_skill("force",800);
        set_skill("ningxie-force",800);
        set_skill("literate",800);
        set_skill("bainiao-jian",800);
        set_skill("parry",800);
        set_skill("xiaoyaoyou",800);
        set_skill("bingpo-blade",800);
        set_skill("spells",800);
        set_skill("sword",800);
        set_skill("pingfeng",800);
        set_skill("unarmed",800);
        set_skill("unarmed",800);
        set_skill("cuixin-zhang",800); 
        set_skill("dengxian-dafa",800);        
        set("max_kee",13000);
        set("max_sen",13000);
        
        create_family("大雪山",2,HIW"迷天邪圣"NOR);
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

        command("cast hufa");               
        command("wear all");
        command("unwield sword");
        command("unwield blade");
        map_skill("unarmed","chuixin-zhang");
        command("perform cuixin");
        
        map_skill("unarmed","pingfeng");
        command("perform shipo");
        
        command("wield blade");
        weapon = query_temp("weapon");
        if( !weapon )
        {
        	add_temp("apply/karma",3000);
			weapon = carry_object(0,"blade",1);
			add_temp("apply/karma",-3000);
		}	
        command("wield blade");
        map_skill("blade","bingpo-blade");
        command("perform windstrike");
        command("perform ningxie");
        
        command("unwield blade");
        command("wield sword");
        weapon = query_temp("weapon");
        if( !weapon )
        {
        	add_temp("apply/karma",3000);
			weapon = carry_object(0,"sword",1);
			add_temp("apply/karma",-3000);
		}	
        command("wield sword");
        map_skill("sword","bainiao-jian");
        command("perform feijian");
        if( random(2) )
                command("perform qijue");
        else    command("perform fengwu");      
        valid_map_skill();       
        if( random(2) )
                command("wield blade");
        else    command("wield sword");
        QUEST_D->randomPfm(this_object());
        command("exert ningxie");
}

