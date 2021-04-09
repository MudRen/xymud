//Cracked by Roath
inherit NPC;
#include <ansi.h>

void create()
{
        set_name("刘伯钦", ({"liu boqin","liu"}));
        set("gender","男性");
        set("age",30);
        set_level(10);
        set("title",HIY"镇山太保"NOR);
        set("long","山中的一个猎户，十分的粗壮。");
        set("per", 20);
        set("str", 50);
        set("attitude","friendly");
        set("force_factor",40);
        set_skill("unarmed",80);
        set_skill("parry",80);
        set_skill("fork",100);

        set("inquiry",([
                "镇山太保" : "镇山太保就是我啊。",
                "here": "这个地方叫做双叉岭",
                ]));
        setup();

        carry_object("/d/obj/cloth/luoyi2")->wear();
        carry_object("/d/obj/weapon/fork/gangcha")->wield();
}