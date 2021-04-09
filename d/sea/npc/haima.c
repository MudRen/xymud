inherit NPC;

void create()
{
        set_name("金背海马", ({"hai ma", "ma"}));
        set("race", "野兽");
        set("age", 25);
        set_level(10);
        set("long", "一只金背的大海马，是龙少爷的座骑。\n");
        set("attitude", "friendly");

     	set("under_water",1);
        set("str", 26);
        set("cor", 30);

        set("limbs", ({ "头部", "身体", "前脚", "後脚", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );
  	set("ride/max_kee", 30);
  	set("ride/max_sen", 30);

	set("ride/msg", "骑");
  	set("ride/dodge", 15);
        set_temp("apply/damage", 5);
        set_temp("apply/armor", 20);

        setup();
}