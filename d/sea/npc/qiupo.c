inherit NPC;

void create()
{
       	set_name("鳅婆", ({"qiupo"}));
       	set_level(50);
	set("long","一位老婆婆，是龙女的贴身仆人．\n");
       	set("gender", "女性");
       	set("age", 56);
	set("per", 20);
       	set("attitude", "peaceful");
       	set("shen_type", 1);
	set_skill("unarmed", 550);
	set_skill("dodge", 580);
	set_skill("parry", 540);
        setup();
	carry_object(0,"neck",random(2))->wear();
	carry_object(0,"ring",random(2))->wear();
	carry_object(0,"cloth",random(2))->wear();
}