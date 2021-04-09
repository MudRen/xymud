
inherit NPC;

void create()
{
        set_name("校尉", ({ "xiao wei", "wei", "guard" }) );
        set("gender", "男性");
        set("age", 25);
        set_level(9);
        set("long",

"这是位守护皇城的金甲武士，身披铜甲，手执金瓜。
他双目精光炯炯，警惕地巡视着四周的情形。\n");
        set("combat_exp", 220000);
	set("title", "御林军");
        set("attitude", "heroism");
        set("str", 25);
        set("max_kee", 850);
        set("max_sen", 600);
        set("force", 400);
        set("max_force", 400);
        set("force_factor", 20);
        set_skill("hammer", 80);
        set_skill("unarmed", 80);
        set_skill("parry", 80);
        set_skill("dodge", 80);
        set_skill("force", 80);
        setup();

        carry_object(0,"hammer",random(2))->wield();
        carry_object(0,"armor",random(2))->wear();
        carry_object(0,"kui",random(2))->wear();
        carry_object(0,"pifeng",random(2))->wear();
        carry_object(0,"shield",random(2))->wear();                        
        carry_object(0,"shoes",random(2))->wear();        
}

void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player()) && 
                (int)ob->query_condition("killer")) {
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, ob);
        }
}


int accept_fight(object me)
{
        message_vision("御林军卫士对$N大喝一声：你活得不耐烦了？皇宫前也敢胡闹！\n", me);
        me->apply_condition("killer", 100);
        kill_ob(me);
        return 1;
}

