#include <ansi.h>
inherit NPC;

int fabao = 0;

void create()
{
	set_name("韩湘子", ({"han xiangzi", "han", "xiangzi"}));
	set_level(40);
	set("title", HIC"八仙之苍梧子"NOR);
	set("gender", "男性" );
	set("age", 22);
	set("long", "好一位俊雅潇洒的相公。韩湘子本是名门之后，却不喜念书入仕。\n被其族中长者以轻狂不学斥出家门。\n");
	set("class", "xian");
	set("attitude", "peaceful");
	create_family("五庄观", 3, "弟子");
	set_skill("unarmed",400);
	set_skill("wuxing-quan",400);
	set_skill("dodge",400);
	set_skill("baguazhen",400);
	set_skill("parry",400);
	set_skill("sword",400);
	set_skill("xiaofeng-sword",400);
	set_skill("force",400);  
	set_skill("zhenyuan-force",400);
	set_skill("literate",400);
	set_skill("spells",400);
	set_skill("taiyi",400);
	map_skill("spells", "taiyi");
	map_skill("force", "zhenyuan-force");
	map_skill("unarmed", "wuxing-quan");
	map_skill("sword", "xiaofeng-sword");
	map_skill("dodge", "baguazhen");

	set("force_factor", 40);
	set("mana_factor", 40);
	setup();
	carry_object(0,"cloth",random(3))->wear();
	carry_object(0,"sword",random(3))->wield();
}

void donghai()
{
	if( fabao==0 )
	{
		fabao=1;
		message_vision("\n$N祭起手中仙笛，霞光一闪，长笛迎风化作一叶小舟，$N踏歌其上，潇洒而去。\n",this_object());
	}
	else
	{
		if( random(2) )
			message_vision("$N唱道：问谁，侠气如泓？看世间，欢笑悲痛。芳名千载何用，欢笑自在秋冬。我只求，逍遥无穷。\n",this_object());
		else	message_vision("$N唱道：吹奏天上曲，仙乐朦胧。\n",this_object());
	}
}