inherit NPC;

void create()
{
       set_name("泥娃娃", ({"mud baby", "baby"}));
       set("long", "一个三尺多高的小娃娃，全身上下象是泥胎一般。\n");
       set("gender", "男性");
	set_level(1);
	set("per", 20);
       set("age", 6);
       set("attitude", "peaceful");
       set("shen_type", 1);
       set_skill("unarmed", 5);
	set_skill("dodge", 10);
        setup();
       add_money("silver", 1);
}

int accept_fight(object me)
{
	command("say 嘻，好啊！\n");
        return 1;
}

void die()
{
        if( environment() ) {
                message("sound", "\n\n泥娃娃一噘嘴，喊道：不跟你玩了！\n眼前闪乎一下泥娃娃已不见了，地下只留下一堆泥水。\n", environment());
        }
        destruct(this_object());
}

