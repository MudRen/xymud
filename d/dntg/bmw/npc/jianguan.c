 
inherit NPC;
 
void create()
{
	set_name("监官", ({"jian guan","guan"})); 
        set("gender", "男性" );
	set("long", "御马监监官。\n");
        set("age",20);
        set_level(150);
	set("title", "御马监");
        set("str", 30);
        set("int", 20);
	set("con", 30);
	set("spi", 20);
        set("per", 15);
	set("class", "xian");
	set("attitude", "friendly");
        set("combat_exp", 4000);
  	set("daoxing", 8000000);
        setup();
        carry_object("/d/obj/cloth/xianpao")->wear();
}