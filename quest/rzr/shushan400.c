#include <ansi.h>
inherit __DIR__"rzr.c";

void valid_map_skill()
{
        map_skill("unarmed","hunyuan-zhang");
        map_skill("force","zixia-shengong");
        map_skill("spells","taoism");
        map_skill("sword","mindsword");
        map_skill("parry","mindsword");
        map_skill("dodge","wangqing-jue");
        set("force_factor",50);
        set("mana_factor",query_skill("spells")/2);
}       

void setnames()
{
        set_name("公孙八娘",({"gongsun","niang"}));
        set("gender","女性");
        set("age",20);
        set("str",32);
        set("con",21);
        set("int",23);
        set("spi",20);
        set("cor",10);
        set("cps",10);
        set("kar",35);
        set("per",31);
        set("wiz_test",1);
        set("level",400);
        set("mp","shushan");
}

void setskills()
{                        
        set_skill("canxin-jian",400);
        set_skill("dodge",400);
        set_skill("force",400);
        set_skill("hunyuan-zhang",400);
        set_skill("literate",400);
        set_skill("mindsword",400);
        set_skill("parry",400);
        set_skill("pingfeng",400);
        set_skill("sevensteps",400);
        set_skill("spells",400);
        set_skill("sword",400);
        set_skill("taoism",400);
        set_skill("unarmed",400);
        set_skill("wangqing-jue",400);
        set_skill("yujianshu",400);
        set_skill("zixia-shengong",400);
        
        set("max_kee",6000);
        set("max_sen",6000);
        create_family("蜀山派",2,"女剑客");
        set("family/master_name","剑圣");
        set("family/master_id","jian sheng");
}

void do_hit(object who)
{
        object weapon;
        remove_call_out("do_hit");
        reset_eval_cost();
        if( !who || !this_object()->is_fighting(who) )
                return;
        command("wear all");
        command("unwield blade");
        command("wield sword");
        weapon = query_temp("weapon");
        if( !weapon )
        {
        	add_temp("apply/karma",3000);
			weapon = carry_object(0,"sword",1);
			add_temp("apply/karma",-3000);
		}	
		command("wield all");
        set("force_factor",query_skill("force")/2);
        map_skill("sword","yujianshu");
        command("perform wanjian");
        command("perform dodge.yunyi");
        map_skill("unarmed","pingfeng");
        command("unwield sword");
        command("perform shipo");
        valid_map_skill();       
        QUEST_D->randomPfm(this_object());
}


