//Cracked by Roath
inherit NPC;
void create()
{
        set_name("山妖", ({"shan yao", "yao"}));
        set_level(30);
        set("long", "一个凶神恶煞般的山妖。\n");
        set("age", 30);
        set("attitude", "herosim");
        set("gender", "男性");
        set("class", "yaomo");
        set("per", 10);

        set("eff_dx", -20000);
        set("nkgain", 200);

        set("force_factor", 20);
        set("mana_factor", 10);
        set_skill("unarmed",300);
        set_skill("force",300);
        set_skill("spells",300);
        set_skill("dodge",300);
        set_skill("parry",300);
        set_skill("blade",300);
        set_skill("wuhu-blade",300);
        map_skill("blade", "wuhu-blade");
        map_skill("parry", "wuhu-blade");
        setup();
        carry_object("/d/obj/armor/shoupi")->wear();
        carry_object(0,"blade",random(2))->wield();
}