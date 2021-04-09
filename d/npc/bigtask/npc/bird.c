#include <ansi.h>
#include <taskyao.h>

void set_skills();
int announced=0;
void create()
{
        seteuid(getuid());
	set_name("四眼翠雀"NOR,({"cui que" ,"cuique" ,"bird"}));
        set("family/family_name","五庄观");

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
        set("mana",3000+random(1000));
        set("mana_factor",150);
        set("combat_exp",500000+random(1000000));
        set("daoxing",100000+random(300000));

        set("stay_time",time()+600+random(60));
        set("nk_gain", 250+random(50));
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
        j= 150+random(150);       
        me->set_skill("unarmed", j);
        me->set_skill("dodge", j);
        me->set_skill("parry", j);
        me->set_skill("force", j);
        me->set_skill("spells", j);
 
        me->set_skill("hammer", j+random(15));
        me->set_skill("kaishan-chui", j+random(15));
        me->set_skill("sword",j+random(15));
        me->set_skill("sanqing-jian",j+random(15));
        me->set_skill("baguazhen", j+random(15));
        me->set_skill("taiyi", j+random(15));
        me->set_skill("wuxing-quan", j+random(15));
        me->set_skill("zhenyuan-force", j+random(15));

        me->map_skill("force", "zhenyuan-force");
        me->map_skill("sword", "sanqing-jian");
        me->map_skill("hammer","kaishan-chui");
        me->map_skill("parry", "kaishan-chui");
        me->map_skill("spells", "taiyi");
        me->map_skill("dodge", "baguazhen");
        me->map_skill("unarmed", "wuxing-quan");

	set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
        (: cast_spell, "zhenhuo" :),
        (: cast_spell, "baxian" :),
        }) );

        if (random(2))
           weapon=new("/d/obj/weapon/hammer/jingua");
        else
           weapon=new("/d/obj/weapon/sword/qingfeng");
        weapon->move(me);
        command("wield all");
}

