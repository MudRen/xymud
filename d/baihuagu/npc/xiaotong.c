#include <ansi.h>
inherit NPC;

string ask_gu();

void create()
{
        set_name("小童", ({ "xiao tong", "tong" ,"kid"}));
        set_level(29);
        set("age", 5);
	set("title", "采药的");        
        set("gender", "男性");
        set("long","采药的小童，时常在附近采药。\n");
        set("attitude", "peaceful");
	set("str", 20);
        set("combat_exp", 20000);
	set("max_kee", 400);
	set("max_sen", 400);
	set("max_force", 200);
	set("force", 200);
	set("force_factor", 10);
        set_skill("unarmed", 240);
        set_skill("dodge", 240);
        set_skill("parry", 240);
        set_skill("blade", 240);
        set_skill("force", 240);
        set("inquiry", ([
          	"百花谷": (: ask_gu :),
            	"baihuagu" : (: ask_gu :),           	
            	"xianzi" : "\n好象天上下来的仙女，她在花中飞舞！\n",           	
            	"凝眸仙子" : "\n好象天上下来的仙女，她在花中飞舞！\n",           	
            	"仙子" : "\n好象天上下来的仙女，她在花中飞舞！\n",           	
]));

        setup();
        carry_object(0,"cloth",random(5))->wear();
        carry_object(0,"shoes",random(5))->wear();
}

string ask_gu()
{
    	object who=this_player();
    	if (who->query("family/family_name") != "百花谷")
		return "那是个神秘的地方，有位美丽的仙女。";
	message_vision("$N对$n说道：你是仙子门下，我带你进去。\n",this_object(),who);
	message_vision("$N领着$n转身消失在花丛中。\n",this_object(),who);
	who->move("/d/baihuagu/flower1");
	return "请随我来。";
}
