// jiading.c

inherit NPC;

void create()
{
	set_name("巡山妖", ({"yaomo"}));
	set_level(37);
	set("long","一个相貌凶险的盗贼, 你仔细一看, 只见他股后似
有一条尾巴。啊！难怪盗贼如此凶狠，原是早已豺
狼成精，并非凡胎啊。\n");
	set("gender", "男性");
	set("age", 20+random(15));
	set("attitude", "peaceful");
	set("shen_type", 1);

        set_skill("unarmed",370);
	set("per", 5);
	set("bellicosity", 20000);
	set_skill("parry",370);
	set_skill("dodge",370);
	set_skill("blade",370);
	set_skill("kugu-blade",370);
	map_skill("blade","kugu-blade");
	map_skill("parry","kugu-blade");
	map_skill("dodge","kugu-blade");
	
	setup();
	carry_object(0,"blade",random(2))->wield();
        
}
