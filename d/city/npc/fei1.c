inherit NPC;

void create()
{
        set_name("打手", ({"da shou", "shou"}));
        set_level(17);
        set("age", 22);
        set("gender", "男性");
        set("long",
"虽然武功不怎么样，但心黑手辣，也不好惹。\n");
        set("attitude", "heroism");

        set("combat_exp", 10000+random(2000));
        set("shen_type", 1);

        set_skill("unarmed", 20);
        set_skill("dodge", 20);
        set_skill("parry", 20);
        set_skill("blade", 20);

        set("chat_chance_combat", 10);
        set("chat_msg_combat", ({
                "打手大喊，敢跟老子过不去，去死吧！\n"
        }));
        setup();
	carry_object(0,"cloth",random(2))->wear();        
	carry_object(0,"blade",random(2))->wield(); }


