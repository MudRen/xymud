inherit NPC;

void create()
{
set_name("龙队队长",({"long dui","dui"}));
set("gender","男性");
set("age",25);
set("per",24);
setup();
carry_object("/d/obj/armor/jinjia.c")->wear();
}

string query_place()
{
return "/quest/演练战/room1";
}
