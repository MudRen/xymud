//Cracked by Roath


inherit NPC;
void create()
{
       set_name("翠兰", ({"cui lan","lan","cui"}));
       set("long","这是高员外的三女儿，长的花容月貌．\n");
       set("gender", "女性");
       set("per",39);
       set("age", 18);
       set("attitude", "friendly");
       set("shen_type", 1);
       set("combat_exp", 500);
       set("daoxing", 500);
       set("chat_msg",({
        "翠兰叹息道：什么时候才可以回家啊。"}));
       setup();
       carry_object("/d/gao/obj/pink_cloth")->wear();
}
