// 陷空山无底洞蚀日鼠魔 Shumo.c
// Cracked by 凌惊雪 12-16-2002

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
void create()
{
  set_name("蚀日鼠魔", ({"shu mo","shu", "mo", "master"}));
  set_level(135);
  set_weight(10000000);
  set("gender", "男性" );
  set("class", "yaomo" );
  set("age", 900);
  set("long", 
"自从陷空山形成那日，就有了蚀日鼠魔，万鼠之王。\n"
"没有人知道无底洞是怎么来的，没有人知道洞里有多少秘密。\n");
  set("title", HIY"万鼠之王"NOR);
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

  setup();
  carry_object("/d/obj/weapon/blade/modao")->wield();
  carry_object("/d/npc/obj/armor")->wear();
}