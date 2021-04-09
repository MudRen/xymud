//Cracked by Roath
// rewritten by snowcat on 12.12.1997

inherit NPC;
#include <ansi.h>
void create()
{
  set_name("李天王", ({"li tianwang", "li", "tianwang"}));
  set_level(38);
  set("gender", "男性");
  set("age", 100);
  set("attitude", "friendly");
  set("combat_exp", 1250000);
  set("daoxing", 2000000);

  set("per", 25);
  set_skill("dodge", 380);
  set_skill("force", 380);
  set_skill("parry", 380);
  set_skill("spells",380);
  set_skill("buddhism", 380);
  set_skill("jienan-zhi", 380);
  set_skill("lotusmove", 380);
  map_skill("unarmed", "jienan-zhi");
  map_skill("dodge", "lotusmove");
  map_skill("spells", "buddhism");
  set("max_sen",1800);
  set("max_gee",1800);
  set("max_gin",1800);
  set("force",1800);
  set("max_force",1800);
  set("max_mana",1800);
  set("force_factor",125);
  setup();

  carry_object("/d/obj/armor/jinjia")->wear();

}