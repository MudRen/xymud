#include <ansi.h>
inherit SUPER_NPC;

int Die = 0;

void create()
{
        set_name(HIM"紫霞仙子"NOR, ({"zixia xianzi", "zixia", "xianzi","master"}));
        set("long", "她就是盘丝洞的开山祖师,传说她是佛祖的一棵灯芯。随佛祖修道悟
真,后来思凡下界占了花果山一处洞府,开山立派,传授门徒。\n");
        set("title", HIB"盘丝大仙"NOR);
        set("gender", "女性");
        set("age", 20);
        set("class","yaomo");
        set("attitude", "friendly");
        set("rank_info/respect", "小姑娘");
        set("force_factor", 100);
        set("mana_factor", 150);
        set_skill("literate", 180);
        set_skill("unarmed", 200);
        set_skill("dodge", 200);
        set_skill("zhuyan", 250);
        set_skill("force", 180);
        set_skill("parry", 180);
        set_skill("sword", 200);
        set_skill("spells", 170);
        set_skill("whip", 200);
        set_skill("pansi-dafa", 170);
        set_skill("lanhua-shou", 180);
        set_skill("jiuyin-xinjing", 180);
        set_skill("chixin-jian", 180);
        set_skill("qin", 180);
        set_skill("yueying-wubu", 180);
        set_skill("yinsuo-jinling", 200);
        map_skill("spells", "pansi-dafa");
        map_skill("unarmed", "lanhua-shou");
        map_skill("force", "jiuyin-xinjing");
        map_skill("sword", "chixin-jian");
        map_skill("parry", "yinsuo-jinling");
        map_skill("dodge", "yueying-wubu");
        map_skill("whip", "yinsuo-jinling");
        set("no_cast",1);
        set("no_perform",1);
        create_family("盘丝洞",2, "红");
   	add_temp("apply/max_kee",10000);
   	add_temp("apply/max_sen",10000);
        setup();
}

void dies()
{
        object qingxia,erlang,dog,me;

        qingxia = query("my_sister");
        erlang = query("my_killer");
	me = query("owner");
	
	if( environment() )
		message("vision",HIM"\n\n紫霞"NOR YEL"惨叫一声，就地瘫倒，现出了原形，却是一根枯草！\n"NOR,environment());
	if( qingxia )
	{
		if( environment() )
			message("vision",HIR"\n\n火光一闪"HIG+qingxia->name()+NOR YEL"也现出了原形，却是一根枯草！\n"NOR,environment());	
		destruct(qingxia);
	}
	if( erlang )
	{
		erlang->command("chat* pei");
		if( me )
			CHANNEL_D->do_channel(erlang,"chat","可恼！"+me->name()+RANK_D->query_rude(me)+"竟敢勾结紫青二妖，瞒天过海，欺骗本尊！");
		else	CHANNEL_D->do_channel(erlang,"chat","可恼！紫青二妖竟敢瞒天过海，欺骗本尊！");	
		if( environment() )
			message("vision", "\n\n\n二郎神怒道：尔等莫要猖狂，待我到如来佛祖那里告状去！\n\n二郎神搭上白云，往西天灵山飞去。。。\n\n",environment());
		dog = erlang->query_temp("invoker");
		if( dog )
		{    
			if( environment() )			
     				message("vision", "啸天犬也跟着二郎神往西逃去。\n\n", environment());
			destruct(dog);
		}
		destruct(erlang);
	}
	if( me )
		me->set("family/guanli_pansi_fail",time());
	if( base_name(environment())=="/quest/family/pansi/hgs" )
	{
		if( !environment()->query("exits") )
			environment()->set("exits/down","/d/pansi/hubian");
	}
	destruct(this_object());
}

void die()
{
	object me = this_object();
	if( Die>0 )
		return;
	QUEST_D->addEffKee(me);
	QUEST_D->addKee(me);
	QUEST_D->addSen(me);
	QUEST_D->addEffSen(me);
	if( query("kee")<1 || query("sen")<1 
	 || query("eff_kee")<1 || query("eff_sen")<1 )
	{
		Die = 1;
		dies();
		return;
	}	 
}

void unconcious()
{
	die();
}