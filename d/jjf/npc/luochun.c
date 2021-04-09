//created 8-8-97 pickle
//罗春
inherit SUPER_NPC;

string ask_xi();

void create()
{
  set_name("罗春", ({"luo chun", "luo", "chun", "luochun"}));
  set_level(30);
  set ("long", @LONG
罗春是罗府的心腹家将，办事甚是得力。传说他是罗艺的私生子，
是罗成的亲哥哥。罗春的一手霸王枪使得纯熟无比，在战场上曾经
颇立战功。
LONG);
  create_family("将军府", 3, "蓝");
  set("title", "罗府家将");
  set("gender", "男性");
  set("age", 40);
  set("per", 25);
  set_skill("force",300);
  set_skill("lengquan-force",300);
  set_skill("parry",300);
  set_skill("dodge",300);
  set_skill("yanxing-steps",300);
  set_skill("unarmed",300);
  set_skill("changquan",300);
  set_skill("spear",220);
  set_skill("bawang-qiang", 220);
  map_skill("force", "lengquan-force");
  map_skill("unarmed", "changquan");
  map_skill("spear", "bawang-qiang");
  map_skill("parry", "bawang-qiang");
  map_skill("dodge", "yanxing-steps");
  set("max_sen", 600);
  set("max_kee", 1200);
  set("force", 2000);
  set("max_force", 1500);
  set("force_factor", 20);
  set_temp("weapon_level",1+random(20));
  set_temp("armor_level",1+random(20));
  setup();
  carry_object(0,"spear",random(2))->wield();
  carry_object(0,"armor",random(2))->wear();
  carry_object(0,"kui",random(2))->wear();
  carry_object(0,"cloth",random(2))->wear();
  carry_object(0,"shoes",random(2))->wear();
  carry_object(0,"pifeng",random(2))->wear();
  carry_object(0,"shield",random(2))->wear();
}

int accept_fight(object me)
{
  command("say 在这里打架，不怕惊动了楼上的贵人？\n");
  return 0;
}
