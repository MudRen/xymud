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
        set("force_factor",50);
        set("mana_factor",query_skill("spells")/2);
}       


void setnames()
{
        set_name("哥舒崇",({"geshu","ye"}));
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
        set("level",200);               

        set_skill("blade",200);
        set_skill("dodge",200);
        set_skill("force",200);
        set_skill("huntian-qigong",200);
        set_skill("literate",200);
        set_skill("jinwu-blade",200);
        set_skill("parry",200);
        set_skill("kugu-blade",200);
        set_skill("lingfu-steps",200);
        set_skill("spells",200);
        set_skill("sword",200);
        set_skill("pingfeng",200);
        set_skill("unarmed",200);
        set_skill("qixiu-jian",200);
        set_skill("sanqing-jian",200);
        set_skill("wangqing-jue",200);
        set_skill("unarmed",200);
        set_skill("yinfeng-zhua",200);
        set_skill("yaofa",200);       
        
        set("max_kee",6000);
        set("max_sen",6000);
        
        create_family("陷空山无底洞",3,HIR"枯骨魔尊"NOR);
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
}

