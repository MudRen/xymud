// by snowcat 12/8/1997         

inherit NPC;

string *names = ({
  "诵经僧人",
  "出勤僧人",
  "俗家僧人",
  "修禅僧人",
  "传法僧人",
});

void create()
{
  int i = random(sizeof(names));
  set_name(names[i], ({"he shang"}));
  set("gender", "男性");
  set_level(20);
  set("age", 40+random(20));
  set("per", 14+random(20));
  set("attitude", "friendly");
  set("shen_type", 1);
  set("people", "people");
  set("force_factor",2);
  set("max_gin",300);
  set("max_kee",300);
  set("max_sen",300);
  set("max_force",400);
  set("max_mana",400);
  set_skill("unarmed", 10+random(90));
  set_skill("dodge", 10+random(90));
  set_skill("parry", 10+random(90));
  setup();
  carry_object("/d/obj/cloth/sengyi")->wear();
}

