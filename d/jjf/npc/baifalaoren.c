// lao ren, 2001,lestat
#include <ansi.h>
inherit SUPER_NPC;
inherit F_MASTER;

string kick_back();
string begin_go();

void create()
{
	set_name(HIW"白发老人"NOR, ({ "lao ren", "lao", "laoren","ren", "baifa", "immortal", "master", "shifu" }));
	set_level(150);
	set("gender", "男性");
	set("age", 100);
	set("per", 130);
	set("long","
这是一位鹤发童颜的老人。他看起来似乎很老的样子，
但偏又是红光满面。看到你打量他，他对你和蔼地笑了
一笑。

");
	set("title", HIY"神仙"NOR);
	set("daoxing", 2000000);
	
	set_skill("literate", 1500);
	set_skill("unarmed", 1500);
	set_skill("changquan", 1500);
	set_skill("force", 1500);
	set_skill("lengquan-force", 1500);
	set_skill("axe", 1500);
	set_skill("dodge", 1500);
	set_skill("parry", 1500);
	set_skill("sanban-axe", 1500);
	set_skill("bawang-qiang", 1500);
	set_skill("spells", 1500);
	set_skill("baguazhou", 1500);
	set_skill("mace", 1500);
	set_skill("wusi-mace", 1500);
	set_skill("jinglei-mace", 1500);
	set_skill("spear", 1500);
	set_skill("yanxing-steps", 1500);
	map_skill("force", "lengquan-force");
	map_skill("spells", "baguazhou");
	map_skill("axe", "sanban-axe");
	map_skill("parry", "sanban-axe");
	map_skill("dodge", "yanxing-steps");
	map_skill("spear", "bawang-qiang");
	map_skill("unarmed", "changquan");
	set("force_factor", 140);
	set("mana_factor", 150);

	set("inquiry", ([
    		"name"    : "我是谁？我也不记得了。",
    		"here"    : "这是一场梦。",
    		"rumors"  : "消息？你不专心学艺，又来打听什么消息？",
    		"回去"    : (: kick_back :),
    		"return"  : (: kick_back :),
    		"灵台观礼"  : (: begin_go :),
	]) );
	create_family("将军府", 1, "蓝");
	set_temp("weapon_level",50+random(50));
	set_temp("armor_level",50+random(50));
	set("env/test","HIR");
	setup();
	if( random(2) )
		carry_object(0,"axe",1)->wield();
	else if( random(2) )
		carry_object(0,"spear",1)->wield();	
	else	carry_object(0,"mace",1)->wield();		
	carry_object(0,"cloth")->wear();
	carry_object(0,"shoes")->wear();
}

void go_back()
{
	remove_call_out("go_back");
	if( !environment() )
		return;
	if( base_name(environment())=="/d/jjf/sleep-2" )
		return;
	message_vision("\n"HIC"白发老人道：观礼事毕，老夫这就回去，老祖所议之事，容某考虑考虑。\n"NOR,this_object());
        message_vision(HIC"只见$N"HIC"化作一道金光冲天而去。\n"NOR,this_object());
	delete_temp("no_return");
	this_object()->move("/d/jjf/sleep-2");
	message_vision(HIC"\n$N"HIY"伸了伸懒腰道：呵呵，好一个南柯一梦。\n"NOR,this_object());			
}

string begin_go()
{
	int f;
	mapping job;
	object me,ob;
	me=this_player();
	ob=this_object();

	if( !me->query_temp("pendding/fc_visite")
    	 || me->is_knowing("puti_panlong") )
    		return 0;	
	if( base_name(environment())!="/d/jjf/sleep-2" )
    		return "此事待你我梦中相见时再说。";
        if( me->query_temp("pendding/fc_visite_jjf") )
        {	
		tell_object(me,CYN+name()+CYN"说道：" + RANK_D->query_respect(me) + "与老夫甚是有缘，既然亲自来请，那灵台观礼老夫这就同" + RANK_D->query_respect(me) + "去看看。\n"NOR);
		me->move("/d/lingtai/inside1");
		ob->move("/d/lingtai/inside1");
		ob->set_temp("no_return",1);
		message_vision("\n$N只觉得一道白光一闪，整个人便随白发老人一同来到了另外一个地方．\n"NOR,me);
		remove_call_out("go_back");
    		call_out("go_back",2700);
		return "我与老祖正好有事相商。";
	}
    	if( !me->query_temp("jjf/白发有缘") )	
        	return "老夫近日来不愿出游。";
        job = me->query_xy_job();
	if( !job || !mapp(job) )
		f = 1;
	else if( undefinedp(job["门派任务"]) )
		f = 1;
	else
	{
		job = job["门派任务"];
		if( undefinedp(job["succ"]) )
			f =1;
		else if( random(job["succ"]/10+1)<30 )
			f = 1;
		else	f = 2;		
	}		
        if( f==1 )
        	return "先去助你师门完成一些任务吧。";
	me->set_temp("pendding/fc_visite_jjf",1);
	me->delete_temp("jjf/白发有缘");
	me->add_temp("pendding/fc_visited",1);
	tell_object(me,HIY"【灵台观礼】你已成功邀请到"+chinese_number(me->query_temp("pendding/fc_visited"))+"位圣贤参加灵台观礼。\n"NOR);
	return "观礼之日还请" + RANK_D->query_respect(me) + "再来告知一声。";	
}

string kick_back()
{
	object me=this_player();

	message_vision(CYN"$n抬手朝$N的前额猛的一拍，喝声「去！」\n"NOR, me, this_object());
	message_vision(CYN"$N的身影渐渐淡去了．．．\n"NOR, me);
	me->move("/d/jjf/guest_bedroom");
	message_vision("$N突然惊醒坐起，原来是南柯一梦．．．\n", me);
	return "";
}

int accept_fight(object me)
{
	tell_object(me,CYN+name()+CYN"说道：唉，年轻人，火气就是大。别动粗别动粗！\n"NOR);
	return 0;
}

void attempt_apprentice(object me)
{
	int effstr=(int)(me->query("str")+me->query_skill("unarmed",1)/10-2);
	string myrespect=RANK_D->query_respect(me);

	if(me->query("family/master_id") != "cheng yaojin"
   	|| !me->query_temp("jjf/白发有缘"))
        {
        	tell_object(me,CYN+name()+CYN"说道：这。。。老夫素来不收无缘之人，"+myrespect+"还是回去吧。\n"NOR);
        	return;
        }
	if(random(effstr)<30 || me->query_level()<50 )
        {
        	tell_object(me,CYN+name()+CYN"说道："+myrespect+"的臂力低了些，恐怕难以学斧。\n"NOR);
        	return;
        }
        if( !me->query("family/family_name") || me->query("class")!="fighter" )
        {
		if( !me->query_temp("pendding/jjf_class") )
    		{
			tell_object(me,CYN+name()+CYN"说道：你乃带艺入师，先去问问管家机缘吧！\n"NOR);
      			return 0;
    		}        	
        }
        if( !me->query("shilian") && me->query("shilian")!="jjf" )
        {
        	EMOTE_D->do_emote(this_object(), "smile",geteuid(me),CYN,0,0,0);
           	tell_object(me,CYN+name()+CYN"说道：入我门下，还是先去找尉迟恭才行。\n"NOR);
           	return ;
        }
	EMOTE_D->do_emote(this_object(), "nod",geteuid(me),CYN,0,0,0);
	tell_object(me,CYN+name()+CYN"说道：看来"+myrespect+"与我有缘，老夫就收下你吧！\n"NOR);
	command("recruit " + me->query("id") );
	return;
}