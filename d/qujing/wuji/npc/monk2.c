// by snowcat oct 22 1997

inherit NPC;

void create()
{
  set_name("守寺僧", ({"shousi seng", "seng"}));
  set("gender", "男性");
  set("combat_exp", 1000+random(50000));
  set("daoxing", 50000);

  set("age", 40+random(20));
  set("per", 14+random(20));
  set("attitude", "friendly");
  set("shen_type", 1);
  set("people", "people");
  set("force_factor",6);
  set_level(20);
  set_skill("unarmed", 30+random(90));
  set_skill("dodge", 30+random(90));
  set_skill("parry", 30+random(90));
  setup();
  carry_object("/d/obj/cloth/sengyi")->wear();
}