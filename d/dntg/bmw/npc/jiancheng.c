 
inherit NPC;
void create()
{
	set_name("监丞", ({"jian cheng"})); 
        set("gender", "男性" );
	set("long", "御马监监丞。\n");
        set("age",40);
        set("str", 30);
        set_level(150);
	set("title", "御马监");
        set("int", 20);
	set("con", 30);
	set("spi", 20);
        set("per", 15);
	set("class", "xian");
	set("attitude", "friendly");
        set("combat_exp", 8500);
  	set("daoxing", 15000000);
        setup();
        carry_object("/d/obj/cloth/xianpao")->wear();
}