//tomcat
//nuwa.c
#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
   set_name("李聃", ({"li dan", "li", "laojun"}));
   set_level(153);
   set("title", HIW"太上老君"NOR);
   set("gender", "男性" );
   set("age", 180);
//   set("per", 24);
//   set("str", 30);
   set("long", "先天而老後天生，借李成形得姓名；曾拜鸿钧修道德，方能一气化三清！\n");
   set("class", "xian");
//   set("combat_exp", 5600000);
   set("attitude", "peaceful");
   create_family("五庄观", 1, "祖师");
   set("rank_info/respect", "老君");
   set_skill("unarmed", 1530);
   set_skill("wuxing-quan", 1530);
   set_skill("dodge", 1530);
   set_skill("baguazhen", 1530);
   set_skill("parry", 1530);
   set_skill("sword", 1530);
   set_skill("sanqing-jian", 1530);
   set_skill("staff", 1530);
   set_skill("fumo-zhang", 1530);
   set_skill("hammer", 1530);
   set_skill("kaishan-chui", 1530);
   set_skill("blade", 1530);
   set_skill("yange-blade", 1530);
   set_skill("force", 1530);   
   set_skill("zhenyuan-force", 1530);
   set_skill("literate", 1530);
   set_skill("spells", 1530);
   set_skill("taiyi", 1530);
   map_skill("spells", "taiyi");
   map_skill("force", "zhenyuan-force");
   map_skill("unarmed", "wuxing-quan");
   map_skill("sword", "sanqing-jian");
   map_skill("dodge", "baguazhen");
   map_skill("staff", "fumo-zhang");
   map_skill("blade", "yange-blade");
   map_skill("hammer", "kaishan-chui");

  set("str",100);
  set("per",100);
  set("max_kee", 10000);
  set("max_gin", 10000);
  set("max_sen", 10000);
  set("force", 10000);
  set("max_force", 10000);
  set("force_factor", 500);
  set("max_mana", 10000);
  set("mana", 10000);
  set("mana_factor", 500);
  set("combat_exp", 4000000);
  set("daoxing", 10000000);

   set("spell_qiankun_on", 1); //to use cast qiankun, must set this.
   set("chat_chance_combat", 90);
   set("chat_msg_combat", 
   ({
     (: cast_spell, "zhenhuo" :),
     (: cast_spell, "qiankun" :),
   }) );
       setup();
       carry_object("/d/obj/cloth/baguapao")->wear();
       carry_object(0,"sword",random(2))->wield();
       
}