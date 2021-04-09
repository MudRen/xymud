#include <ansi.h>
inherit NPC;

int fabao = 0;

void create()
{
	set_name("铁拐李", ({"tieguai li", "tieguai", "li"}));
      	set_level(40);
	set("title", HIC"八仙之凝阳子"NOR);
	set("gender", "男性" );
	set("age", 42);
	set("per", 22);
	set("long", "他脚登一双烂草鞋，身着一件早就没了本来面目的脏袍，嘴里哼着走调小曲，一副悠闲神态。\n");
	set("class", "xian");
	set("attitude", "peaceful");
	create_family("五庄观", 3, "弟子");
	set_skill("unarmed",400);
	set_skill("wuxing-quan",400);
	set_skill("dodge",400);
	set_skill("baguazhen",400);
	set_skill("parry",400);
	set_skill("staff",400);
	set_skill("fumo-zhang",400);
	set_skill("force",400);   
	set_skill("zhenyuan-force",400);
	set_skill("literate",400);
	set_skill("spells",400);
	set_skill("taiyi",400);
	map_skill("spells", "taiyi");
	map_skill("force", "zhenyuan-force");
	map_skill("unarmed", "wuxing-quan");
	map_skill("staff", "fumo-zhang");
	map_skill("dodge", "baguazhen");

	set("force_factor", 40);
	set("mana_factor", 40);
	setup();
	carry_object("/d/obj/cloth/pobuyi")->wear();
	carry_object("/d/obj/cloth/lancaoxie")->wear();
	carry_object(0,"staff",random(3))->wield();
}

void donghai()
{
	if( fabao==0 )
	{
		fabao=1;
		message_vision("\n$N祭起手中酒葫芦，霞光一闪，葫芦迎风变得巨大，飘在海面上沉沉浮浮，$N跨坐其上，好不逍遥。\n",this_object());
	}
	else
	{
		if( random(2) )
			message_vision("$N唱道：问谁，侠气如泓？看世间，欢笑悲痛。芳名千载何用，欢笑自在秋冬。我只求，逍遥无穷。\n",this_object());
		else	message_vision("$N唱道：望酒影醉看人间，尘世太多苦痛。\n",this_object());
	}
}