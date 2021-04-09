inherit NPC;
void create()
{
  set_name("翊圣真君",({"yisheng zhenjun","zhenjun","jun"}));
  set("gender", "男性");
  set("age", 45);
  set("long", "    \n玉帝的贴身侍卫，在灵霄宝殿前守卫着。\n");
  set_level(130+random(10));
  set("attitude", "heroism");
  set("class", "xian");
  set("daoxing", 3000000);
  set("force_factor", 20);
  set("mana_factor", 40);

  set_skill("dodge", 1300);
  set_skill("baguazhen", 1300);
  set_skill("force", 1300);
  set_skill("zhenyuan-force", 1300);
  set_skill("spells", 1300);
  set_skill("taiyi", 1300);
  set_skill("unarmed", 1300);
  set_skill("wuxing-quan", 1300);
  set_skill("parry", 1300);


map_skill("dodge", "baguazhen");
map_skill("force", "zhenyuan-force");
map_skill("spells", "taiyi");
map_skill("unarmed", "wuxing-quan");
map_skill("parry", "wuxing-quan");

setup();

carry_object("/d/obj/cloth/jinpao")->wear();
add_money("silver", 80);

}
