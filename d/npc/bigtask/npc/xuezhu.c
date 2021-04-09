#include <ansi.h>
#include <taskyao.h>

void set_skills();
int announced=0;
void create()
{
        seteuid(getuid());
	set_name("彩雪蛛"NOR,({"caixue zhu" ,"caixue" ,"zhu"}));
        set("family/family_name","月宫");

        set("age",30);
        set("str",30);
        set("per",20);
        set("combat_exp",5000);
        set("attitude", "heroism");
        set_skill("unarmed",200);
        set("chat_chance", 10);
        set("chat_msg", ({
                (: random_move :)
        }));
        setup();
        carry_object("/d/obj/drug/jinchuang");
        carry_object("/d/obj/drug/jinchuang");
        carry_object("/d/obj/drug/jinchuang");
        carry_object("/d/obj/drug/jinchuang");
        carry_object("/d/obj/drug/jinchuang");
        carry_object("/d/obj/drug/jinchuang");
        add_money("gold", 5);
}
void copy_status(object me)
{
        object *inv;
        mapping skill_status,map_status;
        string *sname,*mname;
        int i, eff_dx, nk_factor;
			mapping name;
	
        set("enable_type","飞贼");
        set("str",30);
        set("int",30);
        set("con",30);
        set("per",30);
        set("cor",30);
        set("spi",30);
        set("cps",30);
        set("kar",30);

        set("max_kee",10000+random(1000));
        set("eff_kee",10000+random(1000));
        set("kee",10000+random(1000));

        set("max_gin",5000+random(1000));
        set("eff_gin",5000+random(1000));
        set("gin",5000+random(1000));

        set("max_sen",5000+random(1000));
        set("eff_sen",5000+random(1000));
        set("sen",5000+random(1000));

        set("max_force",4000+random(1000));
        set("force",8000+random(1000));
        set("force_factor",250);

        set("max_mana",2000+random(1000));
        set("mana",4000+random(1000));
        set("mana_factor",250);
        set("combat_exp",500000+random(1000000));
        set("daoxing",100000+random(300000));

        set("stay_time",time()+600+random(60));
        set("nk_gain", 320+random(50));
        set("nk_factor", 10);

        
        set("bellicosity",300);
        carry_object("/d/qujing/jindou/obj/boots")->wear();
        carry_object("/d/qujing/jindou/obj/finger")->wear();
        carry_object("/d/qujing/jindou/obj/hands")->wear();
        carry_object("/d/qujing/jindou/obj/head")->wear();
        
        set_skills();

        //carry_object("/d/obj/drug/jinchuang");       
        reset_eval_cost();
}

void set_skills()
{
        object me=this_object();
        object weapon;
        int j;
        j= 300+random(100);       
        set("gender", "女性");
        me->set_skill("unarmed", j);
        me->set_skill("dodge", j);
        me->set_skill("parry", j);
        me->set_skill("force", j);
        me->set_skill("spells", j);
 
        me->set_skill("whip", j+random(15));
        me->set_skill("jueqingbian", j+random(15));
        me->set_skill("sword",j+random(15));
        me->set_skill("snowsword",j+random(15));
        me->set_skill("moondance", j+random(15));
        me->set_skill("moonshentong", j+random(15));
        me->set_skill("baihua-zhang", j+random(15));
        me->set_skill("moonforce", j+random(15));

        me->map_skill("force", "moonforce");
        me->map_skill("sword", "snowsword");
        me->map_skill("whip","jueqingbian");
        me->map_skill("parry", "jueqingbian");
        me->map_skill("spells", "moonshentong");
        me->map_skill("dodge", "moondance");
        me->map_skill("unarmed", "baihua-zhang");

	set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
        (: cast_spell, "arrow" :),
        (: cast_spell, "shiyue" :),
        }) );

        if (random(2))
             weapon=new("/d/sea/obj/dragonwhip");
        else
           weapon=new("/d/obj/weapon/sword/qingfeng");
        weapon->move(me);
        
        command("wield all");
}

