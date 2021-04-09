// tian-ding1.c
// created 4-8-97 pickle
#include <ansi.h>
inherit NPC;
string *first_name = ({ "庞进阁","刘晚旗","苟余阳","毕岩庭"});
// 庞，刘，苟，毕，邓，辛，张，陶

varargs void drool(string msg, string who);

void create()
{
  string name, id;

  name = first_name[random(sizeof(first_name))];

  set_name(name, ({ "tian ding", "tian", "ding" }) );
  set("gender", "男性" );
  set("long", "

对于你的存在，"+name+"似乎丝毫没有注意。
直到你走近天门，他才谨慎起来，目光朝你扫了一扫。
");
  set("title", "大力天丁");
  set("age", 35+random(10));
  set("attitude", "peaceful");
  set("str", 27);
  set("int", 25);
  set("combat_exp",400000);
  set("force",500);
  set("max_force",500);
  set("force_factor", 20);
  set("max_kee", 900);
  set("max_sen", 600);
  set("max_mana", 400);
  set("mana", 400);
  set("mana_factor", 20);
  set_skill("unarmed",99);
  set_skill("dodge",99);
  set_skill("parry",99);
  set_skill("spear",99);
  set_skill("force",99);
  setup();
  carry_object("/d/obj/armor/yinjia")->wear();
  carry_object("/d/obj/weapon/spear/tieqiang")->wield();
}
