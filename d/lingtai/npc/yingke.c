// worker.c

inherit NPC;

void create()
{
        set_name("晨月", ({"chen yue"}));
        set_level(10);
        set("gender", "男性" );
        set("age", 13);
	set("title", "山门迎客");
        set("long", "一个小道士，每天负责在山门迎接远道而来的客人．\n");
        set("attitude", "friendly");
        set_skill("dodge", 100);
        set("per", 30);
        setup();
        carry_object(0,"cloth",random(3))->wear();
}