// lestat 2001


#include <ansi.h>

inherit NPC;

void create()
{
	    set_name("太清道人",({"taiqing"}));
		set("title", HIC"太清道人"NOR);
//        set("gender","男性");
//        set("age", 60);
        set("str", 40);
        set("cor", 30);
		set("con", 30);
		set("cps", 30);
		set("spi", 30);
		set("int", 30);
//        set_temp("apply/damage", 125);
//        set_temp("apply/armor", 500);
 	    set_skill("unarmed", 100);
 	    set_skill("wuxing-quan", 100);
 	    set_skill("dodge", 100);
   set_skill("baguazhen", 100);
   set_skill("parry", 100);
   set_skill("sword", 100);
   set_skill("xiaofeng-sword", 100);
   set_skill("blade", 100);
   set_skill("yange-blade", 100);
   set_skill("staff", 100);
   set_skill("fumo-zhang", 100);
   set_skill("hammer", 100);
   set_skill("kaishan-chui", 100);
   set_skill("force", 100);   
   set_skill("zhenyuan-force", 100);
   set_skill("literate", 100);
   set_skill("spells", 100);
   set_skill("taiyi", 100);
   map_skill("spells", "taiyi");
   map_skill("force", "zhenyuan-force");
   map_skill("unarmed", "wuxing-quan");
   map_skill("sword", "xiaofeng-sword");
   map_skill("dodge", "baguazhen");
   map_skill("staff", "fumo-zhang");
   map_skill("blade", "yange-blade");
   map_skill("hammer", "kaishan-chui");
   map_skill("parry", "xiaofeng-sword");
   set("combat_exp", 1000000);
   set("daoxing", 1000000);
   create_family("五庄观", 2, "弟子");
   set("chat_chance_combat", 90);
   set("chat_msg_combat", 
   ({
//     (: cast_spell, "zhenhuo" :),
(: perform_action,"sword", "huichang" :),
   }) );
   setup();
   carry_object("/d/obj/cloth/baguapao")->wear();
//   carry_object("/d/obj/weapon/hammer/bahammer")->wield();
   carry_object("/d/obj/weapon/sword/qingfeng")->wield();
}

void copy_status(object me,object ob)
{
    me->set("name",ob->query("name"));
    me->set("gender",ob->query("gender"));
	me->set("age",ob->query("age"));
    me->set("nickname",ob->query("nickname"));
	me->set_skill("staff", (int)ob->query_skill("staff", 1)*5/4);
	me->set_skill("sword", (int)ob->query_skill("sword", 1)*5/4);
	me->set_skill("hammer", (int)ob->query_skill("hammer", 1)*5/4);
	me->set_skill("dodge", (int)ob->query_skill("dodge", 1)*5/4);
	me->set_skill("unarmed", (int)ob->query_skill("unarmed", 1)*5/4);
	me->set_skill("parry", (int)ob->query_skill("parry", 1)*5/4);
	me->set_skill("spells", (int)ob->query_skill("spells", 1)*5/4);
	me->set_skill("blade", (int)ob->query_skill("blade", 1)*5/4);
	me->set_skill("force", (int)ob->query_skill("force", 1)*5/4);
	me->set_skill("wuxing-quan", (int)ob->query_skill("wuxing-quan",1)*5/4);
	me->set_skill("baguazhen", (int)ob->query_skill("baguazhen", 1)*5/4);
	me->set_skill("taiyi", (int)ob->query_skill("taiyi", 1)*5/4);
	me->set_skill("xiaofeng-sword", (int)ob->query_skill("xiaofeng-sword", 1)*5/4);
//	me->set_skill("kaishan-chui", (int)ob->query_skill("kaishan-chui", 1)*5/4);
	me->set_skill("sanqing-jian", (int)ob->query_skill("sanqing-jian", 1)*5/4);
	me->set_skill("zhenyuan-force", (int)ob->query_skill("zhenyuan-force", 1)*5/4);	
   me->set("max_kee",ob->query("max_kee"));
   me->set("eff_kee",ob->query("eff_kee"));
   me->set("kee",ob->query("kee"));

   me->set("max_gin",ob->query("max_gin"));
   me->set("eff_gin",ob->query("eff_gin"));
   me->set("gin",ob->query("gin"));

   me->set("max_sen",ob->query("max_sen"));
   me->set("eff_sen",ob->query("eff_sen"));
   me->set("sen",ob->query("sen"));

   me->set("max_force",ob->query("max_force")*5/4);
   me->set("force",ob->query("force")*5/4);
   me->set("force_factor",ob->query("force_factor")*5/4);

   me->set("max_mana",ob->query("max_mana")*5/4);
   me->set("mana",ob->query("mana")*5/4);
   me->set("mana_factor",ob->query("mana_factor")*5/4);
   me->set("combat_exp",ob->query("combat_exp")*5/4);
   me->set("daoxing",ob->query("daoxing")*5/4);
}

void die()
{
        message("vision",
                MAG "但听一声钟响，太清"+ name() + "身子一晃，化成一股紫气冲天而去。\n" NOR,environment(),
                this_object() );
        destruct(this_object());
}

int heal_up()
{
   object me=this_object();
   object who=present(me->query("leader"),environment(me) );
        if( environment() && (!is_fighting() || !objectp(who) || !who->is_fighting() )  ) {
                call_out("die", 1);
                return 1;
        }
   if( (int)me->query("time") > 10 ) {
     call_out("die",1);
     return 1;
   }
   add("time", 1);
        return ::heal_up() + 1;
}

void invocation(object who)
{
   int i;
   object me,*enemy;

   me=this_object();
   message("vision",
     HIC +who->query("name")+"唱道:

	 『混沌从来不计年，鸿蒙剖处我居先；叁同先天地玄黄理，任我傍门望眼穿。』

	 只听得正东上一声钟响，顿时眼前出现一位"+who->query("name")+"！\n" NOR,
     environment(),this_object());
   copy_status(me,who);
   enemy=who->query_enemy();
   i=sizeof(enemy);
   while(i--) {
                if( enemy[i] && living(enemy[i]) ) {
                        kill_ob(enemy[i]);
                        if( userp(enemy[i]) ) enemy[i]->fight_ob(this_object());
                        else enemy[i]->kill_ob(this_object());
                }
        }
   set("leader", (string)who->query("id"));
        set_follow(who);
}
