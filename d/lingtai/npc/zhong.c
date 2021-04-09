// worker.c

inherit NPC;

void create()
{
        set_name("道士", ({"taoist", "dao"}));
        set_level(13);
        set("gender", "男性" );
        set("age", 23);
        set("long", "一个道士，看起来无精打采的样子。\n");
        set("attitude", "peaceful");
        set_skill("dodge", 120);
	set("class", "taoist");
        set_skill("parry", 130);
        set_skill("unarmed", 130);  
        set("per", 30);
        setup();
	carry_object(0,"cloth",random(3))->wear();
}