#include <ansi.h>
inherit SUPER_NPC;
inherit F_MASTER;

void create()
{
	set_name(MAG"青霞仙子"NOR, ({"qingxia xianzi", "qingxia", "xianzi","master"}));
       	set("long", "她是紫霞仙子的孪生姐姐,曾被佛祖把她和紫霞仙子捏在一棵灯芯里。後因紫霞仙子思凡
下界开山立派,故追至此处。\n");
	set("title", HIY"佛祖灯芯"NOR);
       	set("gender", "女性");
       	set("age", 20);
       	set("class","yaomo");
       	set("attitude", "friendly");
       	set_level(130);
       	set("force_factor", 125);
       	set("mana_factor",1300);
       	set_skill("literate",1300);
       	set_skill("unarmed", 1300);
       	set_skill("dodge", 1300);
       	set_skill("force", 1300);
       	set_skill("parry",1300);
       	set_skill("sword", 1300);
       	set_skill("spells",1300);
   	set_skill("pansi-dafa", 1300);
   	set_skill("lanhua-shou", 1300);
   	set_skill("jiuyin-xinjing",1300);
   	set_skill("qingxia-jian", 1300);
   	set_skill("yueying-wubu",1300);
   	map_skill("spells", "pansi-dafa");
   	map_skill("unarmed", "lanhua-shou");
   	map_skill("force", "jiuyin-xinjing");
   	map_skill("sword", "qingxia-jian");
   	map_skill("parry", "qingxia-jian");
   	map_skill("dodge", "yueying-wubu");
   	create_family("盘丝洞", 1, "红");
	set("env/test","HIB");
        setup();
        carry_object(0,"cloth",1)->wear();
        carry_object(0,"shoes",1)->wear();
        carry_object(0,"neck",1)->wear();
        carry_object(0,"ring",1)->wear();
        carry_object(0,"kui",1)->wear();
        carry_object(0,"pifeng",1)->wear();
        carry_object(0,"sword",1)->wield();
}

void attempt_apprentice(object ob)
{
	if( ob->query_level()<90 )
	{
		command("say " + RANK_D->query_respect(ob) +"的道行不够高深，有些绝学秘法恐怕难以领悟。\n");
   		return;
   	}
        command("pat "+ob->query("id"));
        command("say 好，希望" + RANK_D->query_respect(ob) +
"多加努力，把我们盘丝洞发扬光大。\n");
       	command("recruit " + ob->query("id") );
   	return;
}

int recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob) )
		ob->set("class", "yaomo");
}

int accept_fight(object me)
{
	return 0;
}

void die()
{
	if( environment() )
		message("vision","\n\n火光一闪，"+this_object()->name()+"化作一道金光遁去。。。。\n\n",environment());	
        destruct(this_object());
}