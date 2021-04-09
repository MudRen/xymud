// gargoyle.c
#include <ansi.h>
inherit SUPER_NPC;
inherit F_MASTER;

void create()
{
        set_name("阴长生", ({ "yin changsheng", "yin", "changsheng" }));
        set_level(60);
        set("long","阴长生本是个落弟秀才，后在丰都山修练成仙，御封「阴王」。\n");
        set("attitude", "peaceful");
        set("age", 30);
        create_family("阎罗地府", 3, "你好");
	set("title", "寂灭司主");
	set("nickname", "阴王");
	set("daoxing", 400000);
	set("class", "ghost");
	set("force", 2500);
	set("max_force", 1500);
	set("force_factor", 100);
	set("max_mana", 1500);
	set("mana", 2500);
	set("mana_factor", 100);

	set_skill("literate", 600);
	set_skill("ghost-steps", 600);
        set_skill("dodge", 600);
        set_skill("unarmed", 600);
	set_skill("parry", 600);
	set_skill("spells", 600);
	set_skill("gouhunshu", 1180);
	set_skill("jinghun-zhang", 600);
	set_skill("force", 600);
	set_skill("tonsillit", 600);
	set_skill("sword", 600);
	set_skill("zhuihun-sword", 600);
	
	map_skill("sword", "zhuihun-sword");
	map_skill("parry", "zhuihun-sword");
	map_skill("spells", "gouhunshu");
	map_skill("dodge", "ghost-steps");
	map_skill("force", "tonsillit");
	map_skill("unarmed", "jinghun-zhang");
        set("nkgain", 400);
        set_temp("armor_level",39);
        set_temp("weapon_level",39);
        setup();
	carry_object(0,"sword",random(3))->wield();
	carry_object(0,"cloth",random(3))->wear();
	carry_object(0,"neck",random(3))->wear();
	carry_object(0,"shoes",random(3))->wear();
	carry_object(0,"ring",random(3))->wear();
	carry_object(0,"pifeng",random(3))->wear();
	carry_object(0,"kui",random(3))->wear();
	carry_object(0,"armor",random(3))->wear();
	powerup(0,1);
}

void attempt_apprentice()
{	
	object me;
	me = this_player();
	
        if( me->query_level()<40 )
        {
                EMOTE_D->do_emote(this_object(), "sigh",geteuid(me),CYN,0,0,0);
                tell_object(me,CYN+name()+CYN"说道：这位"+RANK_D->query_respect(me)+"还是先去找黑白无常打好基础再来。\n");
                return ;
        }
	if( me->query("class")!="ghost" )
	{
		if( !me->query_temp("pendding/hell_class") )
        	{
                	EMOTE_D->do_emote(this_object(), "shake",geteuid(me),CYN,0,0,0);
                	tell_object(me,CYN+name()+CYN"说道：吾等不收外门弟子，若诚心想入我门，还是先去帮阎罗核对生死簿吧。\n"NOR);
                	return ;
                }		
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