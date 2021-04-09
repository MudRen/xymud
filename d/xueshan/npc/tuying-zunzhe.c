// tuying-zunzhe.c...weiqi, 97.09.15.
#include <ansi.h>
inherit SUPER_NPC;

string expell_me(object me);

void create()
{
	set_name("秃鹰尊者", ({"tuying zunzhe", "tuying", "zunzhe"}));
	set_level(120);
	set("gender", "男性" );
	set("age", 53);
	set("long", "大鹏明王座下四护法尊者之一。额头高耸，一看就知道功力深厚。\n");
	set("class", "yaomo");
	set("attitude", "peaceful");
	create_family2("大雪山","鹰族",2, "明王护法");
	set_skill("unarmed",1200);
	set_skill("cuixin-zhang",1200);
	set_skill("dodge", 1200);
	set_skill("xiaoyaoyou", 1200);
	set_skill("parry",1200);
	set_skill("blade",1200);
	set_skill("bingpo-blade",1200);
	set_skill("force",1200);   
	set_skill("ningxie-force",1200);
	set_skill("literate", 1200);
	set_skill("spells",1200);
	set_skill("dengxian-dafa", 1200);
	set_skill("throwing",1200);
	
	map_skill("spells", "dengxian-dafa");
	map_skill("force", "ningxie-force");
	map_skill("unarmed", "cuixin-zhang");
	map_skill("blade", "bingpo-blade");
	map_skill("dodge", "xiaoyaoyou");
	map_skill("parry", "cuixin-zhang");
	
	set_skill("jiefeng",1000);
	
	set("force_factor", 50);
	set("mana_factor", 25);
        set("eff_dx", -120000);
        set("nkgain", 300);
	set("inquiry", ([
		"leave": (: expell_me :),
		"name": "嘿嘿！\n",
		"here": "多看少说！\n",
	]) );
	set("env/test","HIB");
	set_temp("weapon_level",60+random(50));
	set_temp("armor_level",60+random(50));
	setup();
	carry_object(0,"blade",random(10))->wield();
	carry_object(0,"cloth",random(10))->wear();
	carry_object(0,"armor",random(10))->wear();
	carry_object(0,"pifeng",random(10))->wear();
	carry_object(0,"shoes",random(10))->wear();
	carry_object(0,"kui",random(10))->wear();
	powerup(1,1);
}

string expell_me(object me)
{       
	me=this_player();
	if((string)me->query("family/family_name")=="大雪山") 
	{
		message_vision("秃鹰尊者面色一沉，道：现在正是本门危急之时...\n", me);
		me->set_temp("xs_betray", 1);
		message_vision("秃鹰尊者阴森森地盯着$N，接着道：你真的想逃(true)？\n", me);
		return ("嘿嘿！\n");
	}
	return ("问什么问！自己想去！\n");
}

void init()
{
	::init();
	add_action("do_true", "true");
}

int do_true(string arg)
{
	if((string)this_player()->query("family/family_name")!="大雪山")
		return 0;
	if(this_player()->query_temp("xs_betray")) 
	{
		if( FAMILY_D->leave_family(this_player(),this_object()) )
		{
			this_player()->delete_temp("xs_betray");
			message_vision("$N答道：弟子讲的真心话！\n\n", this_player());
			message_vision("秃鹰尊者叹了口气道：好！你从此便是本门的敌人了！\n", this_player());
			message_vision("秃鹰尊者一脚踢中$N的屁股，$N腾云驾雾般飞了出去...\n", this_player());
			this_player()->move("/d/xueshan/binggu");
			tell_room( environment(this_player()),"只听劈啪！一声，一个人从空中飞过来，死猪般地摔在地上。\n", ({this_player()}));
			return 1;
		}
	}	
	return 0;
}
