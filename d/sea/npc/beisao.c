inherit NPC;

void create()
{
       set_name("贝嫂", ({"beisao"}));
       set_level(18);
set("long","一位中年妇女，是龙女的贴身仆人．\n");
       set("gender", "女性");
       set("age", 36);
	set("per", 20);
       set("attitude", "peaceful");
       set("shen_type", 1);
	set_skill("unarmed", 160);
	set_skill("dodge", 180);
	set_skill("parry", 160);
        set("combat_exp", 36000);
        setup();
        carry_object(0,"cloth",random(2))->wear();
	carry_object(0,"neck",random(2))->wear();
	carry_object(0,"ring",random(2))->wear();
	carry_object(0,"hand",random(2))->wear();
}

