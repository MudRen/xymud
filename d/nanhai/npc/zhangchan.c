//Cracked by Roath
// zhangchan.c 掌禅僧
// By Dream Dec. 20, 1996
#include <ansi.h>
inherit SUPER_NPC;

string ask_staff(object who);
string ask_hammer(object who);

void create()
{
	object ob;
	set_name("掌禅僧", ({ "zhangchan seng", "seng" }));
      	set_level(60);
      	create_family("南海普陀山", 4, "弟子");
      	set("title","普陀山执事");
	set("gender", "男性");
	set("age", 35);
	set("attitude", "peaceful");
	set("class", "bonze");
	set("force_factor", 20);
	set("mana_factor", 20);

	set_skill("literate",600);
	set_skill("spells",600);
	set_skill("buddhism",600);
	set_skill("unarmed",600);
	set_skill("jienan-zhi",600);
	set_skill("dodge",600);
	set_skill("lotusmove",600);
	set_skill("parry",600);
	set_skill("force",600);
	set_skill("lotusforce",600);
	set_skill("staff",600);
	set_skill("lunhui-zhang",600);
	set_skill("blade",600);
	set_skill("cibeidao",600);
	map_skill("blade","cibeidao");
	map_skill("spells", "buddhism");
	map_skill("unarmed", "jienan-zhi");
	map_skill("dodge", "lotusmove");
	map_skill("force", "lotusforce");
	map_skill("parry", "lunhui-zhang");
	map_skill("staff", "lunhui-zhang");
	set_skill("bubu-shenglian",600);
	
	set("inquiry", ([
		"佛杖": (: ask_staff :),
		"大力降魔杵" : (: ask_hammer :),
	]) );
        set("env/test","HIB");
	set_temp("weapon_level",60);
	set_temp("armor_level",60);
	setup();
	carry_object(0,"staff",1)->wield();
	carry_object("/d/nanhai/obj/sengpao")->wear();
	carry_object(0,"neck",1)->wear();
	carry_object(0,"ring",1)->wear();
	carry_object(0,"shoes",1)->wear();
	carry_object(0,"pifeng",1)->wear();
	carry_object(0,"waist",1)->wear();
	carry_object(0,"wrists",1)->wear();
	powerup(0,1);
}

string ask_staff(object who)
{
	object staff,ob;
	who = this_player();
	if(who->query("family/family_name") != "南海普陀山") 
		return RANK_D->query_respect(who) +"与本门毫无渊源，为什么问起这个？\n";
	if( time()<query("give_staff")+300 )
		return "你来的不巧，兵器刚刚给人了。";
	if( who->query_level()>=30 )
		set_temp("weapon_level",30);
	else	set_temp("weapon_level",who->query_level()+1);
	staff = carry_object(0,"staff",0);
	if( staff )
	{
		command("give "+geteuid(staff)+" to "+geteuid(who));
		set("give_staff",time());
		return "你先用着。";
	}
	return "暂时没兵器发了。";
}

string ask_hammer(object me)
{
	me = this_player();
	if( me->query("family/family_name") != "南海普陀山" )
		return 0;
	if( me->query("bonze/class")!="bonze" )
		return "阿弥陀佛，此乃佛家忿怒身秘法。";	
	if( me->is_knowing("putuo_bighammer") )
		return "阿弥陀佛，你是来骚扰老僧么？";
	if( time()<me->query("family/last_hammer")+900 )
		return "阿弥陀佛，你刚刚来过，还是先去磨练磨练。";	
	message_vision(CYN"$N"CYN"说道：降魔杵乃坚固锋利之智，可断除烦恼，除妖魔，可断鬼神、非人、天魔、恶咒之迫害，并可降魔息灾消除厄难。"NOR"\n",this_object());
	return "你可愿意接受磨炼？(agree)";
}

void init()
{
	add_action("do_agree","agree");
	add_action("do_agree","ok");
}

int do_agree()
{
	object room,me = this_player();
	if( me->query("family/family_name") != "南海普陀山" )
		return 0;
	if( me->query("bonze/class")!="bonze" )
		return 0;
	if( me->is_knowing("putuo_bighammer") )
		return 0;
	if( time()<me->query("family/last_hammer")+900 )
		return 0;
	if( me->is_busy() )
		return 0;
	me->set("family/last_hammer",time());	
	me->start_busy(3);
	write(CYN"你说道：弟子愿意。"NOR"\n");
	EMOTE_D->do_emote(this_object(), "nod",geteuid(me),CYN,0,0,0);
	write(CYN+name()+CYN"说道：老衲这就新开一静室，你且在内潜心修炼，能否悟到，便看你的造化。"NOR"\n");
	room = me->query_temp("bighammer_room");
	if( !room || !objectp(room) )
	{
		room = clone_object("/quest/family/putuo/bighammer");
		me->set_temp("bighammer_room",room);
	}
	room->set("owner_id",me->query("id"));
	room->set("start_time",time());
	message_vision(HIY"$N"HIY"领路将$n"HIY"引至一旁的静室之中。\n\n"NOR,this_object(),me);
	me->move(room);
	return 1;
}

void attempt_apprentice(object ob)
{
	if( ob->query_level()>65 )
	{
		EMOTE_D->do_emote(this_object(), "pa",geteuid(ob),CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：" + RANK_D->query_respect(ob) +"是我的前辈，还是进去找两位吧。\n"NOR);
		return;
	}
	if( ob->query("class") && ob->query("class")!="bonze"
	 && !ob->query("family/putuo_class_succ") )
	{
		EMOTE_D->do_emote(this_object(), "?",geteuid(ob),CYN,0,0,0);
		tell_object(ob,CYN+name()+CYN"说道：阿弥陀佛，施主是啥来头啊？带艺拜师，还是去找惠岸长老吧。\n"NOR);
		return;
	}
	if( (string)ob->query("bonze/class")!="bonze" )
	{
		tell_object(ob,CYN+name()+CYN"说道：阿弥陀佛，施主，我普陀暂不招俗家弟子，你还是寻其他宝刹试试。\n"NOR);
		tell_object(ob,CYN+name()+CYN"说道：如诚心观拜我佛，还是找门下剃度僧帮你去发。\n"NOR);
		return;
	}
	ob->delete("family/putuo_class_guai");
	ob->delete("family/putuo_class_succ");		
	EMOTE_D->do_emote(this_object(), "great",geteuid(ob),CYN,0,0,0);
	tell_object(ob,CYN+name()+CYN"说道：好，希望" + RANK_D->query_respect(ob) +"多加努力，把我们佛法发扬光大。\n"NOR);
        command("recruit " + geteuid(ob) );
        CHANNEL_D->do_channel(this_object(),"chat","南海普陀山又多了一个弟子  "+ob->name(1)+HIW"\n                                 佛家的势力加强了。\n"NOR);
        return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
		ob->set("class", "bonze");
}