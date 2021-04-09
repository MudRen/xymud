// guanjia.c
// 9-2-97 pickle
inherit SUPER_NPC;
inherit F_MASTER;
#include <ansi.h>

string expell_me(object me);

void create()
{
	set_name("田鼠精", ({"tian shu", "tian", "shu", "tianshu", "monster"}));
	set_level(86);
	set("gender", "女性");
	set("age", 23);
	set("long",
"她就是无底洞的大管家。想当年她和玉鼠一齐修仙成了人形，\n"
"但因资质太差，成正果终究是无望。照顾着当年的交情，玉鼠\n"
"安排她做了这洞的管家。\n");
	create_family("陷空山无底洞", 2, "弟子");
	set("title", "大管家");
	set("attitude", "heroic");
	set_skill("literate", 10);
	set_skill("unarmed", 855);
	set_skill("parry", 855);
	set_skill("spells", 855);  
	set_skill("sword", 855);  
	set_skill("qixiu-jian", 855);
	set_skill("yinfeng-zhua", 855);
	set_skill("lingfu-steps", 855);
	set_skill("dodge", 855);
	set_skill("force", 855);
	set_skill("yaofa", 855);
	set_skill("huntian-qigong", 855);
	map_skill("force", "huntian-qigong");
  	map_skill("unarmed", "yinfeng-zhua");
  	map_skill("spells", "yaofa");
  	map_skill("sword", "qixiu-jian");
  	map_skill("parry", "qixiu-jian");
  	map_skill("dodge", "lingfu-steps");
  
	set("per", 30);
	set("force_factor", 20);
	set("mana_factor", 25);
	set("inquiry", ([
                "叛门": (: expell_me :),
                "leave": (: expell_me :),
		"name": "本姑娘就是这无底洞的大总管！",
		"here": "你瞎了眼啦？这里就是鼎鼎大名的陷空山无底洞！",
		"rumors": "不知道！找别人问去。",
		"人肉包子": "你瞎了眼啦？本姑娘又不是厨子！",
	]) );  
	setup();
  	carry_object("/d/obj/weapon/blade/blade.c")->wield();
  	carry_object("/d/obj/cloth/yuanxiang")->wear();
  	carry_object("/d/obj/cloth/nichang")->wear();
}

string expell_me(object me)
{
  	me=this_player();
  	
	if((string)me->query("family/family_name")=="陷空山无底洞")
  	{
  		if( me->query_level()<40 )
  			return "小妖精，操的还不够！";
                me->set_temp("betray","wdd");
    		return ("什么？想要离开？那你就别怪老娘惩罚！(jieshou)\n");
  	}
  	return ("你是哪里来的！滚！\n");
}

void init()
{
	add_action("do_accept", "jieshou");
}

int do_accept(string arg)
{
	object me=this_player();
	if((string)this_player()->query("family/family_name")!="陷空山无底洞")
		return 0;
        if( me->query_temp("betray")!="wdd" )
    		return 0;
    	if( FAMILY_D->leave_family(this_player(),this_object()) )
    	{
		message_vision("$N道：不错，我要离开无底洞这耗子窝！\n", me);
		EMOTE_D->do_emote(this_object(), "sigh2",geteuid(me),CYN,0,0,0);
		tell_object(me,CYN+name()+CYN"说道：嘿嘿，你是不知道人肉包子好滋味！\n"NOR);
    		return 1;
    	}	
}
