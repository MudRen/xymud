#include <ansi.h>
inherit SUPER_NPC;
inherit F_MASTER;

void create()
{
	set_name("尉迟恭", ({"yuchi gong", "yuchi", "gong", "yuchigong", "jingde", "yuchi jingde", "yuchijingde", "master", "shifu"}));
  	set_level(59);
  	set ("long", @LONG
尉迟恭，字敬德，乃是唐太宗手下猛将。排为隋唐时第
十二条好汉。起初他是反王刘武州殿前元帅，后因兵败
降唐。他惯使一条点钢枪，且喜使一对雌雄竹节钢鞭。
LONG);
 	set("title", "开国元勋");
  	set("gender", "男性");
  	set("age", 43);
  	set("per", 15);
  	set_skill("spear",590);
  	set_skill("force",590);
  	set_skill("dodge",590);
  	set_skill("parry",590);
  	set_skill("mace",590);
  	set_skill("jinglei-mace",590);
  	set_skill("yanxing-steps",590);
  	set_skill("bawang-qiang",590);
  	set_skill("lengquan-force",590);
  	set_skill("unarmed",590);
  	set_skill("changquan",590);
	map_skill("mace", "jinglei-mace");
	map_skill("force", "lengquan-force");
	map_skill("unarmed", "changquan");
	map_skill("spear", "bawang-qiang");
	map_skill("parry", "jinglei-mace");
	map_skill("dodge", "yanxing-steps");
  	set("force_factor", 100);
   	create_family("将军府", 2, "蓝");
   	set_temp("weapon_level",10+random(10));
   	set_temp("armor_level",10+random(10));
  	setup();
 	carry_object(0,"spear",random(5));
  	carry_object(0,"mace",random(4))->wield();
	carry_object(0,"armor",1)->wear();
	carry_object(0,"kui",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"ring",1)->wear();
	carry_object(0,"cloth",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"wrists",1)->wear();
	carry_object(0,"waist",1)->wear();
	carry_object(0,"hand",1)->wear();
  	powerup(0,1);
}
 
int accept_fight(object me)
{
	tell_object(me,CYN+name()+CYN"说道：老夫手重，若是伤人反而不美了。\n"NOR);
  	return 0;
}

void attempt_apprentice(object me)
{
	string myname=RANK_D->query_rude(me);
  	int kar=me->query_kar();
  	int effstr=(int)(me->query("str")+me->query_skill("unarmed",1)/10-2);

	if( me->query("class")=="yaomo" || me->query("class")=="ghost" )
        {
		EMOTE_D->do_emote(this_object(), "pei",geteuid(me),CYN,0,0,0);
           	tell_object(me,CYN+name()+CYN"说道：妖魔鬼怪滚一边去！\n"NOR);
           	return;
        }
        if( me->query("family/family_name")!="将军府" )
        {
		tell_object(me,CYN+name()+CYN"说道：老夫不收外门弟子。\n");
      		return;
        }
        if( me->is_knowing("jjf_breakxing") || me->query("shilian")=="jjf" )
        {
      		EMOTE_D->do_emote(this_object(), "nod",0,CYN,0,0,0);
      		tell_object(me,CYN+name()+CYN"说道："+myname+"果然有两下子，老夫就收下你吧！\n"NOR);
      		command ("recruit " + me->query("id") );
      		return;
        }
  	if ((random(effstr)< 25) || random((int)me->query_con())<20)
    	{
      		tell_object(me,CYN+name()+CYN"说道：这"+myname+"手无缚鸡之力，不配作我徒弟！\n"NOR);
		return;
	}
  	if ( random((int)me->query("cps")) < 20 && random((int)me->query_cor())<20 )
	{
      		tell_object(me,CYN+name()+CYN"说道：这"+myname+"胆子还不如只老鼠！\n"NOR);
      		return;
    	}
    	if( me->query_temp("pendding/jjf_break") )
    	{
		tell_object(me,CYN+name()+CYN"说道：要想拜我为师，倒也不难。只需将那醉星楼拆了就行！\n"NOR);
    		return;
    	}
    	tell_object(me,CYN+name()+CYN"说道：要想拜我为师，倒也不难。只需将那醉星楼拆了就行！\n"NOR);
  	me->set_temp("pendding/jjf_break", 1);
}

int recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob) )
		ob->set("class","fighter");
}