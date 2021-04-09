#include <ansi.h>
inherit __DIR__"rzr.c";

void valid_map_skill()
{
        map_skill("unarmed","yinfeng-zhua");
        map_skill("force","huntian-qigong");
        map_skill("spells","yaofa");
        map_skill("sword","qixiu-jian");
        map_skill("parry","qixiu-jian");
        map_skill("dodge","lingfu-steps");
        set("force_factor",120);
        set("mana_factor",query_skill("spells")/2);
}       


void setnames()
{
        set_name("哥舒翰",({"geshu","ye"}));
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
                 
        set("mp","wdd");
        set("level",800);               

        set_skill("blade",800);
        set_skill("dodge",800);
        set_skill("force",800);
        set_skill("huntian-qigong",800);
        set_skill("literate",800);
        set_skill("jinwu-blade",800);
        set_skill("parry",800);
        set_skill("kugu-blade",800);
        set_skill("lingfu-steps",800);
        set_skill("spells",800);
        set_skill("sword",800);
        set_skill("pingfeng",800);
        set_skill("unarmed",800);
        set_skill("qixiu-jian",800);
        set_skill("sanqing-jian",800);
        set_skill("wangqing-jue",800);
        set_skill("unarmed",800);
        set_skill("yinfeng-zhua",800);
        set_skill("yaofa",800);       
        
        set("max_kee",14000);
        set("max_sen",14000);
        
        create_family("陷空山无底洞",2,HIR"枯骨魔尊"NOR);
        set("family/master_name","玉鼠精");
        set("family/master_id","yu shu");
        powerup(1);
}

void do_hit(object who)
{
        object weapon;
        remove_call_out("do_hit");
        reset_eval_cost();
        if( !who || !this_object()->is_fighting(who) )
                return;
        command("wear all");
        command("unwield sword");
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
        set("force_factor",query_skill("force")/2);
        map_skill("sword","qixiu-jian");
        command("exert shuyi");
        command("perform zxzx");
        map_skill("dodge","kugu-blade");
        command("perform dodge.xiao");
        
        command("unwield sword");
        command("wield blade");
        weapon = query_temp("weapon");
        if( !weapon )
        {
        	add_temp("apply/karma",3000);
			weapon = carry_object(0,"blade",1);
			add_temp("apply/karma",-3000);
		}	
        command("wield blade");
        map_skill("blade","jinwu-blade");
        command("perform jinhong");
        
        map_skill("unarmed","pingfeng");
        command("unwield blade");
        command("perform shipo");
        if( random(2) )
        {
                command("wield sword");
                command("perform duoming");
        }
        map_skill("dodge","wangqing-jue");
        command("perform dodge.wangqing");
        
        valid_map_skill();       
        if( random(2) )
                command("wield blade");
        else    command("wield sword");
        QUEST_D->randomPfm(this_object());
}

