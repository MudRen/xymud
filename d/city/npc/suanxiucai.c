inherit NPC;

void create()
{
        set_name("酸秀才", ({"suan xiucai","xiucai"}));
        set("age", 22);
        set_level(3);
        set("gender", "男性");
        set("long",
"落榜秀才，颇觉得有些怀才不遇。\n");
        set("attitude", "peaceful");
	set("per", 22);
        set("combat_exp", 8000);
        set("shen_type", 1);
        set("class", "scholar");
	set("force", 200);
	set("max_force", 200);
	set("force_factor", 3);
        set_skill("unarmed", 40);
        set_skill("dodge", 40);
	set_skill("parry", 40);
	set_skill("changquan", 20);
	map_skill("unarmed", "changquan");
	setup();
        carry_object(0,"cloth",random(2))->wear();
}

