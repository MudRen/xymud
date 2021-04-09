#include <ansi.h>
inherit NPC;
#include "baxian.h"

int fabao = 0;

void create()
{
	set_name("张果老", ({"zhang guolao", "zhang", "guolao"}));
	set_level(40);
	set("title",HIC"八仙之通玄先生"NOR);
	set("gender", "男性" );
	set("age", 50);
	set("long", "一位笑嘻嘻的滑稽老头。\n");
	set("class", "xian");
	set("attitude", "peaceful");
	create_family("五庄观", 3, "弟子");
	set_skill("unarmed", 400);
	set_skill("wuxing-quan", 400);
	set_skill("dodge", 400);
	set_skill("baguazhen", 400);
	set_skill("parry", 400);
	set_skill("hammer",400);
	set_skill("kaishan-chui", 400);
	set_skill("force", 400);   
	set_skill("zhenyuan-force", 400);
	set_skill("literate",400);
	set_skill("spells", 400);
	set_skill("taiyi", 400);
	map_skill("spells", "taiyi");
	map_skill("force", "zhenyuan-force");
	map_skill("unarmed", "wuxing-quan");
	map_skill("hammer", "kaishan-chui");
	map_skill("dodge", "baguazhen");
	set("force_factor", 40);
	set("mana_factor", 40);
	set("env/test","HIB");
	setup();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object("/d/obj/weapon/hammer/jiuhulu")->wield();
	powerup(0,1);
}

void init()
{
	object lv;
	::init();
	if( !userp(this_player()) )
		return;
	if( !present("xiao maolu",environment()) )
	{
		lv = new(__DIR__"xiaomaolu.c");
        	lv->move( environment() );
        	message_vision("\n$N拿出一张纸驴，口中念念有词”老驴老驴，还不速速归来？！“，火光一闪，纸驴化作了一头白鼻小毛驴。\n",this_object());
		command("mount maolu");
	}	
}

void donghai()
{
	if( fabao==0 )
	{
		fabao=1;
		message_vision("\n$N一拍坐下小毛驴，但见那黑头白鼻的小驴足下顿生祥云，撒开了丫子在海面随波嬉戏。\n",this_object());
	}
	else
	{
		if( random(2) )
			message_vision("$N唱道：问谁，侠气如泓？看世间，欢笑悲痛。芳名千载何用，欢笑自在秋冬。我只求，逍遥无穷。\n",this_object());
		else	message_vision("$N唱道：我倒行归隐山水中，不惹一丝凡庸。\n",this_object());
	}		
}
		
	