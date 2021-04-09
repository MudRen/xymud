// gargoyle.c

#include <ansi.h>
#include <login.h>

inherit SUPER_NPC;
inherit F_MASTER;

void create()
{
	set_name("黑无常", ({ "hei wuchang","wuchang", "hei" }));
        set_level(40);
        set("long","一个黑衣漆黑面皮的使者，黝黑的脸上看不出任何喜怒哀乐。\n");
        set("attitude", "peaceful");
        set("age", 30);
        create_family("阎罗地府", 4, "你好");
        set("per",30);
	set("title", "引魄司主");
  	set("daoxing", 200000);
	set("class", "ghost");
	set("force_factor", 50);
	set("mana_factor", 40);
	set_skill("ghost-steps", 400);
        set_skill("dodge", 400);
        set_skill("unarmed", 400);
	set_skill("parry", 400);
	set_skill("spells", 400);
	set_skill("gouhunshu", 390);
	set_skill("jinghun-zhang", 400);
	set_skill("force", 400);
	set_skill("tonsillit", 390);
	set_skill("stick", 400);
	set_skill("kusang-bang", 250);
	map_skill("stick", "kusang-bang");
	map_skill("parry", "kusang-bang");
	map_skill("spells", "gouhunshu");
	map_skill("dodge", "ghost-steps");
	map_skill("force", "tonsillit");
	map_skill("unarmed", "jinghun-zhang");
	
  	set("inquiry",([
   		"name":"在下引魂使黑无常，奉十殿冥王之命，前往阳间勾魂。\n",
   		"here":"这里是阎罗地府。\n",
   		"勾魂":"我按批文所书勾人，若有冤屈，可与发此公文之冥王申诉(complain)。\n",
   		"冤枉":"我按批文所书勾人，若有冤屈，可与发此公文之冥王申诉(complain)。\n",
   		"冤屈":"我按批文所书勾人，若有冤屈，可与发此公文之冥王申诉(complain)。\n",
  	]));
        setup();
	carry_object("/d/obj/cloth/hei")->wear();
	carry_object(0,"stick",random(10))->wield();
}

void attempt_apprentice()
{	
	object me = this_player();
	if(me->is_ghost() )
	{
		me->reincarnate();
		return;
	}
        EMOTE_D->do_emote(this_object(), "pat",geteuid(me),CYN,0,0,0);
        tell_object(me,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(me) +"多加努力，把我们地府发扬光大。\n"NOR);
        command("recruit " + geteuid(me) );
        CHANNEL_D->do_channel(this_object(),"chat","阎罗地府又多了一个弟子  "+me->name(1)+HIW"\n                                 地府的势力加强了。\n"NOR);
        return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "ghost");
}