//lestat 瘟癀之昊天大帝 吕岳

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

/************************************************************/
void create()
{
  set_name("吕岳", ({"lu yue","luyue", "lu", "monster"}));
  set_level(135);
    set_weight(10000000);
  set("gender", "男性" );
  set("class", "yaomo" );
  set("age", 23);
  set("long", 
"吕岳原为九龙岛炼气士。后拜入碧游宫通天教主座下，万仙阵之后，\n"
"被封为瘟癀之昊天大帝之职，率领瘟部六位正神。\n");
  set("title", HIY"瘟癀之昊天大帝"NOR);
  set("combat_exp", 5000000);
  set("daoxing", 5000000);
  set("attitude", "heroic");
  create_family("陷空山无底洞", 1, "弟子");
  set("int", 25+random(5));
  set("cor", 30+random(10));
  set_skill("unarmed", 1350);
  set_skill("dodge", 1350);
  set_skill("parry", 1350);
  set_skill("literate", 1350);
  set_skill("spells", 1350); 
  set_skill("yaofa", 1350);
  set_skill("sword",1350);
  set_skill("qixiu-jian",1350);
  set_skill("blade", 1350);
  set_skill("kugu-blade", 1350);
  set_skill("lingfu-steps", 1350);
  set_skill("yinfeng-zhua", 1350);
  set_skill("force", 1350);   
  set_skill("huntian-qigong", 1350);
  map_skill("force", "huntian-qigong");
  map_skill("spells", "yaofa");
  map_skill("unarmed", "yinfeng-zhua");
  map_skill("sword", "qixiu-jian");
  map_skill("parry", "kugu-blade");
  map_skill("blade", "kugu-blade");
  map_skill("dodge", "lingfu-steps");
  set("per", 50);
  set("max_kee", 5500);
  set("max_sen", 5500);
  set("force", 5800);
  set("max_force", 5000);
  set("force_factor", 500);
  set("mana",3000);
  set("max_mana", 3000);
  set("mana_factor", 500);

  set("chat_chance_combat", 60);
   
   set("chat_msg_combat", ({
     (: exert_function, "zhangqi" :),
    (: perform_action, "blade.diyu" :)
   }) );
  setup();
  carry_object("/d/obj/weapon/blade/yanblade")->wield();
  carry_object("/d/npc/obj/armor")->wear();
}
/**************************************************************/
