inherit NPC;
void create()
{
        set_name("丫鬟", ({ "ya huan","yahuan" }) );
        set("gender", "女性" );
        set("age", 18);
        set("attitude", "friendly");
        set("per",random(30)+20);
        set("chat_chance", 1);
        set("chat_msg", ({
                "丫鬟认真的开始擦起了桌子和水晶玻璃！\n",
        }) );
         carry_object("/d/obj/cloth/skirt")->wear();
        setup();
}
