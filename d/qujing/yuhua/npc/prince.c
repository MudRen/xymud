// by snowcat 12/8/1997

inherit NPC;

void create()
{
  set_name("老王爷", ({"lao wangye", "wangye", "wang", "ye"}));
  set("title", "玉华县");
  set("gender", "男性");
  set("age", 60);
  set("per", 25);
  set("attitude", "peaceful");
  set("shen_type", 1);
  set_level(6);

  set_skill("unarmed", 60);
  set_skill("dodge", 60);
  set_skill("parry", 60);
  set("force_factor",50);
  set("eff_dx",10000);
  set("nkgain",50);
  setup();
  carry_object("/d/obj/cloth/mangpao")->wear();
}